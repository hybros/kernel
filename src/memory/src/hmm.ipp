#include "../include/hmm.hpp"

// ~ HHeapMemory

HHeapBase::HHeapBase(size_t max_memory_size, uint access_rights) :
    heap_uid(0xF0F0F0F0F0F0F0F0),
    heap_memory_size(0),
    heap_max_memory_size(max_memory_size),
    heap_access_rights(access_rights)
{
}

// ~ HHeapMemoryManager

HHeapMemoryManager::HHeapMemoryManager() :
    HSystem::Manager(HSystem::Manager::HEAP_MEMORY_MANAGER)
{}

HHeapMemoryManager::~HHeapMemoryManager()
{
    SetStatus(false);
}

auto HHeapMemoryManager::CreateHeap() -> HHeapBase *
{
    return CreateHeap(0, 0, 0x1000);
}

auto HHeapMemoryManager::CreateHeap(size_t memory_size) -> HHeapBase *
{
    return CreateHeap(0, 0, memory_size);
}

