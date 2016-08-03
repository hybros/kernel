#include "../../include/x86-64/idt.hpp"

#include <cMemory>
#include <HInterruptManager>
#include <HBitOperations>
#include <HSystem>

#include "../../include/gdt.hpp"

extern "C"
{

extern GDT::Entry *gdt64;

}

HInterruptDescriptorTable64::HInterruptDescriptorTable64(uint entry_number)
{
    idt_entry = new Entry[entry_number];

    idt_pointer.limit = (sizeof(Entry) * entry_number) - 1;
    idt_pointer.offset = reinterpret_cast<uint64>(idt_entry);

    memzero(idt_entry, sizeof(Entry) * entry_number);
}

void HInterruptDescriptorTable64::OverwriteRoutine(uint number, HandlerRoutine handler)
{
    uint64 handler_address = reinterpret_cast<uint64>(handler);
    idt_entry[number].base_low = GetBits(handler_address, 0, 15);
    idt_entry[number].base_middle = GetBits(handler_address, 16, 31);
    idt_entry[number].base_high = GetBits(handler_address, 32, 63);
    idt_entry[number].selector = 0x08;
    idt_entry[number].flags = 0x8E;
    idt_entry[number].zero = 0;
    idt_entry[number].zero0 = 0;
}

auto HInterruptDescriptorTable64::FreeRoutine(uint number) -> bool
{
    if(idt_entry[number].base_middle != 0)
    {
        memzero(&idt_entry[number], sizeof(Entry));
        return true;
    }
    else
        return false;
}

void HInterruptDescriptorTable64::LoadTable()
{
	HSystem::GetInstance() << INFO << "IDT pointer: " << &idt_pointer << "/ offset: " << idt_pointer.offset << endl;
    __asm__ __volatile__("lidt (%%rax)" :: "a"(&idt_pointer));
}
