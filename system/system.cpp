#include "system.hpp"
#include "system_asm.hpp"
#include "proc_ctrl.hpp"
#include "../std/bits.hpp"
#include "../std/helper.hpp"
#include "../std/memory.hpp"
#include "../memory/pmm_standard.hpp"
#include "../memory/hmm_standard.hpp"
#if __x86_64__ || __ppc64__
#include "../memory/x86-64/vmm_standard.hpp"
#else
#include "../memory/x86/vmm_standard.hpp"
#endif

using namespace kernel;
using namespace kernel::memory;
using namespace kernel::video;
using namespace kernel::std;

char kernel::System::system_reserved[sizeof(System)];

extern "C"
{

extern bool system_sse2_support;
extern bool system_avx_support;

void enable_sse2();

}

// ~ System

System::System() : core_kernel_size((reinterpret_cast<ulong>(&kernel_init_end) - reinterpret_cast<ulong>(&kernel_init_start)) + (reinterpret_cast<ulong>(&kernel_main_end) - reinterpret_cast<ulong>(&kernel_main_start))),
                   system_mb_magic(VAR_TO_PTR_VALUE(MULTIBOOT_MAGIC_BUFFER)),
                   system_mb_info(reinterpret_cast<multiboot::multiboot_info*>(VAR_TO_PTR_VALUE(MULTIBOOT_INFO_BUFFER))),    // Loads the Multiboot info structure from the address MULTIBOOT_INFO_BUFFER
                   system_has_msr(HasMSR())
{
    ShowBanner();
    THIS << info << "General -> Kernel size: " << core_kernel_size << B << endl;

#if __x86_64
    system_sse2_support = true;
    THIS << info << "General -> SSE2 must be supported on a x86-64 system ";
    enable_sse2();
    THIS << "and is now enabled." << endl;

    cpuid(1, &system_proc_infos.proc_type_info_eax, &system_proc_infos.proc_brand_id_ebx, &system_proc_infos.feature_flags_ecx, &system_proc_infos.feature_flags_edx);

    system_avx_support = IsBitSet(system_proc_infos.feature_flags_ecx, 27) ;
    if(system_avx_support == true)
    {
        THIS << info << "General -> AVX is supported ";
//        enabled_sse();
        THIS << "and is now enabled." << endl;
    }
    else
        THIS << info << "General -> AVX is not supported." << endl;

#else
    system_sse2_support = IsBitSet(system_proc_infos.feature_flags_edx, 26);
    if(system_sse2_support == true)
    {
        THIS << info << "General -> SSE2 is supported ";
        enabled_sse();
        THIS << "and is now enabled." << endl;
    }
    else
        THIS << info << "General -> SSE2 is not supported." << endl;
#endif
}

System::~System() {}

void System::ShowBanner()
{
    THIS << "-------------------------------|" << " HYBROS " << "|-----------------------------------" << endl;
}

void System::CheckMultibootInfo()
{
    if(IsBitSet(system_mb_info->flags, 0) == true)
    {
        system_mb_mem_size = system_mb_info->mem_lower + system_mb_info->mem_upper;
        THIS << info << "Multiboot -> Full memory size: " << system_mb_mem_size << kB << endl;
    }
    else
        THIS << warning << "Multiboot -> Memory size seems to not be available!" << endl;

    if(IsBitSet(system_mb_info->flags, 1) == true)
        THIS << info << "Multiboot -> BIOS boot device info: " << hex << system_mb_info->boot_device << endl;
    else
        THIS << warning << "Multiboot -> BIOS boot device info seems to not be available!" << endl;

    if(IsBitSet(system_mb_info->flags, 2) == true)
    {
        system_mb_cmdline = reinterpret_cast<char*>(system_mb_info->cmdline);
        THIS << info << "Multiboot -> Command line: " << system_mb_cmdline << endl;
    }
    else
        THIS << warning << "Multiboot -> Command line was not provided!" << endl;

    if(IsBitSet(system_mb_info->flags, 3) == true)
    {
        THIS << info << "Multiboot -> Module/s " << dec << system_mb_info->mods_count << " are available!" << endl;

        multiboot::multiboot_mod_list *module = reinterpret_cast<multiboot::multiboot_mod_list*>(system_mb_info->mods_addr);
        for(uint i = 0; i < system_mb_info->mods_count; i++)
        {
            THIS << "    " << info << "Module " << i << ": " << endl
                 << "        " << "Start address: " << hex << module->mod_start << endl
                 << "        " << "End address:   " << module->mod_end << endl;
            module += sizeof(multiboot::multiboot_mod_list);
        }
    }
    else
        THIS << warning << "Multiboot -> Modules are not available!" << endl;

    if(IsBitSet(system_mb_info->flags, 6) == true)
    {
        THIS << info << "Multiboot -> BIOS memory map is usable." << endl;
    }
    else
        THIS << warning << "Multiboot -> BIOS memory map is not usable!" << endl;

    if(IsBitSet(system_mb_info->flags, 7) == true)
    {
        THIS << info << "Multiboot -> BIOS drives number: " << system_mb_info->drives_length << endl;
    }
    else
        THIS << warning << "Multiboot -> BIOS drives number is not provided!" << endl;
}

