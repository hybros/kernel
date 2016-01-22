#include "../include/system.hpp"
#include "../include/system_internal.hpp"

#include <HSystemPhysicalMemoryManager>
#include <HSystemVirtualMemoryManager>
//#include <HSystemHeapMemoryManager>

ReservedMemory reserved_memory;

void *HSystem::AllocateBlock()
{
    return system_pmm.AllocateBlock();
}

void *HSystem::AllocateBlocks(size_t number_of_blocks)
{
    return system_pmm.AllocateBlocks(number_of_blocks);
}

void HSystem::FreeBlock(void* memory_address)
{
    system_pmm.FreeBlock(memory_address);
}

void HSystem::FreeBlocks(void* memory_address, size_t number_of_blocks)
{
    system_pmm.FreeBlocks(memory_address, number_of_blocks);
}

void HSystem::InitRegion(ulong base, size_t size)
{
    system_pmm.InitRegion(base, size);
}

void HSystem::DeinitRegion(ulong base, size_t size)
{
    system_pmm.DeinitRegion(base, size);
}

auto HSystem::AllocatePage() -> void *
{
    return system_vmm.AllocatePage(true, true, true);
}

auto HSystem::AllocatePage(bool writable) -> void *
{
    return system_vmm.AllocatePage(writable, true, true);
}

auto HSystem::AllocatePage(bool writable, bool supervisor) -> void *
{
    return system_vmm.AllocatePage(writable, supervisor, true);
}

auto HSystem::AllocatePage(bool writable, bool supervisor, bool executable) -> void *
{
    return system_vmm.AllocatePage(writable, supervisor, executable);
}

auto HSystem::AllocatePages(size_t number_of_pages) -> void *
{
    return system_vmm.AllocatePages(number_of_pages);
}

void HSystem::FreePage(void *virtual_address)
{
    system_vmm.FreePage(virtual_address);
}

void HSystem::FreePages(void *virtual_address, size_t number_of_pages)
{
    system_vmm.FreePages(virtual_address, number_of_pages);
}

auto HSystem::MapPage(ulong same_address, ulong additional_flag) -> bool
{
    return system_vmm.MapPage(same_address, same_address, additional_flag);
}

auto HSystem::MapPage(ulong physical_address, ulong virtual_address, ulong additional_flag) -> bool
{
    return system_vmm.MapPage(physical_address, virtual_address, additional_flag);
}

auto HSystem::MapPages(ulong same_address, size_t memory_size, ulong additional_flag) -> bool
{
    return system_vmm.MapPages(same_address, same_address, memory_size, additional_flag);
}

auto HSystem::MapPages(ulong physical_address, ulong virtual_address, size_t memory_size, ulong additional_flag) -> bool
{
    return system_vmm.MapPages(physical_address, virtual_address, memory_size, additional_flag);
}

auto HSystem::UnmapPage(ulong virtual_address) -> bool
{
    return system_vmm.UnmapPage(virtual_address);
}

auto HSystem::UnmapPages(ulong virtual_address, size_t memory_size) -> bool
{
    return system_vmm.UnmapPages(virtual_address, memory_size);
}

void *HSystem::AllocateMemory(size_t memory_size)
{
    return system_hmm.AllocateMemory(memory_size);
}

void HSystem::FreeMemory(void *memory_address)
{
    system_hmm.FreeMemory(memory_address);
}

auto HSystem::CreateHeap(ulong physical_address, ulong virtual_address, size_t memory_size) -> HHeapBase *
{
    return system_hmm.CreateHeap(physical_address, virtual_address, memory_size);
}

auto HSystem::SwitchUsedHeap(ulong heap_uid) -> bool
{
    return system_hmm.SwitchUsedHeap(heap_uid);
}

auto HSystem::FreeHeap(ulong heap_uid) -> bool
{
    return system_hmm.FreeHeap(heap_uid);
}
