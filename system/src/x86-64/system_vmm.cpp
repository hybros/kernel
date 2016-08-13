#include "../../include/x86-64/system_vmm.hpp"

#include <Hybros/System>
#include <HTerminal>

#include "../../include/system_manager.hpp"

namespace Hybros
{
namespace VirtualMemory
{

Manager::Manager()
{
    current_pml4 = reinterpret_cast<PML4*>(INIT_PML4);
    current_pdpt = reinterpret_cast<PDPT*>(INIT_PDPT);
    current_pdt  = reinterpret_cast<PDT*>(INIT_PDT);
    current_pt   = reinterpret_cast<PT*>(INIT_PT);
}

auto Manager::getPageSize() const -> size_t
{
    return PAGE_SIZE;
}

//Manager::~VirtualMemoryManager()
//{

//}

void *Manager::allocatePage(bool writable, bool supervisor, bool executable)
{
    ulong physical_address = PTR_TO_VAR(allocateBlock());
    ulong virtual_address = physical_address;

    if(supervisor == true)
        virtual_address |= KERNEL_MODE_BASE;

    uint entry_number = MapBeginningPage(physical_address, virtual_address);
    if(entry_number != 0xFFFFFFFF)
    {
        PTEntry *pt_entry = &current_pt->entry[entry_number];

        if(writable == true)
            PT::SetAttribute(pt_entry, PTEntry::WRITABLE);

        if(supervisor == false)
            PT::SetAttribute(pt_entry, PTEntry::USER);

        if(executable == false)
            PT::SetAttribute(pt_entry, PTEntry::NOT_EXECUTABLE);

        return VAR_TO_PTR(virtual_address);
    }
    else
        return nullptr;
}

void *Manager::allocatePages(ulong number_of_pages)
{
    size_t needed_pages = number_of_pages;
    size_t found_page_number = 0;
    for(ulong i = 0; i < PAGE_ENTRIES; i++)
    {
        if(IsBitSet(current_pt->entry[i], PRESENT_BIT) == false)
            needed_pages--;
        else if(IsBitSet(current_pt->entry[i], PRESENT_BIT) == true && needed_pages < number_of_pages)
            needed_pages = number_of_pages;
        else if(needed_pages == 0)
        {
            found_page_number = i - number_of_pages;
            break;
        }
    }

    if(found_page_number == 0)
    {
        PDTEntry *pdt_entry = FindFreePDTEntry();
        current_pt = reinterpret_cast<PT*>(SYSTEM.AllocateBlock());
        if(current_pt == nullptr)
            return nullptr;

        memzero(current_pt, sizeof(PT));
        PDT::SetPTBase(pdt_entry, current_pt);
        PDT::SetAttribute(pdt_entry, PDTEntry::WRITABLE);
        PDT::SetAttribute(pdt_entry, PDTEntry::PRESENT);
    }
    else
    {
        for(ulong i = found_page_number; i < found_page_number + number_of_pages; i++)
        {
            void *base_address = SYSTEM.AllocateBlock();

            PTEntry *entry = &current_pt->entry[i];
            PT::SetPhysicalBase(entry, PTR_TO_VAR(base_address));
            PT::SetAttribute(entry, PTEntry::WRITABLE);
            PT::SetAttribute(entry, PTEntry::PRESENT);
        }
    }
}

void Manager::freePage(void *virtual_address)
{
    PTEntry *entry = &current_pt->entry[PT::GetEntryNumber(PTR_TO_VAR(virtual_address))];
    if(entry)
        PT::ClearAttribute(entry, PTEntry::PRESENT);
}

void Manager::freePages(void *virtual_address, ulong number_of_pages)
{
    for(ulong i = PT::GetEntryNumber(PTR_TO_VAR(virtual_address)); i <= number_of_pages; i++)
    {
        PTEntry *entry = &current_pt->entry[i];
        if(entry)
            PT::ClearAttribute(entry, PTEntry::PRESENT);
    }
}

bool Manager::mapPage(ulong physical_address, ulong virtual_address, ulong additional_flag)
{
    physical_address = RoundDownToPrevPage(physical_address);
    virtual_address = RoundDownToPrevPage(virtual_address);

    /*SYSTEM << INFO << "HYBROS -> ~ Manager: MapPage()" << endl
           << "    " << INFO << "Physical address: " << physical_address << endl
           << "    " << INFO << "Virtual address: " << virtual_address << endl;*/

//    uint entry_number = PT::GetEntryNumber(virtual_address);
//    if(PT::IsPresent(&current_pt->entry[entry_number]) == true)
//    {
//        SYSTEM << "    " << SUCC << "Page present!" << endl;
//        return true;
//    }

    uint entry_number = MapBeginningPage(physical_address, virtual_address);
    if(entry_number != 0xFFFFFFFF)
    {
        PTEntry *pt_entry = &current_pt->entry[entry_number];
        PT::SetAttribute(pt_entry, *(reinterpret_cast<PTEntry::Flags *>(&additional_flag)));
        return true;
    }
    else
        return false;
}

bool Manager::mapPages(ulong physical_address, ulong virtual_address, size_t memory_size, ulong additional_flag)
{
    physical_address = RoundDownToPrevPage(physical_address);
    virtual_address = RoundDownToPrevPage(virtual_address);

    uint entry_number = MapBeginningPage(physical_address, virtual_address);
    if(entry_number == 0xFFFFFFFF)
        return false;

    for(uint current_entry = entry_number, needed_pages = RoundUpToNextPage(memory_size); current_entry < (entry_number + needed_pages); current_entry++, physical_address += PAGE_SIZE)
    {
        PTEntry *pt_entry = &current_pt->entry[current_entry];
        if(PT::IsPresent(pt_entry) == false)
        {
            PT::SetPhysicalBase(pt_entry, physical_address);
            PT::SetAttribute(pt_entry, *(reinterpret_cast<PTEntry::Flags*>(&additional_flag)));
            PT::SetAttribute(pt_entry, PTEntry::PRESENT);
        }
    }
    return true;
}

auto Manager::unmapPage(ulong virtual_address) -> bool
{
    PTEntry *pt_entry = &current_pt->entry[PT::GetEntryNumber(virtual_address)];
    if(PT::IsPresent(pt_entry) == true)
    {
        PT::ClearAttribute(pt_entry, PTEntry::PRESENT);
        return true;
    }
    else
        return false;
}

auto Manager::unmapPages(ulong virtual_address, ulong memory_size) -> bool
{
    for(uint current_entry = PT::GetEntryNumber(virtual_address), needed_pages = RoundUpToNextPage(memory_size); current_entry < (PT::GetEntryNumber(virtual_address) + needed_pages); current_entry++)
    {
        PTEntry *pt_entry = &current_pt->entry[current_entry];
        if(PT::IsPresent(pt_entry) == true)
            PT::ClearAttribute(pt_entry, PTEntry::PRESENT);
    }
    return true;
}

PML4Entry *Manager::findFreePML4Entry()
{
    for(uint i = 0; i < PAGE_ENTRIES; i++)
    {
        if(PML4::IsPresent(&current_pml4->entry[i]) == false)
            return &current_pml4->entry[i];
    }
    return nullptr;
}

PDPTEntry *Manager::findFreePDPTEntry()
{
    for(uint i = 0; i < PAGE_ENTRIES; i++)
    {
        if(PDPT::IsPresent(&current_pdpt->entry[i]) == false)
            return &current_pdpt->entry[i];
    }

    PML4Entry *free_entry = FindFreePML4Entry();
    current_pdpt = PML4::GetPDPTBase(free_entry);
    if(current_pdpt == nullptr)
    {
        current_pdpt = reinterpret_cast<PDPT*>(SYSTEM.AllocateBlock());
        if(current_pdpt == nullptr)
            return nullptr;

        memzero(current_pdpt, sizeof(PDPT));
        PML4::SetPDPTBase(free_entry, current_pdpt);
    }
    PML4::SetAttribute(free_entry, PML4Entry::PRESENT);

    PDPT::SetAttribute(&current_pdpt->entry[0], PDPTEntry::PRESENT);
    return &current_pdpt->entry[0];
}

PDTEntry *Manager::findFreePDTEntry()
{
    for(uint i = 0; i < PAGE_ENTRIES; i++)
    {
        if(PDT::IsPresent(&current_pdt->entry[i]) == false)
            return &current_pdt->entry[i];
    }

    PDPTEntry *free_entry = FindFreePDPTEntry();
    current_pdt = PDPT::GetPDTBase(free_entry);
    if(current_pdt == nullptr)
    {
        current_pdt = reinterpret_cast<PDT*>(SYSTEM.AllocateBlock());
        if(current_pdt == nullptr)
            return nullptr;

        memzero(current_pdt, sizeof(PDT));
        PDPT::SetPDTBase(free_entry, current_pdt);
    }
    PDPT::SetAttribute(free_entry, PDPTEntry::PRESENT);

    PDT::SetAttribute(&current_pdt->entry[0], PDTEntry::PRESENT);
    return &current_pdt->entry[0];
}

PTEntry *Manager::findFreePTEntry()
{
    for(uint i = 0; i < PAGE_ENTRIES; i++)
    {
        if(PT::IsPresent(&current_pt->entry[i]) == false)
            return &current_pt->entry[i];
    }

    PDTEntry *free_entry = FindFreePDTEntry();
    current_pt = PDT::GetPTBase(free_entry);
    if(current_pt == nullptr)
    {
        current_pt = reinterpret_cast<PT*>(SYSTEM.AllocateBlock());
        if(current_pt == nullptr)
            return nullptr;

        memzero(current_pt, sizeof(PT));
        PDT::SetPTBase(free_entry, current_pt);
    }
    PDT::SetAttribute(free_entry, PDTEntry::PRESENT);

    PT::SetAttribute(&current_pt->entry[0], PTEntry::PRESENT);
    return &current_pt->entry[0];
}

auto Manager::mapBeginningPage(ulong physical_address, ulong virtual_address) -> uint
{
	/*SYSTEM << INFO << "HYBROS -> Debugging... <----------------------------------------" << endl
		<< "~ Manager: MapBeginningPage()" << endl
		<< "    " << INFO << "Physical address: " << hex << physical_address << endl
		<< "    " << INFO << "Virtual address: " << virtual_address << dec << endl;*/
    PML4Entry *pml4_entry = &current_pml4->entry[PML4::GetEntryNumber(virtual_address)];
	//SYSTEM << "    " << INFO << "PML4 entry: " << hex << static_cast<uint64&>(*pml4_entry) << endl;
    if(PML4::IsPresent(pml4_entry) == false)
    {
		//SYSTEM << "             - Is not present!" << endl;
        PDPT *related_pdpt = PML4::GetPDPTBase(pml4_entry);
        if(related_pdpt == nullptr)
        {
            related_pdpt = reinterpret_cast<PDPT*>(SYSTEM.AllocateBlock());
            if(related_pdpt == nullptr)
                return 0xFFFFFFFF;

            current_pdpt = related_pdpt;
        }
        else
            current_pdpt = related_pdpt;

        memzero(current_pdpt, sizeof(PDPT));
        PML4::SetPDPTBase(pml4_entry, current_pdpt);
        PML4::SetAttribute(pml4_entry, PML4Entry::WRITABLE);
        PML4::SetAttribute(pml4_entry, PML4Entry::PRESENT);
    }
	else
	{
		//SYSTEM << "             - Is present!" << endl;
		current_pdpt = PML4::GetPDPTBase(pml4_entry);
	}

	uint entry = PDPT::GetEntryNumber(virtual_address);
    PDPTEntry *pdpt_entry = &current_pdpt->entry[entry];
	//SYSTEM << "    " << INFO << "PDPT entry: " << hex << current_pdpt << endl; //static_cast<uint64&>(*pdpt_entry) << endl;
    if(PDPT::IsPresent(pdpt_entry) == false)
    {
        PDT *related_pdt = PDPT::GetPDTBase(pdpt_entry);
        if(related_pdt == nullptr)
        {
            related_pdt = reinterpret_cast<PDT*>(SYSTEM.AllocateBlock());
            if(related_pdt == nullptr)
                return 0xFFFFFFFF;

            current_pdt = related_pdt;
        }
        else
            current_pdt = related_pdt;

        memzero(current_pdt, sizeof(PDT));
        PDPT::SetPDTBase(pdpt_entry, current_pdt);
        PDPT::SetAttribute(pdpt_entry, PDPTEntry::WRITABLE);
        PDPT::SetAttribute(pdpt_entry, PDPTEntry::PRESENT);
    }
    else
        current_pdt = PDPT::GetPDTBase(pdpt_entry);

    //SYSTEM << " | PDPT entry: " << static_cast<uint64&>(*pdpt_entry);

    PDTEntry *pdt_entry = &current_pdt->entry[PDT::GetEntryNumber(virtual_address)];
    if(PDT::IsPresent(pdt_entry) == false)
    {
        PT *related_pt = PDT::GetPTBase(pdt_entry);
        if(related_pt == nullptr)
        {
            related_pt = reinterpret_cast<PT*>(SYSTEM.AllocateBlock());
            if(related_pt == nullptr)
                return 0xFFFFFFFF;

            current_pt = related_pt;
        }
        else
            current_pt = related_pt;

        memzero(current_pt, sizeof(PT));
        PDT::SetPTBase(pdt_entry, current_pt);
        PDT::SetAttribute(pdt_entry, PDTEntry::WRITABLE);
        PDT::SetAttribute(pdt_entry, PDTEntry::PRESENT);
    }
    else
        current_pt = PDT::GetPTBase(pdt_entry);

    //SYSTEM << "    " << INFO << "PT: " << current_pt << endl;
    uint entry_number = PT::GetEntryNumber(virtual_address);
    PTEntry *pt_entry = &current_pt->entry[entry_number];
    if(PT::IsPresent(pt_entry) == false)
    {
        PT::SetPhysicalBase(pt_entry, physical_address);
        PT::SetAttribute(pt_entry, PTEntry::PRESENT);
    }
	//SYSTEM << INFO << "HYBROS -> Debugging end <-------------------------------------" << endl;
    return entry_number;
}

auto Manager::roundDownToPrevPage(size_t memory) const -> ulong
{
    return ((memory / PAGE_SIZE) * PAGE_SIZE);
}

auto Manager::roundUpToNextPage(ulong memory_size) const -> ulong
{
    int remainder = memory_size % PAGE_SIZE;
    return ((memory_size + PAGE_SIZE - remainder));
}

auto Manager::roundUpToNextPageNumber(ulong memory_size) const -> ulong
{
    int remainder = memory_size % PAGE_SIZE;
    return ((memory_size + PAGE_SIZE - remainder) / PAGE_SIZE);
}
