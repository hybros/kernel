#ifndef __KERNEL_ERROR_CODES__
#define __KERNEL_ERROR_CODES__

#include "../std/data_types.hpp"

namespace kernel
{

enum ErrorCodes
{
    ERROR_PMM_NO_FREE_BLOCKS,
    ERROR_PMM_OUT_OF_MEMORY
};

enum ErrorCauseIdClass
{
    SYSTEM,
    TERMINAL,
    PMM,
    VMM,
    HMM,
    LOCAL_APIC
};

enum ErrorCauseIdFunction
{
    // System

    // PhysicalMemoryManager
    INITPHYSICALMEMORYMANAGER,
    ALLOCATEBLOCK,
    ALLOCATEBLOCKS,
    FREEBLOCK,
    FREEBLOCKS,
    INITREGION,
    DEINITREGION,

    // VirtualMemoryManager
    INITVIRTUALMEMORYMANAGER,
    ALLOCATEPAGE,
    ALLOCATEPAGES,
    FREEPAGE,
    FREEPAGES                   = 0x50000,
    MAPPAGE                     = 0x60000,
    MAPPAGES                    = 0x70000
};

struct ErrorInfo
{
    uint error_code;
    uint error_importance;
    char *error_info;
    uint error_cause_id;
    char *error_cause;
    bool error_handled;
};


}

#endif // __KERNEL_ERROR_CODES__
