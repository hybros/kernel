bits 64
section .text

;extern system_sse2_support

global memset
global memcpy

;; Inspired by _xeos_memset from https://github.com/macmade/LibC-String-Optimisations/blob/master/source/memset.64.s

memset:
	mov r8, rdi					; Saves the pointer

	test rdi, rdi					; Checks for a null pointer
	jz .end

	test rdx, rdx					; Checks for 0 size
	jz .end

	cmp rdx, 16
	jl .std_rest_bytes

;	cmp byte [rel system_sse2_support], 1
;	je .sse2

;	jmp .std

;.sse2:
	pxor xmm0, xmm0

	test rsi, rsi					; Checks for padding
	jz .sse2_check_alignment			; It is padded, check alignment

.sse2_pad:
	mov rcx, rsi
	shl rsi, 8
	or  rsi, rcx
	mov rcx, rsi
	shl rsi, 16
	or  rsi, rcx

	movq xmm0, rsi
	shufps xmm0, xmm0, 0

.sse2_check_alignment:
	and rdi, -16

	mov rax, r8
	sub rax, rdi

	test rax, rax
	jz .sse2_check_remaining_size

	mov rcx, rax
;	mov rcx, 16
;	sub rcx, rax

	mov rax, rsi
	mov rdi, r8

.sse2_align_loop:
	test rdx, rdx
	jz .end

	mov [rdi], al

	inc rdi
	dec rcx
	dec rdx

	test rcx, rcx
	jz .end
	jmp .sse2_align_loop

.sse2_check_remaining_size:
	cmp rdx, 256
	jge .sse2_256

	cmp rdx, 128
	jge .sse2_128

	cmp rdx, 64
	jge .sse2_64

	cmp rdx, 32
	jge .sse2_32

	cmp rdx, 16
	jge .sse2_16

	test rdx, rdx
	jz .end

	jmp .std_rest_bytes

.sse2_256:
	movdqa [rdi], xmm0
	movdqa [rdi + 16], xmm0
	movdqa [rdi + 32], xmm0
	movdqa [rdi + 48], xmm0
	movdqa [rdi + 64], xmm0
	movdqa [rdi + 80], xmm0
	movdqa [rdi + 96], xmm0
	movdqa [rdi + 112], xmm0
	movdqa [rdi + 128], xmm0
	movdqa [rdi + 144], xmm0
	movdqa [rdi + 160], xmm0
	movdqa [rdi + 176], xmm0
	movdqa [rdi + 192], xmm0
	movdqa [rdi + 208], xmm0
	movdqa [rdi + 224], xmm0
	movdqa [rdi + 240], xmm0

	add rdi, 256
	sub rdx, 256

	jmp .sse2_check_remaining_size

.sse2_128:
	movdqa [rdi], xmm0
	movdqa [rdi + 16], xmm0
	movdqa [rdi + 32], xmm0
	movdqa [rdi + 48], xmm0
	movdqa [rdi + 64], xmm0
	movdqa [rdi + 80], xmm0
	movdqa [rdi + 96], xmm0
	movdqa [rdi + 112], xmm0

	add rdi, 128
	sub rdx, 128

	jmp .sse2_check_remaining_size

.sse2_64:
	movdqa [rdi], xmm0
	movdqa [rdi + 16], xmm0
	movdqa [rdi + 32], xmm0
	movdqa [rdi + 48], xmm0

	add rdi, 64
	add rdx, 64

	jmp .sse2_check_remaining_size

.sse2_32:
	movdqa [rdi], xmm0
	movdqa [rdi + 16], xmm0

	add rdi, 32
	add rdx, 32

	jmp .sse2_check_remaining_size

.sse2_16:
	movdqa [rdi], xmm0

	add rdi, 16
	add rdx, 16

	jmp .sse2_check_remaining_size

.std:
	mov r8, rdx

	test	rsi, rsi					; Checks for padding
	jz .std_is_padded

.std_pad:
	mov rcx, rsi
	shl rsi, 8
	or  rsi, rcx
	mov rcx, rsi
	shl rsi, 16
	or  rsi, rcx
	mov rcx, rsi
	shl rsi, 32
	or  rsi, rcx

