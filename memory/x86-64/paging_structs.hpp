#ifndef __PAGING_STRUCTURES__
#define __PAGING_STRUCTURES__

#include "../../std/data_types.hpp"
#include "../../std/bits.hpp"

#define PAGE_ENTRIES    512
#define PAGE_SIZE       4096                  //Pages are 4k aligned

namespace kernel
{
namespace memory
{

enum PageTranslation4kB
{
    PHYSICAL_PAGE_OFFSET    = 0xFFF,                //00000000000000000000000000000000 00000000000000000000111111111111
    PT_OFFSET               = 0x1FF000,             //00000000000000000000000000000000 00000000000111111111000000000000
    PDT_OFFSET              = 0x3FE00000,           //00000000000000000000000000000000 00111111111000000000000000000000
    PDPT_OFFSET             = 0x7FC0000000,         //00000000000000000000000001111111 11000000000000000000000000000000
    PML4_OFFSET             = 0xFF8000000000,       //00000000000000001111111110000000 00000000000000000000000000000000

    PT_START_BIT            = 12,
    PDT_START_BIT           = 21,
    PDPT_START_BIT          = 30,
    PML4_START_BIT          = 39
};

enum PML4EntryFlags : ulong
{
    PML4_PRESENT            = 1,                    //00000000000000000000000000000000 00000000000000000000000000000001
    PML4_WRITABLE           = 2,                    //00000000000000000000000000000000 00000000000000000000000000000010
    PML4_USER               = 4,                    //00000000000000000000000000000000 00000000000000000000000000000100
    PML4_WRITETHROUGH       = 8,                    //00000000000000000000000000000000 00000000000000000000000000001000
    PML4_NOT_CACHEABLE      = 0x10,                 //00000000000000000000000000000000 00000000000000000000000000010000
    PML4_ACCESSED           = 0x20,                 //00000000000000000000000000000000 00000000000000000000000000100000
    PML4_PDPT_BASE          = 0xFFFFFFFFFF000,      //00000000000011111111111111111111 11111111111111111111000000000000
    PML4_NOT_EXECUTABLE     = 0x8000000000000000    //10000000000000000000000000000000 00000000000000000000000000000000
};

enum PDPTEntryFlags : ulong
{
    PDPT_PRESENT            = 1,                    //00000000000000000000000000000000 00000000000000000000000000000001
    PDPT_WRITABLE           = 2,                    //00000000000000000000000000000000 00000000000000000000000000000010
    PDPT_USER               = 4,                    //00000000000000000000000000000000 00000000000000000000000000000100
    PDPT_WRITETHROUGH       = 8,                    //00000000000000000000000000000000 00000000000000000000000000001000
    PDPT_NOT_CACHEABLE      = 0x10,                 //00000000000000000000000000000000 00000000000000000000000000010000
    PDPT_ACCESSED           = 0x20,                 //00000000000000000000000000000000 00000000000000000000000000100000
    PDPT_PDT_BASE           = 0xFFFFFFFFFF000,   	//00000000000011111111111111111111 11111111111111111111000000000000
    PDPT_NOT_EXECUTABLE     = 0x8000000000000000    //10000000000000000000000000000000 00000000000000000000000000000000
};


enum PDTEntryFlags : ulong
{
    PDT_PRESENT             = 1,                    //00000000000000000000000000000000 00000000000000000000000000000001
    PDT_WRITABLE            = 2,                    //00000000000000000000000000000000 00000000000000000000000000000010
    PDT_USER                = 4,                    //00000000000000000000000000000000 00000000000000000000000000000100
    PDT_WRITETHROUGH        = 8,                    //00000000000000000000000000000000 00000000000000000000000000001000
    PDT_NOT_CACHEABLE       = 0x10,                 //00000000000000000000000000000000 00000000000000000000000000010000
    PDT_ACCESSED            = 0x20,                 //00000000000000000000000000000000 00000000000000000000000000100000
    PDT_PT_BASE             = 0xFFFFFFFFFF000,      //00000000000011111111111111111111 11111111111111111111000000000000
    PDT_NOT_EXECUTABLE      = 0x8000000000000000    //10000000000000000000000000000000 00000000000000000000000000000000
};

enum PTEntryFlags : ulong
{
    PT_PRESENT              = 1,                    //00000000000000000000000000000000 00000000000000000000000000000001
    PT_WRITABLE             = 2,                    //00000000000000000000000000000000 00000000000000000000000000000010
    PT_USER                 = 4,                    //00000000000000000000000000000000 00000000000000000000000000000100
    PT_WRITETHROUGH         = 8,                    //00000000000000000000000000000000 00000000000000000000000000001000
    PT_NOT_CACHEABLE        = 0x10,                 //00000000000000000000000000000000 00000000000000000000000000010000
    PT_ACCESSED             = 0x20,                 //00000000000000000000000000000000 00000000000000000000000000100000
    PT_DIRTY                = 0x40,                 //00000000000000000000000000000000 00000000000000000000000001000000
    PT_PAT                  = 0x80,                 //00000000000000000000000000000000 00000000000000000000000010000000
    PT_CPU_GLOBAL           = 0x100,                //00000000000000000000000000000000 00000000000000000000000100000000
    PT_LV4_GLOBAL           = 0x200,                //00000000000000000000000000000000 00000000000000000000001000000000
    PT_FRAME                = 0xFFFFFFFFFF000,      //00000000000011111111111111111111 11111111111111111111000000000000
    PT_NOT_EXECUTABLE       = 0x8000000000000000    //10000000000000000000000000000000 00000000000000000000000000000000
};

enum EntryBits
{
    PRESENT_BIT             = 0,
    WRITABLE_BIT            = 1,
    USER_BIT                = 2,
    WRITETHROUGH_BIT        = 3,
    NOT_CACHEABLE_BIT       = 4,
    ACCESSED_BIT            = 5,
    DIRTY_BIT               = 6,
    PAT_BIT                 = 7,
    CPU_GLOBAL_BIT          = 8,
    LV4_GLOBAL_BIT          = 9,
    NEXT_LEVEL_BASE_BIT     = 12,
    NOT_EXEC_BIT            = 63
};


typedef ulong PML4Entry, PDPTEntry, PDTEntry, PTEntry;

struct PageTable
{
    PTEntry entry[PAGE_ENTRIES];

