#ifndef __VIRTUAL_MEMORY_MANAGEMENT__4KB_TRANSLATION__
#define __VIRTUAL_MEMORY_MANAGEMENT__4KB_TRANSLATION__

#include <HVirtualMemoryManager>

#include "../../include/pre_mm.hpp"

#define INIT_PML4 0x8000
#define INIT_PDPT 0x9000
#define INIT_PDT  0xA000
#define INIT_PT   0xB000

class HSystem::VirtualMemoryManager : public HVirtualMemoryManager
{
public:
    VirtualMemoryManager();
    ~VirtualMemoryManager() = default;

    auto GetPageSize() const -> size_t;

    void *AllocatePage(bool writable, bool supervisor, bool executable);
    void *AllocatePages(ulong number_of_pages);
    void FreePage(void *virtual_address);
    void FreePages(void *virtual_address, ulong number_of_pages);

    bool MapPage(ulong physical_address, ulong virtual_address, ulong additional_flag = PTEntry::WRITABLE);
    bool MapPages(ulong physical_address, ulong virtual_address, size_t memory_size, ulong additional_flag = PTEntry::WRITABLE);
    auto UnmapPage(ulong virtual_address) -> bool;
    auto UnmapPages(ulong virtual_address, ulong memory_size) -> bool;

    PML4Entry *FindFreePML4Entry();
    PDPTEntry *FindFreePDPTEntry();
    PDTEntry  *FindFreePDTEntry();
    PTEntry   *FindFreePTEntry();

protected:
    auto MapBeginningPage(ulong physical_address, ulong virtual_address) -> uint;

    auto RoundDownToPrevPage(size_t memory) const -> ulong;
    auto RoundUpToNextPage(size_t memory) const -> ulong;
    auto RoundUpToNextPageNumber(size_t memory) const -> ulong;

private:
    PML4 *current_pml4 ;
    PDPT *current_pdpt;
    PDT  *current_pdt;
    PT   *current_pt;
};

#endif //__VIRTUAL_MEMORY_MANAGEMENT__4KB_TRANSLATION__
