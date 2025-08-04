; MeraLang → NASM Mapping (All Commands, Constructs, Features)

; === Data Section ===
section .data
    msg db "Hello, {name}", 0
    mem_buffer times 1024 db 0

; === Text Section ===
section .text
    global _start

_start:
    ; val x = 5
    mov eax, 5

    ; val sum = a + b (derive sum from a by b)
    mov eax, [a]
    add eax, [b]
    mov [sum], eax

    ; say "Hello"
    mov edi, 1          ; stdout
    mov rsi, msg        ; message
    mov edx, 14         ; length
    mov eax, 1          ; sys_write
    syscall

    ; try / catch / rewind stub
    call risky_op
    jnc .continue
.catch:
    call rewind_capsule
    jmp .exit
.continue:
    ; loop i from 0 to 10
    xor ecx, ecx
.loop:
    cmp ecx, 10
    jge .done
    ; loop body
    inc ecx
    jmp .loop
.done:

.exit:
    mov eax, 60         ; sys_exit
    xor edi, edi
    syscall
