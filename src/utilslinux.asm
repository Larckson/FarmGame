global get_time
global mem_alloc
global mem_free
global print_text
global read_text
global print_char
global print_int

global abs_val
global copy_string
global mem_set
global get_rand
global set_rand
global text_to_int
global has_newline
global int_to_str
global my_strlen
global my_strstr
global my_memcpy
global u64_to_dec_left

; ─────────────────────────────────────────────────────────────────
; LINUX SYSCALL NUMBERS (x86-64)
; ─────────────────────────────────────────────────────────────────
SYS_READ          equ 0
SYS_WRITE         equ 1
SYS_MMAP          equ 9
SYS_MUNMAP        equ 11
SYS_CLOCK_GETTIME equ 228

STDOUT_FD         equ 1
STDIN_FD          equ 0

PROT_READ         equ 1
PROT_WRITE        equ 2
MAP_PRIVATE       equ 2
MAP_ANONYMOUS     equ 0x20

CLOCK_REALTIME    equ 0

; ─────────────────────────────────────────────────────────────────
; UNINITIALISED DATA
; ─────────────────────────────────────────────────────────────────
section .bss
    char_buf resb 1
    int_buf  resb 32
    timespec resq 2             ; [0] = tv_sec, [1] = tv_nsec
    sigaction_buf resb 32

; ─────────────────────────────────────────────────────────────────
; INITIALISED DATA
; ─────────────────────────────────────────────────────────────────
section .data
    seed    dq 6364136223846793005
    lcg_inc dq 1442695040888963407

; ─────────────────────────────────────────────────────────────────
; CODE
; ─────────────────────────────────────────────────────────────────
section .text

; get_time() → rax
; returns Unix timestamp (seconds since epoch)
get_time:
    mov     rax, SYS_CLOCK_GETTIME
    mov     rdi, CLOCK_REALTIME
    lea     rsi, [rel timespec]
    syscall

    mov     rax, [rel timespec]     ; tv_sec
    ret

; mem_alloc(size_t size) → rax
; rdi = size
mem_alloc:
    push    rbx
    mov     rbx, rdi

    mov     rax, SYS_MMAP
    xor     rdi, rdi
    lea     rsi, [rbx + 8]
    mov     rdx, PROT_READ | PROT_WRITE
    mov     r10, MAP_PRIVATE | MAP_ANONYMOUS
    mov     r8,  -1
    xor     r9,  r9
    syscall

    test    rax, rax
    js      .mem_alloc_done
    mov     [rax], rbx          ; store requested size
    add     rax, 8              ; return pointer past header
.mem_alloc_done:
    pop     rbx
    ret

; mem_free(void* ptr)
; rdi = pointer returned by mem_alloc
mem_free:
    push    rbx
    mov     rbx, rdi

    sub     rbx, 8              ; back to header
    mov     rsi, [rbx]          ; original size
    add     rsi, 8              ; include header

    mov     rax, SYS_MUNMAP
    mov     rdi, rbx
    syscall

    pop     rbx
    ret

; print_char(char* c)
; rdi = pointer to single char
print_char:
    push    rbx
    mov     rbx, rdi

    mov     al, [rbx]
    mov     [rel char_buf], al

    mov     rax, SYS_WRITE
    mov     rdi, STDOUT_FD
    lea     rsi, [rel char_buf]
    mov     rdx, 1
    syscall

    mov     eax, 1

    pop     rbx
    ret

; print_text(const char* s) → rax
; rdi = null-terminated string
print_text:
    push    rbx
    push    r12

    mov     rbx, rdi
    xor     r12d, r12d

.print_text_loop:
    movzx   eax, byte [rbx]
    test    al, al
    jz      .print_text_done

    mov     [rel char_buf], al

    mov     rax, SYS_WRITE
    mov     rdi, STDOUT_FD
    lea     rsi, [rel char_buf]
    mov     rdx, 1
    syscall

    inc     r12d
    inc     rbx
    jmp     .print_text_loop

.print_text_done:
    mov     eax, r12d

    pop     r12
    pop     rbx
    ret

; read_text(char* buf, int size)
; rdi = buffer, rsi = capacity
read_text:
    push    rbx
    push    r12

    mov     rbx, rdi        ; buffer
    mov     r12, rsi        ; capacity

.retry:
    mov     rax, SYS_READ
    mov     rdi, STDIN_FD
    mov     rsi, rbx
    mov     rdx, r12
    syscall                 ; rax = bytes_read or -errno

    ; rax < 0  → error / EINTR / signal
    test    rax, rax
    js      .interrupted

    ; rax == 0 → EOF / no data
    jz      .empty

    ; normal read
    cmp     rax, r12
    jge     .full           ; clamp if exactly full or more

    mov     byte [rbx + rax], 0
    jmp     .done

.full:
    mov     byte [rbx + r12 - 1], 0
    jmp     .done

