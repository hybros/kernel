#ifndef __STANDARD_KERNEL_HEAP_IMPLEMENTATION__
#define __STANDARD_KERNEL_HEAP_IMPLEMENTATION__

#include "hmm_temp.hpp"
#include "../std/data_types.hpp"
#include "../std/bitmap.hpp"
#include "../std/list.hpp"
#include "../std/vector.hpp"
#include "../system/pre_mm.hpp"

namespace kernel
{

class System;

namespace memory
{

class StandardHeap;

struct StandardHeapChunk
{
    StandardHeap *chunk_parent;
    size_t chunk_size;
    char chunk_start[0];

    inline StandardHeapChunk(StandardHeap *parent_heap, size_t memory_size);
};

struct StandardHeap : public HeapTemplate, private std::List<StandardHeapChunk>
{
    inline StandardHeap(ulong start_address, size_t memory_size, uint access_rights = 0xFFFFFFFF);

    void *FindFreeMemory(size_t needed_memory_size);
};

}

namespace std
{

template<> void List<memory::StandardHeap*>::PushFirstElement(kernel::memory::StandardHeap * const &data);

}

namespace memory
{

class StandardHeapMemoryManager : public HeapMemoryManagerTemplate
{
public:
    StandardHeapMemoryManager(ulong physical_address, ulong virtual_address, size_t memory_size);
    ~StandardHeapMemoryManager();

    static inline HMMTemplate *Init(ulong physical_memory_address, ulong virtual_memory_address, size_t memory_size);

    void *AllocateMemory(size_t memory_size);
    void FreeMemory(void *memory_address);

    StandardHeap *CreateHeap(ulong physical_address, ulong virtual_address, size_t memory_size);
    bool SwitchUsedHeap(StandardHeap *new_current_heap);
    void FreeHeap(StandardHeap *old_heap);

    ErrorInfo &GetErrorInfo();

private:
    std::List<StandardHeap*> heaps;
    StandardHeap *kernel_heap;
    StandardHeap *current_heap;

    void *AllocateKernelMemory(size_t memory_size);
};

static char hmm_reserved[sizeof(StandardHeapMemoryManager)];

// ~ StandardHeapChunk

StandardHeapChunk::StandardHeapChunk(StandardHeap *parent_heap, size_t memory_size) : chunk_parent(parent_heap), chunk_size(memory_size) {}

// ~ StandardHeap

StandardHeap::StandardHeap(ulong start_address, size_t memory_size, uint access_rights) : HeapTemplate(start_address, memory_size, access_rights) {}

// ~ StandardHeapMemoryManager

HMMTemplate *StandardHeapMemoryManager::Init(ulong physical_memory_address, ulong virtual_memory_address, size_t memory_size)
{
    //return new (hmm_reserved) StandardHeapMemoryManager(physical_memory_address, virtual_memory_address, memory_size);
}

}
}

#endif //__STANDARD_KERNEL_HEAP_IMPLEMENTATION__
