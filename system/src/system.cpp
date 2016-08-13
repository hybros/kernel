#include "../include/system.hpp"

#include <HBitOperations>
#include <HStdHelper>
#include <cMemory>
#include <HSystemPhysicalMemoryManager>
#include <HSystemVirtualMemoryManager>
#include <HSystemHeapMemoryManager>
#include <HInterprocessInterrupt>
#include <HSystemTerminal>

#include "../include/pre_mm.hpp"
#include "../include/system_asm.hpp"
#include "../include/system_helper.hpp"
#include "../include/system_internal.hpp"

#define SYSTEM_PMM_START 200
#define SYSTEM_VMM_START 300
#define SYSTEM_HMM_START 400

extern "C"
{

extern uchar ap_number;
extern void boot_ap();
extern void boot_ap_end();

}

void HSystem::CheckMultibootInfo()
{
    if(IsBitSet(system_mb_info->flags, 0) == true)
    {
        system_mb_mem_size = system_mb_info->mem_lower + system_mb_info->mem_upper;
        system_term << INFO << "HYBROS -> Multiboot: Full memory size: " << system_mb_mem_size << kB << endl;
    }
    else
        system_term << WARN << "HYBROS -> Multiboot: Memory size seems to not be available!" << endl;

    if(IsBitSet(system_mb_info->flags, 1) == true)
        system_term << INFO << "HYBROS -> Multiboot: BIOS boot device info: " << hex << system_mb_info->boot_device << dec << endl;
    else
        system_term << WARN << "HYBROS -> Multiboot: BIOS boot device info seems to not be available!" << endl;

    if(IsBitSet(system_mb_info->flags, 2) == true)
    {
        system_mb_cmdline = reinterpret_cast<char*>(system_mb_info->cmdline);
        system_term << INFO << "HYBROS -> Multiboot: Command line: " << static_cast<const char *>(system_mb_cmdline) << endl;
    }
    else
        system_term << WARN << "HYBROS -> Multiboot: Command line was not provided!" << endl;

    if(IsBitSet(system_mb_info->flags, 3) == true)
    {
        system_term << INFO << "HYBROS -> Multiboot: Module/s " << dec << system_mb_info->mods_count << " are available!" << endl;

        multiboot::multiboot_mod_list *module = reinterpret_cast<multiboot::multiboot_mod_list*>(system_mb_info->mods_addr);
        for(uint i = 0; i < system_mb_info->mods_count; i++)
        {
            system_term << "    " << INFO << "Module " << i << ": " << endl
                        << "        " << "Start address: " << hex << module->mod_start << endl
                        << "        " << "End address:   " << module->mod_end << endl;
            module += sizeof(multiboot::multiboot_mod_list);
        }
    }
    else
        system_term << WARN << "HYBROS -> Multiboot: Modules are not available!" << endl;

    if(IsBitSet(system_mb_info->flags, 6) == true)
    {
        system_term << INFO << "HYBROS -> Multiboot: BIOS memory map is usable." << endl;
    }
    else
        system_term << WARN << "HYBROS -> Multiboot: BIOS memory map is not usable!" << endl;

    if(IsBitSet(system_mb_info->flags, 7) == true)
    {
        system_term << INFO << "HYBROS -> Multiboot: BIOS drives number: " << system_mb_info->drives_length << endl;
    }
    else
        system_term << WARN << "HYBROS -> Multiboot: BIOS drives number is not provided!" << endl;
}

void HSystem::CheckMultiboot2Info()
{
}

bool HSystem::CheckMultiProcessorSupport()
{
    uint ebda = GetBIOSDataAreaValue<ushort>(BDA_LPT4_EBDA) << 4;  // Usually
    uint low_memory = system_mb_info->mem_lower * 1000;     // In kilobytes; so x * 1024 to get size in bytes
    void *rsdp_address = nullptr,
         *mp_address = nullptr;

    if(ebda > 0)
        rsdp_address = GetRootSystemDescriptionPointer(ebda, 1024);

    if(rsdp_address == nullptr)
        rsdp_address = GetRootSystemDescriptionPointer(0xE0000, 0x1FFFF);

    if(rsdp_address)
        system_term << "    " << INFO << "RSDP descriptor found at: " << rsdp_address << endl;
    else
        system_term << "    " << INFO << "RSDP descriptor not found!" << endl;

    if(ebda > 0)
        mp_address = GetFloatingPointStructure(ebda, 1024);

    if(mp_address == nullptr)
        mp_address = GetFloatingPointStructure(low_memory - 1024, 1024);

    if(mp_address == nullptr)
        mp_address = GetFloatingPointStructure(0xF0000, 0x10000);

    if(mp_address == nullptr)
    {
        system_term << "    " << WARN << "Multiprocessor signature not found..." << endl;
        return false;
    }
    else
    {
        system_term << "    " << INFO << "Multiprocessor signature found at: " << static_cast<const void *>(mp_address) << endl;
        tmp_pointer = mp_address;
        return true;
    }
}

