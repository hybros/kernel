#ifndef __PAGING_STRUCTURES__
#define __PAGING_STRUCTURES__

#include <HStdTypes>
#include <HBitOperations>

#define PAGE_ENTRIES    512
#define PAGE_SIZE       4096                  //Pages are 4k aligned

struct PageTable;
struct PageDirectoryTable;
struct PageDirectoryPointerTable;

enum HPageTranslation4kB
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

    inline operator uint64 &();
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

    inline auto ToPT() const -> PageTable *;

    inline operator uint64 &();
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

    inline auto ToPDT() const -> PageDirectoryTable *;

    inline operator uint64 &();
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

    inline auto ToPDPT() const -> PageDirectoryPointerTable *;

    inline operator uint64 &();
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

    inline static auto IsPresent(PTEntry *entry) -> bool;
    inline static auto IsWritable(PTEntry *entry) -> bool;
    inline static auto IsUserMode(PTEntry *entry) -> bool;
    inline static auto IsWritethoughEnabled(PTEntry *entry) -> bool;
    inline static auto IsCachable(PTEntry *entry) -> bool;
    inline static auto WasAccessed(PTEntry *entry) -> bool;

    inline static void SetAttribute(PTEntry *entry, PTEntry::Flags flag);
    inline static void ClearAttribute(PTEntry *entry, PTEntry::Flags flag);

    inline static auto GetEntryNumber(ulong virtual_address) -> ulong;

    inline static auto GetPhysicalBase(PTEntry *entry) -> ulong;
    inline static void SetPhysicalBase(PTEntry *entry, const ulong physical_address);
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

    inline static void SetAttribute(PDTEntry *entry, PDTEntry::Flags flag);
    inline static void ClearAttribute(PDTEntry *entry, PDTEntry::Flags flag);

    inline static auto GetEntryNumber(ulong virtual_address) -> ulong;

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

    inline static void SetAttribute(PDPTEntry *entry, PDPTEntry::Flags flag);
    inline static void ClearAttribute(PDPTEntry *entry, PDPTEntry::Flags flag);

    inline static auto GetEntryNumber(ulong virtual_address) -> ulong;

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

    inline static void SetAttribute(PML4Entry *entry, PML4Entry::Flags flag);
    inline static void ClearAttribute(PML4Entry *entry, PML4Entry::Flags flag);

    inline static auto GetEntryNumber(ulong virtual_address) -> ulong;

    inline static PDPT *GetPDPTBase(PML4Entry *entry);
    inline static void SetPDPTBase(PML4Entry *entry, ulong pdpt_address);
    inline static void SetPDPTBase(PML4Entry *entry, PDPT *address);
} __attribute__((__packed__));
typedef PageMapLevel4 PML4;

#endif //__PAGING_STRUCTURES__
