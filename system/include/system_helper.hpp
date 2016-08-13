#ifndef __SYSTEM_HELPER_FUNCTIONS__
#define __SYSTEM_HELPER_FUNCTIONS__

#include <HSystemTerminal>
#include <HSystemPhysicalMemoryManager>
#include <HSystemVirtualMemoryManager>
#include <HStdMath>

template<class T>
auto operator <<(HSystem &system, T data) -> HTerminal &;

//auto operator <<(HSystem &system, HForeground foreground_color) -> HTerminal &;
//auto operator <<(HSystem &system, HBackground background_color) -> HTerminal &;
//auto operator <<(HSystem &system, const uchar &number_base) -> HTerminal &;
//auto operator <<(HSystem &system, HInfoLevel info) -> HTerminal &;
//auto operator <<(HSystem &system, HMathUnits) -> HTerminal &;
//auto operator <<(HSystem &system, char character) -> HTerminal &;
//auto operator <<(HSystem &system, const char *string) -> HTerminal &;
//auto operator <<(HSystem &system, const HString &string) -> HTerminal &;
//auto operator <<(HSystem &system, const void *pointer) -> HTerminal &;
//auto operator <<(HSystem &system, ulong number) -> HTerminal &;


#endif
