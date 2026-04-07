#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAGIC 0x54AF3B2CUL

/*
 * Output layout:
 *   [script header]        sh runs this; cmd jumps to :BATCH_START
 *   [base64 win binary]    cmd decodes this via powershell; sh skips (after exec)
 *   ": END_B64\n"          sentinel
 *   [linux binary raw]     sh extracts via dd
 *   [fat header 40 bytes]
 *
 * No raw binary bytes appear before the script's "exit /b", so cmd's
 * file-buffer pre-scan never hits a 0x1A (Ctrl-Z / EOF marker).
 *
 * The base64 block is valid ASCII so cmd reads through it safely.
 * powershell decodes it with [Convert]::FromBase64String().
 *
 * Placeholders (11 chars each, patched in-place):
 *   LINUX_OFF__  offset of linux binary from file start
 *   LINUX_SZ___  size of linux binary
 */

/* Script up to (not including) the base64 blob */
/* Split into multiple strings to avoid C90 string length limit (509 chars) */
static const char script_top_a[] =
    ":; # 2>NUL & goto :BATCH_START\n"
    ":; set -e\n"
    ":; TMP=$(mktemp /tmp/run.XXXXXX)\n"
    ":; trap 'rm -f \"$TMP\"' EXIT\n"
    ":; dd if=\"$0\" bs=1 skip=LINUX_OFF__ count=LINUX_SZ___ 2>/dev/null > \"$TMP\"\n"
    ":; chmod +x \"$TMP\"\n"
    ":; exec \"$TMP\" \"$@\"\n"
    ":BATCH_START\n"
    "@echo off\n"
    "setlocal\n"
    "set TMP_OUT=%TEMP%\\run_%RANDOM%.exe\n";

static const char script_top_b[] =
    "powershell -NoProfile -Command \""
        "$lines=[System.IO.File]::ReadAllLines('%~f0');"
        "$b64='';"
        "$in=$false;"
        "foreach($l in $lines){"
            "if($l -eq ':BEGIN_B64'){$in=$true;continue};"
            "if($l -eq ':END_B64'){break};"
            "if($in){$b64+=$l}"
        "};"
        "$bytes=[Convert]::FromBase64String($b64);"
        "[System.IO.File]::WriteAllBytes($env:TMP_OUT,$bytes)"
    "\"\n"
    "\"%TMP_OUT%\" %*\n"
    "set EC=%ERRORLEVEL%\n"
    "del \"%TMP_OUT%\"\n"
    "exit /b %EC%\n"
    ":BEGIN_B64\n";

static const char script_mid[] =
    ":END_B64\n"
    ": BINARY_DATA_BELOW\n";

/* base64 encoding table */
static const char b64[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static void base64_encode(FILE *out, const unsigned char *in, size_t len) {
    size_t i;
    size_t col = 0;
    unsigned char a, b, c;
    for (i = 0; i < len; i += 3) {
        a = in[i];
        b = (i+1 < len) ? in[i+1] : 0;
        c = (i+2 < len) ? in[i+2] : 0;
        fputc(b64[a >> 2], out);
        fputc(b64[((a & 3) << 4) | (b >> 4)], out);
        fputc((i+1 < len) ? b64[((b & 15) << 2) | (c >> 6)] : '=', out);
        fputc((i+2 < len) ? b64[c & 63] : '=', out);
        col += 4;
        if (col >= 76) {
            fputc('\n', out);
            col = 0;
        }
    }
    if (col > 0) fputc('\n', out);
}

static unsigned char *read_file(const char *path, size_t *sz) {
    unsigned char *buf;
    FILE *f = fopen(path, "rb");
    if (!f) { perror(path); return NULL; }
    fseek(f, 0, SEEK_END);
    *sz = (size_t)ftell(f);
    fseek(f, 0, SEEK_SET);
    buf = malloc(*sz);
    if (!buf) { fclose(f); return NULL; }
    fread(buf, 1, *sz, f);
    fclose(f);
    return buf;
}

static void patch_placeholder(char *buf, const char *needle, uint64_t value) {
    char tmp[12];
    char *p = strstr(buf, needle);
    if (!p) {
        fprintf(stderr, "pack: placeholder '%s' not found\n", needle);
        exit(1);
    }
    snprintf(tmp, sizeof(tmp), "%-11lu", (unsigned long)value);
    memcpy(p, tmp, 11);
}

/* Calculate base64 encoded size (with newlines every 76 chars) */
static size_t b64_encoded_size(size_t raw) {
    size_t chars = ((raw + 2) / 3) * 4;
    size_t newlines = (chars + 75) / 76;
    return chars + newlines;
}

struct fat_header {
    uint64_t magic;
    uint64_t linux_offset;
    uint64_t win_offset;
    uint64_t win_size;
    uint64_t linux_size;
};

int main(int argc, char **argv) {
    size_t lin_sz, win_sz;
    size_t top_a_len, top_b_len, mid_len, b64_sz;
    uint64_t linux_offset, linux_size;
    unsigned char *lin_bin;
    unsigned char *win_bin;
    char *top_a;
    char *top_b;
    FILE *out;
    struct fat_header hdr;

    if (argc != 4) {
        fprintf(stderr,
            "Usage: pack <linux_bin> <win_bin> <output.bat>\n"
            "\n"
            "  On Windows: output.bat\n"
            "  On Linux:   sh output.bat  (or chmod+x)\n");
        return 1;
    }

    lin_bin = read_file(argv[1], &lin_sz);
    win_bin = read_file(argv[2], &win_sz);
    if (!lin_bin || !win_bin) return 1;

    top_a_len = sizeof(script_top_a) - 1;
    top_b_len = sizeof(script_top_b) - 1;
    mid_len   = sizeof(script_mid) - 1;
    b64_sz    = b64_encoded_size(win_sz);

    linux_offset = (uint64_t)(top_a_len + top_b_len + b64_sz + mid_len);
    linux_size   = (uint64_t)lin_sz;

    top_a = malloc(top_a_len + 1);
    top_b = malloc(top_b_len + 1);
    memcpy(top_a, script_top_a, top_a_len + 1);
    memcpy(top_b, script_top_b, top_b_len + 1);
    patch_placeholder(top_a, "LINUX_OFF__", linux_offset);
    patch_placeholder(top_a, "LINUX_SZ___", linux_size);

    out = fopen(argv[3], "wb");
    if (!out) { perror(argv[3]); return 1; }

    fwrite(top_a, 1, top_a_len, out);
    fwrite(top_b, 1, top_b_len, out);
    base64_encode(out, win_bin, win_sz);
    fwrite(script_mid, 1, mid_len, out);
    fwrite(lin_bin, 1, lin_sz, out);

    hdr.magic        = MAGIC;
    hdr.linux_offset = linux_offset;
    hdr.win_offset   = 0;
    hdr.win_size     = win_sz;
    hdr.linux_size   = linux_size;
    fwrite(&hdr, 1, sizeof(hdr), out);
    fclose(out);

    free(lin_bin); free(win_bin); free(top_a); free(top_b);

    printf("Packed: %s  (b64_win=%lu  linux=%lu  linux_offset=%lu)\n",
           argv[3], (unsigned long)b64_sz, (unsigned long)lin_sz,
           (unsigned long)linux_offset);
    return 0;
}
