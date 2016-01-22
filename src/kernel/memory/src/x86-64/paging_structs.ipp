#include "../../include/x86-64/paging_structs.hpp"

// ~ PML4Entry

auto PML4Entry::ToPDPT() const -> PDPT *
{
    return reinterpret_cast<PageDirectoryPointerTable*>(GetBits<uint64>(entry, PDPT_BASE));
}

PML4Entry::operator uint64 &()
{
    return entry;
}

// ~ PDPTEntry

auto PDPTEntry::ToPDT() const -> PDT *
{
    return reinterpret_cast<PageDirectoryTable*>(GetBits<uint64>(entry, PDT_BASE));
}

PDPTEntry::operator uint64 &()
{
    return entry;
}

// ~ PDTEntry

auto PDTEntry::ToPT() const -> PT *
{
    return reinterpret_cast<PageTable*>(GetBits(entry, PT_BASE));
}

PDTEntry::operator uint64 &()
{
    return entry;
}

// ~ PTEntry

PTEntry::operator uint64 &()
{
    return entry;
}

// ~ PageMapLevel4

bool PageMapLevel4::IsPresent(PML4Entry *entry)
{
    return IsBitSet(*entry, PRESENT_BIT);
}

bool PageMapLevel4::IsWritable(PML4Entry *entry)
{
    return IsBitSet(*entry, WRITABLE_BIT);
}

bool PageMapLevel4::IsUserMode(PML4Entry *entry)
{
    return IsBitSet(*entry, USER_BIT);
}

bool PageMapLevel4::IsWritethoughEnabled(PML4Entry *entry)
{
    return IsBitSet(*entry, WRITETHROUGH_BIT);
}

bool PageMapLevel4::IsCachable(PML4Entry *entry)
{
    return (IsBitSet(*entry, NOT_CACHEABLE_BIT)) ? false : true;
}

bool PageMapLevel4::WasAccessed(PML4Entry *entry)
{
    return IsBitSet(*entry, ACCESSED_BIT);
}

void PageMapLevel4::SetAttribute(PML4Entry *entry, PML4Entry::Flags flag)
{
    *entry |= flag;
}

void PageMapLevel4::ClearAttribute(PML4Entry *entry, PML4Entry::Flags flag)
{
    *entry &= ~flag;
}

auto PageMapLevel4::GetEntryNumber(ulong virtual_address) -> ulong
{
    return GetBits(virtual_address, 39, 47);
}

PDPT *PageMapLevel4::GetPDPTBase(PML4Entry *entry)
{
    return entry->ToPDPT();
}

void PageMapLevel4::SetPDPTBase(PML4Entry *entry, ulong pdpt_address)
{
    SetBits(static_cast<uint64 &>(*entry), PML4Entry::PDPT_BASE, pdpt_address);
}

void PageMapLevel4::SetPDPTBase(PML4Entry *entry, PDPT *address)
{
    SetBits(static_cast<uint64 &>(*entry), PML4Entry::PDPT_BASE, reinterpret_cast<uint64>(address));
}

// ~ PageDirectoryPointerTable

bool PageDirectoryPointerTable::IsPresent(PDPTEntry *entry)
{
    return IsBitSet(*entry, PRESENT_BIT);
}

bool PageDirectoryPointerTable::IsWritable(PDPTEntry *entry)
{
    return IsBitSet(*entry, WRITABLE_BIT);
}

bool PageDirectoryPointerTable::IsUserMode(PDPTEntry *entry)
{
    return IsBitSet(*entry, USER_BIT);
}

bool PageDirectoryPointerTable::IsWritethoughEnabled(PDPTEntry *entry)
{
    return IsBitSet(*entry, WRITETHROUGH_BIT);
}

bool PageDirectoryPointerTable::IsCachable(PDPTEntry *entry)
{
    return (IsBitSet(*entry, NOT_CACHEABLE_BIT)) ? false : true;
}

bool PageDirectoryPointerTable::WasAccessed(PDPTEntry *entry)
{
    return IsBitSet(*entry, ACCESSED_BIT);
}

void PageDirectoryPointerTable::SetAttribute(PDPTEntry *entry, PDPTEntry::Flags flag)
{
    *entry |= flag;
}

void PageDirectoryPointerTable::ClearAttribute(PDPTEntry *entry, PDPTEntry::Flags flag)
{
    *entry &= ~flag;
}