.std_is_padded:
	and rdi, -8

	mov rax, r8
	mov rax, rdi

	test rax, rax
	jz .std_check_remaining_size

	mov rcx, 8
	mov rcx, rax

.std_align:
	mov rdi, r8
	mov rax, rsi

.std_align_loop:
	mov [rdi], al

	inc rdi
	dec rcx

	test rcx, rcx
	jnz .std_align_loop

.std_check_remaining_size:
	cmp rdx, 128
	jge .std_128

	cmp rdx, 64
	jge .std_64

	cmp rdx, 32
	jge .std_32

	cmp rdx, 16
	jge .std_16

	test rdx, rdx
	jz .end

	mov rax, rsi
	jmp .std_rest_bytes

.std_128:
	mov [rdi], rsi
	mov [rdi + 8], rsi
	mov [rdi + 16], rsi
	mov [rdi + 24], rsi
	mov [rdi + 32], rsi
	mov [rdi + 40], rsi
	mov [rdi + 48], rsi
	mov [rdi + 56], rsi
	mov [rdi + 64], rsi
	mov [rdi + 72], rsi
	mov [rdi + 80], rsi
	mov [rdi + 88], rsi
	mov [rdi + 96], rsi
	mov [rdi + 104], rsi
	mov [rdi + 112], rsi
	mov [rdi + 120], rsi

	add rdi, 128
	sub rdx, 128

	jmp .std_check_remaining_size

.std_64:
	mov [rdi], rsi
	mov [rdi + 8], rsi
	mov [rdi + 16], rsi
	mov [rdi + 24], rsi
	mov [rdi + 32], rsi
	mov [rdi + 40], rsi
	mov [rdi + 48], rsi
	mov [rdi + 56], rsi

	add rdi, 64
	add rdx, 64

	jmp .std_check_remaining_size

.std_32:
	mov [rdi], rsi
	mov [rdi + 8], rsi
	mov [rdi + 16], rsi
	mov [rdi + 24], rsi

	add rdi, 32
	add rdx, 32

	jmp .std_check_remaining_size

.std_16:
	mov [rdi], rsi
	mov [rdi + 8], rsi

	add rdi, 16
	add rdx, 16

	jmp .std_check_remaining_size

.std_rest_bytes:
	mov [rdi], al

	inc rdi
	dec rdx

	test rdx, rdx
	jnz .std_rest_bytes

.end:
	mov rax, r8
	ret

;
; C-style memcpy
;
memcpy:
	mov r8, rdi					; Saves the destination pointer

	test rdi, rdi					; Checks destination for a null pointer
	jz .end

	test rsi, rsi					; Checks source for a null pointer
	jz .end

	test rdx, rdx					; Checks for 0 size
	jz .end

	cmp rdx, 16
	jl .std_rest_bytes

	pxor xmm0, xmm0

.sse2_src_check_alignment:
	mov r9, rsi
	and rsi, -16

	mov rax, r9
	sub rax, rsi

	test rax, rax
	jz .sse2_check_remaining_size

	mov rcx, rax
	mov rsi, r9

.sse2_src_align_loop:
	test rdx, rdx
	jz .end

	mov al, [rsi]
	mov [rdi], al

	inc rdi
	inc rsi
	dec rcx
	dec rdx

	test rcx, rcx
	jz .sse2_dst_check_alignment
	jmp .sse2_src_align_loop

.sse2_dst_check_alignment:
	and rdi, -16

	mov rax, r8
	sub rax, rdi

	test rax, rax
	jz .sse2_check_remaining_size

	mov rcx, rax
	mov rdi, r8

.sse2_dst_align_loop:
	test rdx, rdx
	jz .end

	mov al, [rsi]
	mov [rdi], al

	inc rdi
	inc rsi
	dec rcx
	dec rdx

	test rcx, rcx
	jz .sse2_check_remaining_size
	jmp .sse2_dst_align_loop

