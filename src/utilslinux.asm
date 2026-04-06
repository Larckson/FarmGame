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

global setup_signals

%define SYS_SIGACTION 13
%define SIGUSR1       10

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

; no-op signal handler
sigusr1_handler:
    ret

; robust setup_signals - zero buffer, install no-op handler, check syscall result
section .data
sig_setup_fail_msg: db "setup_signals: sigaction failed", 10, 0

section .text
global setup_signals

setup_signals:
    ; zero sigaction_buf (32 bytes)
    lea     rax, [rel sigaction_buf]
    xor     rcx, rcx
.zero_loop:
    mov     byte [rax + rcx], 0
    inc     rcx
    cmp     rcx, 32
    jb      .zero_loop

    ; fill sigaction_buf
    lea     rcx, [rel sigusr1_handler]
    mov     [rax], rcx        ; sa_handler (offset 0)
    mov     qword [rax + 8], 0    ; sa_flags = 0 (no SA_RESTART)
    mov     qword [rax + 16], 0   ; sa_restorer = NULL
    mov     qword [rax + 24], 0   ; sa_mask = 0

    ; syscall: rt_sigaction(SIGUSR1, &sigaction_buf, NULL, sizeof(sigset_t))
    mov     rax, SYS_SIGACTION
    mov     rdi, SIGUSR1
    lea     rsi, [rel sigaction_buf]
    xor     rdx, rdx
    mov     r10, 8
    syscall

    ; check return value (rax == 0 on success)
    test    rax, rax
    jz      .setup_done

    ; on error, print a diagnostic (non-fatal) so you can see failure under gdb/run
    lea     rdi, [rel sig_setup_fail_msg]
    call    print_text

.setup_done:
    ret
