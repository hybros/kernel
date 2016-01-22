#ifndef __SYSTEM_INFO_AND_GENERAL_STRUCTURES__
#define __SYSTEM_INFO_AND_GENERAL_STRUCTURES__

#include <HStdTypes>

extern "C"
{

extern ulong kernel_init_start, kernel_init_end, kernel_main_start, kernel_main_end;

}

enum HInfoLevel
{
    HYBROS,
    SUCC,
    INFO,
    CHECK,
    WARN,
    ERROR
};

struct HBootDevice
{
    uchar bios_drive_number;
    uchar top_level_partition;
    uchar sub_partition_1;
    uchar sub_partition_2;
};

struct HProcessorInfos
{
    uint proc_type_info_eax;
    uint proc_brand_id_ebx;
    uint feature_flags_ecx;
    uint feature_flags_edx;
};

struct HRegisterAccessInfo
{
    uint register_number;
    uint register_offset;
    DataSize register_type_size;

    inline HRegisterAccessInfo(uchar register_num, uchar position, DataSize type_size);
};

#define BDA_COM1            0x00
#define BDA_COM2            0x02
#define BDA_COM3            0x04
#define BDA_COM4            0x06
#define BDA_LPT1            0x08
#define BDA_LPT2            0x0A
#define BDA_LPT3            0x0C
#define BDA_LPT4_EBDA       0x0E
#define BDA_EQUIP_WORD      0x10
#define BDA_POST_STATUS     0x12
#define BDA_LOW_MEM_SIZE    0x13
#define BDA_POST_SYS_FLAG   0x15

// ~ HRegisterAccessInfo

HRegisterAccessInfo::HRegisterAccessInfo(uchar register_num, uchar position, DataSize type_size) : register_number(register_num), register_offset(position), register_type_size(type_size) {}


#endif