    inline static bool IsPresent(PTEntry *entry);
    inline static bool IsWritable(PTEntry *entry);
    inline static bool IsUserMode(PTEntry *entry);
    inline static bool IsWritethoughEnabled(PTEntry *entry);
    inline static bool IsCachable(PTEntry *entry);
    inline static bool WasAccessed(PTEntry *entry);

    inline static void SetAttribute(PTEntry *entry, PTEntryFlags flag);
    inline static void ClearAttribute(PTEntry *entry, PTEntryFlags flag);

    inline static uint GetEntryNumber(uint virtual_address);

    inline static ulong GetPhysicalBase(PTEntry *entry);
    inline static void SetPhysicalBase(PTEntry *entry, ulong physical_address);
} __attribute__((__packed__));
typedef PageTable PT;

struct PageDirectoryTable
{
    PDTEntry entry[PAGE_ENTRIES];

    inline static bool IsPresent(PDTEntry *entry);
    inline static bool IsWritable(PDTEntry *entry);
    inline static bool IsUserMode(PDTEntry *entry);
    inline static bool IsWritethoughEnabled(PDTEntry *entry);
    inline static bool IsCachable(PDTEntry *entry);
    inline static bool WasAccessed(PDTEntry *entry);

    inline static void SetAttribute(PDTEntry *entry, PDTEntryFlags flag);
    inline static void ClearAttribute(PDTEntry *entry, PDTEntryFlags flag);

    inline static uint GetEntryNumber(uint virtual_address);

    inline static PT  *GetPTBase(PDTEntry *entry);
    inline static void SetPTBase(PDTEntry *entry, ulong pt_address);
    inline static void SetPTBase(PDTEntry *entry, PT *address);
} __attribute__((__packed__));
typedef PageDirectoryTable PDT;

struct PageDirectoryPointerTable
{
    PDPTEntry entry[PAGE_ENTRIES];

    inline static bool IsPresent(PDPTEntry *entry);
    inline static bool IsWritable(PDPTEntry *entry);
    inline static bool IsUserMode(PDPTEntry *entry);
    inline static bool IsWritethoughEnabled(PDPTEntry *entry);
    inline static bool IsCachable(PDPTEntry *entry);
    inline static bool WasAccessed(PDPTEntry *entry);

    inline static void SetAttribute(PDPTEntry *entry, PDPTEntryFlags flag);
    inline static void ClearAttribute(PDPTEntry *entry, PDPTEntryFlags flag);

    inline static uint GetEntryNumber(uint virtual_address);

    inline static PDT *GetPDTBase(PDPTEntry *entry);
    inline static void SetPDTBase(PDPTEntry *entry, ulong pdt_address);
    inline static void SetPDTBase(PDPTEntry *entry, PDT *address);
} __attribute__((__packed__));
typedef PageDirectoryPointerTable PDPT;

struct PageMapLevel4
{
    PML4Entry entry[PAGE_ENTRIES];