bool HSystem::InitMemoryManagers()
{
    new (&system_pmm) PhysicalMemoryManager(system_mb_info, system_mb_mem_size);
    system_term << INFO << "HYBROS -> Memory Managers: PhysicalMemoryManager initialised!" << endl;

    new (&system_vmm) VirtualMemoryManager;
    system_vmm.SetStatus(true);
    system_term << INFO << "HYBROS -> Memory Managers: VirtualMemoryManager initialised!" << endl;

//    system_vmm.MapPages(0x00200000, KERNEL_HEAP, KERNEL_HEAP_END - KERNEL_HEAP);

    new (&system_hmm) HeapMemoryManager(0x00200000, KERNEL_HEAP, KERNEL_HEAP_SIZE);
    system_term << INFO << "HYBROS -> Memory Managers: HeapMemoryManager initialised!" << endl;

    tmp_pointer = new multiboot::multiboot_info;
    memcpy(tmp_pointer, system_mb_info, sizeof(multiboot::multiboot_info));
    system_mb_info = reinterpret_cast<multiboot::multiboot_info *>(tmp_pointer);

    system_term << "    " << INFO << "Multiboot info copied to: " << system_mb_info << endl;

    return true;
}

auto HSystem::InitInterruptManager() -> bool
{
	new (&system_im) InterruptManager;
	return true;
}

auto HSystem::InitProcessors() -> bool
{
    if(tmp_pointer == nullptr)
        return false;

    MPFloatPointStruct *mp_fps = reinterpret_cast<MPFloatPointStruct*>(tmp_pointer);
    if(mp_fps->feature_bytes[0] == 0)
    {
        const char mp_ct_sign[] = "PCMP";
        MPConfigTab *mp_ct = reinterpret_cast<MPConfigTab*>(mp_fps->mp_config_table);
        if(IsStructureValid(reinterpret_cast<uchar*>(mp_ct), mp_ct_sign, 4, mp_ct->base_table_length) == true)          // Calculation is much simpler with 'base_table_length' than with other tests
        {
            system_term << INFO << "HYBROS -> Multi processor setup: Configuration Table address: " << static_cast<void*>(mp_ct) << endl;
            system_local_apics.Resize(sizeof(HLocalAPIC) * 4);
            return ProcessMPConfigTable(mp_ct);
        }
        else
            system_term << INFO << "HYBROS -> Multi processor setup: Configuration Table address: " << reinterpret_cast<char*>(mp_ct->signature) << endl;
    }
    else if(mp_fps->feature_bytes[0] == 1)
        system_term << INFO << "Multi processor setup -> Running on dual core system (1)" << endl;
    else if(mp_fps->feature_bytes[0] == 2)
        system_term << INFO << "Multi processor setup -> Running on dual core system (2)" << endl;
    else if(mp_fps->feature_bytes[0] == 3)
        system_term << INFO << "Multi processor setup -> Running on dual core system (3)" << endl;
    else if(mp_fps->feature_bytes[0] == 4)
        system_term << INFO << "Multi processor setup -> Running on dual core system (4)" << endl;
    else if(mp_fps->feature_bytes[0] == 5)
        system_term << INFO << "Multi processor setup -> Running on dual core system (5)" << endl;
    else if(mp_fps->feature_bytes[0] == 6)
        system_term << INFO << "Multi processor setup -> Running on dual core system (6)" << endl;
    else if(mp_fps->feature_bytes[0] == 7)
        system_term << INFO << "Multi processor setup -> Running on dual core system (7)" << endl;

    return false;
}

