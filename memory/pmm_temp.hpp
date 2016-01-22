#ifndef __PHYSICAL_MEMORY_TEMPLATES__
#define __PHYSICAL_MEMORY_TEMPLATES__

#include "../std/data_types.hpp"
#include "../system/error_codes.hpp"

namespace kernel
{
namespace memory
{

enum
{
    PMM_REGION_FULLY_USED = 2,
    PMM_REGION_PARTLY_USED = 1,
    PMM_REGION_NOT_USED = 0
};

class PhysicalMemoryManagerTemplate
{
public:
    virtual void* AllocateBlock() = 0;
    virtual void* AllocateBlocks(size_t number_of_blocks) = 0;
    virtual void  FreeBlock(void* memory_address) = 0;
    virtual void  FreeBlocks(void* memory_address, size_t number_of_blocks) = 0;

    virtual uint IsRegionUsed(ulong base_address, size_t memory_size) = 0;
    virtual void InitRegion(ulong base_address, size_t memory_size) = 0;
    virtual void DeinitRegion(ulong base_address, size_t memory_size) = 0;

    virtual inline uint GetBlockSize();
};
typedef class PhysicalMemoryManagerTemplate PMMTemplate;

// ~ PhysicalMemoryManagerTemplate

uint PhysicalMemoryManagerTemplate::GetBlockSize()
{
    return 1024;
}

}
}

#endif
