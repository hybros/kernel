#include "../include/system_helper.hpp"

#include <HSystemTerminal>

template<class T>
auto operator <<(HSystem &system, T data) -> HTerminal &
{
    return (system.system_term << data);
}
