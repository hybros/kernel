#ifndef __VIRTUAL_MEMORY_TEMPLATES__
#define __VIRTUAL_MEMORY_TEMPLATES__

#include <HSystemManager>

class HVirtualMemoryManager : public HSystem::Manager
{
public:
    inline HVirtualMemoryManager();

    virtual auto GetPageSize() const -> size_t = 0;

    virtual void *AllocatePage(bool writable, bool supervisor, bool executable) = 0;
    virtual void *AllocatePages(size_t number_of_pages) = 0;
    virtual void FreePage(void *virtual_address) = 0;
    virtual void FreePages(void *virtual_address, size_t number_of_pages) = 0;

    virtual bool MapPage(ulong physical_address, ulong virtual_address, ulong additional_flag) = 0;
    virtual bool MapPages(ulong physical_address, ulong virtual_address, size_t memory_size, ulong additional_flag) = 0;
    virtual bool UnmapPage(ulong virtual_address) = 0;
    virtual bool UnmapPages(ulong virtual_address, size_t memory_size) = 0;
};


#endif
