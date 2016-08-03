#ifndef __PHYSICAL_MEMORY_TEMPLATES__
#define __PHYSICAL_MEMORY_TEMPLATES__

#include <HSystemManager>

class HPhysicalMemoryManager : public HSystem::Manager
{
public:
    enum RegionUse
    {
        REGION_FULLY_USED = 2,
        REGION_PARTLY_USED = 1,
        REGION_NOT_USED = 0
    };

    inline HPhysicalMemoryManager();

    virtual auto AllocateBlock() -> void* = 0;
    virtual auto AllocateBlocks(size_t number_of_blocks) -> void* = 0;
    virtual void FreeBlock(void* memory_address) = 0;
    virtual void FreeBlocks(void* memory_address, size_t number_of_blocks) = 0;

    virtual auto IsRegionUsed(ulong base_address, size_t memory_size) -> RegionUse = 0;
    virtual void InitRegion(ulong base_address, size_t memory_size) = 0;
    virtual void DeinitRegion(ulong base_address, size_t memory_size) = 0;

    virtual inline auto GetBlockSize() -> size_t;
};


#endif
