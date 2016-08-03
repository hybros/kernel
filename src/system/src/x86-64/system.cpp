#include "../../include/system.hpp"

#include <HLocalAPIC>

#include "../../include/system_internal.hpp"

extern "C"
{

//extern bool system_sse2_support;
extern bool system_avx_support;
//extern ulong *system_memory;

void enable_sse2();

}

extern ReservedMemory reserved_memory;

HSystem::HSystem() :
    core_kernel_size((reinterpret_cast<ulong>(&kernel_init_end) - reinterpret_cast<ulong>(&kernel_init_start)) + (reinterpret_cast<ulong>(&kernel_main_end) - reinterpret_cast<ulong>(&kernel_main_start))),
    system_mb_magic(VAR_TO_PTR_VALUE(MULTIBOOT_MAGIC_BUFFER)),
    system_mb_info(reinterpret_cast<multiboot::multiboot_info*>(VAR_TO_PTR_VALUE(MULTIBOOT_INFO_BUFFER))),    // Loads the Multiboot info structure pointer from the address MULTIBOOT_INFO_BUFFER
    system_has_msr(HasMSR()),
    system_term(reinterpret_cast<Terminal &>(reserved_memory.terminal)),
    system_pmm(reinterpret_cast<PhysicalMemoryManager &>(reserved_memory.pmm)),
    system_vmm(reinterpret_cast<VirtualMemoryManager &>(reserved_memory.vmm)),
    system_hmm(reinterpret_cast<HeapMemoryManager &>(reserved_memory.hmm)),
    system_im(reinterpret_cast<InterruptManager &>(reserved_memory.im))
{
    new (&system_term) Terminal;
    ShowBanner();
    system_term << INFO << "HYBROS -> Kernel size: " << core_kernel_size << B << endl;

    system_term << INFO << "HYBROS -> SSE2 must be supported on a x86-64 system ";
    enable_sse2();
    system_term << "and is now enabled." << endl;

    cpuid(1, system_proc_infos.proc_type_info_eax, system_proc_infos.proc_brand_id_ebx, system_proc_infos.feature_flags_ecx, system_proc_infos.feature_flags_edx);

    system_avx_support = IsBitSet(system_proc_infos.feature_flags_ecx, 27) ;
    if(system_avx_support == true)
    {
        system_term << INFO << "HYBROS -> AVX is supported ";
//        enabled_sse();
        system_term << "and is now enabled." << endl;
    }
    else
        system_term << INFO << "HYBROS -> AVX is not supported." << endl;
}

auto HSystem::InitSystem() -> HSystem &
{
    new (reserved_memory.system) HSystem();
    return reinterpret_cast<HSystem&>(reserved_memory.system);
}

auto HSystem::GetInstance() -> HSystem &
{
    return reinterpret_cast<HSystem&>(reserved_memory.system);
}

void HSystem::ShowBanner()
{
    system_term << HForeground::LIGHT_GREY << "---------------------------------|" << HForeground::YELLOW << " HYBROS " << HForeground::LIGHT_GREY << "|------------------------------------" << endl;
}


//#else
//    system_sse2_support = IsBitSet(system_proc_infos.feature_flags_edx, 26);
//    if(system_sse2_support == true)
//    {
//        THIS << INFO << "General -> SSE2 is supported ";
//        enabled_sse();
//        THIS << "and is now enabled." << endl;
//    }
//    else
//        THIS << INFO << "General -> SSE2 is not supported." << endl;
//#endif
