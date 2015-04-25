#include "vmm_standard.hpp"
#include "../../system/system.hpp"
using namespace kernel::memory;

StandardVirtualMemoryManager::StandardVirtualMemoryManager() : system(System::GetInstance())
{
    current_pml4 = reinterpret_cast<PML4*>(INIT_PML4);
    current_pdpt = reinterpret_cast<PDPT*>(INIT_PDPT);
    current_pdt  = reinterpret_cast<PDT*>(INIT_PDT);
    current_pt   = reinterpret_cast<PT*>(INIT_PT);
}

StandardVirtualMemoryManager::~StandardVirtualMemoryManager()
{

}

void *StandardVirtualMemoryManager::AllocatePage(bool writeable, bool supervisor, bool executable, void *physical_address)
{
    PTEntry *entry = FindFreePTEntry();
    if(entry)
    {
        if(physical_address == nullptr)
            physical_address = system.AllocateBlock();
        PT::SetPhysicalBase(entry, PTR_TO_VAR(physical_address));

        if(writeable == true)
            PT::SetAttribute(entry, PT_WRITABLE);

        if(supervisor == false)
            PT::SetAttribute(entry, PT_USER);

        if(executable == false)
            PT::SetAttribute(entry, PT_NOT_EXECUTABLE);

        PT::SetAttribute(entry, PT_PRESENT);
        return physical_address;
    }
    return nullptr;
}

void *StandardVirtualMemoryManager::AllocatePages(size_t number_of_pages)
{
    size_t needed_pages = number_of_pages;
    uint found_page_number = 0;
    for(uint i = 0; i < PAGE_ENTRIES; i++)
    {
        if(std::IsBitSet(current_pt->entry[i], PRESENT_BIT) == false)
            needed_pages--;
        else if(std::IsBitSet(current_pt->entry[i], PRESENT_BIT) == true && needed_pages < number_of_pages)
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
        current_pt = reinterpret_cast<PT*>(system.AllocateBlock());
        if(current_pt == nullptr)
            return nullptr;

        memzero(current_pt, sizeof(PT));
        PDT::SetPTBase(pdt_entry, current_pt);
        PDT::SetAttribute(pdt_entry, PDT_WRITABLE);
        PDT::SetAttribute(pdt_entry, PDT_PRESENT);
    }
    else
    {
        for(uint i = found_page_number; i < found_page_number + number_of_pages; i++)
        {
            void *base_address = system.AllocateBlock();

            PTEntry *entry = &current_pt->entry[i];
            PT::SetPhysicalBase(entry, PTR_TO_VAR(base_address));
            PT::SetAttribute(entry, PT_WRITABLE);
            PT::SetAttribute(entry, PT_PRESENT);
        }
    }
}

void StandardVirtualMemoryManager::FreePage(void *virtual_address)
{
    PTEntry *entry = &current_pt->entry[PT::GetEntryNumber(PTR_TO_VAR(virtual_address))];
    if(entry)
        PT::ClearAttribute(entry, PT_PRESENT);
}

void StandardVirtualMemoryManager::FreePages(void *virtual_address, size_t number_of_pages)
{
    for(uint i = PT::GetEntryNumber(PTR_TO_VAR(virtual_address)); i <= number_of_pages; i++)
    {
        PTEntry *entry = &current_pt->entry[i];
        if(entry)
            PT::ClearAttribute(entry, PT_PRESENT);
    }
}

bool StandardVirtualMemoryManager::MapPage(ulong physical_address, ulong virtual_address, ulong additional_flag)
{
    PML4Entry *pml4_entry = &current_pml4->entry[PML4::GetEntryNumber(virtual_address)];
    if(PML4::IsPresent(pml4_entry) == false)
    {
        PML4::SetPDPTBase(pml4_entry, current_pdpt);
        PML4::SetAttribute(pml4_entry, PML4_WRITABLE);
        PML4::SetAttribute(pml4_entry, PML4_PRESENT);
    }

    PDPTEntry *pdpt_entry = &current_pdpt->entry[PDPT::GetEntryNumber(virtual_address)];
    if(PDPT::IsPresent(pdpt_entry) == false)
    {
        PDPT::SetPDTBase(pdpt_entry, current_pdt);
        PDPT::SetAttribute(pdpt_entry, PDPT_WRITABLE);
        PDPT::SetAttribute(pdpt_entry, PDPT_PRESENT);
    }

    PDTEntry *pdt_entry = &current_pdt->entry[PDT::GetEntryNumber(virtual_address)];
    if(PDT::IsPresent(pdt_entry) == false)
    {
        PDT::SetPTBase(pdt_entry, current_pt);
        PDT::SetAttribute(pdt_entry, PDT_WRITABLE);
        PDT::SetAttribute(pdt_entry, PDT_PRESENT);
    }

    PTEntry *pt_entry = &current_pt->entry[PT::GetEntryNumber(virtual_address)];
    if(PT::IsPresent(pt_entry) == false)
    {
        PT::SetPhysicalBase(pt_entry, physical_address);
        PT::SetAttribute(pt_entry, *(reinterpret_cast<PTEntryFlags*>(&additional_flag)));
        PT::SetAttribute(pt_entry, PT_PRESENT);
    }
    return true;
}

