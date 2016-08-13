#include "../include/system_pmm.hpp"

#include <HStdHelper>
#include <HSystem>
#include <HBitOperations>

// ~ HSystem::PhysicalMemoryManager

HSystem::PhysicalMemoryManager::PhysicalMemoryManager(multiboot::multiboot_info* multiboot_info, size_t memory_size) :
    pmm_max_blocks((memory_size * 1000) / BLOCK_SIZE),
    pmm_used_blocks(pmm_max_blocks)
{
    bitmap_pointer = reinterpret_cast<ulong *>(0xC000);
    bitmap_size = pmm_max_blocks / (BLOCKS_PER_BYTE * sizeof(ulong));
    //SYSTEM << INFO << "HYBROS -> ~ HSystem::PhysicalMemoryManager: Max. number of blocks: " << dec << pmm_max_blocks << endl 
           //<< INFO << "HYBROS -> ~ HSystem::PhysicalMemoryManager: Bitmap size: " << bitmap_size << B << endl;
    memset(bitmap_pointer, 0xFF, bitmap_size);

    multiboot::multiboot_memory_map_t* mmap = reinterpret_cast<multiboot::multiboot_memory_map_t *>(multiboot_info->mmap_addr);
    while(PTR_TO_VAR(mmap) < (multiboot_info->mmap_addr + multiboot_info->mmap_length))
    {
        if(mmap->type == 1)
        {
            InitRegion(mmap->addr, mmap->len);
        }
        else
        {
            DeinitRegion(mmap->addr, mmap->len);
        }

        mmap = reinterpret_cast<multiboot::multiboot_memory_map_t*>(PTR_TO_VAR(mmap) + mmap->size + sizeof(uint));
    }

    DeinitRegion(0x00100000, 100000);
    DeinitRegion(PTR_TO_VAR(bitmap_pointer), bitmap_size);
    DeinitRegion(PTR_TO_VAR(multiboot_info), BLOCK_SIZE);
    DeinitRegion(0, 0x0011000);
}

auto HSystem::PhysicalMemoryManager::GetBlockSize() -> size_t
{
    return BLOCK_SIZE;
}

void* HSystem::PhysicalMemoryManager::AllocateBlock()
{
    if((pmm_max_blocks - pmm_used_blocks) == 0)
    {
//        SetErrorCode(ERROR_PMM_NO_FREE_BLOCKS, PMM | ALLOCATEBLOCK);
        return nullptr;
    }

    uint free_bit = FindFirstFreeBit();
    if(free_bit == -1)
    {
//        SetErrorCode(ERROR_PMM_OUT_OF_MEMORY, PMM | ALLOCATEBLOCK);
        return nullptr;
    }

    SetBit(free_bit);

    pmm_used_blocks++;
    ulong temp_address = free_bit * BLOCK_SIZE;
    return reinterpret_cast<void*>(temp_address);
}

void* HSystem::PhysicalMemoryManager::AllocateBlocks(size_t number_of_blocks)
{
    if((pmm_max_blocks - pmm_used_blocks) <= number_of_blocks)
    {
//        SetErrorCode(ERROR_PMM_NO_FREE_BLOCKS, PMM | ALLOCATEBLOCKS);
        return nullptr;
    }

    int free_bit = FindFirstFreeBits(number_of_blocks / (sizeof(ulong) * 8));
    if(free_bit == -1)
    {
//        SetErrorCode(ERROR_PMM_OUT_OF_MEMORY, PMM | ALLOCATEBLOCKS);
        return nullptr;
    }

    for(uint i = 0; i < number_of_blocks; i++)
        SetBit(free_bit + i);

    uint temp_address = free_bit * BLOCK_SIZE;
    pmm_used_blocks += number_of_blocks;
    return reinterpret_cast<void*>(temp_address);
}

void HSystem::PhysicalMemoryManager::FreeBlock(void* block_address)
{
    ulong temp_address = reinterpret_cast<ulong>(block_address);
    ulong frame = temp_address / BLOCK_SIZE;

    ClearBit(frame);

    pmm_used_blocks--;
}

void HSystem::PhysicalMemoryManager::FreeBlocks(void* block_address, size_t number_of_blocks)
{
    ulong temp_address = reinterpret_cast<ulong>(block_address);
    ulong frame = temp_address / BLOCK_SIZE;

    for(uint i = 0; i < number_of_blocks; i++)
        ClearBit(frame + i);

    pmm_used_blocks -= number_of_blocks;
}

