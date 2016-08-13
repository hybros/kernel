#ifndef __VIRTUAL_MEMORY_MANAGEMENT__4KB_TRANSLATION__
#define __VIRTUAL_MEMORY_MANAGEMENT__4KB_TRANSLATION__

#include <HVirtualMemoryManager>

#include "../../include/pre_mm.hpp"

#define INIT_PML4 0x8000
#define INIT_PDPT 0x9000
#define INIT_PDT  0xA000
#define INIT_PT   0xB000

namespace Hybros
{

class HSystem::VirtualMemoryManager : public HVirtualMemoryManager
{
public:
    VirtualMemoryManager();
    ~VirtualMemoryManager() = default;

    auto getPageSize() const -> size_t;

    void *allocatePage(bool writable, bool supervisor, bool executable);
    void *allocatePages(ulong number_of_pages);
    void freePage(void *virtual_address);
    void freePages(void *virtual_address, ulong number_of_pages);

    bool mapPage(ulong physical_address, ulong virtual_address, ulong additional_flag = PTEntry::WRITABLE);
    bool mapPages(ulong physical_address, ulong virtual_address, size_t memory_size, ulong additional_flag = PTEntry::WRITABLE);
    auto unmapPage(ulong virtual_address) -> bool;
    auto unmapPages(ulong virtual_address, ulong memory_size) -> bool;

    PML4Entry *findFreePML4Entry();
    PDPTEntry *findFreePDPTEntry();
    PDTEntry  *findFreePDTEntry();
    PTEntry   *findFreePTEntry();

protected:
    auto mapBeginningPage(ulong physical_address, ulong virtual_address) -> uint;

    auto roundDownToPrevPage(size_t memory) const -> ulong;
    auto roundUpToNextPage(size_t memory) const -> ulong;
    auto roundUpToNextPageNumber(size_t memory) const -> ulong;

private:
    PML4 *current_pml4 ;
    PDPT *current_pdpt;
    PDT  *current_pdt;
    PT   *current_pt;
};

}

#endif //__VIRTUAL_MEMORY_MANAGEMENT__4KB_TRANSLATION__
