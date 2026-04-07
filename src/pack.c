/* pack.c — C90, NO CRT, NO HEADERS, loads pure-language script files and assembles hybrid launcher */

typedef unsigned long       u32;
typedef unsigned long long  u64;
typedef unsigned char       u8;

/* ─────────────────────────────────────────────────────────────── */
/* External ASM helpers                                            */
/* ─────────────────────────────────────────────────────────────── */
extern void* mem_alloc(u64 size);
extern void  mem_free(void* p);
extern long  print_text(const char* s);
extern void  copy_string(char* d, const char* s);
extern void  mem_set(void* dst, int v, unsigned int n);

/* ─────────────────────────────────────────────────────────────── */
/* Win32 API imports                                               */
/* ─────────────────────────────────────────────────────────────── */

typedef void* HANDLE;
typedef long  BOOL;
typedef u32   DWORD;

extern HANDLE __stdcall CreateFileA(
    const char* lpFileName,
    u32 dwDesiredAccess,
    u32 dwShareMode,
    void* lpSecurityAttributes,
    u32 dwCreationDisposition,
    u32 dwFlagsAndAttributes,
    HANDLE hTemplateFile
);

extern BOOL __stdcall ReadFile(
    HANDLE hFile,
    void* lpBuffer,
    u32 nBytesToRead,
    u32* lpBytesRead,
    void* lpOverlapped
);

extern BOOL __stdcall WriteFile(
    HANDLE hFile,
    const void* lpBuffer,
    u32 nBytesToWrite,
    u32* lpBytesWritten,
    void* lpOverlapped
);

extern BOOL __stdcall CloseHandle(HANDLE hFile);

extern BOOL __stdcall GetFileSizeEx(
    HANDLE hFile,
    void* lpLargeIntegerOut
);

/* ─────────────────────────────────────────────────────────────── */

#define MAGIC 0x54AF3B2CUL

#define GENERIC_READ    0x80000000UL
#define GENERIC_WRITE   0x40000000UL
#define FILE_SHARE_READ 1
#define OPEN_EXISTING   3
#define CREATE_ALWAYS   2
#define FILE_ATTRIBUTE_NORMAL 0x80

/* ─────────────────────────────────────────────────────────────── */

static u32 my_strlen(const char* s) {
    u32 n = 0;
    while (s[n]) n++;
    return n;
}

static void* my_memcpy(void* dst, const void* src, u32 n) {
    u8* d = (u8*)dst;
    const u8* s = (const u8*)src;
    while (n--) *d++ = *s++;
    return dst;
}

static char* my_strstr(char* h, const char* n) {
    u32 i, j;
    u32 hl = my_strlen(h);
    u32 nl = my_strlen(n);
    if (nl > hl) return 0;

    for (i = 0; i <= hl - nl; i++) {
        for (j = 0; j < nl; j++) {
            if (h[i+j] != n[j]) goto next;
        }
        return h + i;
    next:;
    }
    return 0;
}

static void u64_to_dec_left(char* out, u64 v) {
    char tmp[32];
    u32 i = 0, j, len;

    if (v == 0) {
        tmp[i++] = '0';
    } else {
        while (v && i < 31) {
            tmp[i++] = (char)('0' + (v % 10));
            v /= 10;
        }
    }

    len = i;
    for (j = 0; j < len; j++)
        out[j] = tmp[len - 1 - j];

    while (j < 11) out[j++] = ' ';
}

/* ─────────────────────────────────────────────────────────────── */
/* File helpers                                                    */
/* ─────────────────────────────────────────────────────────────── */

