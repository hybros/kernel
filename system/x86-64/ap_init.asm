bits 16
section .ap_init

ap_init:
	xor ax, ax
	mov ss, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	cld

	lgdt [gdt]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	jmp gdt.code:back_in_pmode

bits 32
back_in_pmode:
	nop

gdt:
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

align 4
    .pointer:                    ; The GDT-pointer.
    dw $ - gdt - 1		        ; Limit.
    dd gdt


