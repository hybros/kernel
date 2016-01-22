#include "../include/system_hmm.hpp"

#include <HSystem>
#include <HStdHelper>

// ~ HSystemHeapChunk

HSystemHeapChunk::HSystemHeapChunk(HSystemHeapChunk *prev, HSystemHeapChunk *next, size_t size) :
    chunk_prev(prev),
    chunk_next(next),
    chunk_size(size)
{}

// ~ HSystemHeap

HSystemHeap::HSystemHeap(size_t max_memory_size, uint access_rights) :
    HHeapBase(max_memory_size, access_rights)
{}

// ~ HSystem::HeapMemoryManager

HSystem::HeapMemoryManager::HeapMemoryManager(ulong physical_address, ulong virtual_address, size_t max_memory_size)
{
    vector_buffer = reinterpret_cast<HSystemHeap **>(SYSTEM.AllocatePage(true, true, true));
    vector_capacity = PAGE_SIZE;

	/*SYSTEM << INFO << "HYBROS -> ~ HSystem::HeapMemoryManager: HeapMemoryManager()" << endl
				   << " - Vector: " << vector_buffer << endl;*/
    hmm_kernel_heap = reinterpret_cast<HSystemHeap *>(CreateHeap(physical_address, virtual_address, max_memory_size));
    /*SYSTEM << " - Kernel heap address: " << hmm_kernel_heap << endl;*/
}

auto HSystem::HeapMemoryManager::CreateHeap(ulong physical_address, ulong virtual_address, size_t max_memory_size) -> HHeapBase *
{
    if(physical_address && virtual_address)
    {
        SYSTEM.InitRegion(physical_address, max_memory_size);
        SYSTEM.MapPages(physical_address, virtual_address, max_memory_size, PTEntry::WRITABLE);
    }
    else
        virtual_address = reinterpret_cast<ulong>(SYSTEM.AllocatePage(true, true, false));

	/*SYSTEM << INFO << "HYBROS -> ~ HSystem::HeapMemoryManager: CreateHeap()"
		<< "            - Virtual address: " << virtual_address << " - Memory size: " << max_memory_size << endl;*/

    if(max_memory_size == 0)
        max_memory_size = 0x1000;

    HSystemHeap *new_heap = AddHeap(virtual_address, max_memory_size);
    if(new_heap != nullptr)
        hmm_current_heap = new_heap;

    return new_heap;
}

auto HSystem::HeapMemoryManager::GetHeap(ulong heap_uid) -> HHeapBase &
{
    uint position = GetHeapPosition(heap_uid);
    if(position != 0xFFFFFFFF)
        return *GetElement(position);
    else
    {
        HHeapBase heap;
        return heap;
    }
}

auto HSystem::HeapMemoryManager::SwitchUsedHeap(ulong heap_uid) -> bool
{
    uint position = GetHeapPosition(heap_uid);
    if(position != 0xFFFFFFFF)
    {
        hmm_current_heap = GetElement(position);
        return true;
    }
    else
        return false;
}

auto HSystem::HeapMemoryManager::FreeHeap(ulong heap_uid) -> bool
{
    uint position = GetHeapPosition(heap_uid);
    if(position != 0xFFFFFFFF)
    {
        EraseElement(position);
        return true;
    }
    else
        return false;
}

auto HSystem::HeapMemoryManager::AllocateMemory(size_t memory_size) -> void *
{
    // Align memory size to 16 byte boundary
    size_t aligned_size = RoundUpToNextBoundary(memory_size);

    // Checks if there is enough space left for the desired memory_size + sizeof(HSystemHeapChunk)
    if(hmm_current_heap->heap_max_memory_size <= (hmm_current_heap->heap_memory_size + sizeof(HSystemHeapChunk) + memory_size))
    {
        // Creates a new heap with size of 0x1000 or (if greater size is needed) with the memory_size rounded to the next page as size
        if(CreateHeap(0, 0, RoundUpToNextPage(memory_size)) == nullptr)
            return nullptr;

        // Initializes the first chunk
        HSystemHeapChunk *first_chunk = reinterpret_cast<HSystemHeapChunk *>(PTR_TO_VAR(hmm_current_heap) + sizeof(HSystemHeap));
        first_chunk->chunk_size = aligned_size;
        hmm_current_heap->heap_memory_size += (sizeof(HSystemHeapChunk) + aligned_size);
        return ReturnAddress(first_chunk);
    }

    // Checks if the first chunk of the current heap is not in use
    HSystemHeapChunk *current_chunk = reinterpret_cast<HSystemHeapChunk *>(PTR_TO_VAR(hmm_current_heap) + sizeof(HSystemHeap));
    if(current_chunk->chunk_size == 0)
    {
        current_chunk->chunk_size = aligned_size;
        hmm_current_heap->heap_memory_size += (sizeof(HSystemHeapChunk) + aligned_size);
        return ReturnAddress(current_chunk);
    }

    // Iterates through each chunk to find an unused one
    while(current_chunk->chunk_next != nullptr)
    {
        if(current_chunk->chunk_size == 0)
        {
            current_chunk->chunk_size = aligned_size;
            hmm_current_heap->heap_memory_size += (sizeof(HSystemHeapChunk) + aligned_size);
            return ReturnAddress(current_chunk);
        }

        current_chunk = current_chunk->chunk_next;
    }

    // No unused chunk found.. Time to create a new one
    HSystemHeapChunk *new_chunk = AddChunk(current_chunk, aligned_size);
    return ReturnAddress(new_chunk);
}