void System::CheckMultiboot2Info()
{
}

bool System::CheckMultiProcessorSupport()
{
    uint ebda = GetBIOSDataAreaValueW(BDA_LPT4_EBDA) << 4,  // Usually
         low_memory = system_mb_info->mem_lower * 1024;     // In kilobytes; so x * 1024 to get size in bytes
    void *mp_address = nullptr;

    if(ebda != 0)
        mp_address = system_pc.GetFloatingPointerStructure(ebda, 1024);
    if(mp_address == nullptr)
        mp_address = system_pc.GetFloatingPointerStructure(low_memory - 1024, 1024);
    if(mp_address == nullptr)
        mp_address = system_pc.GetFloatingPointerStructure(0xF0000, 0x10000);

    if(mp_address == nullptr)
    {
        THIS << warning << "Multi processor setup -> No signature found..." << endl;
        return false;
    }
    else
    {
        THIS << info << "Multi processor setup -> Signature found at: " << mp_address << endl;
        tmp_pointer = mp_address;
        return true;
    }
}

bool System::InitMemoryManagers()
{
    if(system_pmms.RegisterManager(memory::StandardPhysicalMemoryManager::Init(system_mb_info, system_mb_mem_size)) == false)
        return false;
    system_terms << info << "Memory Managers -> PhysicalMemoryManager initialised!" << video::endl;

    if(system_vmms.RegisterManager(memory::StandardVirtualMemoryManager::Init()) == false)
        return false;
    system_terms << info << "Memory Managers -> VirtualMemoryManager initialised!" << video::endl;

    system_vmms.MapPages(0x00200000, KERNEL_HEAP, KERNEL_HEAP_END - KERNEL_HEAP, memory::PT_WRITABLE);

//    if(system_hmms.RegisterManager(memory::StandardHeapMemoryManager::Init(KERNEL_HEAP, KERNEL_HEAP_END)) == false)
//        return false;
//    system_terms << info << "Memory Managers -> HeapMemoryManager initialised!" << video::endl;

    return true;
}

uint System::InitProcessors()
{
    system_pc.InitProcessorController(reinterpret_cast<processor::MPFloatPointStruct*>(tmp_pointer));
}

bool System::IsStructureValid(uchar *address, char *struct_signature, size_t struct_size)
{
    if(address[0] == struct_signature[0] && address[1] == struct_signature[1] && address[2] == struct_signature[2] && address[3] == struct_signature[3])
    {
        uchar checksum = 0;
        for(int i = 0; i < struct_size; i++)
            checksum += address[i];

        if(checksum == 0)
            return true;
    }
    return false;
}

uint System::GetBIOSDataAreaValueL(uint offset)
{
    return VAR_TO_PTR_VALUE(0x400 + offset);
}

ushort System::GetBIOSDataAreaValueW(uint offset)
{
    return VAR_TO_PTR_VALUE(0x400 + offset);
}

uint System::GetMultibootMagic()
{
    return system_mb_magic;
}

multiboot::multiboot_info *System::GetMultibootInfo()
{
    return system_mb_info;
}

bool System::HasMSR()
{
    uint eax = 0, edx = 0;
    cpuid(1, &eax, &edx);
    return IsBitSet(edx, 5);
}






