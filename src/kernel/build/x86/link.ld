ENTRY(entry)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
     . = 0x100000;                                    /*0x0000000000100000 */

	kernel_start = .;

	.text :
	{
		*(.multiboot)
		*(.text)
	}
	
	.data ALIGN(0x1000) :
	{
		__init_array = .;
		KEEP(*( .init_array ));
		KEEP(SORT_BY_NAME(*)( .init_array));
		__init_array_end = .;
		
		__fini_array = .;
		KEEP(*( .fini_array ));
		KEEP(SORT_BY_NAME(*)( .fini_array ));
		__fini_array_end = .;
		*(.data)
		*(.rodata*)
	}
		
	.bss ALIGN(0x1000) :
	{
		*(COMMON)
		*(.bss)
	}
	
	/DISCARD/ :
	{
		*(.comment)
		*(.eh_frame)
	}

	kernel_end = .;
}
