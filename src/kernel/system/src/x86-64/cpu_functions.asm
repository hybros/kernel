bits 32
section .init
global load_gdt

load_gdt:
	lgdt [eax]
	mov ax, 0x10                    ; Set the A-register to the data descriptor.
	mov ds, ax                      ; Set the data segment to the A-register.
	mov es, ax                      ; Set the extra segment to the A-register.
	mov fs, ax                      ; Set the F-segment to the A-register.
	mov gs, ax                      ; Set the G-segment to the A-register.
	ret

bits 64
section .text
global enable_sse2

enable_sse2:
	mov rax, cr0
	and rax, ~(1 << 4)
	or rax, 1 << 1
	mov cr0, rax

	mov rax, cr4
	or rax, 3 << 9
	mov cr4, rax
	ret

section .data
global system_sse2_support
global system_avx_support

system_sse2_support db 0
system_avx_support db 0
