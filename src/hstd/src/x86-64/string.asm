bits 64
section .text

global strlen

strlen:
	mov rax, 0
	test rdi, rdi					; Checks for a null pointer
	jz .end

.count_loop:
	mov al, [rdi]
	cmp al, '\0'
	je .end

	inc rax
	inc rdi
	jmp .count_loop

.end:
	ret
