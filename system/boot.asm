bits 32
section .multiboot

MULTIBOOT_PAGE_ALIGN   equ 1 << 0
MULTIBOOT_MEMORY_INFO  equ 1 << 1

MULTIBOOT_MAGIC     equ 0x1BADB002
MULTIBOOT_FLAGS     equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
MULTIBOOT_CHECKSUM  equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

align 4
multiboot_header:
	dd MULTIBOOT_MAGIC
	dd MULTIBOOT_FLAGS
	dd MULTIBOOT_CHECKSUM

MULTIBOOT2_MAGIC          equ 0xE85250F6
MULTIBOOT2_ARCHITECTURE   equ 0                                                               ; IA-32
MULTIBOOT2_HEADER_LENGTH  equ (multiboot2_header_end - multiboot2_header)
MULTIBOOT2_CHECKSUM       equ -(MULTIBOOT2_MAGIC + MULTIBOOT2_ARCHITECTURE + MULTIBOOT2_HEADER_LENGTH) 	

align 8
multiboot2_header:
	dd MULTIBOOT2_MAGIC 
	dd MULTIBOOT2_ARCHITECTURE
	dd MULTIBOOT2_HEADER_LENGTH
	dd MULTIBOOT2_CHECKSUM

	dw 0, 0
	dd 8
multiboot2_header_end:

section .bss
global kernel_stack

resb 0x1000
kernel_stack:
