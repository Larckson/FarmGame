global copy_string
global get_time
global mem_alloc
global mem_free
global get_rand
global set_rand
global print_text
global read_text
global print_char
global print_int
global text_to_int
global gfx_abs

extern GetSystemTimeAsFileTime
extern GetProcessHeap
extern HeapAlloc
extern HeapFree
extern GetStdHandle
extern WriteConsoleA
extern ReadConsoleA

STD_OUTPUT_HANDLE equ -11
STD_INPUT_HANDLE  equ -10

section .data
    seed    dq 6364136223846793005
    lcg_inc dq 1442695040888963407

section .bss
    hStdOut  resq 1
    hStdIn   resq 1
    char_buf resb 1
    int_buf  resb 32

section .text

; ═════════════════════════════════════════════════════════════════
; gfx_abs(int x) -> eax  (branchless absolute value)
; ═════════════════════════════════════════════════════════════════
gfx_abs:
    mov     eax, ecx
    mov     edx, eax
    sar     edx, 31
    add     eax, edx
    xor     eax, edx
    ret


; ═════════════════════════════════════════════════════════════════
; copy_string(char* d, char* s)
; ═════════════════════════════════════════════════════════════════
copy_string:
.loop:
    mov     al, [rdx]
    mov     [rcx], al
    inc     rdx
    inc     rcx
    test    al, al
    jne     .loop
    ret


; ═════════════════════════════════════════════════════════════════
; get_time() -> rax
; ═════════════════════════════════════════════════════════════════
get_time:
    push    rbx
    sub     rsp, 48
    lea     rcx, [rsp+32]
    call    GetSystemTimeAsFileTime
    mov     eax, [rsp+32]
    mov     edx, [rsp+36]
    shl     rdx, 32
    or      rax, rdx
    mov     rcx, 116444736000000000
    sub     rax, rcx
    mov     rcx, 10000000
    xor     rdx, rdx
    div     rcx
    add     rsp, 48
    pop     rbx
    ret


; ═════════════════════════════════════════════════════════════════
; mem_alloc(size_t size) -> rax
; ═════════════════════════════════════════════════════════════════
mem_alloc:
    push    rbx
    sub     rsp, 56
    mov     rbx, rcx
    call    GetProcessHeap
    mov     rcx, rax
    xor     rdx, rdx
    mov     r8,  rbx
    call    HeapAlloc
    add     rsp, 56
    pop     rbx
    ret


; ═════════════════════════════════════════════════════════════════
; mem_free(void* ptr)
; ═════════════════════════════════════════════════════════════════
mem_free:
    push    rbx
    sub     rsp, 56
    mov     rbx, rcx
    call    GetProcessHeap
    mov     rcx, rax
    xor     rdx, rdx
    mov     r8,  rbx
    call    HeapFree
    add     rsp, 56
    pop     rbx
    ret


; ═════════════════════════════════════════════════════════════════
; set_rand / get_rand
; ═════════════════════════════════════════════════════════════════
set_rand:
    mov     [rel seed], rcx
    ret

get_rand:
    mov     rax, [rel seed]
    mov     rcx, 6364136223846793005
    imul    rax, rcx
    add     rax, [rel lcg_inc]
    mov     [rel seed], rax
    shr     rax, 33
    ret


; ═════════════════════════════════════════════════════════════════
; print_char(char* c)
; ═════════════════════════════════════════════════════════════════
print_char:
    push    rbp
    mov     rbp, rsp
    push    rbx
    sub     rsp, 56
    mov     rbx, rcx
    mov     rcx, STD_OUTPUT_HANDLE
    call    GetStdHandle
    mov     [rel hStdOut], rax
    mov     al, [rbx]
    mov     [rel char_buf], al
    mov     rcx, [rel hStdOut]
    lea     rdx, [rel char_buf]
    mov     r8,  1
    lea     r9,  [rsp+32]
    mov     qword [rsp+40], 0
    call    WriteConsoleA
    add     rsp, 56
    pop     rbx
    pop     rbp
    ret


; ═════════════════════════════════════════════════════════════════
; print_text(const char* s) -> rax
; ═════════════════════════════════════════════════════════════════
print_text:
    push    rbp
    mov     rbp, rsp
    push    rbx
    sub     rsp, 56
    mov     rbx, rcx
    mov     dword [rsp+40], 0
    mov     rcx, STD_OUTPUT_HANDLE
    call    GetStdHandle
    mov     [rel hStdOut], rax