.empty:
    mov     byte [rbx], 0
    xor     eax, eax        ; return 0
    jmp     .done

.interrupted:
    ; read was interrupted by SIGUSR1 (or other signal)
    ; treat as "no input" and return 0 safely
    mov     byte [rbx], 0
    xor     eax, eax        ; return 0
    jmp     .done

.done:
    pop     r12
    pop     rbx
    ret


; print_int(long long num) → rax
; rdi = signed 64-bit integer
print_int:
    push    rbx
    push    r12
    push    r13
    push    r14
    push    r15

    mov     rbx, rdi

    lea     r12, [rel int_buf]
    mov     byte [r12+31], 0
    mov     r13, 30

    xor     r14, r14
    test    rbx, rbx
    jns     .print_int_convert
    mov     r14, 1
    neg     rbx

.print_int_convert:
    mov     rax, rbx
    mov     rcx, 10
.print_int_digit_loop:
    xor     rdx, rdx
    div     rcx
    add     dl, '0'
    mov     [r12+r13], dl
    dec     r13
    test    rax, rax
    jnz     .print_int_digit_loop

    test    r14, r14
    jz      .print_int_write
    mov     byte [r12+r13], '-'
    dec     r13

.print_int_write:
    inc     r13

    mov     r15, 31
    sub     r15, r13

    mov     rax, SYS_WRITE
    mov     rdi, STDOUT_FD
    lea     rsi, [r12+r13]
    mov     rdx, r15
    syscall

    mov     rax, r15

    pop     r15
    pop     r14
    pop     r13
    pop     r12
    pop     rbx
    ret

; abs_val(int x) -> eax
; Linux: edi = x
abs_val:
    mov     eax, edi
    mov     edx, eax
    sar     edx, 31
    add     eax, edx
    xor     eax, edx
    ret

; copy_string(char* d, char* s)
; Linux: rdi = d, rsi = s
copy_string:
    mov     r8,  rdi
    mov     r9,  rsi
.copy_string_loop:
    mov     al,  [r9]
    mov     [r8], al
    inc     r9
    inc     r8
    test    al, al
    jne     .copy_string_loop
    ret

; mem_set(void* dst, int val, unsigned int n)
; Linux: rdi = dst, rsi = val, rdx = n
mem_set:
    test    edx, edx
    jz      .mem_set_done
    movzx   eax, sil
.mem_set_loop:
    mov     [rdi], al
    inc     rdi
    dec     edx
    jnz     .mem_set_loop
.mem_set_done:
    ret

; set_rand(unsigned long seed_val)
; Linux: rdi = seed_val
set_rand:
    mov     [rel seed], rdi
    ret

; get_rand() -> rax
get_rand:
    mov     rax, [rel seed]
    mov     rcx, 6364136223846793005
    imul    rax, rcx
    add     rax, [rel lcg_inc]
    mov     [rel seed], rax
    shr     rax, 33
    ret

; text_to_int(char* buf, int* out) -> rax
; Linux: rdi = buf, rsi = out
text_to_int:
    push    rbx
    push    r12

    mov     rbx, rdi
    mov     r12, rsi
    xor     ecx, ecx            ; accumulator
    xor     r8d, r8d            ; negative flag
    xor     r9d, r9d            ; digit count

    movzx   eax, byte [rbx]
    cmp     al, '-'
    jne     .text_to_int_digits
    mov     r8d, 1
    inc     rbx

.text_to_int_digits:
    movzx   eax, byte [rbx]
    cmp     al, '0'
    jl      .text_to_int_done
    cmp     al, '9'
    jg      .text_to_int_done
    sub     al, '0'
    imul    ecx, ecx, 10
    add     ecx, eax
    inc     r9d
    inc     rbx
    jmp     .text_to_int_digits

.text_to_int_done:
    test    r9d, r9d
    jz      .text_to_int_fail

    test    r8d, r8d
    jz      .text_to_int_store
    neg     ecx

.text_to_int_store:
    mov     [r12], ecx
    mov     eax, 1
    jmp     .text_to_int_ret

.text_to_int_fail:
    xor     eax, eax

.text_to_int_ret:
    pop     r12
    pop     rbx
    ret

; has_newline(char* buf, int len) -> rax
; rdi = buf, esi = len
has_newline:
    xor     eax, eax
.loop:
    cmp     eax, esi
    jge     .not_found
    movzx   r8d, byte [rdi + rax]
    test    r8b, r8b
    jz      .not_found          ; hit null terminator before \n = no newline
    cmp     r8b, 0x0A
    je      .found
    inc     eax
    jmp     .loop
.found:
    mov     eax, 1
    ret
.not_found:
    xor     eax, eax
    ret