auto PageDirectoryPointerTable::GetEntryNumber(ulong virtual_address) -> ulong
{
    return GetBits(virtual_address, 30, 38);
}

PDT *PageDirectoryPointerTable::GetPDTBase(PDPTEntry *entry)
{
    return entry->ToPDT();
}

void PageDirectoryPointerTable::SetPDTBase(PDPTEntry *entry, ulong pdpt_address)
{
    SetBits(static_cast<uint64 &>(*entry), PDPTEntry::PDT_BASE, pdpt_address);
}

void PageDirectoryPointerTable::SetPDTBase(PDPTEntry *entry, PDT *address)
{
    SetBits(static_cast<uint64 &>(*entry), PDPTEntry::PDT_BASE, reinterpret_cast<ulong>(address));
}

// ~ PageDirectoryTable

bool PageDirectoryTable::IsPresent(PDTEntry *entry)
{
    return IsBitSet(*entry, PRESENT_BIT);
}

bool PageDirectoryTable::IsWritable(PDTEntry *entry)
{
    return IsBitSet(*entry, WRITABLE_BIT);
}

bool PageDirectoryTable::IsUserMode(PDTEntry *entry)
{
    return IsBitSet(*entry, USER_BIT);
}

bool PageDirectoryTable::IsWritethoughEnabled(PDTEntry *entry)
{
    return IsBitSet(*entry, WRITETHROUGH_BIT);
}

bool PageDirectoryTable::IsCachable(PDTEntry *entry)
{
    return (IsBitSet(*entry, NOT_CACHEABLE_BIT)) ? false : true;
}

bool PageDirectoryTable::WasAccessed(PDTEntry *entry)
{
    return IsBitSet(*entry, ACCESSED_BIT);
}

void PageDirectoryTable::SetAttribute(PDTEntry *entry, PDTEntry::Flags flag)
{
    *entry |= flag;
}

void PageDirectoryTable::ClearAttribute(PDTEntry *entry, PDTEntry::Flags flag)
{
    *entry &= ~flag;
}

auto PageDirectoryTable::GetEntryNumber(ulong virtual_address) -> ulong
{
    return GetBits(virtual_address, 21, 29);
}

PT *PageDirectoryTable::GetPTBase(PDTEntry *entry)
{
    return entry->ToPT();
}

void PageDirectoryTable::SetPTBase(PDTEntry *entry, ulong pt_address)
{
    SetBits(static_cast<uint64 &>(*entry), PDTEntry::PT_BASE, pt_address);
}

void PageDirectoryTable::SetPTBase(PDTEntry *entry, PT *address)
{
    SetBits(static_cast<uint64 &>(*entry), PDTEntry::PT_BASE, reinterpret_cast<uint64>(address));
}

// ~ PageTable

bool PageTable::IsPresent(PTEntry *entry)
{
    return IsBitSet(*entry, PRESENT_BIT);
}

bool PageTable::IsWritable(PTEntry *entry)
{
    return IsBitSet(*entry, WRITABLE_BIT);
}

bool PageTable::IsUserMode(PTEntry *entry)
{
    return IsBitSet(*entry, USER_BIT);
}

bool PageTable::IsWritethoughEnabled(PTEntry *entry)
{
    return IsBitSet(*entry, WRITETHROUGH_BIT);
}

bool PageTable::IsCachable(PTEntry *entry)
{
    return (IsBitSet(*entry, NOT_CACHEABLE_BIT)) ? false : true;
}

bool PageTable::WasAccessed(PTEntry *entry)
{
    return IsBitSet(*entry, ACCESSED_BIT);
}

void PageTable::SetAttribute(PTEntry *entry, PTEntry::Flags flag)
{
    *entry |= flag;
}

void PageTable::ClearAttribute(PTEntry *entry, PTEntry::Flags flag)
{
    *entry &= ~flag;
}

auto PageTable::GetEntryNumber(ulong virtual_address) -> ulong
{
    return GetBits(virtual_address, 12, 20);
}

auto PageTable::GetPhysicalBase(PTEntry *entry) -> ulong
{
    return (GetBits(static_cast<uint64 &>(*entry), PTEntry::FRAME) << 12);
}

void PageTable::SetPhysicalBase(PTEntry *entry, ulong physical_address)
{
    SetBits(static_cast<uint64 &>(*entry), PTEntry::FRAME, static_cast<uint64>(physical_address));
}
