global get_time
global mem_alloc
global mem_free
global print_text
global read_text
global print_char
global print_int

extern GetSystemTimeAsFileTime
extern GetProcessHeap
extern HeapAlloc
extern HeapFree
extern GetStdHandle
extern WriteConsoleA
extern ReadConsoleA

global abs_val
global copy_string
global mem_set
global get_rand
global set_rand
global text_to_int
global has_newline
global int_to_str

; ─────────────────────────────────────────────────────────────────
; CONSTANTS
; ─────────────────────────────────────────────────────────────────
STD_OUTPUT_HANDLE equ -11
STD_INPUT_HANDLE  equ -10

; ─────────────────────────────────────────────────────────────────
; DATA
; ─────────────────────────────────────────────────────────────────
section .data
    seed    dq 6364136223846793005
    lcg_inc dq 1442695040888963407

; ─────────────────────────────────────────────────────────────────
; BSS
; ─────────────────────────────────────────────────────────────────
section .bss
    hStdOut  resq 1
    hStdIn   resq 1
    char_buf resb 1
    int_buf  resb 32

; ─────────────────────────────────────────────────────────────────
; CODE
; ─────────────────────────────────────────────────────────────────
section .text

; get_time() → rax
; returns Unix timestamp (seconds since epoch)
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

; mem_alloc(size_t size) → rax
; rcx = size
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

; mem_free(void* ptr)
; rcx = pointer
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

; print_char(char* c)
; rcx = pointer to single char
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
    mov     eax, 1

    add     rsp, 56
    pop     rbx
    pop     rbp
    ret

; print_text(const char* s) → rax
; rcx = null-terminated string
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

.print_text_loop:
    movzx   eax, byte [rbx]
    test    al, al
    jz      .print_text_done

    mov     [rel char_buf], al
    mov     rcx, [rel hStdOut]
    lea     rdx, [rel char_buf]
    mov     r8,  1
    lea     r9,  [rsp+32]
    mov     qword [rsp+48], 0
    call    WriteConsoleA

    inc     dword [rsp+40]
    inc     rbx
    jmp     .print_text_loop

.print_text_done:
    mov     eax, [rsp+40]
    add     rsp, 56
    pop     rbx
    pop     rbp
    ret

; read_text(char* buf, int size)
; Windows x64: rcx = buffer, rdx = capacity
read_text:
    push    rbp
    mov     rbp, rsp
    push    rbx
    push    rdi
    push    rsi
    sub     rsp, 40                 ; 32 bytes shadow + 8 scratch, keep 16‑byte alignment

    mov     rbx, rcx                ; rbx = buffer
    mov     rdi, rdx                ; rdi = capacity

    ; GetStdHandle(STD_INPUT_HANDLE)
    mov     rcx, STD_INPUT_HANDLE
    call    GetStdHandle
    mov     [rel hStdIn], rax

    ; ReadConsoleA(hStdIn, buf, capacity-1, &charsRead, NULL)
    mov     rcx, [rel hStdIn]       ; hConsole
    mov     rdx, rbx                ; lpBuffer
    lea     r8,  [rdi-1]            ; nCharsToRead = capacity-1
    lea     r9,  [rsp+24]           ; lpNumberOfCharsRead (inside shadow space)
    mov     qword [rsp+32], 0       ; lpReserved = NULL (5th arg at [rsp+32])
    call    ReadConsoleA

    ; scan for '\r' and terminate
    mov     rcx, [rsp+24]           ; rcx = chars read
    mov     rsi, rbx                ; rsi = scan pointer

.read_text_find_cr:
    test    rcx, rcx
    jz      .read_text_done
    movzx   eax, byte [rsi]
    cmp     al, 0x0D                ; '\r'
    je      .read_text_terminate
    inc     rsi
    dec     rcx
    jmp     .read_text_find_cr

.read_text_terminate:
    mov     byte [rsi], 0           ; null‑terminate at CR

.read_text_done:
    add     rsp, 40
    pop     rsi
    pop     rdi
    pop     rbx
    pop     rbp
    ret


; print_int(long long num) → rax
; rcx = signed 64-bit integer
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
    jns     .print_int_convert
    mov     r8, 1
    neg     rbx

.print_int_convert:
    mov     rax, rbx
    mov     rcx, 10
.print_int_digit_loop:
    xor     rdx, rdx
    div     rcx
    add     dl, '0'
    mov     [rdi+rsi], dl
    dec     rsi
    test    rax, rax
    jnz     .print_int_digit_loop

    test    r8, r8
    jz      .print_int_write
    mov     byte [rdi+rsi], '-'
    dec     rsi

.print_int_write:
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

; abs_val(int x) -> eax
; Windows: ecx = x
abs_val:
    mov     eax, ecx
    mov     edx, eax
    sar     edx, 31
    add     eax, edx
    xor     eax, edx
    ret

; copy_string(char* d, char* s)
; Windows: rcx = d, rdx = s
copy_string:
    mov     r8,  rcx
    mov     r9,  rdx
.copy_string_loop:
    mov     al,  [r9]
    mov     [r8], al
    inc     r9
    inc     r8
    test    al, al
    jne     .copy_string_loop
    ret

; mem_set(void* dst, int val, unsigned int n)
; Windows: rcx = dst, rdx = val, r8d = n
mem_set:
    test    r8d, r8d
    jz      .mem_set_done
    movzx   eax, dl
.mem_set_loop:
    mov     [rcx], al
    inc     rcx
    dec     r8d
    jnz     .mem_set_loop
.mem_set_done:
    ret

; set_rand(unsigned long seed_val)
; Windows: rcx = seed_val
set_rand:
    mov     [rel seed], rcx
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
; Windows: rcx = buf, rdx = out
text_to_int:
    push    rbx
    push    r12

    mov     rbx, rcx
    mov     r12, rdx
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
; Windows: rcx = buf, edx = len
has_newline:
    xor     eax, eax

.loop:
    cmp     eax, edx
    jge     .not_found

    mov     r8b, [rcx + rax]
    cmp     r8b, 10
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
; Windows: rcx = num, rdx = buf
int_to_str:
    push    rbx
    push    r12
    push    r13

    movsx   rbx, ecx
    mov     r12, rdx

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

    mov     rcx, r12            ; dst
    mov     rdx, r9             ; src
    call    copy_string

    pop     r13
    pop     r12
    pop     rbx
    ret
