
;KERNEL_VIRTUAL_BASE equ 0xFFFFFFFFF0000000

bits 16
section .ap_init
global boot_ap
global boot_ap_end
;global ap_number

extern load_gdt

ap_number db 0

boot_ap:
    cli

    xor ax, ax
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    cld

    mov eax, gdt_selector
    call load_gdt

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp dword 0x8:(back_in_pmode)

gdt_selector:
    dw (gdt_end - gdt) - 1
    dd gdt

boot_ap_end:
    hlt
    jmp boot_ap_end

bits 32
back_in_pmode:
    nop
    jmp back_in_pmode

gdt:
    .pointer:                    ; The GDT-pointer.
;	dw (gdt_end - gdt) - 1		   ; Limit.
    dq gdt

    .null: equ $ - gdt	        ; The null descriptor.
    dd 0
    dd 0

    .code: equ $ - gdt	        ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011000b                 ; Access.
    db 00100000b                 ; Granularity.
    db 0                         ; Base (high).

    .data: equ $ - gdt	        ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010000b                 ; Access.
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).

;align 4

gdt_end:


