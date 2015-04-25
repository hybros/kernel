#ifndef __SYSTEM_FUNCTIONS__
#define __SYSTEM_FUNCTIONS__

#include "../std/data_types.hpp"

namespace kernel
{
namespace memory
{

class HeapMemoryTemplate;

}

class Terminal;

union SystemFunctionsAddress
{
    void *(*AllocateBlock)();
    void *(*AllocateBlocks)(size_t number_of_blocks);
    void (*FreeBlock)(void* memory_address);
    void (*FreeBlocks)(void* memory_address, size_t number_of_blocks);

    void (*InitRegion)(ulong base, size_t size);
    void (*DeinitRegion)(ulong base, size_t size);

    void *(*AllocatePage)(bool writable, bool supervisor, bool executable);
    void *(*AllocatePages)(size_t number_of_pages);
    void (*FreePage)(void *virtual_address);
    void (*FreePages)(void *virtual_address, size_t number_of_pages);

    bool (*MapPage)(ulong physical_address, ulong virtual_address, ulong additional_flag);
    bool (*MapPages)(ulong physical_address, ulong virtual_address, size_t memory_size, ulong additional_flag);
    bool (*UnmapPage)(ulong virtual_address);
    bool (*UnmapPages)(ulong virtual_address, size_t memory_size);

    void *(*AllocateMemory)(size_t memory_size);
    void (*FreeMemory)(void *memory_address);

    memory::HeapMemoryTemplate *(*CreateHeap)(ulong memory_start_address, ulong memory_end_address);
    bool (*SwitchHeap)(memory::HeapMemoryTemplate *new_current_heap);
    void (*FreeHeap)(memory::HeapMemoryTemplate *old_heap);
};

}

#endif // __SYSTEM_FUNCTIONS__

