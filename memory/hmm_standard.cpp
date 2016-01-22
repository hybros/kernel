#include "hmm_standard.hpp"
#include "../system/system.hpp"
#include "../std/helper.hpp"

// ~ List<StandardHeapChunk>

template<>
void kernel::std::List<kernel::memory::StandardHeapChunk>::PushLastElement(const kernel::memory::StandardHeapChunk &data)
{
    memory::StandardHeap *parent_heap = data.chunk_parent;
    Node *new_last = new (VAR_TO_PTR(parent_heap->heap_start_address + parent_heap->heap_memory_in_use)) Node(data, list_count, list_last, nullptr);
    list_last->node_next = new_last;
    list_last = new_last;
    list_size += sizeof(Node);
    list_count++;
}

// ~ List<StandardHeap>

template<>
void kernel::std::List<kernel::memory::StandardHeap*>::PushFirstElement(kernel::memory::StandardHeap * const &data)
{
    static Node new_first(data, 0, nullptr, list_first);
    list_first = &new_first;
    list_size += sizeof(Node);
    list_count++;
//  UpdatePosition(list_first->node_next, false);
}

using namespace kernel::memory;
// ~ StandardHeap

void *StandardHeap::FindFreeMemory(size_t needed_memory_size)
{
    Node *current_node = list_first, *next_node = nullptr;
    ulong current_node_end_address = 0;
    while(current_node != list_last)
    {
        next_node = current_node->node_next;
        current_node_end_address = reinterpret_cast<ulong>(current_node + sizeof(Node) + current_node->node_data.chunk_size);
        if(current_node_end_address < next_node && (reinterpret_cast<ulong>(next_node) - current_node_end_address) >= (sizeof(Node) + needed_memory_size))
            return reinterpret_cast<void*>(current_node_end_address);
    }
    return nullptr;
}

// ~ StandardHeapMemoryManager

StandardHeapMemoryManager::StandardHeapMemoryManager(ulong physical_address, ulong virtual_address, size_t memory_size)
{
    if(physical_address && virtual_address && memory_size)
    {
        SYSTEM.InitRegion(physical_address, memory_size);
        SYSTEM.MapPages(physical_address, virtual_address, memory_size);

        kernel_heap = current_heap = new (VAR_TO_PTR(virtual_address)) StandardHeap(virtual_address + sizeof(StandardHeap), memory_size);
        heaps.PushFirstElement(kernel_heap);
    }
}

StandardHeap *StandardHeapMemoryManager::CreateHeap(ulong physical_address, ulong virtual_address, size_t memory_size)
{
    StandardHeap *new_heap = nullptr;
    if(physical_address && virtual_address)
    {
        SYSTEM.InitRegion(physical_address, memory_size);
        SYSTEM.MapPages(physical_address, virtual_address, memory_size);

        if(memory_size == 0)
            memory_size = 0x1000;

        new_heap = new (VAR_TO_PTR(virtual_address)) StandardHeap(virtual_address + sizeof(StandardHeap), memory_size);
    }
    else
    {
        void *new_heap_base = SYSTEM.AllocatePage();

        if(memory_size == 0)
            memory_size = 0x1000;

        new_heap = new (new_heap_base) StandardHeap(PTR_TO_VAR(new_heap_base) + sizeof(StandardHeap), memory_size);
    }

    heaps.PushLastElement(new_heap);
    return new_heap;
}

bool StandardHeapMemoryManager::SwitchUsedHeap(StandardHeap *new_current_heap)
{
    if(heaps.IsPresent(new_current_heap) == true)
    {
        current_heap = new_current_heap;
        return true;
    }
    else
        return false;
}

void StandardHeapMemoryManager::FreeHeap(StandardHeap *old_heap)
{
    heaps.RemoveElement(old_heap);
}

void *StandardHeapMemoryManager::AllocateMemory(size_t memory_size)
{
    if(current_heap->heap_memory_in_use < memory_size)
        return nullptr;

    StandardHeapChunk new_chunk(current_heap, memory_size);
    StandardHeapChunk *chunk_pointer = current_heap->FindUnusedChunk(memory_size);
    if(chunk_pointer != nullptr)
    {
        memcpy(chunk_pointer, &new_chunk, sizeof(StandardHeapChunk));
        return chunk_pointer->chunk_start;
    }

    ulong new_chunk_address = current_heap->heap_start_address + current_heap->GetLastElement().chunk_size;
    current_heap->PushLastElement(new_chunk);
    current_heap->heap_memory_in_use += memory_size + current_heap->GetNodeSize();

    return VAR_TO_PTR(new_chunk_address + current_heap->GetNodeSize());
}

void StandardHeapMemoryManager::FreeMemory(void *memory_address)
{
    StandardHeapChunk *heap_chunk = reinterpret_cast<StandardHeapChunk*>(PTR_TO_VAR(memory_address) - heap_chunk->chunk_parent->GetNodeSize());
    heap_chunk->chunk_parent->RemoveElement(*heap_chunk);
}

kernel::ErrorInfo &StandardHeapMemoryManager::GetErrorInfo()
{
    ErrorInfo error;
    return error;
}
