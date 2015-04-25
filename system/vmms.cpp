#include "vmms.hpp"

// ~ List<VMMTemplate*>

template<>
void kernel::std::List<kernel::memory::VMMTemplate*>::PushFirstElement(kernel::memory::VMMTemplate * const &data)
{
    static Node new_first(data, 0, nullptr, list_first);
    list_first = &new_first;
    list_size += sizeof(Node);
    list_count++;
}

// ~ VirtualMemoryManagementServer
using namespace kernel;

bool VirtualMemoryManagementServer::RegisterManager(memory::VMMTemplate *new_vmm)
{
    if(new_vmm == nullptr)
        return false;

    if(current_vmm == nullptr)
    {
        vmms.PushFirstElement(new_vmm);
        current_vmm = new_vmm;
        return true;
    }

    vmms.PushLastElement(new_vmm);
    return true;
}

bool VirtualMemoryManagementServer::UnregisterManager(memory::VMMTemplate *old_vmm)
{
    if(old_vmm == nullptr)
        return false;

    vmms.RemoveElement(old_vmm);

    if(current_vmm == old_vmm)
        current_vmm = vmms.GetFirstElement();

    return true;
}
