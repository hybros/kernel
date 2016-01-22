#ifndef __PROCESSOR_INFORMATIONS__
#define __PROCESSOR_INFORMATIONS__

#include "../std/data_types.hpp"

namespace kernel
{
namespace processor
{

typedef struct RegisterAccessInfo RegAccInfo;

struct MultiProcessorFloatingPointStructure
{
    uchar signature[4];
    uint  mp_config_table;
    uchar length;
    uchar version;
    uchar checksum;
    uchar feature_bytes[5];
};
typedef MultiProcessorFloatingPointStructure MPFloatPointStruct;

struct MultiProcessorConfigurationTable
{
    uchar  signature[4];
    ushort base_table_length;
    uchar  spec_rev;
    uchar  checksum;
    uchar  oem_id_string[8];
    uchar  product_id_string[12];
    uint   oem_table_pointer;
    ushort oem_table_size;
    ushort entry_count;
    uint   local_apic_address;                  // Address is memory-mapped
    ushort extended_table_length;
    uchar  extended_table_checksum;
    uchar  reserved;
} __attribute__ ((__packed__));
typedef MultiProcessorConfigurationTable MPConfigTab;

enum MultiProcessorEntryTypes
{
    MP_PROCESSOR = 0,
    MP_BUS = 1,
    MP_IO_APIC = 2,
    MP_IO_INTERRUPT_ASSIGN = 3,
    MP_LOCAL_INTERRUPT_ASSIGN = 4
};
typedef MultiProcessorEntryTypes MPEntryTypes;

struct MultiProcessorEntry
{
    uchar entry_type;
    uchar local_apic_id;
    uchar local_apic_version;
    uchar cpu_flags;
    uint cpu_signature;
    uint feature_flags;
    uint reserved[2];
}; //__attribute__((__packed__));
typedef MultiProcessorEntry MPEntry;

struct MultiProcessorBusEntry
{
    uchar entry_type;
    uchar bus_id;
    uchar bus_type_string[6];
};
typedef MultiProcessorBusEntry MPBusEntry;

struct MultiProcessorIOAPICEntry
{
    uchar entry_type;
    uchar local_apic_id;
    uchar local_apic_version;
    uchar io_apic_flags;
    uint mmapped_io_apic_address;
};
typedef MultiProcessorIOAPICEntry MPIOAPICEntry;

struct MultiProcessorIOInterruptAssignementEntry
{
    uchar entry_type;
    uchar interrput_type;
    ushort io_interrupt_flag;
    uchar source_bus_id;
    uchar source_bus_irq;
    uchar destination_io_apic_id;
    uchar destination_io_apic_intin;
};
typedef MultiProcessorIOInterruptAssignementEntry MPIOIntAssignEntry;

struct MultiProcessorLocalInterruptAssignementEntry
{
    uchar entry_type;
    uchar interrput_type;
    ushort local_interrupt_flag;
    uchar source_bus_id;
    uchar source_bus_irq;
    uchar destination_local_apic_id;
    uchar destination_local_apic_lintin;
};
typedef MultiProcessorLocalInterruptAssignementEntry MPLocalIntAssignEntry;

}
}

#endif // __PROCESSOR_INFORMATIONS__

