#include "pmms.hpp"
#include "system.hpp"
#include "../std/list.hpp"
#include "../memory/pmm_temp.hpp"

// ~ List<PMMTemplate*>

template<>
void kernel::std::List<kernel::memory::PMMTemplate*>::PushFirstElement(kernel::memory::PMMTemplate * const &data)
{
    static Node new_first(data, 0, nullptr, list_first);
    list_first = &new_first;
    list_size += sizeof(Node);
    list_count++;
//  UpdatePosition(list_first->node_next, false);
}

// ~ PhysicalMemoryManagerServer
using namespace kernel;

bool PhysicalMemoryManagerServer::RegisterManager(memory::PMMTemplate *new_pmm)
{
    if(new_pmm == nullptr)
        return false;

    if(current_pmm == nullptr)
    {
        pmms.PushFirstElement(new_pmm);
        current_pmm = new_pmm;
        return true;
    }

    pmms.PushLastElement(new_pmm);
    return true;
}

bool PhysicalMemoryManagerServer::UnregisterManager(memory::PMMTemplate *old_pmm)
{
    if(old_pmm == nullptr)
        return false;

    pmms.RemoveElement(old_pmm);

    if(current_pmm == old_pmm)
        current_pmm = pmms.GetFirstElement();

    return true;
}

void PhysicalMemoryManagerServer::LoadCurrentManager(uint &new_current_pmm_id)
{
    current_pmm = pmms.GetElement(new_current_pmm_id);
}
