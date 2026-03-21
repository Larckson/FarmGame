global abs_val
global copy_string
global get_time
global mem_alloc
global mem_free
global mem_set
global get_rand
global set_rand
global print_text
global read_text
global print_char
global print_int
global text_to_int

; These live in Kernel32.dll, goes back to early versions of Windows like Windows 95
extern GetSystemTimeAsFileTime ; gets system time as 64bit val
extern GetProcessHeap ; returns a handle to the default heap of the current process
extern HeapAlloc ; allocates a block of memory from a heap handle
extern HeapFree ; frees a block back to a heap handle
extern GetStdHandle ; returns a handle to stdin, stdout, or stderr given a constant like -11
extern WriteConsoleA ; writes a string to a console handle. ASCII bytes
extern ReadConsoleA ; reads a line of input from a console handle into a buffer. ASCII bytes

; ─────────────────────────────────────────────────────────────────
; CONSTANTS
; ─────────────────────────────────────────────────────────────────
STD_OUTPUT_HANDLE equ -11
STD_INPUT_HANDLE  equ -10

; ─────────────────────────────────────────────────────────────────
; INITIALISED DATA
;   seed    — current LCG state, starts at the multiplier value
;   lcg_inc — additive constant for the LCG step
; ─────────────────────────────────────────────────────────────────
section .data
    seed    dq 6364136223846793005
    lcg_inc dq 1442695040888963407

; ─────────────────────────────────────────────────────────────────
; UNINITIALISED DATA
;   hStdOut  — cached stdout handle
;   hStdIn   — cached stdin handle
;   char_buf — single byte staging buffer for WriteConsoleA
;   int_buf  — 32 byte scratch buffer for print_int digit assembly
; ─────────────────────────────────────────────────────────────────
section .bss
    hStdOut  resq 1
    hStdIn   resq 1
    char_buf resb 1
    int_buf  resb 32

section .text

; ═════════════════════════════════════════════════════════════════
; abs_val(int x) -> eax  (branchless absolute value)
; ═════════════════════════════════════════════════════════════════
abs_val:
    mov     eax, ecx
    mov     edx, eax
    sar     edx, 31
    add     eax, edx
    xor     eax, edx
    ret

; ═════════════════════════════════════════════════════════════════
; copy_string(char* d, char* s)
;   rcx = d  destination buffer
;   rdx = s  source string (null terminated)
;
;   Copies bytes from s into d one at a time including the null
;   terminator. No bounds checking — caller must ensure d is large
;   enough to hold s.
; ═════════════════════════════════════════════════════════════════
copy_string:
.copy_string_loop:
    mov     al, [rdx]           ; load next byte from source
    mov     [rcx], al           ; write it to destination
    inc     rdx                 ; advance source pointer
    inc     rcx                 ; advance destination pointer
    test    al, al              ; was the byte just written a null?
    jne     .copy_string_loop   ; no  — keep copying
    ret                         ; yes — done


; ═════════════════════════════════════════════════════════════════
; get_time() → rax
;
;   Returns the current Unix timestamp (seconds since 1970-01-01)
;   as an unsigned 64-bit integer.
;
;   Strategy:
;     1. Call GetSystemTimeAsFileTime to get a FILETIME — a 64-bit
;        count of 100-nanosecond intervals since 1601-01-01.
;     2. Subtract the number of 100ns intervals between 1601 and
;        1970 (116444736000000000).
;     3. Divide by 10,000,000 to convert 100ns units to seconds.
;
;   Stack layout (after push rbx, sub rsp 48):
;     [rsp+32..39]  FILETIME low  dword  (written by GetSystemTimeAsFileTime)
;     [rsp+36..39]  FILETIME high dword
;     [rsp+ 0..31]  shadow space for callees
; ═════════════════════════════════════════════════════════════════
get_time:
    push    rbx
    sub     rsp, 48

    lea     rcx, [rsp+32]               ; pass pointer to FILETIME slot on stack
    call    GetSystemTimeAsFileTime

    mov     eax, [rsp+32]               ; read low  32 bits of FILETIME
    mov     edx, [rsp+36]               ; read high 32 bits of FILETIME
    shl     rdx, 32                     ; shift high half into upper 32 bits of rdx
    or      rax, rdx                    ; combine into full 64-bit FILETIME value

    mov     rcx, 116444736000000000     ; epoch delta in 100ns units
    sub     rax, rcx                    ; convert base from 1601 to 1970

    mov     rcx, 10000000               ; 100ns units per second
    xor     rdx, rdx                    ; clear rdx for 128-bit divide
    div     rcx                         ; rax = seconds since Unix epoch

    add     rsp, 48
    pop     rbx
    ret


