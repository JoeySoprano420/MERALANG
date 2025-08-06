; utils.asm
print_hello:
    mov rdi, message
    call print_string
    ret

print_string:
    ; Assume syscall to write string
    ret

message db "Hello, MeraLang World!", 0

init:
    ; Initialization code here
    ret

exit_process:
    mov rdi, 0
    call ExitProcess
