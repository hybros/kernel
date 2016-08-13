#ifndef __SYSTEM_MANAGER__
#define __SYSTEM_MANAGER__

#include <HStdTypes>

#include "system.hpp"

namespace Hybros
{
namespace System
{

class Manager
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

public:
    Manager(Type type);
    ~Manager() = default;

    auto isActive() -> bool;
    void setStatus(bool activate_manager);

private:
    const Type mgr_type;
    const uint mgr_id;
    bool mgr_currently_active;
};

}
}


#endif // __SYSTEM_MANAGER__