.pt_loop:
    movzx   eax, byte [rbx]
    test    al, al
    jz      .pt_done
    mov     [rel char_buf], al
    mov     rcx, [rel hStdOut]
    lea     rdx, [rel char_buf]
    mov     r8,  1
    lea     r9,  [rsp+32]
    mov     qword [rsp+48], 0
    call    WriteConsoleA
    inc     dword [rsp+40]
    inc     rbx
    jmp     .pt_loop
.pt_done:
    mov     eax, [rsp+40]
    add     rsp, 56
    pop     rbx
    pop     rbp
    ret


; ═════════════════════════════════════════════════════════════════
; read_text(char* buf, int size)
; ═════════════════════════════════════════════════════════════════
read_text:
    push    rbp
    mov     rbp, rsp
    push    rbx
    push    rdi
    sub     rsp, 48
    mov     rbx, rcx
    mov     rdi, rdx
    mov     rcx, STD_INPUT_HANDLE
    call    GetStdHandle
    mov     [rel hStdIn], rax
    mov     rcx, [rel hStdIn]
    mov     rdx, rbx
    mov     r8,  rdi
    lea     r9,  [rsp+32]
    mov     qword [rsp+40], 0
    call    ReadConsoleA
    mov     rsi, rbx
.rt_find_cr:
    movzx   eax, byte [rsi]
    test    al, al
    jz      .rt_done
    cmp     al, 0x0D
    je      .rt_terminate
    inc     rsi
    jmp     .rt_find_cr
.rt_terminate:
    mov     byte [rsi], 0
.rt_done:
    add     rsp, 48
    pop     rdi
    pop     rbx
    pop     rbp
    ret


; ═════════════════════════════════════════════════════════════════
; print_int(long long num) -> rax
; ═════════════════════════════════════════════════════════════════
print_int:
    push    rbp
    mov     rbp, rsp
    push    rbx
    push    rdi
    push    rsi
    sub     rsp, 40
    mov     rbx, rcx
    mov     rcx, STD_OUTPUT_HANDLE
    call    GetStdHandle
    mov     [rel hStdOut], rax
    lea     rdi, [rel int_buf]
    mov     byte [rdi+31], 0
    mov     rsi, 30
    xor     r8, r8
    test    rbx, rbx
    jns     .pi_convert
    mov     r8, 1
    neg     rbx
.pi_convert:
    mov     rax, rbx
    mov     rcx, 10
.pi_digit:
    xor     rdx, rdx
    div     rcx
    add     dl, '0'
    mov     [rdi+rsi], dl
    dec     rsi
    test    rax, rax
    jnz     .pi_digit
    test    r8, r8
    jz      .pi_write
    mov     byte [rdi+rsi], '-'
    dec     rsi
.pi_write:
    inc     rsi
    mov     r10, 31
    sub     r10, rsi
    mov     rcx, [rel hStdOut]
    lea     rdx, [rdi+rsi]
    mov     r8,  r10
    lea     r9,  [rsp+32]
    mov     qword [rsp+40], 0
    call    WriteConsoleA
    mov     rax, r10
    add     rsp, 40
    pop     rsi
    pop     rdi
    pop     rbx
    pop     rbp
    ret


; ═════════════════════════════════════════════════════════════════
; text_to_int(char* buf, int* out) -> rax
; ═════════════════════════════════════════════════════════════════
text_to_int:
    push    rbx
    push    rdi
    sub     rsp, 40
    mov     rbx, rcx
    mov     rdi, rdx
    xor     ecx, ecx
    xor     r8d, r8d
    xor     r9d, r9d
    movzx   eax, byte [rbx]
    cmp     al, '-'
    jne     .ti_digits
    mov     r8d, 1
    inc     rbx
.ti_digits:
    movzx   eax, byte [rbx]
    cmp     al, '0'
    jl      .ti_done
    cmp     al, '9'
    jg      .ti_done
    sub     al, '0'
    imul    ecx, ecx, 10
    add     ecx, eax
    inc     r9d
    inc     rbx
    jmp     .ti_digits
.ti_done:
    test    r9d, r9d
    jz      .ti_fail
    test    r8d, r8d
    jz      .ti_store
    neg     ecx
.ti_store:
    mov     [rdi], ecx
    mov     eax, 1
    jmp     .ti_ret
.ti_fail:
    xor     eax, eax
.ti_ret:
    add     rsp, 40
    pop     rdi
    pop     rbx
    ret
