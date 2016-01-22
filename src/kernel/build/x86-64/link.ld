ENTRY(kinit);
OUTPUT(elf64_x86_64);

KERNEL_VIRTUAL_BASE = 0xFFFFFFFFF0000000;		   /*0xFFFFFFFFF0000000 or 0xFFFFFFFFEFF00000*/

SECTIONS
{
	. = 0x100000;                                    /*0x0000000000100000 */

	kernel_init_start = .;

	.init ALIGN(0x1000) :
	{
		*(.multiboot)
		*(.init)
                *(.ap_init)
	}

	kernel_init_end = .;

	. += KERNEL_VIRTUAL_BASE;

	kernel_main_start = .;

	.text ALIGN(0x1000) : AT(ADDR(.text) - KERNEL_VIRTUAL_BASE)
	{
		*(.text)
		*(.gnu.linkonce.t*)
	}

    .rodata ALIGN(0x1000) : AT(ADDR(.rodata) - KERNEL_VIRTUAL_BASE)
    {
        *(.rodata*)
		*(.gnu.linkonce.r*)
    }
	
	.data ALIGN(0x1000) : AT(ADDR(.data) - KERNEL_VIRTUAL_BASE)
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
		*(.metadata)
		*(.gnu.linkonce.d*)
	}
		
	.bss ALIGN(0x1000) : AT(ADDR(.bss) - KERNEL_VIRTUAL_BASE)
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

	kernel_main_end = .;
}
