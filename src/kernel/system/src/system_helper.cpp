#include "../include/system_helper.hpp"

#include <HSharedPointer>
#include <HSystemManager>

using namespace kernel;

auto operator <<(HSystem &system, HForeground foreground_color) -> HTerminal &
{
    system.GetCurrentManager(HSystem::Manager::TERMINAL);
}

auto operator <<(HSystem &system, HBackground background_color) -> HTerminal &
{
//    return system;
}

auto operator <<(HSystem &system, const uchar &number_base) -> HTerminal &
{
 //   return system;
}

auto operator <<(HSystem &system, HInfoLevel info) -> HTerminal &
{
//    return system;
}

auto operator <<(HSystem &system, HMathUnits) -> HTerminal &
{
 //   return system;
}

auto operator <<(HSystem &system, char character) -> HTerminal &
{
 //   return system;
}

auto operator <<(HSystem &system, const char *string) -> HTerminal &
{
 //   return system;
}

auto operator <<(const HSystem &system, const HString &string) -> HTerminal &
{
 //   return system;
}

auto operator <<(const HSystem &system, const void *pointer) -> HTerminal &
{
 //   return system;
}

auto operator <<(const HSystem &system, ulong number) -> HTerminal &
{
//    return system;
}