auto HSystem::GetRootSystemDescriptionPointer(ulong start_address, size_t length) -> RSDPDescriptor *
{
    const char rsdp_sign[] = "RSD PTR ";
    for(uchar *address = reinterpret_cast<uchar *>(start_address); address < reinterpret_cast<uchar *>(start_address + length); address += sizeof(rsdp_sign))
    {
        if(IsStructureValid(address, rsdp_sign, sizeof(rsdp_sign), sizeof(RSDPDescriptor)) == true)
            return reinterpret_cast<RSDPDescriptor*>(address);
    }
    return nullptr;
}

auto HSystem::GetFloatingPointStructure(ulong address_to_start, ulong length) -> MPFloatPointStruct *
{
    const char mp_sign[] = "_MP_";
    for(uchar *address = reinterpret_cast<uchar *>(address_to_start); address < reinterpret_cast<uchar *>(address_to_start + length); address += 16)
    {
        if(IsStructureValid(address, mp_sign, sizeof(mp_sign), 16) == true)
            return reinterpret_cast<MPFloatPointStruct*>(address);
    }
    return nullptr;
}

auto HSystem::BootProcessor(HLocalAPIC &local_apic, uint local_apic_id) -> bool
{
	system_term << "    " << INFO << "Local APIC id: " << local_apic_id << endl;

    HLocalAPIC::IntCmdReg int_cmd_reg = 0xC4500;
//    int_cmd_reg.SetVector(0);
//    int_cmd_reg.SetDeliveryMode(HLocalAPIC::IntCmdReg::INIT);
//    int_cmd_reg.SetDeliveryStatus(HLocalAPIC::IntCmdReg::IDLE);
//    int_cmd_reg.SetDestinationMode(HLocalAPIC::IntCmdReg::PHYSICAL);
//    int_cmd_reg.SetDestinationShorthand(HLocalAPIC::IntCmdReg::NO_SHORTHAND);
//    int_cmd_reg.SetAssertLevel(HLocalAPIC::IntCmdReg::DE_ASSERT);
//    int_cmd_reg.SetTriggerMode(HLocalAPIC::IntCmdReg::EDGE);
    system_term << "    " << INFO << "Interrupt Command Register: " << static_cast<uint32>(int_cmd_reg) << endl;
    local_apic.SendIPI(local_apic_id, int_cmd_reg);

    uint wait = 0;
    while(wait < 10000)
        wait++;

    int_cmd_reg = 0xC4600 | 0x10;
    local_apic.SendIPI(local_apic_id, int_cmd_reg);
}

