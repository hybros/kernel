#ifndef __INTERRUPT_DESCRIPTOR_TABLE__
#define __INTERRUPT_DESCRIPTOR_TABLE__

#include <HStdTypes>

class HInterruptHandler;

class HInterruptDescriptorTable32
{
public:
    struct Entry
    {
        uint16 base_low;
        uint16 selector;
        uint8 zero;
        uint8 flags;
        uint16 base_high;
    };

    struct Pointer
    {
        uint16 limit;
        uint32 pointer;
    };

private:
    Entry entry[256];
    Pointer pointer;
};

using IDT32 = HInterruptDescriptorTable32;


#endif
