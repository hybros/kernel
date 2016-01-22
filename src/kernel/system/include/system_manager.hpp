#ifndef __SYSTEM_MANAGER__
#define __SYSTEM_MANAGER__

#include <HStdTypes>

#include "system.hpp"

struct HSystem::ManagerGroup
{
    HTerminal *terminal;
    HPhysicalMemoryManager *pmm;
    HVirtualMemoryManager *vmm;
};

class HSystem::Manager
{
public:
    enum Type
    {
        TERMINAL,

        PROCESSOR_CONTROLLER,

        PHYSICAL_MEMORY_MANAGER,
        VIRTUAL_MEMORY_MANAGER,
        HEAP_MEMORY_MANAGER
    };

    Manager(Type type);
    ~Manager() = default;

    auto IsActive() -> bool;
    void SetStatus(bool activate_manager);

protected:
    operator HSystem &();

private:
    const Type mgr_type;
    const uint mgr_id;
    bool mgr_currently_active;
};

using HManager = HSystem::Manager;

#define SYSTEM static_cast<HSystem &>(THIS)


#endif // __SYSTEM_MANAGER__
