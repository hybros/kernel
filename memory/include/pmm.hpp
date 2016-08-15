#ifndef __PHYSICAL_MEMORY_TEMPLATES__
#define __PHYSICAL_MEMORY_TEMPLATES__

#include <Hybros/SystemManager>

namespace Hybros
{
namespace PhysicalMemory
{

class Manager : public System::Manager
{
public:
    enum RegionUse
    {
        REGION_FULLY_USED = 2,
        REGION_PARTLY_USED = 1,
        REGION_NOT_USED = 0
    };

    Manager() : 
        System::Manager(System::Manager::PHYSICAL_MEMORY_MANAGER)
    {
    }

    virtual auto allocateBlock() -> void* = 0;
    virtual auto allocateBlocks(size_t number_of_blocks) -> void* = 0;
    virtual void freeBlock(void* memory_address) = 0;
    virtual void freeBlocks(void* memory_address, size_t number_of_blocks) = 0;

    virtual auto isRegionUsed(ulong base_address, size_t memory_size) -> RegionUse = 0;
    virtual void initRegion(ulong base_address, size_t memory_size) = 0;
    virtual void deinitRegion(ulong base_address, size_t memory_size) = 0;

    virtual auto getBlockSize() -> size_t = 0;
};

}
}


#endif