bool StandardVirtualMemoryManager::MapPages(ulong physical_address, ulong virtual_address, size_t memory_size, ulong additional_flag)
{
    PML4Entry *pml4_entry = &current_pml4->entry[PML4::GetEntryNumber(virtual_address)];
    system << info << "VMM -> MapPage() PML4 entry: " << std::hex << *pml4_entry;
    if(PML4::IsPresent(pml4_entry) == false)
    {
        PML4::SetPDPTBase(pml4_entry, current_pdpt);
        PML4::SetAttribute(pml4_entry, PML4_WRITABLE);
        PML4::SetAttribute(pml4_entry, PML4_PRESENT);
    }

    PDPTEntry *pdpt_entry = &current_pdpt->entry[PDPT::GetEntryNumber(virtual_address)];
    if(PDPT::IsPresent(pdpt_entry) == false)
    {
        PDPT::SetPDTBase(pdpt_entry, current_pdt);
        PDPT::SetAttribute(pdpt_entry, PDPT_WRITABLE);
        PDPT::SetAttribute(pdpt_entry, PDPT_PRESENT);
    }
    system << " PDPT entry: " << *pdpt_entry;

    PDTEntry *pdt_entry = &current_pdt->entry[PDT::GetEntryNumber(virtual_address)];
    if(PDT::IsPresent(pdt_entry) == false)
    {
        current_pt = reinterpret_cast<PT*>(system.AllocateBlock());
        if(current_pt == nullptr)
            return false;

        memzero(current_pt, sizeof(PT));
        PDT::SetPTBase(pdt_entry, current_pt);
        PDT::SetAttribute(pdt_entry, PDT_WRITABLE);
        PDT::SetAttribute(pdt_entry, PDT_PRESENT);
    }
    system << " PDT entry: " << *pdt_entry;

    uint needed_pages = memory_size / PAGE_SIZE;
    system << " Needed pages: " << std::dec << memory_size << video::endl;
    for(uint current_entry = PT::GetEntryNumber(virtual_address), needed_pages = memory_size / PAGE_SIZE; current_entry < (PT::GetEntryNumber(virtual_address) + needed_pages); current_entry++, physical_address += PAGE_SIZE)
    {
        PTEntry *pt_entry = &current_pt->entry[current_entry];
        if(PT::IsPresent(pt_entry) == false)
        {
            PT::SetPhysicalBase(pt_entry, physical_address);
            PT::SetAttribute(pt_entry, *(reinterpret_cast<PTEntryFlags*>(&additional_flag)));
            PT::SetAttribute(pt_entry, PT_PRESENT);
        }
    }
    return true;
}

bool StandardVirtualMemoryManager::UnmapPage(ulong virtual_address)
{

}

bool StandardVirtualMemoryManager::UnmapPages(ulong virtual_address, size_t memory_size)
{

}

PML4Entry *StandardVirtualMemoryManager::FindFreePML4Entry()
{
    for(uint i = 0; i < PAGE_ENTRIES; i++)
    {
        if(PML4::IsPresent(&current_pml4->entry[i]) == false)
            return &current_pml4->entry[i];
    }
    return nullptr;
}

PDPTEntry *StandardVirtualMemoryManager::FindFreePDPTEntry()
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
        current_pdpt = reinterpret_cast<PDPT*>(system.AllocateBlock());
        if(current_pdpt == nullptr)
            return nullptr;

        memzero(current_pdpt, sizeof(PDPT));
        PML4::SetPDPTBase(free_entry, current_pdpt);
    }
    PML4::SetAttribute(free_entry, PML4_PRESENT);

    PDPT::SetAttribute(&current_pdpt->entry[0], PDPT_PRESENT);
    return &current_pdpt->entry[0];
}

PDTEntry *StandardVirtualMemoryManager::FindFreePDTEntry()
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
        current_pdt = reinterpret_cast<PDT*>(system.AllocateBlock());
        if(current_pdt == nullptr)
            return nullptr;

        memzero(current_pdt, sizeof(PDT));
        PDPT::SetPDTBase(free_entry, current_pdt);
    }
    PDPT::SetAttribute(free_entry, PDPT_PRESENT);

    PDT::SetAttribute(&current_pdt->entry[0], PDT_PRESENT);
    return &current_pdt->entry[0];
}

PTEntry *StandardVirtualMemoryManager::FindFreePTEntry()
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
        current_pt = reinterpret_cast<PT*>(system.AllocateBlock());
        if(current_pt == nullptr)
            return nullptr;

        memzero(current_pt, sizeof(PT));
        PDT::SetPTBase(free_entry, current_pt);
    }
    PDT::SetAttribute(free_entry, PDT_PRESENT);

    PT::SetAttribute(&current_pt->entry[0], PT_PRESENT);
    return &current_pt->entry[0];
}
