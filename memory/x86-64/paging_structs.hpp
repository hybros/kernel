#ifndef __PAGING_STRUCTURES__
#define __PAGING_STRUCTURES__

#include <HStdTypes>
#include <HBitOperations>

#define PAGE_ENTRIES    512
#define PAGE_SIZE       4096                  //Pages are 4k aligned

namespace Hybros
{
namespace VirtualMemory
{

struct PageTable;
struct PageDirectoryTable;
struct PageDirectoryPointerTable;

enum PageTranslation4kB
{
    PHYSICAL_PAGE_OFFSET    = 0xFFF,                //00000000000000000000000000000000 00000000000000000000111111111111
    PT_OFFSET               = 0x1FF000,             //00000000000000000000000000000000 00000000000111111111000000000000
    PDT_OFFSET              = 0x3FE00000,           //00000000000000000000000000000000 00111111111000000000000000000000
    PDPT_OFFSET             = 0x7FC0000000,         //00000000000000000000000001111111 11000000000000000000000000000000
    PML4_OFFSET             = 0xFF8000000000,       //00000000000000001111111110000000 00000000000000000000000000000000
};

class PTEntry
{
public:
    enum Flags : uint64
    {
        PRESENT              = 1,                    //00000000000000000000000000000000 00000000000000000000000000000001
        WRITABLE             = 2,                    //00000000000000000000000000000000 00000000000000000000000000000010
        USER                 = 4,                    //00000000000000000000000000000000 00000000000000000000000000000100
        WRITETHROUGH         = 8,                    //00000000000000000000000000000000 00000000000000000000000000001000
        NOT_CACHEABLE        = 0x10,                 //00000000000000000000000000000000 00000000000000000000000000010000
        ACCESSED             = 0x20,                 //00000000000000000000000000000000 00000000000000000000000000100000
        DIRTY                = 0x40,                 //00000000000000000000000000000000 00000000000000000000000001000000
        PAT                  = 0x80,                 //00000000000000000000000000000000 00000000000000000000000010000000
        CPU_GLOBAL           = 0x100,                //00000000000000000000000000000000 00000000000000000000000100000000
        LV4_GLOBAL           = 0x200,                //00000000000000000000000000000000 00000000000000000000001000000000
        FRAME                = 0xFFFFFFFFFF000,      //00000000000011111111111111111111 11111111111111111111000000000000
        NOT_EXECUTABLE       = 0x8000000000000000    //10000000000000000000000000000000 00000000000000000000000000000000
    };

    uint64 entry;

    operator uint64 &()
    {
        return entry;
    }
};

class PDTEntry
{
public:
    enum Flags : uint64
    {
        PRESENT             = 1,                    //00000000000000000000000000000000 00000000000000000000000000000001
        WRITABLE            = 2,                    //00000000000000000000000000000000 00000000000000000000000000000010
        USER                = 4,                    //00000000000000000000000000000000 00000000000000000000000000000100
        WRITETHROUGH        = 8,                    //00000000000000000000000000000000 00000000000000000000000000001000
        NOT_CACHEABLE       = 0x10,                 //00000000000000000000000000000000 00000000000000000000000000010000
        ACCESSED            = 0x20,                 //00000000000000000000000000000000 00000000000000000000000000100000
        PT_BASE             = 0xFFFFFFFFFF000,      //00000000000011111111111111111111 11111111111111111111000000000000
        NOT_EXECUTABLE      = 0x8000000000000000    //10000000000000000000000000000000 00000000000000000000000000000000
    };

    uint64 entry;

    auto toPT() const -> PageTable *
    {
        return reinterpret_cast<PageTable*>(GetBits(entry, PT_BASE));
    }

    operator uint64 &()
    {
        return entry;
    }
};

class PDPTEntry
{
public:
    enum Flags : uint64
    {
        PRESENT            = 1,                    //00000000000000000000000000000000 00000000000000000000000000000001
        WRITABLE           = 2,                    //00000000000000000000000000000000 00000000000000000000000000000010
        USER               = 4,                    //00000000000000000000000000000000 00000000000000000000000000000100
        WRITETHROUGH       = 8,                    //00000000000000000000000000000000 00000000000000000000000000001000
        NOT_CACHEABLE      = 0x10,                 //00000000000000000000000000000000 00000000000000000000000000010000
        ACCESSED           = 0x20,                 //00000000000000000000000000000000 00000000000000000000000000100000
        PDT_BASE           = 0xFFFFFFFFFF000,      //00000000000011111111111111111111 11111111111111111111000000000000
        NOT_EXECUTABLE     = 0x8000000000000000    //10000000000000000000000000000000 00000000000000000000000000000000
    };

    uint64 entry;

    auto toPDT() const -> PageDirectoryTable *
    {
        return reinterpret_cast<PageDirectoryTable*>(GetBits<uint64>(entry, PDT_BASE));
    }

    operator uint64 &()
    {
        return entry;
    }
};

class PML4Entry
{
public:
    enum Flags : uint64
    {
        PRESENT            = 1,                    //00000000000000000000000000000000 00000000000000000000000000000001
        WRITABLE           = 2,                    //00000000000000000000000000000000 00000000000000000000000000000010
        USER               = 4,                    //00000000000000000000000000000000 00000000000000000000000000000100
        WRITETHROUGH       = 8,                    //00000000000000000000000000000000 00000000000000000000000000001000
        NOT_CACHEABLE      = 0x10,                 //00000000000000000000000000000000 00000000000000000000000000010000
        ACCESSED           = 0x20,                 //00000000000000000000000000000000 00000000000000000000000000100000
        PDPT_BASE          = 0xFFFFFFFFFF000,      //00000000000011111111111111111111 11111111111111111111000000000000
        NOT_EXECUTABLE     = 0x8000000000000000    //10000000000000000000000000000000 00000000000000000000000000000000
    };

