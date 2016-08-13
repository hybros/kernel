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

namespace Hybros
{

    template<class T> friend auto operator <<(System &system, T data) -> HTerminal &;
    friend struct ReservedMemory;

public:
    class Manager;
    struct ManagerGroup;

    using ManagerList = HList<Manager *>;
    using ManagerIDs  = HVector<uint>;
    using ManagerType = ulong;

    ~System();

    static auto initSystem() -> System &;
    static auto getInstance() -> System &;

    inline void showBanner();

    auto getMultibootMagic() -> uint;
    auto getMultibootInfo() -> multiboot::multiboot_info *;

    void checkMultibootInfo();
    void checkMultiboot2Info();
    auto checkMultiProcessorSupport() -> bool;

    auto initMemoryManagers() -> bool;
	auto initInterruptManager() -> bool;
    auto initProcessors() -> bool;

    auto bootProcessor(HLocalAPIC &local_apic, uint local_apic_id) -> bool;

//  Memory-mapped register manipulation wrapper
    template<typename T> inline auto readRegister(ulong config_address, HRegisterAccessInfo reg_info) -> T;

//  Error registration and handling function
//    inline void RegisterError(ErrorInfo &info);

//  BIOS information functions
    template<typename T> auto getBIOSDataAreaValue(ulong offset) -> T;

//  Structure validation function
    auto isStructureValid(uchar *address, const char *struct_sign, size_t struct_sign_size, size_t struct_size) -> bool;

//  Manager class registration and administration
    auto registerManager(System::Manager new_manager) -> bool;
    auto unregisterManager(System::Manager old_manager) -> bool;
    auto createUniqueManagerId(System::Manager &manager) -> uint;

    auto getManager(uint &manager_id) -> Manager *;
    auto getManagerId(Manager *searched_manager) -> uint;
    auto getCurrentManager(System::ManagerType type) -> Manager *;
    auto getCurrentManagerId(System::ManagerType type) -> uint;
    void loadCurrentManager(uint &new_current_manager_id, System::ManagerType type);

    auto getCurrentManagers() const -> ManagerGroup &;

    auto allocateBlock() -> void *;
    auto allocateBlocks(size_t number_of_blocks) -> void *;
    void freeBlock(void* memory_address);
    void freeBlocks(void* memory_address, size_t number_of_blocks);

    void initRegion(ulong base, size_t size);
    void deinitRegion(ulong base, size_t size);

    auto allocatePage() -> void *;
    auto allocatePage(bool writable) -> void *;
    auto allocatePage(bool writable, bool supervisor) -> void *;
    auto allocatePage(bool writable, bool supervisor, bool executable) -> void *;
    auto allocatePages(size_t number_of_pages) -> void *;
    void freePage(void *virtual_address);
    void freePages(void *virtual_address, size_t number_of_pages);

    auto mapPage(ulong same_address, ulong additional_flag = 2) -> bool;
    auto mapPage(ulong physical_address, ulong virtual_address, ulong additional_flag = 2) -> bool;
    auto mapPages(ulong same_address, size_t memory_size, ulong additional_flag = 2) -> bool;
    auto mapPages(ulong physical_address, ulong virtual_address, size_t memory_size, ulong additional_flag = 2) -> bool;
    auto unmapPage(ulong virtual_address) -> bool;
    auto unmapPages(ulong virtual_address, size_t memory_size) -> bool;

    auto allocateMemory(size_t memory_size) -> void *;
    void freeMemory(void *memory_address);

    auto createHeap(ulong physical_address, ulong virtual_address, size_t memory_size) -> HHeapBase *;
    auto switchUsedHeap(ulong heap_uid) -> bool;
    auto freeHeap(ulong heap_uid) -> bool;

    auto isDebuggingEnabled() const -> bool;

protected:
    System();

    auto hasMSR() -> bool;

    auto getRootSystemDescriptionPointer(ulong start_address, size_t length) -> RSDPDescriptor *;

    auto getFloatingPointStructure(ulong start_address, ulong length) -> MPFloatPointStruct *;
    auto processMPConfigTable(MPConfigTab *mp_ct) -> bool;

    void relocateAPInitFunction();

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