; int_to_str(long long num, char* buf)
; Linux: rdi = num, rsi = buf
int_to_str:
    push    rbx
    push    r12
    push    r13

    movsx   rbx, edi
    mov     r12, rsi

    lea     r13, [rel int_buf]
    mov     byte [r13+31], 0
    mov     rcx, 30

    xor     r8, r8
    test    rbx, rbx
    jns     .convert
    mov     r8, 1
    neg     rbx

.convert:
    mov     rax, rbx
    mov     rbx, 10
.digit_loop:
    xor     rdx, rdx
    div     rbx
    add     dl, '0'
    mov     [r13+rcx], dl
    dec     rcx
    test    rax, rax
    jnz     .digit_loop

    test    r8, r8
    jz      .copy
    mov     byte [r13+rcx], '-'
    dec     rcx

.copy:
    inc     rcx
    lea     r9, [r13+rcx]       ; source

    mov     rdi, r12            ; dst
    mov     rsi, r9             ; src
    call    copy_string

    pop     r13
    pop     r12
    pop     rbx
    ret

;my_strlen
my_strlen:
    ; RDI = pointer to string
    xor     rax, rax        ; n = 0

.len_loop:
    mov     dl, [rdi + rax] ; load byte s[n]
    test    dl, dl          ; zero?
    jz      .done
    inc     rax
    jmp     .len_loop

.done:
    ret

; ================================================================
; char* my_strstr(char* h, const char* n)
;   RDI = h
;   RSI = n
; returns:
;   RAX = pointer to first occurrence or 0
; calls:
;   my_strlen (SysV ABI)
; ================================================================

my_strstr:
    push    rbx
    push    r12
    push    r13
    push    r14

    mov     r12, rdi        ; h
    mov     r13, rsi        ; n

    ; hl = my_strlen(h)
    mov     rdi, r12
    call    my_strlen
    mov     r8, rax         ; hl

    ; nl = my_strlen(n)
    mov     rdi, r13
    call    my_strlen
    mov     r9, rax         ; nl

    cmp     r9, r8
    ja      .not_found

    xor     r10, r10        ; i = 0
    mov     r11, r8
    sub     r11, r9         ; hl - nl

.outer_loop:
    cmp     r10, r11
    ja      .not_found

    xor     rbx, rbx        ; j = 0

.inner_loop:
    cmp     rbx, r9
    jae     .match

    ; r14 = i + j
    mov     r14, r10
    add     r14, rbx

    mov     al, [r12 + r14] ; h[i+j]
    mov     dl, [r13 + rbx] ; n[j]
    cmp     al, dl
    jne     .next_i

    inc     rbx
    jmp     .inner_loop

.match:
    lea     rax, [r12 + r10]
    jmp     .done

.next_i:
    inc     r10
    jmp     .outer_loop

.not_found:
    xor     rax, rax

.done:
    pop     r14
    pop     r13
    pop     r12
    pop     rbx
    ret

    ; ================================================================
; my_memcpy - Linux x86-64 (System V)
; void* my_memcpy(void* dst, const void* src, unsigned long n)
;   RDI = dst
;   RSI = src
;   RDX = n
; returns:
;   RAX = dst
; ================================================================

my_memcpy:
    mov     rax, rdi        ; rax = dst
    test    rdx, rdx        ; n == 0 ?
    jz      .done

.copy_loop:
    mov     cl, [rsi]       ; load *src
    mov     [rdi], cl       ; store to *dst
    inc     rdi
    inc     rsi
    dec     rdx
    jnz     .copy_loop

.done:
    ret

    ; ================================================================
; void u64_to_dec_left(char* out, unsigned long long v)
;   RDI = out
;   RSI = v
; ================================================================

u64_to_dec_left:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 48             ; space for tmp[32] etc.

    mov     r8, rdi             ; r8 = out
    mov     rax, rsi            ; rax = v
    xor     r9d, r9d            ; i = 0

    lea     r10, [rbp - 32]     ; tmp base

    test    rax, rax
    jnz     .conv_loop

    mov     byte [r10], '0'
    inc     r9d
    jmp     .have_digits

.conv_loop:
    cmp     r9d, 31
    jae     .have_digits
    test    rax, rax
    jz      .have_digits

    xor     rdx, rdx
    mov     rcx, 10
    div     rcx                 ; rax = v / 10, rdx = v % 10

    add     dl, '0'
    mov     [r10 + r9], dl
    inc     r9d
    jmp     .conv_loop

.have_digits:
    mov     r11d, r9d           ; len = i
    xor     r12d, r12d          ; j = 0

.rev_loop:
    cmp     r12d, r11d
    jae     .pad_spaces

    mov     edx, r11d
    dec     edx
    sub     edx, r12d
    mov     bl, [r10 + rdx]
    mov     [r8 + r12], bl
    inc     r12d
    jmp     .rev_loop

.pad_spaces:
    cmp     r12d, 11
    jae     .done

    mov     byte [r8 + r12], ' '
    inc     r12d
    jmp     .pad_spaces

.done:
    add     rsp, 48
    pop     rbp
    ret
