#ifndef __PHYSICAL_MEMORY_MANAGER__
#define __PHYSICAL_MEMORY_MANAGER__

#include "../std/data_types.hpp"
#include "../std/list.hpp"
#include "../memory/pmm_temp.hpp"

namespace kernel
{

namespace std
{

template<> void List<memory::PMMTemplate*>::PushFirstElement(memory::PMMTemplate * const &data);

}

class PhysicalMemoryManagerServer
{
public:
    inline PhysicalMemoryManagerServer();
    inline ~PhysicalMemoryManagerServer();

    bool RegisterManager(memory::PMMTemplate *new_pmm);
    bool UnregisterManager(memory::PMMTemplate *old_pmm);

    inline memory::PMMTemplate *GetManager(uint &pmm_id);
    inline uint GetManagerID(memory::PMMTemplate *searched_pmmm);                     // just list position
    inline memory::PMMTemplate *GetCurrentManager();
    inline uint GetCurrentManagerID();
    void LoadCurrentManager(uint &new_current_pmm_id);

    inline void* AllocateBlock();
    inline void* AllocateBlocks(size_t number_of_blocks);
    inline void  FreeBlock(void* block_address);
    inline void  FreeBlocks(void* block_address, size_t number_of_blocks);

    inline void InitRegion(ulong base, size_t size);
    inline void DeinitRegion(ulong base, size_t size);

private:
    memory::PMMTemplate *current_pmm;
    std::List<memory::PMMTemplate*> pmms;
};

typedef class PhysicalMemoryManagerServer PMMServer;

// ~ PhysicalMemoryManagementServer

PhysicalMemoryManagerServer::PhysicalMemoryManagerServer() {}

PhysicalMemoryManagerServer::~PhysicalMemoryManagerServer()
{
    pmms.Clear();
}

memory::PMMTemplate *PhysicalMemoryManagerServer::GetManager(uint &pmm_id)
{
    return pmms.GetElement(pmm_id);
}

uint PhysicalMemoryManagerServer::GetManagerID(memory::PMMTemplate *searched_pmmm)
{
    return pmms.GetPosition(searched_pmmm);
}

memory::PMMTemplate *PhysicalMemoryManagerServer::GetCurrentManager()
{
    return current_pmm;
}

uint PhysicalMemoryManagerServer::GetCurrentManagerID()
{
    return pmms.GetPosition(current_pmm);
}

void PhysicalMemoryManagerServer::LoadCurrentManager(uint &new_current_pmm_id)
{
    current_pmm = pmms.GetElement(new_current_pmm_id);
}

void* PhysicalMemoryManagerServer::AllocateBlock()
{
    return current_pmm->AllocateBlock();
}

void* PhysicalMemoryManagerServer::AllocateBlocks(size_t number_of_blocks)
{
    return current_pmm->AllocateBlocks(number_of_blocks);
}

void PhysicalMemoryManagerServer::FreeBlock(void* block_address)
{
    current_pmm->FreeBlock(block_address);
}

void PhysicalMemoryManagerServer::FreeBlocks(void* block_address, size_t number_of_blocks)
{
    current_pmm->FreeBlocks(block_address, number_of_blocks);
}

void PhysicalMemoryManagerServer::InitRegion(ulong base, size_t size)
{
    current_pmm->InitRegion(base, size);
}

void PhysicalMemoryManagerServer::DeinitRegion(ulong base, size_t size)
{
    current_pmm->DeinitRegion(base, size);
}

}


#endif
