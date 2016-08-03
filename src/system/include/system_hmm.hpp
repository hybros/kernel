#ifndef __STANDARD_KERNEL_HEAP_IMPLEMENTATION__
#define __STANDARD_KERNEL_HEAP_IMPLEMENTATION__

#include <HBitmap>
#include <HList>
#include <HVector>
#include <HHeapMemoryManager>

class HSystemHeap;
class HSystemHeapChunk;

struct HSystemHeapChunk
{
    HSystemHeapChunk *chunk_prev;
    HSystemHeapChunk *chunk_next;
    size_t chunk_size;

    HSystemHeapChunk() = default;
    HSystemHeapChunk(HSystemHeapChunk *prev, HSystemHeapChunk *next, size_t size);
};

struct HSystemHeap : public HHeapBase
{
    HSystemHeap() = default;
    HSystemHeap(size_t max_memory_size, uint access_rights = 0xFFFFFFFF);
};

class HSystem::HeapMemoryManager : public HHeapMemoryManager, HVector<HSystemHeap *>
{
public:
    HeapMemoryManager(ulong physical_memory_address, ulong virtual_memory_address, size_t max_memory_size);
    ~HeapMemoryManager();

    auto AllocateMemory(size_t memory_size) -> void *;
    void FreeMemory(void *memory_address);

    auto CreateHeap(ulong physical_address, ulong virtual_address, size_t max_memory_size) -> HHeapBase *;
    auto GetHeap(ulong heap_uid) -> HHeapBase &;
    auto SwitchUsedHeap(ulong heap_uid) -> bool;
    auto FreeHeap(ulong heap_uid) -> bool;

protected:
    auto GetHeapPosition(ulong heap_uid) -> uint;

    auto AddHeap(ulong heap_address, size_t max_memory_size) -> HSystemHeap *;
    auto AddChunk(HSystemHeapChunk *prev, size_t memory_size) -> HSystemHeapChunk *;

    auto FreeChunk(HSystemHeapChunk *chunk) -> bool;

    auto RoundUpToNextPage(ulong memory_size) const -> ulong;
    auto RoundUpToNextBoundary(ulong memory_size) const -> ulong;

    auto ReturnAddress(HSystemHeapChunk *used_chunk) -> void *;

private:
    HSystemHeap *hmm_kernel_heap;
    HSystemHeap *hmm_current_heap;
};


#endif //__STANDARD_KERNEL_HEAP_IMPLEMENTATION__
