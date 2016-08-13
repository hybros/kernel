#ifndef __VIRTUAL_MEMORY_TEMPLATES__
#define __VIRTUAL_MEMORY_TEMPLATES__

#include <HSystemManager>

namespace Hybros
{
namespace VirtualMemory
{

class Manager : public System::Manager
{
public:
    Manager() : 
        System::Manager(HSystem::Manager::VIRTUAL_MEMORY_MANAGER)
    {
    }

    virtual auto getPageSize() const -> size_t = 0;

    virtual void *allocatePage(bool writable, bool supervisor, bool executable) = 0;
    virtual void *allocatePages(size_t number_of_pages) = 0;
    virtual void freePage(void *virtual_address) = 0;
    virtual void freePages(void *virtual_address, size_t number_of_pages) = 0;

    virtual bool mapPage(ulong physical_address, ulong virtual_address, ulong additional_flag) = 0;
    virtual bool mapPages(ulong physical_address, ulong virtual_address, size_t memory_size, ulong additional_flag) = 0;
    virtual bool unmapPage(ulong virtual_address) = 0;
    virtual bool unmapPages(ulong virtual_address, size_t memory_size) = 0;
};

}
}

#endif
