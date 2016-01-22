#ifndef __VIRTUAL_MEMORY_MANAGEMENT__4KB_TRANSLATION__
#define __VIRTUAL_MEMORY_MANAGEMENT__4KB_TRANSLATION__

#include "paging_structs.hpp"
#include "../vmm_temp.hpp"
#include "../../std/data_types.hpp"
#include "../../system/pre_mm.hpp"

#define INIT_PML4 0x1000
#define INIT_PDPT 0x2000
#define INIT_PDT  0x3000
#define INIT_PT   0x4000

namespace kernel
{

class System;

namespace memory
{

class StandardVirtualMemoryManager : public VMMTemplate
{
public:
    ~StandardVirtualMemoryManager();

    static inline VMMTemplate *Init();

    void *AllocatePage(bool writable, bool supervisor, bool executable, void *physical_address);
    void *AllocatePages(size_t number_of_pages);
    void FreePage(void *virtual_address);
    void FreePages(void *virtual_address, size_t number_of_pages);

    bool MapPage(ulong physical_address, ulong virtual_address, ulong additional_flag = memory::PT_WRITABLE);
    bool MapPages(ulong physical_address, ulong virtual_address, size_t memory_size, ulong additional_flag = memory::PT_WRITABLE);
    bool UnmapPage(ulong virtual_address);
    bool UnmapPages(ulong virtual_address, size_t memory_size);

    memory::PML4Entry *FindFreePML4Entry();
    memory::PDPTEntry *FindFreePDPTEntry();
    memory::PDTEntry  *FindFreePDTEntry();
    memory::PTEntry   *FindFreePTEntry();

protected:
    StandardVirtualMemoryManager();

private:
    memory::PML4 *current_pml4 ;
    memory::PDPT *current_pdpt;
    memory::PDT  *current_pdt;
    memory::PT   *current_pt;

    System &system;
};
typedef class StandardVirtualMemoryManager StandardVMM;

static char vmm_reserved[sizeof(StandardVirtualMemoryManager)];


// ~ StandardVirtualMemoryManager

VMMTemplate *StandardVirtualMemoryManager::Init()
{
    return new (vmm_reserved) StandardVirtualMemoryManager();
}

}
}

#endif //__VIRTUAL_MEMORY_MANAGEMENT__4KB_TRANSLATION__
