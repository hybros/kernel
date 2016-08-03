#ifndef __HEAP_MEMORY_TEMPLATES__
#define __HEAP_MEMORY_TEMPLATES__

#include <HSystemManager>

struct HHeapBase
{
    ulong heap_uid;
    size_t heap_memory_size;
    size_t heap_max_memory_size;
    ulong heap_access_rights;

    HHeapBase() = default;
    inline HHeapBase(size_t max_memory_size, uint access_rights);
    virtual ~HHeapBase() = default;
};

class HHeapMemoryManager : public HSystem::Manager
{
public:
    inline HHeapMemoryManager();
    inline ~HHeapMemoryManager();

    virtual void *AllocateMemory(size_t memory_size) = 0;
    virtual void FreeMemory(void *memory_address) = 0;

    virtual inline auto CreateHeap() -> HHeapBase *;
    virtual inline auto CreateHeap(size_t memory_size) -> HHeapBase *;
    virtual auto CreateHeap(ulong physical_address, ulong virtual_address, size_t memory_size) -> HHeapBase * = 0;
    virtual auto GetHeap(ulong heap_uid) -> HHeapBase & = 0;
    virtual auto SwitchUsedHeap(ulong new_used_heap_uid) -> bool = 0;
    virtual auto FreeHeap(ulong heap_uid) -> bool = 0;
};


#endif
