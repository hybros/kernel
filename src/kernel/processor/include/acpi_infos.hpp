#ifndef __ACPI_STRUCTURES__
#define __ACPI_STRUCTURES__

#include <HStdTypes>

struct RSDPDescriptor
{
    char signature[8];
    uchar checksum;
    char oem_id[6];
    uchar revision;
    uint rsdt_address;
} __attribute__((packed));

#endif
