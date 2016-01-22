bits 32
section .init
global kinit
global load_gdt
extern KERNEL_VIRTUAL_BASE, tmp_stack
extern check_cpuid, check_x64_compatibility, setup_x64
extern load_gdt
extern kernel_stack

MULTIBOOT_MAGIC_BUFFER equ 0x6000
MULTIBOOT_INFO_BUFFER  equ 0x6008

kinit:
    mov esp, tmp_stack

    mov dword [MULTIBOOT_MAGIC_BUFFER], eax
    mov dword [MULTIBOOT_INFO_BUFFER], ebx

    call check_cpuid
    cmp eax, 1
    jne .error

    call check_x64_compatibility
    cmp eax, 1
    jne .error

    call setup_x64

    mov eax, gdt64.pointer
    call load_gdt

    jmp gdt64.code:yeah_here_we_go

.error:
    mov byte [0xB8000], 'E'
    mov byte [0xB8001], 0xE | 0 << 4 ; background black, foreground yellow
    mov byte [0xB8002], 'R'
    mov byte [0xB8003], 0xE | 0 << 4
    mov byte [0xB8004], 'R'
    mov byte [0xB8005], 0xE | 0 << 4
    mov byte [0xB8006], 'O'
    mov byte [0xB8007], 0xE | 0 << 4
    mov byte [0xB8008], 'R'
    mov byte [0xB8009], 0xE | 0 << 4
    mov byte [0xB800A], '!'
    mov byte [0xB800B], 0xE | 0 << 4

.game_over:
    cli
    hlt
    jmp .game_over

bits 64
yeah_here_we_go:
    cli                           ; Clear the interrupt flags

    lea rcx, [last_jump]
    jmp rcx

last_jump:
    call kentry

gdt64:
    .null: equ $ - gdt64         ; The null descriptor.
    dq 0

    .code: equ $ - gdt64         ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011000b                 ; Access.
    db 00100000b                 ; Granularity.
    db 0                         ; Base (high).

    .data: equ $ - gdt64         ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010000b                 ; Access.
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).

align 4
    dw 0
    .pointer:                    ; The GDT-pointer.
    dw $ - gdt64 - 1             ; Limit.
    dq gdt64

section .text
extern kmain
extern __cxa_finalize
global kentry

kentry:
    lea rsp, [rel kernel_stack]

    call kmain

    ;sub rsp, 8
    ;mov qword [rsp], qword 0x0
    ;call __cxa_finalize
    ;add rsp, 8

.end:
    cli
    hlt
    jmp .end