.sse2_check_remaining_size:
	cmp rdx, 256
	jge .sse2_256

	cmp rdx, 128
	jge .sse2_128

	cmp rdx, 64
	jge .sse2_64

	cmp rdx, 32
	jge .sse2_32

	cmp rdx, 16
	jge .sse2_16

	test rdx, rdx
	jz .end

	jmp .std_rest_bytes

.sse2_256:
	movdqa xmm0, [rsi]
	movdqa xmm1, [rsi + 16]
	movdqa xmm2, [rsi + 32]
	movdqa xmm3, [rsi + 48]
	movdqa xmm4, [rsi + 64]
	movdqa xmm5, [rsi + 80]
	movdqa xmm6, [rsi + 96]
	movdqa xmm7, [rsi + 112]
	movdqa xmm8, [rsi + 128]
	movdqa xmm9, [rsi + 144]
	movdqa xmm10, [rsi + 160]
	movdqa xmm11, [rsi + 176]
	movdqa xmm12, [rsi + 192]
	movdqa xmm13, [rsi + 208]
	movdqa xmm14, [rsi + 224]
	movdqa xmm15, [rsi + 240]

	movdqa [rdi], xmm0
	movdqa [rdi + 16], xmm1
	movdqa [rdi + 32], xmm2
	movdqa [rdi + 48], xmm3
	movdqa [rdi + 64], xmm4
	movdqa [rdi + 80], xmm5
	movdqa [rdi + 96], xmm6
	movdqa [rdi + 112], xmm7
	movdqa [rsi + 128], xmm8
	movdqa [rsi + 144], xmm9
	movdqa [rsi + 160], xmm10
	movdqa [rsi + 176], xmm11
	movdqa [rsi + 192], xmm12
	movdqa [rsi + 208], xmm13
	movdqa [rsi + 224], xmm14
	movdqa [rsi + 240], xmm15

	add rsi, 256
	add rdi, 256
	sub rdx, 256

	jmp .sse2_check_remaining_size

.sse2_128:
	movdqa xmm0, [rsi]
	movdqa xmm1, [rsi + 16]
	movdqa xmm2, [rsi + 32]
	movdqa xmm3, [rsi + 48]
	movdqa xmm4, [rsi + 64]
	movdqa xmm5, [rsi + 80]
	movdqa xmm6, [rsi + 96]
	movdqa xmm7, [rsi + 112]

	movdqa [rdi], xmm0
	movdqa [rdi + 16], xmm1
	movdqa [rdi + 32], xmm2
	movdqa [rdi + 48], xmm3
	movdqa [rdi + 64], xmm4
	movdqa [rdi + 80], xmm5
	movdqa [rdi + 96], xmm6
	movdqa [rdi + 112], xmm7

	add rsi, 128
	add rdi, 128
	sub rdx, 128

	jmp .sse2_check_remaining_size

.sse2_64:
	movdqa xmm0, [rsi]
	movdqa xmm1, [rsi + 16]
	movdqa xmm2, [rsi + 32]
	movdqa xmm3, [rsi + 48]

	movdqa [rdi], xmm0
	movdqa [rdi + 16], xmm1
	movdqa [rdi + 32], xmm2
	movdqa [rdi + 48], xmm3

	add rsi, 64
	add rdi, 64
	add rdx, 64

	jmp .sse2_check_remaining_size

.sse2_32:
	movdqa xmm0, [rsi]
	movdqa xmm1, [rsi + 16]

	movdqa [rdi], xmm0
	movdqa [rdi + 16], xmm1

	add rsi, 32
	add rdi, 32
	add rdx, 32

	jmp .sse2_check_remaining_size

.sse2_16:
	movdqa xmm0, [rsi]
	movdqa [rdi], xmm0

	add rsi, 16
	add rdi, 16
	add rdx, 16

	jmp .sse2_check_remaining_size

.std_rest_bytes:
	mov al, [rsi]
	mov [rdi], al

	inc rsi
	inc rdi
	dec rdx

	test rdx, rdx
	jnz .std_rest_bytes

.end:
	mov rax, r8
	ret