void HSystem::HeapMemoryManager::FreeMemory(void *memory_address)
{
    // Get the chunk header and free the memory
    HSystemHeapChunk *current_chunk = reinterpret_cast<HSystemHeapChunk *>(PTR_TO_VAR(memory_address) - sizeof(HSystemHeapChunk));
    SYSTEM << INFO << "HYBROS -> ~ HSystem::HeapMemoryManager: FreeMemory() - Chunk address: " << current_chunk << endl;
    FreeChunk(current_chunk);
}

auto HSystem::HeapMemoryManager::GetHeapPosition(ulong heap_uid) -> uint
{
    for(uint i = 0; i <= LastPosition(); i++)
    {
        if(vector_buffer[i]->heap_uid == heap_uid)
            return i;
    }
    return 0xFFFFFFFF;
}

auto HSystem::HeapMemoryManager::AddHeap(ulong heap_address, size_t max_memory_size) -> HSystemHeap *
{
    if(HasMaximumReached() == true)
    {
        SYSTEM << INFO << "HYBROS -> ~ HSystem::HeapMemoryManager: AddHeap() - Maximum reached: " << vector_capacity << endl;
        return nullptr;
    }

    HSystemHeap *new_heap = new (VAR_TO_PTR(heap_address)) HSystemHeap(max_memory_size);
    if(PushLastElement(new_heap) == true)
        return new_heap;
    else
        return nullptr;
}

auto HSystem::HeapMemoryManager::AddChunk(HSystemHeapChunk *prev, size_t memory_size) -> HSystemHeapChunk *
{
    HSystemHeapChunk *new_chunk = reinterpret_cast<HSystemHeapChunk *>(PTR_TO_VAR(prev) + sizeof(HSystemHeapChunk) + prev->chunk_size);
    /*SYSTEM << INFO << "HYBROS -> ~ HSystem::HeapMemoryManager: AddChunk()" << endl
		<< " - Chunk address: " << new_chunk << endl;*/
    new_chunk->chunk_prev = prev;
    new_chunk->chunk_next = nullptr;
    new_chunk->chunk_size = memory_size;
    prev->chunk_next = new_chunk;
    hmm_current_heap->heap_memory_size += (sizeof(HSystemHeapChunk) + memory_size);
    return new_chunk;
}

auto HSystem::HeapMemoryManager::FreeChunk(HSystemHeapChunk *chunk) -> bool
{
    // Save chunk size and mark chunk as unused
    size_t chunk_size = chunk->chunk_size;
    chunk->chunk_size = 0;

    // Connect chunks before and after the targeted on
    HSystemHeapChunk *prev_chunk = chunk->chunk_prev;
    HSystemHeapChunk *next_chunk = chunk->chunk_next;
    prev_chunk->chunk_next = next_chunk;
    next_chunk->chunk_prev = prev_chunk;

    // Iterate through the chunks to find the heap header
    HSystemHeapChunk *current_chunk = prev_chunk;
    while(current_chunk->chunk_prev != nullptr)
        current_chunk = current_chunk->chunk_prev;

    // Heap header found! Now shrink the heap_memory_size
    HSystemHeap *parent_heap = reinterpret_cast<HSystemHeap *>(PTR_TO_VAR(current_chunk) - sizeof(HSystemHeap));
    SYSTEM << INFO << "HYBROS -> ~ HSystem::HeapMemoryManager: FreeChunk() - Heap address: " << parent_heap << endl;
    parent_heap->heap_memory_size -= (sizeof(HSystemHeapChunk) + chunk_size);
}

auto HSystem::HeapMemoryManager::RoundUpToNextPage(ulong memory_size) const -> ulong
{
    int remainder = memory_size % PAGE_SIZE;
    return (memory_size + PAGE_SIZE - remainder);
}

auto HSystem::HeapMemoryManager::RoundUpToNextBoundary(ulong memory_size) const -> ulong
{
    int remainder = memory_size % 0x10;
    return (memory_size + 0x10 - remainder);
}

auto HSystem::HeapMemoryManager::ReturnAddress(HSystemHeapChunk *used_chunk) -> void *
{
    return reinterpret_cast<void *>(PTR_TO_VAR(&used_chunk->chunk_size) + sizeof(ulong));
}