; ═════════════════════════════════════════════════════════════════
; mem_alloc(size_t size) → rax
;   rcx = number of bytes to allocate
;
;   Allocates memory from the default process heap using the
;   Windows Heap API. Returns a pointer to the allocated block or
;   NULL on failure. Equivalent to malloc() but without the CRT.
;
;   Calls:
;     GetProcessHeap()           → handle to default heap
;     HeapAlloc(heap, 0, size)   → allocated pointer
;
;   rbx is used to preserve the size argument across the first
;   call since rcx is clobbered by GetProcessHeap's return value.
; ═════════════════════════════════════════════════════════════════
mem_alloc:
    push    rbx
    sub     rsp, 56

    mov     rbx, rcx            ; preserve requested size across call
    call    GetProcessHeap      ; rax = handle to default process heap

    mov     rcx, rax            ; hHeap
    xor     rdx, rdx            ; dwFlags = 0 (no special behaviour)
    mov     r8,  rbx            ; dwBytes  = requested size
    call    HeapAlloc           ; rax = pointer to block or NULL

    add     rsp, 56
    pop     rbx
    ret


; ═════════════════════════════════════════════════════════════════
; mem_free(void* ptr)
;   rcx = pointer to block previously returned by mem_alloc
;
;   Releases a heap block back to the default process heap.
;   Equivalent to free() but without the CRT. Passing NULL or a
;   pointer not from mem_alloc is undefined behaviour.
;
;   Calls:
;     GetProcessHeap()            → handle to default heap
;     HeapFree(heap, 0, ptr)      → releases the block
;
;   rbx preserves the pointer across the GetProcessHeap call.
; ═════════════════════════════════════════════════════════════════
mem_free:
    push    rbx
    sub     rsp, 56

    mov     rbx, rcx            ; preserve pointer across call
    call    GetProcessHeap      ; rax = handle to default process heap

    mov     rcx, rax            ; hHeap
    xor     rdx, rdx            ; dwFlags = 0
    mov     r8,  rbx            ; lpMem   = pointer to free
    call    HeapFree

    add     rsp, 56
    pop     rbx
    ret

; ═════════════════════════════════════════════════════════════════
; mem_set(void* dst, int val, unsigned int n)
; ═════════════════════════════════════════════════════════════════
mem_set:
    test    r8d, r8d
    jz      .mem_set_done
    movzx   eax, dl           ; truncate val to one byte
.mem_set_loop:
    mov     [rcx], al
    inc     rcx
    dec     r8d
    jnz     .mem_set_loop
.mem_set_done:
    ret

; ═════════════════════════════════════════════════════════════════
; set_rand(unsigned long seed_val)
;   rcx = seed value
;
;   Seeds the LCG get_rand number generator by writing the supplied
;   value into the seed qword in .data. The next call to get_rand()
;   will use this as its starting state.
; ═════════════════════════════════════════════════════════════════
set_rand:
    mov     [rel seed], rcx
    ret


; ═════════════════════════════════════════════════════════════════
; get_rand() → rax
;
;   Returns a pseudo-get_rand 31-bit integer in the range 0..2^31-1.
;
;   Uses a 64-bit Linear Congruential Generator with the Knuth/
;   glibc constants:
;     next = current * 6364136223846793005 + lcg_inc
;
;   The raw 64-bit state is shifted right 33 bits before returning
;   to discard the low-quality low-order bits and bring the result
;   into the same 0..2147483647 range as the standard rand().
; ═════════════════════════════════════════════════════════════════
get_rand:
    mov     rax, [rel seed]             ; load current LCG state
    mov     rcx, 6364136223846793005    ; LCG multiplier
    imul    rax, rcx                    ; advance state: state *= multiplier
    add     rax, [rel lcg_inc]          ; advance state: state += increment
    mov     [rel seed], rax             ; store updated state
    shr     rax, 33                     ; discard low-quality low bits
    ret                                 ; rax = pseudo-get_rand value


; ═════════════════════════════════════════════════════════════════
; print_char(char* c)
;   rcx = pointer to a single character to print
;
;   Writes exactly one byte to stdout via WriteConsoleA. The byte
;   is staged through char_buf because WriteConsoleA requires a
;   pointer — it cannot take the value directly.
;
;   Used by callers that have a pointer to a lone char field (e.g.
;   a struct member) that is not null-terminated and therefore
;   cannot be passed to print_text.
; ═════════════════════════════════════════════════════════════════
print_char:
    push    rbp
    mov     rbp, rsp
    push    rbx
    sub     rsp, 56

    mov     rbx, rcx                    ; preserve pointer across GetStdHandle

    mov     rcx, STD_OUTPUT_HANDLE
    call    GetStdHandle
    mov     [rel hStdOut], rax          ; cache handle for WriteConsoleA

    mov     al, [rbx]                   ; load the single byte
    mov     [rel char_buf], al          ; stage it for WriteConsoleA
    mov     rcx, [rel hStdOut]
    lea     rdx, [rel char_buf]         ; pointer to the staged byte
    mov     r8,  1                      ; write exactly 1 byte
    lea     r9,  [rsp+32]               ; lpNumberOfCharsWritten (ignored)
    mov     qword [rsp+40], 0           ; lpReserved = NULL
    call    WriteConsoleA

    add     rsp, 56
    pop     rbx
    pop     rbp
    ret


