#ifndef __VIRTUAL_MEMORY_TEMPLATES__
#define __VIRTUAL_MEMORY_TEMPLATES__

#include "../std/data_types.hpp"
#include "../system/error_codes.hpp"

namespace kernel
{
namespace memory
{

class VirtualMemoryManagerTemplate
{
public:
    virtual inline void *AllocatePage(void *physical_address = nullptr);
    virtual inline void *AllocatePage(bool writable, void *physical_address = nullptr);
    virtual inline void *AllocatePage(bool writable, bool supervisor, void *physical_address = nullptr);
    virtual void *AllocatePage(bool writable, bool supervisor, bool executable, void *physical_address = nullptr) = 0;
    virtual void *AllocatePages(size_t number_of_pages) = 0;
    virtual void FreePage(void *virtual_address) = 0;
    virtual void FreePages(void *virtual_address, size_t number_of_pages) = 0;

    virtual inline bool MapPage(ulong same_address, ulong additional_flag);                                 // Same address for physical and virtual memory
    virtual bool MapPage(ulong physical_address, ulong virtual_address, ulong additional_flag) = 0;
    virtual inline bool MapPages(ulong same_address, size_t memory_size, ulong additional_flag);
    virtual bool MapPages(ulong physical_address, ulong virtual_address, size_t memory_size, ulong additional_flag) = 0;
    virtual bool UnmapPage(ulong virtual_address) = 0;
    virtual bool UnmapPages(ulong virtual_address, size_t memory_size) = 0;
};

typedef class VirtualMemoryManagerTemplate VMMTemplate;

// ~ VirtualMemoryManagementTemplate

void *VirtualMemoryManagerTemplate::AllocatePage(void *physical_address)
{
    return AllocatePage(true, true, true, physical_address);
}

void *VirtualMemoryManagerTemplate::AllocatePage(bool writable, void *physical_address)
{
    return AllocatePage(writable, true, true, physical_address);
}

void *VirtualMemoryManagerTemplate::AllocatePage(bool writable, bool supervisor, void *physical_address)
{
    return AllocatePage(writable, supervisor, true, physical_address);
}

bool VirtualMemoryManagerTemplate::MapPage(ulong same_address, ulong additional_flag)
{
    return MapPage(same_address, same_address, additional_flag);
}

bool VirtualMemoryManagerTemplate::MapPages(ulong same_address, size_t memory_size, ulong additional_flag)
{
    return MapPages(same_address, same_address, memory_size, additional_flag);
}

}
}

#endif
