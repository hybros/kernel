bits 32
section .init
global check_cpuid
global check_x64_compatibility
global setup_x64

; Lower half
PML4   equ 0x1000
PDPT   equ 0x2000
PDT    equ 0x3000
PT     equ 0x4000

; Higher half
LAST_ENTRY   equ 0x0FF8     ; Higher half entry for PML4 and PDPT
HIGH_ENTRY   equ 0x0C00     ; Higher half entry for PDT

PAGE_PRESENT equ (1 << 0)
PAGE_WRITE   equ (1 << 1)
PAGE_GLOBAL  equ (1 << 8)

check_cpuid:
        pushfd                 ; Get
        pop eax
        mov ecx, eax           ; Save
        xor eax, 0x200000      ; Flip
        push eax               ; Set
        popfd
        pushfd                 ; And test
        pop eax
        xor eax, ecx           ; Mask changed bits
        shr eax, 21            ; Move bit 21 to bit 0
        and eax, 1             ; And mask others
        push ecx
        popfd                  ; Restore original flags
        ret

check_x64_compatibility:
        mov eax, 0x80000000
        cpuid
        cmp eax, 0x80000001
        jb .no_x64

        mov eax, 0x80000001    ; Set the A-register to 0x80000001.
        cpuid                  ; CPU identification.
        test edx, 1 << 29      ; Test if the LM-bit, which is bit 29, is set in the D-register.
        jz .no_x64             ; They aren't, there is no long mode.
        mov eax, 1
        ret

.no_x64:
        mov eax, 0
        ret

setup_x64:
        mov edx, PML4           ; Sores the address of the first PML4 in edx
        mov edi, edx            ; Stores the address of the memory to flush in edi
        xor eax, eax            ; Sets eax to 0 so that memory will be 0
        mov ecx, 4096           ; Stores size of the memory to flush
        rep stosd               ; Actually flushes

        mov edi, edx                                            ; Points edi to the PML4 again
        mov dword [edi], PDPT                                   ; Stores address of the PDPT in the first PML4 entry
        or  dword [edi], PAGE_PRESENT | PAGE_WRITE              ; Makes present and writeable
        mov dword [edi + LAST_ENTRY], PDPT                      ; Stores address of the PDPT in the last PML4 entry
        or  dword [edi + LAST_ENTRY], PAGE_PRESENT | PAGE_WRITE

        add edi, 0x1000                                         ; Points edi to the PDPT
        mov dword [edi], PDT                                    ; Stores address of the PDT in the first PDPT entry
        or  dword [edi], PAGE_PRESENT | PAGE_WRITE
        mov dword [edi + LAST_ENTRY], PDT                       ; Stores address of the PDT in the last PDPT entry
        or  dword [edi + LAST_ENTRY], PAGE_PRESENT | PAGE_WRITE

        add edi, 0x1000                                         ; Points edi to the PDT
        mov dword [edi], PT                                     ; Stores address of the PT in the first PDT entry
        or  dword [edi], PAGE_PRESENT | PAGE_WRITE
        mov dword [edi + HIGH_ENTRY], PT                        ; Stores address of the PT in the 384th PDT entry
        or  dword [edi + HIGH_ENTRY], PAGE_PRESENT | PAGE_WRITE

        add edi, 0x1000
        mov ecx, 512		; Number of entries to set
        mov eax, PAGE_PRESENT | PAGE_WRITE | PAGE_GLOBAL

.set_entry:		; Set the page entries
        mov dword [edi], eax  	; Set the page in the PT
        add eax, 0x1000		; Add 4096 for next page
        add edi, 8		; Add 8 for next PT entry
        loop .set_entry

.enable_pae:			; Enable PAE by setting the PAE bit (bit 5)
        mov eax, cr4
        or eax, 1 << 5
        mov cr4, eax

.set_paging_entry:	; Point CR3 at the PML4
        mov cr3, edx

.enable_long_mode:		; Enable Long Mode by setting the LM bit (bit 8)
        mov ecx, 0xC0000080
        rdmsr
        or eax, 1 << 8
        wrmsr

.enable_paging:			; Enable Paging by setting the PG bit (bit 31)
        mov eax, cr0
        or eax, 1 << 31
        mov cr0, eax

        ret