static HANDLE file_open_read(const char* path) {
    return CreateFileA(path, GENERIC_READ, FILE_SHARE_READ,
                       0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
}

static HANDLE file_open_write(const char* path) {
    return CreateFileA(path, GENERIC_WRITE, 0,
                       0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
}

static u64 file_size(HANDLE h) {
    u64 out = 0;
    GetFileSizeEx(h, &out);
    return out;
}

static u32 file_read(HANDLE h, void* buf, u32 sz) {
    u32 got = 0;
    ReadFile(h, buf, sz, &got, 0);
    return got;
}

static u32 file_write(HANDLE h, const void* buf, u32 sz) {
    u32 wrote = 0;
    WriteFile(h, buf, sz, &wrote, 0);
    return wrote;
}

/* ─────────────────────────────────────────────────────────────── */
/* Load entire file into memory                                    */
/* ─────────────────────────────────────────────────────────────── */

static char* load_text_file(const char* path, u32* out_len) {
    HANDLE h = file_open_read(path);
    if (!h) return 0;

    u64 sz = file_size(h);
    char* buf = (char*)mem_alloc(sz + 1);

    file_read(h, buf, (u32)sz);
    buf[sz] = 0;

    CloseHandle(h);
    *out_len = (u32)sz;
    return buf;
}

/* ─────────────────────────────────────────────────────────────── */
/* Base64                                                          */
/* ─────────────────────────────────────────────────────────────── */

static const char b64tab[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static void base64_encode(HANDLE out, const u8* in, u32 len) {
    u32 i, col = 0;
    char line[4];
    u8 a, b, c;

    for (i = 0; i < len; i += 3) {
        a = in[i];
        b = (i+1 < len) ? in[i+1] : 0;
        c = (i+2 < len) ? in[i+2] : 0;

        line[0] = b64tab[a >> 2];
        line[1] = b64tab[((a & 3) << 4) | (b >> 4)];
        line[2] = (i+1 < len) ? b64tab[((b & 15) << 2) | (c >> 6)] : '=';
        line[3] = (i+2 < len) ? b64tab[c & 63] : '=';

        file_write(out, line, 4);
        col += 4;

        if (col >= 76) {
            file_write(out, "\n", 1);
            col = 0;
        }
    }
    if (col > 0) file_write(out, "\n", 1);
}

static u32 b64_encoded_size(u32 raw) {
    u32 chars = ((raw + 2) / 3) * 4;
    u32 newlines = (chars + 75) / 76;
    return chars + newlines;
}

/* ─────────────────────────────────────────────────────────────── */

struct fat_header {
    u64 magic;
    u64 linux_offset;
    u64 win_offset;
    u64 win_size;
    u64 linux_size;
};

/* ─────────────────────────────────────────────────────────────── */

int main(int argc, char** argv) {
    HANDLE hlin, hwin, hout;
    u64 lin_sz, win_sz;
    u8* lin_buf;
    u8* win_buf;

    /* pure-language script parts */
    char *sh, *cmd_a, *ps, *cmd_b;
    u32 sh_len, cmd_a_len, ps_len, cmd_b_len;

    /* assembled hybrid parts */
    char *top_a, *top_b;
    u32 top_a_len, top_b_len;

    u32 b64_sz;
    u64 linux_offset;

    struct fat_header hdr;

    if (argc != 4) {
        print_text("Usage: pack <linux_bin> <win_bin> <output.bat>\n");
        return 1;
    }

    /* load pure-language script files */
    sh     = load_text_file("script_sh.txt",     &sh_len);
    cmd_a  = load_text_file("script_cmd_a.txt",  &cmd_a_len);
    ps     = load_text_file("script_ps.txt",     &ps_len);
    cmd_b  = load_text_file("script_cmd_b.txt",  &cmd_b_len);

    if (!sh || !cmd_a || !ps || !cmd_b) {
        print_text("Error loading script files\n");
        return 1;
    }

    /* ─────────────────────────────────────────────────────────── */
    /* Build script_top_a (Linux shell + CMD)                      */
    /* ─────────────────────────────────────────────────────────── */

    {
        const char* hdr_line = ":; # 2>NUL & goto :BATCH_START\n";
        u32 hdr_len = my_strlen(hdr_line);

        const char* prefix = ":; ";
        u32 prefix_len = 3;

        /* worst-case size */
        top_a_len = hdr_len + (sh_len * (prefix_len + 1)) + cmd_a_len + 32;
        top_a = (char*)mem_alloc(top_a_len + 1);

        u32 pos = 0;

        /* header */
        my_memcpy(top_a + pos, hdr_line, hdr_len);
        pos += hdr_len;

        /* prefix each line of script_sh.txt */
        {
            u32 i = 0;
            while (i < sh_len) {
                my_memcpy(top_a + pos, prefix, prefix_len);
                pos += prefix_len;

                while (i < sh_len && sh[i] != '\n')
                    top_a[pos++] = sh[i++];

                if (i < sh_len && sh[i] == '\n') {
                    top_a[pos++] = '\n';
                    i++;
                }
            }
        }

        /* CMD start label */
        {
            const char* lbl = ":BATCH_START\n";
            u32 lbl_len = my_strlen(lbl);
            my_memcpy(top_a + pos, lbl, lbl_len);
            pos += lbl_len;
        }

        /* CMD part A */
        my_memcpy(top_a + pos, cmd_a, cmd_a_len);
        pos += cmd_a_len;

        top_a[pos] = 0;
        top_a_len = pos;
    }

    /* ─────────────────────────────────────────────────────────── */
    /* Build script_top_b (PowerShell + CMD)                       */
    /* ─────────────────────────────────────────────────────────── */

    {
        const char* ps_cmd = "powershell -NoProfile -Command \"";
        const char* end_quote = "\"\n";

        u32 ps_cmd_len = my_strlen(ps_cmd);
        u32 end_quote_len = my_strlen(end_quote);

        top_b_len = ps_cmd_len + ps_len + end_quote_len + cmd_b_len;
        top_b = (char*)mem_alloc(top_b_len + 1);

        u32 pos = 0;

        my_memcpy(top_b + pos, ps_cmd, ps_cmd_len);
        pos += ps_cmd_len;

        my_memcpy(top_b + pos, ps, ps_len);
        pos += ps_len;

        my_memcpy(top_b + pos, end_quote, end_quote_len);
        pos += end_quote_len;

        my_memcpy(top_b + pos, cmd_b, cmd_b_len);
        pos += cmd_b_len;

        top_b[pos] = 0;
        top_b_len = pos;
    }

    /* ─────────────────────────────────────────────────────────── */
    /* Load binaries                                                */
    /* ─────────────────────────────────────────────────────────── */

    hlin = file_open_read(argv[1]);
    hwin = file_open_read(argv[2]);
    if (!hlin || !hwin) {
        print_text("Error opening input binaries\n");
        return 1;
    }

    lin_sz = file_size(hlin);
    win_sz = file_size(hwin);

    lin_buf = (u8*)mem_alloc(lin_sz);
    win_buf = (u8*)mem_alloc(win_sz);

    file_read(hlin, lin_buf, (u32)lin_sz);
    file_read(hwin, win_buf, (u32)win_sz);

    CloseHandle(hlin);
    CloseHandle(hwin);

    /* compute offsets */
    b64_sz = b64_encoded_size((u32)win_sz);
    linux_offset = (u64)(top_a_len + top_b_len + b64_sz +  /* no mid file */
                         9 + 20); /* ":END_B64\n" + ": BINARY_DATA_BELOW\n" */

    /* patch placeholders in top_a */
    {
        char* p;
        char tmp[11];

        p = my_strstr(top_a, "LINUX_OFF__");
        if (!p) { print_text("Missing LINUX_OFF__\n"); return 1; }
        u64_to_dec_left(tmp, linux_offset);
        my_memcpy(p, tmp, 11);

        p = my_strstr(top_a, "LINUX_SZ___");
        if (!p) { print_text("Missing LINUX_SZ___\n"); return 1; }
        u64_to_dec_left(tmp, lin_sz);
        my_memcpy(p, tmp, 11);
    }

    /* open output */
    hout = file_open_write(argv[3]);
    if (!hout) {
        print_text("Error opening output file\n");
        return 1;
    }

    /* write script */
    file_write(hout, top_a, top_a_len);
    file_write(hout, top_b, top_b_len);

    /* write base64 win binary */
    base64_encode(hout, win_buf, (u32)win_sz);

    /* write END_B64 and binary marker */
    file_write(hout, ":END_B64\n", 9);
    file_write(hout, ": BINARY_DATA_BELOW\n", 20);

    /* write linux binary */
    file_write(hout, lin_buf, (u32)lin_sz);

    /* write header */
    hdr.magic        = MAGIC;
    hdr.linux_offset = linux_offset;
    hdr.win_offset   = 0;
    hdr.win_size     = win_sz;
    hdr.linux_size   = lin_sz;

    file_write(hout, &hdr, sizeof(hdr));

    CloseHandle(hout);

    print_text("Packed OK\n");
    return 0;
}