HPhysicalMemoryManager::RegionUse HSystem::PhysicalMemoryManager::IsRegionUsed(ulong base_address, size_t memory_size)
{
    uint free_bit_counter = 0;
    for(size_t block_number = RoundUpToNextBlock(memory_size), block_bit = base_address / BLOCK_SIZE; block_number > 0; block_number--, block_bit++, pmm_used_blocks--)
    {
        if(IsBitSet(block_bit) == false)
            free_bit_counter++;
    }

    if((free_bit_counter * BLOCK_SIZE) == memory_size)
        return REGION_NOT_USED;
    else if((free_bit_counter * BLOCK_SIZE) < memory_size)
        return REGION_PARTLY_USED;
    else
        return REGION_FULLY_USED;
}

void HSystem::PhysicalMemoryManager::InitRegion(ulong base_address, size_t memory_size)
{
    for(size_t blocks = RoundUpToNextBlock(memory_size), align = base_address / BLOCK_SIZE; blocks > 0; blocks--, align++, pmm_used_blocks--)
        ClearBit(align);

    SetBit(0);	//first block is always set. This insures allocs cant be 0
}

void HSystem::PhysicalMemoryManager::DeinitRegion(ulong base_address, size_t memory_size)
{
    for(size_t blocks = RoundUpToNextBlock(memory_size), align = base_address / BLOCK_SIZE; blocks > 0; blocks--, align++, pmm_used_blocks++)
        SetBit(align);

    SetBit(0);	//first block is always set. This insures allocs cant be 0
}

auto HSystem::PhysicalMemoryManager::RoundUpToNextBlock(ulong memory_size) const -> ulong
{
    int remainder = memory_size % BLOCK_SIZE;
    return ((memory_size + BLOCK_SIZE - remainder) / BLOCK_SIZE);
}

//StandardPhysicalMemoryManager::StandardPhysicalMemoryManager(multiboot::multiboot_info* multiboot_info, size_t memory_size)
//{
//    boot_info = multiboot_info;
//    memory_map = VAR_TO_UINT_PTR(0x8000);
//    pmm_memory_size = memory_size;
//    max_blocks = pmm_memory_size / BLOCK_SIZE;
//    used_blocks = max_blocks;
//    memory_map_size =  max_blocks / BLOCK_SIZE;

//    memset(memory_map, 0xF, memory_map_size);

//    multiboot::multiboot_memory_map_t* mmap = reinterpret_cast<multiboot::multiboot_memory_map_t*>(boot_info->mmap_addr);
//    while(reinterpret_cast<ulong>(mmap) < boot_info->mmap_addr + boot_info->mmap_length)
//    {
//        uint length = mmap->len;
//        if(length <= 0)
//        {
//            //ignore entry
//        }

//        if(mmap->type == 1)
//            InitRegion(mmap->addr, length);

//        mmap = reinterpret_cast<multiboot::multiboot_memory_map_t*>(reinterpret_cast<ulong>(mmap) + mmap->size + sizeof(uint));
//    }

//    DeinitRegion(0x00100000, 0x100);
//    DeinitRegion(reinterpret_cast<ulong>(memory_map), memory_map_size);
//    DeinitRegion(0, 0x0010000);
//}

//StandardPhysicalMemoryManager::~StandardPhysicalMemoryManager()
//{
//    memset(memory_map, 0xF, memory_map_size);
//}

//int StandardPhysicalMemoryManager::DetectMemory(memory::SMAPEntry* buffer, int max_entries)
//{
//    uint id = 0;
//    int entry = 0, signature, bytes;
//    do
//    {
//        __asm__ __volatile__("int $0x15" : "=a"(signature), "=c"(bytes), "=b"(id)
//                                         : "a"(0xE820), "b"(id), "c"(24), "d"(SMAP_SIGNATURE), "D"(buffer));
//        if(signature != SMAP_SIGNATURE)
//            return -1;

//        if(bytes > 20 && (buffer->acpi & 0x0001) == 0)
//        {
//            //ignore entry
//        }
//        else
//        {
//            buffer++;
//            entry++;
//        }
//    }
//    while(id != 0 && entry < max_entries);

//    return entry;
//}

//int StandardPhysicalMemoryManager::FindFirstFreeBit()
//{
//    for(uint i = 0; i < GetBlockSize() / 32; i++)
//    {
//        if(memory_map[i] != 0xFFFFFFFF)
//        {
//            for(int j = 0; j < 32; j++)
//            {
//                // ! test each bit in the dword
//                int bit = 1 << j;
//                if(!(memory_map[i] & bit) )
//                    return i * 4 * 8 + j;
//            }
//        }
//    }
//    return -1;
//}

