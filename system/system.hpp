#ifndef __SYSTEM_CONTROL_CLASS__
#define __SYSTEM_CONTROL_CLASS__

#include "multiboot.hpp"
#include "multiboot2.hpp"
#include "../std/data_types.hpp"
#include "../std/helper.hpp"
#include "system_infos.hpp"
#include "multiboot.hpp"
#include "pre_mm.hpp"
#include "error_handler.hpp"
#include "pmms.hpp"
#include "vmms.hpp"
#include "hmms.hpp"
#include "terminal.hpp"
#include "access_ctrl.hpp"
#include "proc_ctrl.hpp"

namespace kernel DLL_PUBLIC
{

#define MULTIBOOT   0x1BADB002
#define MULTIBOOT2  0x2BADBOO2
#define MULTIBOOT_MAGIC_BUFFER 0x6000
#define MULTIBOOT_INFO_BUFFER  MULTIBOOT_MAGIC_BUFFER + 0x8

#define KERNEL_HEAP 0xFFFFFFFFF0000000
#define KERNEL_HEAP_END (KERNEL_HEAP + 0x2000)

#define SYSTEM (System::GetInstance())

class System final
{
public:
//  ------------- INTERN --------------
//  Functions for system initialisation
    ~System();

    inline static System &InitSystem();
    inline static System &GetInstance();

    inline void ShowBanner();

    uint GetMultibootMagic();
    multiboot::multiboot_info *GetMultibootInfo();

    void CheckMultibootInfo();
    void CheckMultiboot2Info();
    bool CheckMultiProcessorSupport();

    bool InitMemoryManagers();
    uint InitProcessors();

    bool BootProcessor(uint local_apic_id);

//  Memory-mapped register manipulation wrapper
    template<typename T> inline T ReadRegister(uint config_address, RegisterAccessInfo reg_info);

//  Memory access and manipulation wrapper
    inline void* AllocateBlock();
    inline void* AllocateBlocks(size_t number_of_blocks);
    inline void  FreeBlock(void* block_address);
    inline void  FreeBlocks(void* block_address, size_t number_of_blocks);

    inline void InitRegion(ulong base, size_t size);
    inline void DeinitRegion(ulong base, size_t size);

    inline void* AllocatePage();
    inline void* AllocatePage(ulong virtual_address);
    inline void* AllocatePages(size_t number_of_pages);
    inline void  FreePage(void* virtual_address);
    inline void  FreePages(void *virtual_address, size_t number_of_pages);

//  Memory allocation wrapper
    inline void *AllocateMemory(size_t size);
    inline void FreeMemory(void *pointer);

//  Terminal wrapper
    template<class C> inline Terminal& operator << (C data);

//  Error registration and handling function
    DLL_PUBLIC void RegisterError(ErrorInfo &info);

//  BIOS information functions
    DLL_PUBLIC uint GetBIOSDataAreaValueL(uint offset);
    DLL_PUBLIC ushort GetBIOSDataAreaValueW(uint offset);

//  Structure validation function
    DLL_PUBLIC bool IsStructureValid(uchar *address, char *struct_signature, size_t struct_size);

//  System API extension functions
    DLL_PUBLIC void *GetSystemFunction(uint function_id);
    DLL_PUBLIC uint RegisterSystemFunction(void *function_address);
    DLL_PUBLIC void UnregisterSystemFunction(uint function_id);

protected:
    System();

    bool HasMSR();

private:
//  Variables
    AccessControl system_ac;
    Terminal system_terms;
    PMMServer system_pmms;
    VMMServer system_vmms;
    HMMServer system_hmms;
    ProcessorController system_pc;

    void *tmp_pointer;
    ulong tmp_buffer;
    uint result;
    size_t core_kernel_size;
    size_t complete_kernel_size;
    uint system_mb_magic;
    multiboot::multiboot_info *system_mb_info;
    size_t system_mb_mem_size;
    char *system_mb_cmdline;
    multiboot2::multiboot_tag *system_mb2_info;
    bool system_has_msr;
    ProcessorInfos system_proc_infos;
    std::Vector<SystemFunction> system_functions;

    static char system_reserved[];
};

// ~ System

System &System::InitSystem()
{
    new (system_reserved) System();
    return reinterpret_cast<System&>(system_reserved);
}

System &System::GetInstance()
{
    return reinterpret_cast<System&>(system_reserved);
}

void* System::AllocateBlock()
{
    return system_pmms.AllocateBlock();
}

void* System::AllocateBlocks(size_t number_of_blocks)
{
    return system_pmms.AllocateBlocks(number_of_blocks);
}

void System::FreeBlock(void* block_address)
{
    system_pmms.FreeBlock(block_address);
}

void System::FreeBlocks(void* block_address, size_t number_of_blocks)
{
    system_pmms.FreeBlocks(block_address, number_of_blocks);
}

void System::InitRegion(ulong base, size_t size)
{
    system_pmms.InitRegion(base, size);
}

void System::DeinitRegion(ulong base, size_t size)
{
    system_pmms.DeinitRegion(base, size);
}

void* System::AllocatePage()
{
    return system_vmms.AllocatePage();
}

void* System::AllocatePages(size_t number_of_pages)
{
    return system_vmms.AllocatePages(number_of_pages);
}

void System::FreePage(void* virtual_address)
{
    system_vmms.FreePage(virtual_address);
}

void System::FreePages(void *virtual_address, size_t number_of_pages)
{
    system_vmms.FreePages(virtual_address, number_of_pages);
}

void *System::AllocateMemory(size_t size)
{
    return system_hmms.AllocateMemory(size);
}

void System::FreeMemory(void *pointer)
{
    system_hmms.FreeMemory(pointer);
}

template<class C>
Terminal &System::operator << (C data)
{
    system_terms << data;
    return system_terms;
}

}

//// @ new

//inline void *operator new (size_t size, void *address) throw()
//{
//    return address;
//}

//inline void *operator new[] (size_t size, void *address) throw()
//{
//    return address;
//}

#endif //__SYSTEM_CONTROL_CLASS__
