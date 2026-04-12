#include "fileswindows.c"

/* ─────────────────────────────────────────────────────────────── */

struct fat_header {
    unsigned long long magic;
    unsigned long long linux_offset;
    unsigned long long win_offset;
    unsigned long long win_size;
    unsigned long long linux_size;
};

/* ─────────────────────────────────────────────────────────────── */

int main(int argc,char** argv) {
    void *hlin,*hwin,*hout;
    unsigned long long lin_sz,win_sz;
    unsigned char* lin_buf;
    unsigned char* win_buf;

    char *sh,*cmd_a,*cmd_c,*cmd_b;
    unsigned long sh_len,cmd_a_len,cmd_c_len,cmd_b_len;

    char *top_a,*top_b;
    unsigned long top_a_len,top_b_len;

    unsigned long b64_sz;
    unsigned long long linux_offset;
    unsigned long long b64_offset;

    struct fat_header hdr;

    if (argc!=4) {
        print_text("Usage: pack <linux_bin> <win_bin> <output.bat>\n");
        return 1;
    }

    /* load pure-language script files */
    sh=load_text_file(".\\compilehelpers\\header1.sh",&sh_len);
    cmd_a=load_text_file(".\\compilehelpers\\header2.cmd",&cmd_a_len);
    cmd_c=load_text_file(".\\compilehelpers\\header3.cmd",&cmd_c_len);
    cmd_b=load_text_file(".\\compilehelpers\\header4.cmd",&cmd_b_len);

    if (!sh||!cmd_a||!cmd_c||!cmd_b) {
        print_text("Error loading script files\n");
        return 1;
    }

    /* ─────────────────────────────────────────────────────────── */
    /* Build script_top_a                                          */
    /* ─────────────────────────────────────────────────────────── */

    {
        const char* hdr_line=":; # 2>NUL & goto :BATCH_START\n";
        unsigned long hdr_len=my_strlen(hdr_line);

        const char* prefix=":; ";
        unsigned long prefix_len=3;

        top_a_len=hdr_len+(sh_len*(prefix_len+1))+cmd_a_len+32;
        top_a=(char*)mem_alloc(top_a_len+1);

        unsigned long pos=0;

        my_memcpy(top_a+pos,hdr_line,hdr_len);
        pos+=hdr_len;

        {
            unsigned long i=0;
            while (i<sh_len) {
                my_memcpy(top_a+pos,prefix,prefix_len);
                pos+=prefix_len;

                while (i<sh_len&&sh[i]!='\n') {
                    if (sh[i]!='\r') {
                        top_a[pos++]=sh[i];
                    }
                    i++;
                }

                if (i<sh_len&&sh[i]=='\n') {
                    top_a[pos++]='\n';
                    i++;
                }
            }
        }

        {
            const char* lbl=":BATCH_START\n";
            unsigned long lbl_len=my_strlen(lbl);
            my_memcpy(top_a+pos,lbl,lbl_len);
            pos+=lbl_len;
        }

        my_memcpy(top_a+pos,cmd_a,cmd_a_len);
        pos+=cmd_a_len;

        top_a[pos]=0;
        top_a_len=pos;
    }

    /* ─────────────────────────────────────────────────────────── */
    /* Build script_top_b                                          */
    /* ─────────────────────────────────────────────────────────── */

    {
        top_b_len=cmd_c_len+cmd_b_len;
        top_b=(char*)mem_alloc(top_b_len+1);

        unsigned long pos=0;

        my_memcpy(top_b+pos,cmd_c,cmd_c_len);
        pos+=cmd_c_len;

        my_memcpy(top_b+pos,cmd_b,cmd_b_len);
        pos+=cmd_b_len;

        top_b[pos]=0;
        top_b_len=pos;
    }

    /* ─────────────────────────────────────────────────────────── */
    /* Load binaries                                                */
    /* ─────────────────────────────────────────────────────────── */

    hlin=CreateFileA(argv[1],0x80000000UL,1,
                       0,3,0x80,0);

    hwin=CreateFileA(argv[2],0x80000000UL,1,
                       0,3,0x80,0);

    if (!hlin||!hwin) {
        print_text("Error opening input binaries\n");
        return 1;
    }

    GetFileSizeEx(hlin,&lin_sz);
    GetFileSizeEx(hwin,&win_sz);

    lin_buf=(unsigned char*)mem_alloc(lin_sz);
    win_buf=(unsigned char*)mem_alloc(win_sz);

    {
        unsigned long tmp;
        ReadFile(hlin,lin_buf,(unsigned long)lin_sz,&tmp,0);
        ReadFile(hwin,win_buf,(unsigned long)win_sz,&tmp,0);
    }

    CloseHandle(hlin);
    CloseHandle(hwin);

    /* compute offsets */
    b64_sz=b64_encoded_size((unsigned long)win_sz);
    b64_offset=top_a_len+top_b_len+11; /* 11 = len(":BEGIN_B64\n") */
    linux_offset=b64_offset+b64_sz+9+20; /* 9=":END_B64\n" 20=": BINARY_DATA_BELOW\n" */

    /* patch placeholders */
    {
        char* p;
        char tmp[11];

        p=my_strstr(top_a,"LINUX_OFF__");
        if (!p) { print_text("Missing LINUX_OFF__\n"); return 1; }
        u64_to_dec_left(tmp,linux_offset);
        my_memcpy(p,tmp,11);

        p=my_strstr(top_a,"LINUX_SZ___");
        if (!p) { print_text("Missing LINUX_SZ___\n"); return 1; }
        u64_to_dec_left(tmp,lin_sz);
        my_memcpy(p,tmp,11);

        p=my_strstr(top_b,"B64_OFF____");
        if (!p) { print_text("Missing B64_OFF____\n"); return 1; }
        u64_to_dec_left(tmp,b64_offset);
        my_memcpy(p,tmp,11);

        p=my_strstr(top_b,"B64_SZ_____");
        if (!p) { print_text("Missing B64_SZ_____\n"); return 1; }
        u64_to_dec_left(tmp,b64_sz);
        my_memcpy(p,tmp,11);

        p=my_strstr(top_b,"B64_SZ_____");
        if (!p) { print_text("Missing B64_SZ_____\n"); return 1; }
        u64_to_dec_left(tmp,b64_sz);
        my_memcpy(p,tmp,11);
    }

    /* open output */
    hout=CreateFileA(argv[3],0x40000000UL,0,
                       0,2,0x80,0);

    if (!hout) {
        print_text("Error opening output file\n");
        return 1;
    }

    {
        unsigned long tmp;

        WriteFile(hout,top_a,top_a_len,&tmp,0);
        WriteFile(hout,top_b,top_b_len,&tmp,0);

        WriteFile(hout,":BEGIN_B64\n",11,&tmp,0);

        base64_encode(hout,win_buf,(unsigned long)win_sz);

        WriteFile(hout,":END_B64\n",9,&tmp,0);
        WriteFile(hout,": BINARY_DATA_BELOW\n",20,&tmp,0);

        WriteFile(hout,lin_buf,(unsigned long)lin_sz,&tmp,0);

        hdr.magic=0x54AF3B2CUL;
        hdr.linux_offset=linux_offset;
        hdr.win_offset=0;
        hdr.win_size=win_sz;
        hdr.linux_size=lin_sz;

        WriteFile(hout,&hdr,sizeof(hdr),&tmp,0);
    }

    CloseHandle(hout);

    print_text("Packed OK\n");
    return 0;
}
