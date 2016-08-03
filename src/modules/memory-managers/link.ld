ENTRY(minit)
OUTPUT(elf64_x86_64)

MODULE_VIRTUAL_BASE = 0xFFFFFFFFF0100000;		   /*0xFFFFFFFFF0000000 or 0xFFFFFFFFEFF00000*/

SECTIONS
{
	. = MODULE_VIRTUAL_BASE;

	module_start = .;

	.text ALIGN(0x1000) : AT(ADDR(.text) - MODULE_VIRTUAL_BASE)
	{
		*(.text)
		*(.gnu.linkonce.t*)
	}

	.data ALIGN(0x1000) : AT(ADDR(.data) - MODULE_VIRTUAL_BASE)
	{
		usable_space = .;
		. += 0x1000;

		*(.data)
		*(.gnu.linkonce.d*)
		*(.rodata*)
		*(.gnu.linkonce.r*)
	}

	.bss ALIGN(0x1000) : AT(ADDR(.bss) - MODULE_VIRTUAL_BASE)
	{
		*(COMMON)
		*(.bss)
		*(.gnu.linkonce.b*)
	}

	/DISCARD/ :
	{
		*(.comment)
		*(.eh_frame)
	}

	module_end = .;
}
