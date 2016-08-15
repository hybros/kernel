#ifndef __SYSTEM_INTERNAL_STRUCTS__
#define __SYSTEM_INTERNAL_STRUCTS__

#include <Hybros/SystemTerminal>
#include <Hybros/SystemPhysicalMemoryManager>
#include <Hybros/SystemVirtualMemoryManager>
#include <Hybros/SystemHeapMemoryManager>
#include <Hybros/SystemInterruptManager>

struct ReservedMemory
{
    char system[sizeof(HSystem)];
    char terminal[sizeof(HSystem::Terminal)];
    char pmm[sizeof(HSystem::PhysicalMemoryManager)];
    char vmm[sizeof(HSystem::VirtualMemoryManager)];
    char hmm[sizeof(HSystem::HeapMemoryManager)];
    char im[sizeof(HSystem::InterruptManager)];
};

//extern ReservedMemory reserved_memory;

#endif
