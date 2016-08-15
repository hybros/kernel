#ifndef __STANDARD_PHYSICAL_MEMORY_MANAGER__
#define __STANDARD_PHYSICAL_MEMORY_MANAGER__

#include <Hybros/PhysicalMemory/Manager>
#include <Hybros/StdTypes>
#include <Hybros/List>
#include <Hybros/Bitmap>

#include "multiboot.hpp"
#include "pre_mm.hpp"

#define BLOCKS_PER_BYTE 8
#define BLOCK_SIZE	    4096
#define BLOCK_ALIGN	    BLOCK_SIZE

#define SMAP_SIGNATURE  0x534D4150

#if __x86_64__
#define KERNEL_VIRTUAL_BASE 0xFFFFFFFFF0000000
#else
#define KERNEL_VIRTUAL_BASE 0xF0000000
#endif

struct SMAPEntry
{
    uint   base_addr_low;
    uint   base_addr_high;
    uint   length_low;
    uint   length_high;
    ushort type;
    ushort acpi;
};



//class StandardPhysicalMemoryManager : PMMTemplate
//{
//public:
//    StandardPhysicalMemoryManager();
//    ~StandardPhysicalMemoryManager();

//    static inline PMMTemplate *Init(multiboot::multiboot_info* multiboot_info, size_t memory_size);

//    void* AllocateBlock();
//    void* AllocateBlocks(size_t number_of_blocks);
//    void  FreeBlock(void* block_address);
//    void  FreeBlocks(void* block_address, size_t number_of_blocks);

//    void InitRegion(ulong base, size_t size);
//    void DeinitRegion(ulong base, size_t size);

//    inline uint GetBlockSize();

//protected:
//    StandardPhysicalMemoryManager(multiboot::multiboot_info* multiboot_info, size_t memory_size);

//    inline uint GetMaxBlocks()  {return max_blocks;}
//    inline uint GetUsedBlocks() {return used_blocks;}
//    inline uint GetFreeBlocks() {return max_blocks - used_blocks;}

//    inline void* GetMemoryMapAddress() {return reinterpret_cast<void*>(memory_map);}
//    inline uint  GetMemoryMapSize()    {return memory_map_size;}
//    inline uint  GetKernelImageSize()  {return kernel_image_size;}

//    int DetectMemory(memory::SMAPEntry* buffer, int max_entries);

//    inline void SetBit  (int bit) {memory_map[bit / 32] |= (1 << (bit % 32));}
//    inline bool UnsetBit(int bit) {return memory_map[bit / 32] & (1 << (bit % 32));}
//    inline bool TestBit (int bit) {return memory_map[bit / 32] & (1 << (bit % 32));}
//    int FindFirstFreeBit();
//    int FindFirstFreeBit(size_t number_of_blocks);

//    void load_pdbr(uint physical_addr) {__asm__ __volatile__("mov %0, %%cr3" :: "a"(physical_addr));}
//    void get_pdbr(uint physical_addr)  {__asm__ __volatile__("mov %%cr3, %0" : "=p"(physical_addr));}

//    void SetErrorCode(ErrorInfo &info);

//private:
//    uint *memory_map, memory_map_size, pmm_memory_size;
//    uint  used_blocks, max_blocks;
//    multiboot::multiboot_info* boot_info;
//    uint  kernel_image_size;
//};

class HSystem::PhysicalMemoryManager : public HBitmap<ulong>, HPhysicalMemoryManager
{
public:
    PhysicalMemoryManager(multiboot::multiboot_info *multiboot_info, size_t memory_size);
    ~PhysicalMemoryManager();

    void* AllocateBlock();
    void* AllocateBlocks(size_t number_of_blocks);
    void  FreeBlock(void* block_address);
    void  FreeBlocks(void* block_address, size_t number_of_blocks);

    auto IsRegionUsed(ulong base_address, size_t memory_size) -> RegionUse;
    void InitRegion(ulong base_address, size_t memory_size);
    void DeinitRegion(ulong base_address, size_t memory_size);

    auto GetBlockSize() -> size_t;

protected:
    auto RoundUpToNextBlock(ulong memory_size) const -> ulong;

private:
    size_t pmm_used_blocks, pmm_max_blocks;
};


#endif // __STANDARD_PHYSICAL_MEMORY_MANAGER__
