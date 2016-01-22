#ifndef __GLOBAL_DESCRIPTOR_TABLE__
#define __GLOBAL_DESCRIPTOR_TABLE__

class HGlobalDescriptorTable
{
public:
    struct Entry
    {
        uint16 limit_low;
        uint16 base_low;
        uint8 base_middle;
        uint8 access;
        uint8 flags;
        uint8 base_high;
    } __attribute__((packed));

    struct Pointer
    {
        uint16 limit;
        uint64 offset;
    } __attribute__((packed));

    HGlobalDescriptorTable() = default;
//    HGlobalDescriptorTable(Entry *current_gdt);
    ~HGlobalDescriptorTable() = default;

protected:
    Entry *gdt_entry;
    Pointer gdt_pointer;
};

using GDT = HGlobalDescriptorTable;

#endif