; ═════════════════════════════════════════════════════════════════
; print_text(const char* s) → rax
;   rcx = pointer to null-terminated string
;
;   Writes each byte of s to stdout one at a time until the null
;   terminator is reached. Returns the number of characters written
;   in rax so the caller can add padding if needed.
;
;   The character count is kept on the stack at [rsp+40] rather
;   than in a caller-saved register because WriteConsoleA is free
;   to clobber any caller-saved register on each call.
; ═════════════════════════════════════════════════════════════════
print_text:
    push    rbp
    mov     rbp, rsp
    push    rbx
    sub     rsp, 56

    mov     rbx, rcx                    ; preserve string pointer
    mov     dword [rsp+40], 0           ; initialise character counter

    mov     rcx, STD_OUTPUT_HANDLE
    call    GetStdHandle
    mov     [rel hStdOut], rax

.print_text_loop:
    movzx   eax, byte [rbx]             ; load next character
    test    al, al
    jz      .print_text_done            ; null terminator — stop

    mov     [rel char_buf], al          ; stage character for WriteConsoleA
    mov     rcx, [rel hStdOut]
    lea     rdx, [rel char_buf]
    mov     r8,  1
    lea     r9,  [rsp+32]
    mov     qword [rsp+48], 0           ; lpReserved = NULL
    call    WriteConsoleA

    inc     dword [rsp+40]              ; increment character counter
    inc     rbx                         ; advance string pointer
    jmp     .print_text_loop

.print_text_done:
    mov     eax, [rsp+40]               ; return character count
    add     rsp, 56
    pop     rbx
    pop     rbp
    ret


; ═════════════════════════════════════════════════════════════════
; read_text(char* buf, int size)
;   rcx = pointer to caller-supplied buffer
;   rdx = capacity of the buffer in bytes
;
;   Reads a line of input from stdin into buf via ReadConsoleA.
;   ReadConsoleA includes the \r\n line ending in the buffer, so
;   after the call this function scans forward from the start of
;   buf to find the \r and overwrites it with a null terminator,
;   giving the caller a clean C string without the newline.
;
;   rbx preserves the buffer pointer and rdi preserves the size
;   across the GetStdHandle and ReadConsoleA calls.
; ═════════════════════════════════════════════════════════════════
read_text:
    push    rbp
    mov     rbp, rsp
    push    rbx
    push    rdi
    sub     rsp, 48

    mov     rbx, rcx                    ; preserve buffer pointer
    mov     rdi, rdx                    ; preserve buffer size

    mov     rcx, STD_INPUT_HANDLE
    call    GetStdHandle
    mov     [rel hStdIn], rax

    mov     rcx, [rel hStdIn]           ; hConsoleInput
    mov     rdx, rbx                    ; lpBuffer
    mov     r8,  rdi                    ; nNumberOfCharsToRead
    lea     r9,  [rsp+32]               ; lpNumberOfCharsRead
    mov     qword [rsp+40], 0           ; pInputControl = NULL
    call    ReadConsoleA

    ; strip the \r\n that ReadConsoleA appends
    mov     rsi, rbx                    ; start scanning from beginning of buf
.read_text_find_cr:
    movzx   eax, byte [rsi]
    test    al, al
    jz      .read_text_done             ; hit null before \r — already clean
    cmp     al, 0x0D                    ; is this \r?
    je      .read_text_terminate
    inc     rsi
    jmp     .read_text_find_cr
.read_text_terminate:
    mov     byte [rsi], 0               ; overwrite \r with null terminator
.read_text_done:
    add     rsp, 48
    pop     rdi
    pop     rbx
    pop     rbp
    ret


