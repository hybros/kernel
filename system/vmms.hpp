#ifndef __VIRTUAL_MEMORY_MANAGER__
#define __VIRTUAL_MEMORY_MANAGER__

#include "../std/data_types.hpp"
#include "../std/bits.hpp"
#include "../std/memory.hpp"
#include "../std/list.hpp"
#include "../memory/vmm_temp.hpp"

namespace kernel
{
namespace memory
{

enum PageTranslationMode
{
    PAGE_TRANSLATION_4KB,
    PAGE_TRANSLATION_2MB,
    PAGE_TRANSLATION_1GB
};

}
namespace std
{

template<> void List<memory::VMMTemplate*>::PushFirstElement(memory::VMMTemplate * const &data);

}

class System;

class VirtualMemoryManagementServer
{
public:
    inline VirtualMemoryManagementServer();
    inline VirtualMemoryManagementServer(memory::VMMTemplate *first_vmm);
    inline ~VirtualMemoryManagementServer();

    bool RegisterManager(memory::VMMTemplate *new_vmm);
    bool UnregisterManager(memory::VMMTemplate *old_vmm);

    inline memory::VMMTemplate *GetManager(uint &vmm_id);
    inline uint GetManagerID(memory::VMMTemplate *searched_vmmm);                     // just list position
    inline memory::VMMTemplate *GetCurrentManager();
    inline uint GetCurrentManagerID();
    inline void LoadCurrentManager(uint &new_current_vmm_id);

    inline void *AllocatePage(void *physical_address = nullptr);
    inline void *AllocatePage(bool writable, void *physical_address = nullptr);
    inline void *AllocatePage(bool writable, bool supervisor, void *physical_address = nullptr);
    inline void *AllocatePage(bool writable, bool supervisor, bool executable, void *physical_address = nullptr);
    inline void *AllocatePages(uint number_of_pages);
    inline void FreePage(void *virtual_address);
    inline void FreePages(void *virtual_address, uint number);

    inline bool MapPage(ulong same_address, ulong additional_flag);                                 // Same address for physical and virtual memory
    inline bool MapPage(ulong physical_address, ulong virtual_address, ulong additional_flag);
    inline bool MapPages(ulong same_address, size_t memory_size, ulong additional_flag);
    inline bool MapPages(ulong physical_address, ulong virtual_address, size_t memory_size, ulong additional_flag);
    inline bool UnmapPage(ulong virtual_address);
    inline bool UnmapPages(ulong virtual_address, size_t memory_size);

private:
    memory::VMMTemplate *current_vmm;
    std::List<memory::VMMTemplate*> vmms;
};

typedef class VirtualMemoryManagementServer VMMServer;

// ~ VirtualMemoryManager

VirtualMemoryManagementServer::VirtualMemoryManagementServer() {}

VirtualMemoryManagementServer::VirtualMemoryManagementServer(memory::VMMTemplate *first_vmm)
{
    vmms.PushFirstElement(first_vmm);
    current_vmm = first_vmm;
}

VirtualMemoryManagementServer::~VirtualMemoryManagementServer()
{
    vmms.Clear();
}

memory::VMMTemplate *VirtualMemoryManagementServer::GetManager(uint &vmm_id)
{
    return vmms.GetElement(vmm_id);
}

uint VirtualMemoryManagementServer::GetManagerID(memory::VMMTemplate *searched_vmmm)
{
    return vmms.GetPosition(searched_vmmm);
}

memory::VMMTemplate *VirtualMemoryManagementServer::GetCurrentManager()
{
    return current_vmm;
}

uint VirtualMemoryManagementServer::GetCurrentManagerID()
{
    return vmms.GetPosition(current_vmm);
}

void VirtualMemoryManagementServer::LoadCurrentManager(uint &new_current_vmm_id)
{
    current_vmm = vmms.GetElement(new_current_vmm_id);
}

void *VirtualMemoryManagementServer::AllocatePage(void *physical_address)
{
    return current_vmm->AllocatePage(true, true, true, physical_address);
}

void *VirtualMemoryManagementServer::AllocatePage(bool writable, void *physical_address)
{
    return current_vmm->AllocatePage(writable, true, true, physical_address);
}

void *VirtualMemoryManagementServer::AllocatePage(bool writable, bool supervisor, void *physical_address)
{
    return current_vmm->AllocatePage(writable, supervisor, true, physical_address);
}

void *VirtualMemoryManagementServer::AllocatePages(uint number)
{
    return current_vmm->AllocatePages(number);
}

void VirtualMemoryManagementServer::FreePage(void *virtual_address)
{
    current_vmm->FreePage(virtual_address);
}

void VirtualMemoryManagementServer::FreePages(void *virtual_address, uint number)
{
    current_vmm->FreePages(virtual_address, number);
}

bool VirtualMemoryManagementServer::MapPage(ulong same_address, ulong additional_flag)
{
    return current_vmm->MapPage(same_address, same_address, additional_flag);
}

bool VirtualMemoryManagementServer::MapPage(ulong physical_address, ulong virtual_address, ulong additional_flag)
{
    return current_vmm->MapPage(physical_address, virtual_address, additional_flag);
}

bool VirtualMemoryManagementServer::MapPages(ulong same_address, size_t memory_size, ulong additional_flag)
{
    return current_vmm->MapPages(same_address, same_address, memory_size, additional_flag);
}

bool VirtualMemoryManagementServer::MapPages(ulong physical_address, ulong virtual_address, size_t memory_size, ulong additional_flag)
{
    return current_vmm->MapPages(physical_address, virtual_address, memory_size, additional_flag);
}

bool VirtualMemoryManagementServer::UnmapPage(ulong virtual_address)
{
    return current_vmm->UnmapPage(virtual_address);
}

bool VirtualMemoryManagementServer::UnmapPages(ulong virtual_address, size_t memory_size)
{
    return current_vmm->UnmapPages(virtual_address, memory_size);
}

}

#endif
