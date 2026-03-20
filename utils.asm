global string_copy
global print_time
global malloc_c
global free_c
global random
global srandom

extern GetSystemTimeAsFileTime
extern GetProcessHeap
extern HeapAlloc
extern HeapFree

section .text

; ─────────────────────────────────────────────
; string_copy(char* d, const char* s)
; ─────────────────────────────────────────────
string_copy:
.copy_loop:
    mov al, [rsi]
    mov [rdi], al
    inc rsi
    inc rdi
    test al, al
    jne .copy_loop
    ret


; ─────────────────────────────────────────────
; unsigned long print_time()
; ─────────────────────────────────────────────
print_time:
    push    rbx
    sub     rsp, 48
    lea     rcx, [rsp+32]
    call    GetSystemTimeAsFileTime
    mov     rax, [rsp+32]
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


; ─────────────────────────────────────────────
; void* malloc_c(size_t size)
;   rcx = size
;
;   push rbx        → realigns rsp to 16
;   sub  rsp, 56    → 32 shadow + 8 save + 16 pad
;   rbx preserved across both calls to hold size
; ─────────────────────────────────────────────
malloc_c:
    push    rbx
    sub     rsp, 56

    mov     rbx, rcx            ; save size across GetProcessHeap call

    call    GetProcessHeap      ; rax = heap handle

    mov     rcx, rax            ; hHeap
    xor     rdx, rdx            ; dwFlags = 0
    mov     r8,  rbx            ; dwBytes = size
    call    HeapAlloc           ; rax = allocated pointer or NULL

    add     rsp, 56
    pop     rbx
    ret


; ─────────────────────────────────────────────
; void free_c(void* ptr)
;   rcx = ptr
; ─────────────────────────────────────────────
free_c:
    push    rbx
    sub     rsp, 56

    mov     rbx, rcx            ; save ptr across GetProcessHeap call

    call    GetProcessHeap      ; rax = heap handle

    mov     rcx, rax            ; hHeap
    xor     rdx, rdx            ; dwFlags = 0
    mov     r8,  rbx            ; lpMem = ptr
    call    HeapFree

    add     rsp, 56
    pop     rbx
    ret

section .data
    seed    dq 6364136223846793005
    lcg_inc dq 1442695040888963407

section .text

srandom:
    mov     [rel seed], rcx
    ret

random:
    mov     rax, [rel seed]
    mov     rcx, 6364136223846793005
    imul    rax, rcx
    add     rax, [rel lcg_inc]
    mov     [rel seed], rax
    shr     rax, 33
    ret