; ═════════════════════════════════════════════════════════════════
; print_int(long long num) → rax
;   rcx = integer to print (signed 64-bit)
;
;   Converts num to its decimal ASCII representation and writes it
;   to stdout. Returns the number of characters written in rax so
;   the caller can pad if needed.
;
;   Strategy:
;     Digits are produced right-to-left by repeatedly dividing by
;     10 and converting the remainder to ASCII, storing each digit
;     into int_buf from index 30 downward. After all digits are
;     placed a '-' is prepended for negative numbers. rsi then
;     points to the first character of the number in int_buf and
;     the length is 31 - rsi.
;
;   r8 is used as the negative flag. It survives across the digit
;   loop because the loop only clobbers rax, rcx, rdx.
; ═════════════════════════════════════════════════════════════════
print_int:
    push    rbp
    mov     rbp, rsp
    push    rbx
    push    rdi
    push    rsi
    sub     rsp, 40

    mov     rbx, rcx                    ; preserve number across GetStdHandle

    mov     rcx, STD_OUTPUT_HANDLE
    call    GetStdHandle
    mov     [rel hStdOut], rax

    lea     rdi, [rel int_buf]
    mov     byte [rdi+31], 0            ; place null terminator at end of buffer
    mov     rsi, 30                     ; start writing digits at index 30

    xor     r8, r8                      ; assume positive
    test    rbx, rbx
    jns     .print_int_convert          ; number is non-negative — skip
    mov     r8, 1                       ; set negative flag
    neg     rbx                         ; make positive for digit extraction

.print_int_convert:
    mov     rax, rbx
    mov     rcx, 10
.print_int_digit_loop:
    xor     rdx, rdx
    div     rcx                         ; rdx = digit, rax = remaining
    add     dl, '0'                     ; convert digit to ASCII
    mov     [rdi+rsi], dl               ; store digit in buffer
    dec     rsi                         ; move one position left
    test    rax, rax
    jnz     .print_int_digit_loop       ; more digits remaining

    test    r8, r8                      ; was the number negative?
    jz      .print_int_write
    mov     byte [rdi+rsi], '-'         ; prepend minus sign
    dec     rsi

.print_int_write:
    inc     rsi                         ; rsi now points to first character

    mov     r10, 31
    sub     r10, rsi                    ; r10 = number of characters to write

    mov     rcx, [rel hStdOut]
    lea     rdx, [rdi+rsi]              ; pointer to first character
    mov     r8,  r10                    ; character count
    lea     r9,  [rsp+32]
    mov     qword [rsp+40], 0
    call    WriteConsoleA

    mov     rax, r10                    ; return character count

    add     rsp, 40
    pop     rsi
    pop     rdi
    pop     rbx
    pop     rbp
    ret


; ═════════════════════════════════════════════════════════════════
; text_to_int(char* buf, int* out) → rax
;   rcx = pointer to null-terminated input string
;   rdx = pointer to int that receives the parsed value
;
;   Parses a signed decimal integer from the start of buf. An
;   optional leading '-' is recognised. Parsing stops at the first
;   non-digit character.
;
;   Returns 1 in rax if at least one digit was consumed (success).
;   Returns 0 in rax if no digits were found (failure).
;   On success the parsed value is written to *out.
;
;   rbx = current position in buf
;   rdi = out pointer
;   ecx = accumulator
;   r8d = negative flag
;   r9d = digit count
; ═════════════════════════════════════════════════════════════════
text_to_int:
    push    rbx
    push    rdi
    sub     rsp, 40

    mov     rbx, rcx                    ; current position in input buffer
    mov     rdi, rdx                    ; pointer to output int
    xor     ecx, ecx                    ; accumulator = 0
    xor     r8d, r8d                    ; negative flag = 0
    xor     r9d, r9d                    ; digit count = 0

    movzx   eax, byte [rbx]             ; peek at first character
    cmp     al, '-'
    jne     .text_to_int_digits            ; not a minus — go straight to digits
    mov     r8d, 1                      ; set negative flag
    inc     rbx                         ; consume the '-'

.text_to_int_digits:
    movzx   eax, byte [rbx]
    cmp     al, '0'
    jl      .text_to_int_done              ; below '0' — not a digit
    cmp     al, '9'
    jg      .text_to_int_done              ; above '9' — not a digit
    sub     al, '0'                     ; convert ASCII digit to value
    imul    ecx, ecx, 10                ; shift accumulator left one decimal place
    add     ecx, eax                    ; add new digit
    inc     r9d                         ; increment digit count
    inc     rbx                         ; advance buffer pointer
    jmp     .text_to_int_digits

.text_to_int_done:
    test    r9d, r9d
    jz      .text_to_int_fail              ; no digits seen — return failure

    test    r8d, r8d
    jz      .text_to_int_store
    neg     ecx                         ; apply sign

.text_to_int_store:
    mov     [rdi], ecx                  ; write result to caller's int
    mov     eax, 1                      ; return 1 = success
    jmp     .text_to_int_ret

.text_to_int_fail:
    xor     eax, eax                    ; return 0 = failure

.text_to_int_ret:
    add     rsp, 40
    pop     rdi
    pop     rbx
    ret