    uint64 entry;

    auto toPDPT() const -> PageDirectoryPointerTable *
    {
        return reinterpret_cast<PageDirectoryPointerTable*>(GetBits<uint64>(entry, PDPT_BASE));
    }

    operator uint64 &()
    {
        return entry;
    }
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

struct PageTable
{
    PTEntry entry[PAGE_ENTRIES];

    static auto isPresent(PTEntry *entry) -> bool;
    static auto isWritable(PTEntry *entry) -> bool;
    static auto isUserMode(PTEntry *entry) -> bool;
    static auto isWritethoughEnabled(PTEntry *entry) -> bool;
    static auto isCachable(PTEntry *entry) -> bool;
    static auto wasAccessed(PTEntry *entry) -> bool;    
    
    static void setAttribute(PTEntry *entry, PTEntry::Flags flag);
    static void clearAttribute(PTEntry *entry, PTEntry::Flags flag);    
    
    static auto getEntryNumber(ulong virtual_address) -> ulong;    
    
    static auto getPhysicalBase(PTEntry *entry) -> ulong;
    static void setPhysicalBase(PTEntry *entry, const ulong physical_address);
} __attribute__((__packed__));
using PT = PageTable;

struct PageDirectoryTable
{
    PDTEntry entry[PAGE_ENTRIES];

    inline static bool isPresent(PDTEntry *entry);
    inline static bool isWritable(PDTEntry *entry);
    inline static bool isUserMode(PDTEntry *entry);
    inline static bool isWritethoughEnabled(PDTEntry *entry);
    inline static bool isCachable(PDTEntry *entry);
    inline static bool wasAccessed(PDTEntry *entry);

    inline static void setAttribute(PDTEntry *entry, PDTEntry::Flags flag);
    inline static void clearAttribute(PDTEntry *entry, PDTEntry::Flags flag);

    inline static auto getEntryNumber(ulong virtual_address) -> ulong;

    inline static PT  *getPTBase(PDTEntry *entry);
    inline static void getPTBase(PDTEntry *entry, ulong pt_address);
    inline static void setPTBase(PDTEntry *entry, PT *address);
} __attribute__((__packed__));
using PDT = PageDirectoryTable;

struct PageDirectoryPointerTable
{
    PDPTEntry entry[PAGE_ENTRIES];

    inline static bool isPresent(PDPTEntry *entry);
    inline static bool isWritable(PDPTEntry *entry);
    inline static bool isUserMode(PDPTEntry *entry);
    inline static bool isWritethoughEnabled(PDPTEntry *entry);
    inline static bool isCachable(PDPTEntry *entry);
    inline static bool wasAccessed(PDPTEntry *entry);

    inline static void setAttribute(PDPTEntry *entry, PDPTEntry::Flags flag);
    inline static void clearAttribute(PDPTEntry *entry, PDPTEntry::Flags flag);

    inline static auto getEntryNumber(ulong virtual_address) -> ulong;

    inline static auto getPDTBase(PDPTEntry *entry) -> PDT *;
    inline static void setPDTBase(PDPTEntry *entry, ulong pdt_address);
    inline static void setPDTBase(PDPTEntry *entry, PDT *address);
} __attribute__((__packed__));
using PDPT = PageDirectoryPointerTable;

struct PageMapLevel4
{
    PML4Entry entry[PAGE_ENTRIES];

    static bool isPresent(PML4Entry *entry)
    {
        return IsBitSet(*entry, PRESENT_BIT);
    }
    static bool isWritable(PML4Entry *entry)
    {
        return IsBitSet(*entry, WRITABLE_BIT);
    }   
    static bool isUserMode(PML4Entry *entry)
    {
        return IsBitSet(*entry, USER_BIT);
    }
    static bool isWritethoughEnabled(PML4Entry *entry)
    {
        return IsBitSet(*entry, WRITETHROUGH_BIT);
    }
    static bool isCachable(PML4Entry *entry)
    {
        return (IsBitSet(*entry, NOT_CACHEABLE_BIT)) ? false : true;
    }
    static bool wasAccessed(PML4Entry *entry)
    {
        return IsBitSet(*entry, ACCESSED_BIT);
    }  
    
    static void setAttribute(PML4Entry *entry, PML4Entry::Flags flag)
    {
        *entry |= flag;
    }
    static void slearAttribute(PML4Entry *entry, PML4Entry::Flags flag)
    {
        *entry &= ~flag;
    }   
    
    static auto getEntryNumber(ulong virtual_address) -> ulong{
        return GetBits(virtual_address, 39, 47);
    }    
    
    static auto getPDPTBase(PML4Entry *entry) -> PDPT *
    {
        return entry->toPDPT();
    }
    static void setPDPTBase(PML4Entry *entry, ulong pdpt_address)
    {
        SetBits(static_cast<uint64 &>(*entry), PML4Entry::PDPT_BASE, pdpt_address);
    }
    static void setPDPTBase(PML4Entry *entry, PDPT *address)
    {
        SetBits(static_cast<uint64 &>(*entry), PML4Entry::PDPT_BASE, reinterpret_cast<uint64>(address));
    }
} __attribute__((__packed__));
using PML4 = PageMapLevel4;

}
}

#endif //__PAGING_STRUCTURES__
