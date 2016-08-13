#include "../include/system_helper.hpp"

#include <HSharedPointer>
#include <SystemManager>

namespace Hybros
{

auto operator <<(System &system, HForeground foreground_color) -> HTerminal &
{
    system.GetCurrentManager(System::Manager::TERMINAL);
}

auto operator <<(System &system, HBackground background_color) -> HTerminal &
{
//    return system;
}

auto operator <<(System &system, const uchar &number_base) -> HTerminal &
{
 //   return system;
}

auto operator <<(System &system, HInfoLevel info) -> HTerminal &
{
//    return system;
}

auto operator <<(System &system, HMathUnits) -> HTerminal &
{
 //   return system;
}

auto operator <<(System &system, char character) -> HTerminal &
{
 //   return system;
}

auto operator <<(System &system, const char *string) -> HTerminal &
{
 //   return system;
}

auto operator <<(const System &system, const HString &string) -> HTerminal &
{
 //   return system;
}

auto operator <<(const System &system, const void *pointer) -> HTerminal &
{
 //   return system;
}

auto operator <<(const System &system, ulong number) -> HTerminal &
{
//    return system;
}

}
