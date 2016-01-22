#ifndef __SYSTEM_INTERRUPT_MANAGER__
#define __SYSTEM_INTERRUPT_MANAGER__

#include <HInterruptManager>
#include <HInterruptDescriptorTable>
#include <HString>
#include <HVector>
#include <HSystemInfos>
#include <HExceptions>

class HSystem::InterruptManager : public HInterruptManager
{
public:
    InterruptManager();
    ~InterruptManager();

    auto GetFirstInterruptNumber() const -> uint;
    auto GetLastInterruptNumber() const -> uint;

    auto GetLastException() const -> HException;

    static void HandleInterrupt(Registers *exception_regs);

    auto AddInterruptHandler(HInterruptHandler &new_handler) -> uint;
    auto RemoveInterruptHandler(uint interrupt_handler_id) -> bool;

    void EnableInterrupts() const;
    void DisableInterrupts() const;

private:
    HVector<HException> exceptions;
    HVector<HInterruptHandler*> int_handlers;
    IDT idt;

    void RemapPIC();
};

#endif
