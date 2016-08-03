#ifndef __INTERRUPT_DESCRIPTOR_TABLE_64__
#define __INTERRUPT_DESCRIPTOR_TABLE_64__

#include <HStdTypes>

class HInterruptHandler;

class HInterruptDescriptorTable64
{
public:
	using HandlerRoutine = void (*)();

    HInterruptDescriptorTable64(uint entry_number = 256);
    ~HInterruptDescriptorTable64();

    void OverwriteRoutine(uint number, HandlerRoutine handler);

    bool FreeRoutine(uint number);

    void LoadTable();

protected:
    struct Entry
    {
        uint16 base_low;
        uint16 selector;
        uint8 zero;
        uint8 flags;
        uint16 base_middle;
        uint32 base_high;
        uint32 zero0;
    } __attribute__((packed));

    struct Pointer
    {
        uint16 limit;
        uint64 offset;
    } __attribute__((packed));

    Entry *idt_entry;
    Pointer idt_pointer;
};

using IDT = HInterruptDescriptorTable64;
using IDT64 = HInterruptDescriptorTable64;


#endif
