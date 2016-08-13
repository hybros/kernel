#ifndef __HEAP_MEMORY_TEMPLATES__
#define __HEAP_MEMORY_TEMPLATES__

#include <HSystemManager>

namespace Hybros
{
namespace HeapMemory
{

struct HeapBase
{
    ulong heap_uid;
    size_t heap_memory_size;
    size_t heap_max_memory_size;
    ulong heap_access_rights;

    HeapBase() = default;
    HeapBase(size_t max_memory_size, uint access_rights) :
        heap_uid(0xF0F0F0F0F0F0F0F0),
        heap_memory_size(0),
        heap_max_memory_size(max_memory_size),
        heap_access_rights(access_rights)
    {
    }
    virtual ~HeapBase() = default;
};

class Manager : public System::Manager
{
public:
    Manager() :
        System::Manager(HSystem::Manager::HEAP_MEMORY_MANAGER)
    {
    }
    ~Manager()
    {
        setStatus(false);
    }

    virtual void *allocateMemory(size_t memory_size) = 0;
    virtual void freeMemory(void *memory_address) = 0;

    virtual auto createHeap() -> HeapBase *
    {
        return createHeap(0, 0, 0x1000);
    }
    virtual auto createHeap(size_t memory_size) -> HeapBase *
    {
        return createHeap(0, 0, memory_size);
    }

    virtual auto createHeap(ulong physical_address, ulong virtual_address, size_t memory_size) -> HHeapBase * = 0;
    virtual auto getHeap(ulong heap_uid) -> HeapBase & = 0;
    virtual auto switchUsedHeap(ulong new_used_heap_uid) -> bool = 0;
    virtual auto freeHeap(ulong heap_uid) -> bool = 0;
};


#endif