auto HSystem::ProcessMPConfigTable(MPConfigTab *mp_ct) -> bool
{
    uchar *entry_type = reinterpret_cast<uchar*>(mp_ct);
    entry_type += sizeof(MPConfigTab);
//    system << info << pc_info << "Configuration table: " << entry_type << endl;
    for(int i = 0; i < mp_ct->entry_count; i++)
    {
//        system << info << "Multi processor setup -> Entry found!" << endl;
        if(*entry_type == MP_PROCESSOR)
        {
            MPEntry *mp_proc_entry = reinterpret_cast<MPEntry*>(entry_type);
//                 << " Local APIC id: " << mp_proc_entry->local_apic_id << endl
//                 << " Local APIC version: " << mp_proc_entry->local_apic_version << endl
//                 << " CPU flags: " << std::bin << mp_proc_entry->cpu_flags << endl
//                 << " Feature flags: " << mp_proc_entry->feature_flags << std::dec << endl;
            if(IsBitSet(mp_proc_entry->cpu_flags, 0) == true)                      // Processor is usable
            {
                if(IsBitSet(mp_proc_entry->cpu_flags, 1) == true)                  // Our currently running boot processor
                {
                    system_term << INFO << "HYBROS System -> Boot processor detected:" << endl
                                << "    " << INFO << "Local APIC address: " << hex << mp_ct->local_apic_address << dec << endl;

                    if(MapPage(mp_ct->local_apic_address) == true)
                        system_term << "    " << INFO << "Local APIC address mapping successful!" << endl;

                    system_local_apics.PushFirstElement(HLocalAPIC(mp_ct->local_apic_address));
                    if(system_local_apics.GetFirstElement().IsEnabled() == true)
                        system_term << "    " << SUCC << "Local APIC enabled." << endl;
                }
                else
                {
                    system_term << INFO << "HYBROS System -> Application processor detected:" << endl;

                    memzero(VAR_TO_PTR(0x10000), 0x1000);

                    system_term << "    " << INFO << "Application processor boot code: " << reinterpret_cast<void*>(boot_ap) << endl
								<< "    " << INFO << "Local APIC address: " << mp_ct->local_apic_address << endl;
                    
//                  system_local_apics.PushLastElement(HLocalAPIC(mp_ct->local_apic_address));
                    if(BootProcessor(system_local_apics.GetFirstElement(), mp_proc_entry->local_apic_id) == true)
                        system_term << "    " << SUCC << "Processor should be booted." << endl;

                    if(system_local_apics.GetLastElement().IsEnabled() == true)
                        system_term << "    " << SUCC << "APIC enabled." << endl;
                }
            }

            entry_type += sizeof(MPEntry);
        }
        else if(*entry_type == MP_BUS)
        {
            MPBusEntry *mp_bus_entry = reinterpret_cast<MPBusEntry*>(entry_type);
//            system << " Type: Bus" << endl;
            entry_type += sizeof(MPBusEntry);
        }
        else if(*entry_type == MP_IO_APIC)
        {
            MPIOAPICEntry *mp_io_apic_entry = reinterpret_cast<MPIOAPICEntry*>(entry_type);
            system_term << " Type: I/O APIC" << endl;
            entry_type += sizeof(MPIOAPICEntry);
        }
        else if(*entry_type == MP_IO_INTERRUPT_ASSIGN)
        {
            MPIOIntAssignEntry *mp_io_int_entry = reinterpret_cast<MPIOIntAssignEntry*>(entry_type);
//            system << " Type: I/O Interrupt Assignment" << endl;
            entry_type += sizeof(MPIOIntAssignEntry);
        }
        else if(*entry_type == MP_LOCAL_INTERRUPT_ASSIGN)
        {
            MPLocalIntAssignEntry *mp_local_int_entry = reinterpret_cast<MPLocalIntAssignEntry*>(entry_type);
//            system << " Type: Local Interrupt Assignment" << endl;
            entry_type += sizeof(MPLocalIntAssignEntry);
        }
        else
        {
//            system << warning << pc_info << "Type: Unkown" << endl;
        }
    }
    return 0;
}

void HSystem::RelocateAPInitFunction()
{
//    uchar *new_address = reinterpret_cast<uchar *>(0x10000);
//    for(uint i = 0; i < (reinterpret_cast<ulong>(boot_ap_end) - reinterpret_cast<ulong>(boot_ap)); i++)
//        new_address[i] = boot_ap[i];
}

auto HSystem::IsStructureValid(uchar *address, const char *struct_sign, size_t struct_sign_size, size_t struct_size) -> bool
{
//    char caddress[10];
//    system_term << "    " << INFO << "Signature check: " << struct_sign << " -> " << reinterpret_cast<char*>(address) << endl;
    if(memcmp(address, struct_sign, struct_sign_size) != 0)
        return false;

    uchar checksum = 0;
    for(uint j = 0; j < struct_size; j++)
        checksum += address[j];

    if(checksum == 0)
        return true;

    return false;
}

template<typename T>
auto HSystem::GetBIOSDataAreaValue(ulong offset) -> T
{
    return *(reinterpret_cast<T *>(0x400 + offset));
}

auto HSystem::GetMultibootMagic() -> uint
{
    return system_mb_magic;
}

multiboot::multiboot_info *HSystem::GetMultibootInfo()
{
    return system_mb_info;
}

bool HSystem::HasMSR()
{
    uint eax = 0, edx = 0;
    cpuid(1, eax, edx);
    return IsBitSet(edx, 5);
}

auto HSystem::GetManager(uint &manager_id) -> HSystem::Manager *
{
}

auto HSystem::GetManagerId(HSystem::Manager *searched_manager) -> uint
{
//    return system_managers.GetPosition(searched_manager);
}

auto HSystem::GetCurrentManager(HSystem::ManagerType type) -> HSystem::Manager *
{
//    return system_managers.GetFirstElement();
}

auto HSystem::GetCurrentManagerId(HSystem::ManagerType type) -> uint
{
//    return system_managers.GetPosition(current_vmm);
}

void HSystem::LoadCurrentManager(uint &new_current_vmm_id, HSystem::ManagerType type)
{
//    current_vmm = system_managers.GetElement(new_current_vmm_id).GetPointer();
}





