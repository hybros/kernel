#include "../include/pmm.hpp"

HPhysicalMemoryManager::HPhysicalMemoryManager() :
    HSystem::Manager(HSystem::Manager::PHYSICAL_MEMORY_MANAGER)
{
}

auto HPhysicalMemoryManager::GetBlockSize() -> size_t
{
    return 4096;
}
