#ifndef __SYSTEM_CONTROL_CLASS__
#define __SYSTEM_CONTROL_CLASS__

#include <HStdHelper>
#include <HInteger>
#include <HList>
#include <HVector>
#include <HMultiProcessor>
#include <HPowerManagement>

#include "system_infos.hpp"
#include "multiboot.hpp"
#include "multiboot2.hpp"
#include "pre_mm.hpp"

class HPhysicalMemoryManager;
class HVirtualMemoryManager;
class HHeapMemoryManager;
class HHeapBase;
class HLocalAPIC;
class HTerminal;

#define MULTIBOOT   0x1BADB002
#define MULTIBOOT2  0x2BADBOO2
#define MULTIBOOT_MAGIC_BUFFER 0x500
#define MULTIBOOT_INFO_BUFFER  MULTIBOOT_MAGIC_BUFFER + 0x8

#define KERNEL_MODE_BASE 0xFFFFFFFF00000000
#define KERNEL_HEAP      0xFFFFFFFFF0200000
#define KERNEL_HEAP_SIZE 0x2000

class HSystem final
{
    template<class T> friend auto operator <<(HSystem &system, T data) -> HTerminal &;
    friend struct ReservedMemory;

public:
    class Manager;
    struct ManagerGroup;

    using ManagerList = HList<Manager *>;
    using ManagerIDs  = HVector<uint>;
    using ManagerType = ulong;

    ~HSystem();

    static auto InitSystem() -> HSystem &;
    static auto GetInstance() -> HSystem &;

    inline void ShowBanner();

    auto GetMultibootMagic() -> uint;
    auto GetMultibootInfo() -> multiboot::multiboot_info *;

    void CheckMultibootInfo();
    void CheckMultiboot2Info();
    auto CheckMultiProcessorSupport() -> bool;

    auto InitMemoryManagers() -> bool;
	auto InitInterruptManager() -> bool;
    auto InitProcessors() -> bool;

    auto BootProcessor(HLocalAPIC &local_apic, uint local_apic_id) -> bool;

//  Memory-mapped register manipulation wrapper
    template<typename T> inline auto ReadRegister(ulong config_address, HRegisterAccessInfo reg_info) -> T;

//  Error registration and handling function
//    inline void RegisterError(ErrorInfo &info);

//  BIOS information functions
    template<typename T> auto GetBIOSDataAreaValue(ulong offset) -> T;

//  Structure validation function
    auto IsStructureValid(uchar *address, const char *struct_sign, size_t struct_sign_size, size_t struct_size) -> bool;

//  Manager class registration and administration
    auto RegisterManager(HSystem::Manager new_manager) -> bool;
    auto UnregisterManager(HSystem::Manager old_manager) -> bool;
    auto CreateUniqueManagerId(HSystem::Manager &manager) -> uint;

    auto GetManager(uint &manager_id) -> Manager *;
    auto GetManagerId(Manager *searched_manager) -> uint;
    auto GetCurrentManager(HSystem::ManagerType type) -> Manager *;
    auto GetCurrentManagerId(HSystem::ManagerType type) -> uint;
    void LoadCurrentManager(uint &new_current_manager_id, HSystem::ManagerType type);

    auto GetCurrentManagers() const -> ManagerGroup &;

    auto AllocateBlock() -> void *;
    auto AllocateBlocks(size_t number_of_blocks) -> void *;
    void FreeBlock(void* memory_address);
    void FreeBlocks(void* memory_address, size_t number_of_blocks);

    void InitRegion(ulong base, size_t size);
    void DeinitRegion(ulong base, size_t size);

    auto AllocatePage() -> void *;
    auto AllocatePage(bool writable) -> void *;
    auto AllocatePage(bool writable, bool supervisor) -> void *;
    auto AllocatePage(bool writable, bool supervisor, bool executable) -> void *;
    auto AllocatePages(size_t number_of_pages) -> void *;
    void FreePage(void *virtual_address);
    void FreePages(void *virtual_address, size_t number_of_pages);

    auto MapPage(ulong same_address, ulong additional_flag = 2) -> bool;
    auto MapPage(ulong physical_address, ulong virtual_address, ulong additional_flag = 2) -> bool;
    auto MapPages(ulong same_address, size_t memory_size, ulong additional_flag = 2) -> bool;
    auto MapPages(ulong physical_address, ulong virtual_address, size_t memory_size, ulong additional_flag = 2) -> bool;
    auto UnmapPage(ulong virtual_address) -> bool;
    auto UnmapPages(ulong virtual_address, size_t memory_size) -> bool;

    auto AllocateMemory(size_t memory_size) -> void *;
    void FreeMemory(void *memory_address);

    auto CreateHeap(ulong physical_address, ulong virtual_address, size_t memory_size) -> HHeapBase *;
    auto SwitchUsedHeap(ulong heap_uid) -> bool;
    auto FreeHeap(ulong heap_uid) -> bool;

    auto IsDebuggingEnabled() const -> bool;

protected:
    HSystem();

    auto HasMSR() -> bool;

    auto GetRootSystemDescriptionPointer(ulong start_address, size_t length) -> RSDPDescriptor *;

    auto GetFloatingPointStructure(ulong start_address, ulong length) -> MPFloatPointStruct *;
    auto ProcessMPConfigTable(MPConfigTab *mp_ct) -> bool;

    void RelocateAPInitFunction();

private:
    class Terminal;
    class PhysicalMemoryManager;
    class VirtualMemoryManager;
    class HeapMemoryManager;
    class InterruptManager;

    Terminal &system_term;
    PhysicalMemoryManager &system_pmm;
    VirtualMemoryManager &system_vmm;
    HeapMemoryManager &system_hmm;
    InterruptManager &system_im;

    ManagerList system_manager_list;
    ManagerIDs system_manager_ids;

    HVector<HLocalAPIC> system_local_apics;

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
    HProcessorInfos system_proc_infos;
};

#endif //__SYSTEM_CONTROL_CLASS__