//int StandardPhysicalMemoryManager::FindFirstFreeBit(size_t number_of_blocks)
//{
//    if(number_of_blocks == 0)
//        return -1;

//    if(number_of_blocks == 1)
//        return FindFirstFreeBit();

//    for(uint i = 0; i < BLOCK_SIZE; i++)
//    {
//        if(memory_map[i] != 0xffffffff)
//        {
//            for(int j = 0; j < 32; j++)
//            {                                       	// test each bit in the dword
//                int bit = 1 << j;
//                if(!(memory_map[i] & bit))
//                {
//                    int starting_bit = i * 32;
//                    starting_bit += bit;	           	//get the free bit in the dword at index i

//                    uint free = 0;                      //loop through each bit to see if its enough space
//                    for(uint count = 0; count <= number_of_blocks; count++)
//                    {
//                        if(!TestBit(starting_bit + count))
//                            free++;	                    // this bit is clear (free frame)

//                        if(free == number_of_blocks)
//                            return i * 4 * 8 + j;       //free count == number_of_blocks needed; return index
//                    }
//                }
//            }
//        }
//    }
//    return -1;
//}

//void StandardPhysicalMemoryManager::InitRegion(ulong base, size_t size)
//{
//    for(int blocks = size / BLOCK_SIZE, align = base / BLOCK_SIZE; blocks > 0; blocks--)
//    {
//        UnsetBit(align++);
//        used_blocks--;
//    }

//    SetBit(0);	//first block is always set. This insures allocs cant be 0
//}

//void StandardPhysicalMemoryManager::DeinitRegion(ulong base, size_t size)
//{
//    for(int blocks = size / BLOCK_SIZE, align = base / BLOCK_SIZE; blocks > 0; blocks--)
//    {
//        SetBit(align++);
//        used_blocks++;
//    }

//    SetBit(0);	//first block is always set. This insures allocs cant be 0
//}

//void* StandardPhysicalMemoryManager::AllocateBlock()
//{
//    uint free_blocks = GetFreeBlocks();
//    if(free_blocks <= 0)
//    {
////        SetErrorCode(ERROR_PMM_NO_FREE_BLOCKS, PMM | ALLOCATEBLOCK);
//        return nullptr;
//    }

//    uint frame = FindFirstFreeBit();
//    if(frame == -1)
//    {
////        SetErrorCode(ERROR_PMM_OUT_OF_MEMORY, PMM | ALLOCATEBLOCK);
//        return nullptr;
//    }

//    SetBit(frame);

//    uint temp_address = frame * BLOCK_SIZE;
//    used_blocks++;

//    return reinterpret_cast<void*>(temp_address);
//}

//void* StandardPhysicalMemoryManager::AllocateBlocks(ulong number_of_blocks)
//{
//    uint free_blocks = GetFreeBlocks();
//    if(free_blocks <= number_of_blocks)
//    {
////        SetErrorCode(ERROR_PMM_NO_FREE_BLOCKS, PMM | ALLOCATEBLOCKS);
//        return nullptr;
//    }

//    int frame = FindFirstFreeBit(number_of_blocks);
//    if(frame == -1)
//    {
////        SetErrorCode(ERROR_PMM_OUT_OF_MEMORY, PMM | ALLOCATEBLOCKS);
//        return nullptr;
//    }

//    for(uint i = 0; i < number_of_blocks; i++)
//        SetBit(frame + i);

//    uint temp_address = frame * BLOCK_SIZE;
//    used_blocks += number_of_blocks;

//    return reinterpret_cast<void*>(temp_address);
//}

//void StandardPhysicalMemoryManager::FreeBlock(void* block_address)
//{
//    ulong temp_address = reinterpret_cast<ulong>(block_address);
//    int frame = temp_address / BLOCK_SIZE;

//    UnsetBit(frame);

//    used_blocks--;
//}

//void StandardPhysicalMemoryManager::FreeBlocks(void* block_address, ulong number_of_blocks)
//{
//    ulong temp_address = reinterpret_cast<ulong>(block_address);
//    int frame = temp_address / BLOCK_SIZE;

//    for (uint i = 0; i < number_of_blocks; i++)
//        UnsetBit(frame + i);

//    used_blocks -= number_of_blocks;
//}