    inline static bool IsPresent(PML4Entry *entry);
    inline static bool IsWritable(PML4Entry *entry);
    inline static bool IsUserMode(PML4Entry *entry);
    inline static bool IsWritethoughEnabled(PML4Entry *entry);
    inline static bool IsCachable(PML4Entry *entry);
    inline static bool WasAccessed(PML4Entry *entry);

    inline static void SetAttribute(PML4Entry *entry, PML4EntryFlags flag);
    inline static void ClearAttribute(PML4Entry *entry, PML4EntryFlags flag);

    inline static uint GetEntryNumber(uint virtual_address);

    inline static PDPT *GetPDPTBase(PML4Entry *entry);
    inline static void SetPDPTBase(PML4Entry *entry, ulong pdpt_address);
    inline static void SetPDPTBase(PML4Entry *entry, PDPT *address);
} __attribute__((__packed__));
typedef PageMapLevel4 PML4;

// ~ PageMapLevel4

bool PageMapLevel4::IsPresent(PML4Entry *entry)
{
    return std::IsBitSet(*entry, PRESENT_BIT);
}

bool PageMapLevel4::IsWritable(PML4Entry *entry)
{
    return std::IsBitSet(*entry, WRITABLE_BIT);
}

bool PageMapLevel4::IsUserMode(PML4Entry *entry)
{
    return std::IsBitSet(*entry, USER_BIT);
}

bool PageMapLevel4::IsWritethoughEnabled(PML4Entry *entry)
{
    return std::IsBitSet(*entry, WRITETHROUGH_BIT);
}

bool PageMapLevel4::IsCachable(PML4Entry *entry)
{
    return (std::IsBitSet(*entry, NOT_CACHEABLE_BIT)) ? false : true;
}

bool PageMapLevel4::WasAccessed(PML4Entry *entry)
{
    return std::IsBitSet(*entry, ACCESSED_BIT);
}

void PageMapLevel4::SetAttribute(PML4Entry *entry, PML4EntryFlags flag)
{
    *entry |= flag;
}

void PageMapLevel4::ClearAttribute(PML4Entry *entry, PML4EntryFlags flag)
{
    *entry &= ~flag;
}

uint PageMapLevel4::GetEntryNumber(uint virtual_address)
{
    return std::GetBits(virtual_address, PML4_OFFSET, PML4_START_BIT);
}

PDPT *PageMapLevel4::GetPDPTBase(PML4Entry *entry)
{
    return reinterpret_cast<PDPT*>(std::GetBits(*entry, PML4_PDPT_BASE, 12));
}

void PageMapLevel4::SetPDPTBase(PML4Entry *entry, ulong pdpt_address)
{
    std::SetBits(*entry, pdpt_address, PML4_PDPT_BASE);
}

void PageMapLevel4::SetPDPTBase(PML4Entry *entry, PDPT *address)
{
    ulong &tmp_entry = *entry, tmp_addr = reinterpret_cast<ulong>(address);
    std::SetBits(tmp_entry, tmp_addr, PML4_PDPT_BASE);
}

// ~ PageDirectoryPointerTable

bool PageDirectoryPointerTable::IsPresent(PDPTEntry *entry)
{
    return std::IsBitSet(*entry, PRESENT_BIT);
}

bool PageDirectoryPointerTable::IsWritable(PDPTEntry *entry)
{
    return std::IsBitSet(*entry, WRITABLE_BIT);
}

bool PageDirectoryPointerTable::IsUserMode(PDPTEntry *entry)
{
    return std::IsBitSet(*entry, USER_BIT);
}

bool PageDirectoryPointerTable::IsWritethoughEnabled(PDPTEntry *entry)
{
    return std::IsBitSet(*entry, WRITETHROUGH_BIT);
}

bool PageDirectoryPointerTable::IsCachable(PDPTEntry *entry)
{
    return (std::IsBitSet(*entry, NOT_CACHEABLE_BIT)) ? false : true;
}

bool PageDirectoryPointerTable::WasAccessed(PDPTEntry *entry)
{
    return std::IsBitSet(*entry, ACCESSED_BIT);
}

void PageDirectoryPointerTable::SetAttribute(PDPTEntry *entry, PDPTEntryFlags flag)
{
    *entry |= flag;
}

void PageDirectoryPointerTable::ClearAttribute(PDPTEntry *entry, PDPTEntryFlags flag)
{
    *entry &= ~flag;
}

uint PageDirectoryPointerTable::GetEntryNumber(uint virtual_address)
{
    return std::GetBits(virtual_address, PDPT_OFFSET, PDPT_START_BIT);
}

PDT *PageDirectoryPointerTable::GetPDTBase(PDPTEntry *entry)
{
    return reinterpret_cast<PDT*>(std::GetBits(*entry, PDPT_PDT_BASE, 12));
}

void PageDirectoryPointerTable::SetPDTBase(PDPTEntry *entry, ulong pdpt_address)
{
    std::SetBits(*entry, pdpt_address, PDPT_PDT_BASE);
}

void PageDirectoryPointerTable::SetPDTBase(PDPTEntry *entry, PDT *address)
{
    ulong &tmp_entry = *entry, tmp_addr = reinterpret_cast<ulong>(address);
    std::SetBits(tmp_entry, tmp_addr, PDPT_PDT_BASE);
}

// ~ PageDirectoryTable

bool PageDirectoryTable::IsPresent(PDTEntry *entry)
{
    return std::IsBitSet(*entry, PRESENT_BIT);
}

bool PageDirectoryTable::IsWritable(PDTEntry *entry)
{
    return std::IsBitSet(*entry, WRITABLE_BIT);
}

bool PageDirectoryTable::IsUserMode(PDTEntry *entry)
{
    return std::IsBitSet(*entry, USER_BIT);
}

bool PageDirectoryTable::IsWritethoughEnabled(PDTEntry *entry)
{
    return std::IsBitSet(*entry, WRITETHROUGH_BIT);
}

bool PageDirectoryTable::IsCachable(PDTEntry *entry)
{
    return (std::IsBitSet(*entry, NOT_CACHEABLE_BIT)) ? false : true;
}

bool PageDirectoryTable::WasAccessed(PDTEntry *entry)
{
    return std::IsBitSet(*entry, ACCESSED_BIT);
}

void PageDirectoryTable::SetAttribute(PDTEntry *entry, PDTEntryFlags flag)
{
    *entry |= flag;
}

void PageDirectoryTable::ClearAttribute(PDTEntry *entry, PDTEntryFlags flag)
{
    *entry &= ~flag;
}

uint PageDirectoryTable::GetEntryNumber(uint virtual_address)
{
    return std::GetBits(virtual_address, PDT_OFFSET, PDT_START_BIT);
}

PT *PageDirectoryTable::GetPTBase(PDTEntry *entry)
{
    return reinterpret_cast<PT*>(std::GetBits(*entry, PDT_PT_BASE, 12));
}

void PageDirectoryTable::SetPTBase(PDTEntry *entry, ulong pt_address)
{
    std::SetBits(*entry, pt_address, PDT_PT_BASE);
}

void PageDirectoryTable::SetPTBase(PDTEntry *entry, PT *address)
{
    ulong &tmp_entry = *entry, tmp_addr = reinterpret_cast<ulong>(address);
    std::SetBits(tmp_entry, tmp_addr, PDT_PT_BASE);
}

// ~ PageTable

bool PageTable::IsPresent(PTEntry *entry)
{
    return std::IsBitSet(*entry, PRESENT_BIT);
}

bool PageTable::IsWritable(PTEntry *entry)
{
    return std::IsBitSet(*entry, WRITABLE_BIT);
}

bool PageTable::IsUserMode(PTEntry *entry)
{
    return std::IsBitSet(*entry, USER_BIT);
}

bool PageTable::IsWritethoughEnabled(PTEntry *entry)
{
    return std::IsBitSet(*entry, WRITETHROUGH_BIT);
}

bool PageTable::IsCachable(PTEntry *entry)
{
    return (std::IsBitSet(*entry, NOT_CACHEABLE_BIT)) ? false : true;
}

bool PageTable::WasAccessed(PTEntry *entry)
{
    return std::IsBitSet(*entry, ACCESSED_BIT);
}

void PageTable::SetAttribute(PTEntry *entry, PTEntryFlags flag)
{
    *entry |= flag;
}

void PageTable::ClearAttribute(PTEntry *entry, PTEntryFlags flag)
{
    *entry &= ~flag;
}

uint PageTable::GetEntryNumber(uint virtual_address)
{
    return std::GetBits(virtual_address, PT_OFFSET, PT_START_BIT);
}

ulong PageTable::GetPhysicalBase(PTEntry *entry)
{
    return reinterpret_cast<ulong>(std::GetBits(*entry, PT_FRAME, 12));
}

void PageTable::SetPhysicalBase(PTEntry *entry, ulong physical_address)
{
    std::SetBits(*entry, physical_address, PT_FRAME);
}

}
}

#endif //__PAGING_STRUCTURES__
