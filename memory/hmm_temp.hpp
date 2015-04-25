#ifndef __HEAP_MEMORY_TEMPLATES__
#define __HEAP_MEMORY_TEMPLATES__

#include "../std/data_types.hpp"
#include "../system/error_codes.hpp"

namespace kernel
{
namespace memory
{

struct HeapMemoryTemplate
{
    ulong heap_start_address;
    size_t heap_memory_size;
    uint heap_access_rights;
    size_t heap_memory_in_use;

    inline HeapMemoryTemplate(ulong start_address, size_t memory_size, uint access_rights);
};
typedef class HeapMemoryTemplate HeapTemplate;

class HeapMemoryManagerTemplate
{
public:
    virtual void *AllocateMemory(size_t memory_size) = 0;
    virtual void FreeMemory(void *memory_address) = 0;

    virtual inline HeapTemplate *CreateHeap();
    virtual inline HeapTemplate *CreateHeap(size_t memory_size);
    virtual HeapTemplate *CreateHeap(ulong physical_address, ulong virtual_address, size_t memory_size) = 0;
    virtual bool SwitchUsedHeap(HeapTemplate *new_used_heap) = 0;
    virtual void FreeHeap(HeapTemplate *heap) = 0;
};
typedef class HeapMemoryManagerTemplate HMMTemplate;

// ~ HeapMemoryTemplate

HeapMemoryTemplate::HeapMemoryTemplate(ulong start_address, size_t memory_size, uint access_rights) : heap_start_address(start_address), heap_memory_size(memory_size), heap_access_rights(access_rights), heap_memory_in_use(0) {}

HeapTemplate *HeapMemoryManagerTemplate::CreateHeap()
{
    return CreateHeap(0, 0, 0x1000);
}

HeapTemplate *HeapMemoryManagerTemplate::CreateHeap(size_t memory_size)
{
    return CreateHeap(0, 0, memory_size);
}

}
}


#endif
