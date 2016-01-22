#ifndef __PCI_INFORMATION_STUFF__
#define __PCI_INFORMATION_STUFF__

#include <HStdTypes>

// General device header

enum HeaderType00
{
    VENDOR_ID           = 0x0,
    DEVICE_ID           = 0x2,
    COMMAND             = 0x4,
    STATUS              = 0x6,
    REVISION_ID         = 0x8,
    PROG_IF             = 0x9,
    SUBCLASS            = 0xA,
    CLASS_CODE          = 0xB,
    CACHE_LINE_SIZE     = 0xC,
    LATENCY_TIMER       = 0xD,
    HEADER_TYPE         = 0xE,
    BIST                = 0xF,
    BASE_ADDR_0         = 0x10,
    BASE_ADDR_1         = 0x14,
    BASE_ADDR_2         = 0x18,
    BASE_ADDR_3         = 0x1C,
    BASE_ADDR_4         = 0x20,
    BASE_ADDR_5         = 0x24,
    CARDBUS_CIS_PTR     = 0x28,
    SUBSYSTEM_VENDOR_ID = 0x2C,
    SUBSYSTEM_ID        = 0x2D,
    EXPANSION_BIOS_BASE = 0x30,
    CAPABILITIES_PTR    = 0x34,
//  RESERVED            = 0x35     | 7 bytes
    INTERRUPT_LINE      = 0x3C,
    INTERRUPT_PIN       = 0x3D,
    MIN_GRANT           = 0x3E,
    MAX_GRANT           = 0x3F,
};

//struct HeaderType00
//{
//    // Register 1 (Offset 0x0)
//    ushort device_id;
//    ushort vendor_id;
//    // Register 2 (Offset 0x4)
//    ushort status;
//    ushort command;
//    // Register 3 (Offset 0x8)
//    uchar class_code;
//    uchar subclass;
//    uchar prog_if;
//    uchar revision_id;
//    // Register 4 (Offset 0xC)
//    uchar bist;
//    uchar header_type;
//    uchar latency_timer;
//    uchar chache_line_size;


//    uint base_address0;
//    uint base_address1;
//    uint base_address2;
//    uint base_address3;
//    uint base_address4;
//    uint base_address5;
//    uint cardbus_cis_ptr;
//    ushort subsystem_id;
//    ushort subsystem_vendor_id;
//    uint exp_rom_base_address;        // Expansion ROM base address
//    ushort reserved1;
//    uchar reserved2;
//    uchar capabilities_pointer;
//    uint reserved3;
//    uchar max_latency;
//    uchar min_grant;
//    uchar interrupt_pin;
//    uchar interrupt_line;
//};

// PCI-to-PCI bridge header
struct HeaderType01                     // register | bits
{
    ushort device_id;                   // 00       | 31-24 23-16
    ushort vendor_id;                   // 00       | 15- 8  7-0
    ushort status;                      // 04       | 31-24 23-16
    ushort command;                     // 04       | 15- 8  7-0
    uchar  class_code;                  // 08       | 31-24
    uchar  subclass;                    // 08       | 23-16
    uchar  prog_if;                     // 08       | 15- 8
    uchar  revision_id;                 // 08       |  7- 0
    uchar  bist;                        // 0C       | 31-24
    uchar  header_type;                 // 0C       | 23-16
    uchar  latency_timer;               // 0C       | 15- 8
    uchar  chache_line_size;            // 0C       |  7- 0

    uint   base_address0;               // 10
    uint   base_address1;               // 14
    uchar  secondary_latency_timer;     // 18       | 31-24
    uchar  subordinate_bus_number;      // 18       | 23-16
    uchar  secondary_bus_number;        // 18       | 15- 8
    uchar  primary_bus_number;          // 18       |  7- 0
    ushort secondary_status;            // 1C       | 31-24 23-16
    uchar  io_limit;                    // 1C       | 15- 8  7- 0
    uchar  io_base;                     // 1C       |  7- 0
    ushort memory_limit;                // 20       | 31-24 23-16
    ushort memory_base;                 // 20       | 15- 8  7- 0
    ushort prefetchable_memory_limit;   // 24       | 31-24 23-16
    ushort prefetchable_memory_base;    // 24       | 15- 8  7- 0
    uint   prefetchable_base_upper;     // 28
    uint   prefetchable_limit_upper;    // 2C
    ushort io_limit_upper;              // 30       | 31-24 23-16
    ushort io_base_upper;               // 30       | 15- 8  7- 0
    ushort reserved1;                   // 34       | 31-24 23-16
    uchar  reserved2;                   // 34       | 15- 8
    uchar  capability_pointer;          // 34       |  7- 0
    uint   expansion_rom_base_address;  // 38
    ushort bridge_control;              // 3C       | 31-24 23-16
    uchar  interrupt_pin;               // 3C       | 15- 8
    uchar  interrupt_line;              // 3C       |  7- 0
};

// PCI-to-CardBus bridge header
struct HeaderType02                     // register | bits
{
    ushort device_id;                   // 00       | 31-24 23-16
    ushort vendor_id;                   // 00       | 15- 8  7-0
    ushort status;                      // 04       | 31-24 23-16
    ushort command;                     // 04       | 15- 8  7-0
    uchar  class_code;                  // 08       | 31-24
    uchar  subclass;                    // 08       | 23-16
    uchar  prog_if;                     // 08       | 15- 8
    uchar  revision_id;                 // 08       |  7- 0
    uchar  bist;                        // 0C       | 31-24
    uchar  header_type;                 // 0C       | 23-16
    uchar  latency_timer;               // 0C       | 15- 8
    uchar  chache_line_size;            // 0C       |  7- 0

    uint   cardbus_base_address;        // 10
    ushort secondary_status;            // 14       | 31-24 23-16
    uchar  reserved;                    // 14       | 15-08
    uchar  offset_capabilities_list;    // 14       |  7- 0
    uchar  cardbus_latency_timer;       // 18       | 31-24
    uchar  subordinate_bus_number;      // 18       | 23-16
    uchar  cardbus_bus_number;          // 18       | 15-08
    uchar  pci_bus_number;              // 18       |  7- 0
    uint   memory_base_address_0;       // 1C
    uint   memory_limit_0;              // 20
    uint   memory_base_address_1;       // 24
    uint   memory_limit_1;              // 28
    uint   io_base_address_0;           // 2C
    uint   io_limit_0;                  // 30
    uint   io_base_address_1;           // 34
    uint   io_limit_1;                  // 38
    ushort bridge_control;              // 3C       | 31-24 23-16
    uchar  interrupt_pin;               // 3C       | 15-08
    uchar  interrupt_line;              // 3C       |  7- 0
    ushort subsystem_vendor_id;         // 40       | 31-24 23-16
    ushort subsystem_device_id;         // 40       | 15-08  7- 0
    uint   pc_card_legacy_mode_address; // 44
};

enum DeviceTypes
{
    NO_PRIOR_DEFINITION                                = 0x00,
    MASS_STORAGE_CONTROLLER                            = 0x01,
    NETWORK_CONTROLLER                                 = 0x02,
    DISPLAY_CONTROLLER                                 = 0x03,
    MULTIMEDIA_CONTROLLER                              = 0x04,
    MEMORY_CONTROLLER                                  = 0x05,
    BRIDGE_DEVICE                                      = 0x06,
    SIMPLE_COMMUNICATION_CONTROLLERS                   = 0x07,
    BASE_SYSTEM_PERIPHERALS                            = 0x08,
    INPUT_DEVICES                                      = 0x09,
    DOCKING_STATIONS                                   = 0x0A,
    PROCESSORS                                         = 0x0B,
    SERIAL_BUS_CONTROLLERS                             = 0x0C,
    WIRELESS_CONTROLLERS                               = 0x0D,
    INTELLIGENT_IO_CONTROLLERS                         = 0x0E,
    SATELLITE_COMMUNICATION_CONTROLLERS                = 0x0F,
    ENCRYPTION_DECRYPTION_CONTROLLERS                  = 0x10,
    DATA_ACQUISITION_AND_SIGNAL_PROCESSING_CONTROLLERS = 0x11,
    RESERVED,                                       // = 0x12 - 0xFE
    NO_DEFINED_CLASS                                   = 0xFF
};

enum DeviceFuncitons                  // Class code | subclass | prog if
{
    ANY_DEVICE_EXCEPT_VGA,            // 0x00       | 0x00     | 0x00
    VGA_COMPATIBLE_DEVICE,            // 0x00       | 0x01     | 0x00

    SCSI_BUS_CONTROLLER,              // 0x01       | 0x00     | 0x00
    IDE_CONTROLLER,                   // 0x01       | 0x01     | 0x--
    FLOPPY_DISK_CONTROLLER,           // 0x01       | 0x02     | 0x00
    IPI_BUS_CONTROLLER,               // 0x01       | 0x03     | 0x00
    RAID_CONTROLLER,                  // 0x01       | 0x04     | 0x00
    ATA_CONTROLLER_SINGLE_DMA,        // 0x01       | 0x05     | 0x20
    ATA_CONTROLLER_CHAINED_DMA,       // 0x01       | 0x05     | 0x30
    SATA_VENDOR_INTERFACE,            // 0x01       | 0x06     | 0x00
    SATA_AHCI_1_0,                    // 0x01       | 0x06     | 0x01
    SERIAL_ATTACHED_SCSI,             // 0x01       | 0x07     | 0x00
    OTHER_MASS_STORAGE_CONTROLLER,    // 0x01       | 0x80     | 0x00

    ETHERNET_CONTROLLER,              // 0x02       | 0x00     | 0x00
    TOKEN_RING_CONTROLLER,            // 0x02       | 0x01     | 0x00
    FDDI_CONTROLLER,                  // 0x02       | 0x02     | 0x00
    ATM_CONTROLLER,                   // 0x02       | 0x03     | 0x00
    ISDN_CONTROLLER,                  // 0x02       | 0x04     | 0x00
    WORLDFIP_CONTROLLER,              // 0x02       | 0x05     | 0x00
    PICMG_2_14_MULTI_COMPUTING,       // 0x02       | 0x06     | 0x--
    OTHER_NETWORK_CONTROLLER,         // 0x02       | 0x80     | 0x00

    VGA_COMPATIBLE_CONTROLLER,        // 0x03       | 0x00     | 0x00
    _8512_COMPATIBEL_CONTROLLER,      // 0x03       | 0x00     | 0x01
    XGA_CONTROLLER,                   // 0x03       | 0x01     | 0x00
    _3D_CONTROLLER,                   // 0x03       | 0x02     | 0x00
    OTHER_DISPLAY_CONTROLLER,         // 0x03       | 0x80     | 0x00

    VIDEO_DEVICE,                     // 0x04       | 0x00     | 0x00
    AUDIO_DEVICE,                     // 0x04       | 0x01     | 0x00
    COMPUTER_TELEPHONY_DEVICE,        // 0x04       | 0x02     | 0x00
    OTHER_MULTIMEDIA_DEVICE,          // 0x04       | 0x80     | 0x00

    RAM_CONTROLLER,                   // 0x05       | 0x00     | 0x00
    FLASH_CONTROLLER,                 // 0x05       | 0x01     | 0x00
    OTHER_MEMORY_CONTROLLER,          // 0x05       | 0x80     | 0x00

    HOST_BRIDGE,                      // 0x06       | 0x00     | 0x00
    ISA_BRIDGE,                       // 0x06       | 0x01     | 0x00
    EISA_BRIDGE,                      // 0x06       | 0x02     | 0x00
    MCA_BRIDGE,                       // 0x06       | 0x03     | 0x00
    PCI_TO_PCI_BRIDGE,                // 0x06       | 0x04     | 0x00
    PCI_TO_PCI_BRIDGE_SUB_DECODE,     // 0x06       | 0x04     | 0x01
    PCMCIA_BRIDGE,                    // 0x06       | 0x05     | 0x00
    NUBUS_BRIDGE,                     // 0x06       | 0x06     | 0x00
    CARDBUS_BRIDGE,                   // 0x06       | 0x07     | 0x00
    RACEWAY_BRIDGE,                   // 0x06       | 0x08     | 0x--
    PCI_TO_PCI_BRIDGE_SEMI_T_PRI,     // 0x06       | 0x09     | 0x40
    PCI_TO_PCI_BRIDGE_SEMI_T_SEC,     // 0x06       | 0x09     | 0x80
    INFINIBRAND_TO_PCI_HOST_BRIDGE,   // 0x06       | 0x0A     | 0x00
    OTHER_BRIDGE_DEVICE,              // 0x06       | 0x80     | 0x00

    GENERIC_XT_SERIAL_CONTROLLER,     // 0x07       | 0x00     | 0x00
    _16450_SERIAL_CONTROLLER,         // 0x07       | 0x00     | 0x01
    _16550_SERIAL_CONTROLLER,         // 0x07       | 0x00     | 0x02
    _16650_SERIAL_CONTROLLER,         // 0x07       | 0x00     | 0x03
    _16750_SERIAL_CONTROLLER,         // 0x07       | 0x00     | 0x04
    _16850_SERIAL_CONTROLLER,         // 0x07       | 0x00     | 0x05
    _16950_SERIAL_CONTROLLER,         // 0x07       | 0x00     | 0x06
    PARALLEL_PORT,                    // 0x07       | 0x01     | 0x00
    BI_DIRECTIONAL_PARALLEL_PORT,     // 0x07       | 0x01     | 0x01
    ECP_1X_COMPILANT_PARALLEL_PORT,   // 0x07       | 0x01     | 0x02
    IEEE_1284_CONTROLLER,             // 0x07       | 0x01     | 0x03
    IEEE_1284_TARGET_DEVICE,          // 0x07       | 0x01     | 0xFE
    MULTIPORT_SERIAL_CONTROLLER,      // 0x07       | 0x02     | 0x00
    GENERIC_MODEM,                    // 0x07       | 0x03     | 0x00
    _16450_COMPILANT_INTERFACE,       // 0x07       | 0x03     | 0x01
    _16550_COMPILANT_INTERFACE,       // 0x07       | 0x03     | 0x02
    _16650_COMPILANT_INTERFACE,       // 0x07       | 0x03     | 0x03
    _16750_COMPILANT_INTERFACE,       // 0x07       | 0x03     | 0x04
    IEEE_488_1_2_CONTROLLER,          // 0x07       | 0x04     | 0x00
    SMART_CARD,                       // 0x07       | 0x05     | 0x00
    OTHER_COMMUNICATIONS_DEVICE,      // 0x07       | 0x80     | 0x00

    GENERIC_8259_PIC,                 // 0x08       | 0x00     | 0x00
    ISA_PIC,                          // 0x08       | 0x00     | 0x01
    EISA_PIC,                         // 0x08       | 0x00     | 0x02
    IO_APIC_INTERRUPT_CONTROLLER,     // 0x08       | 0x00     | 0x10
    IOX_APIC_INTERRUPT_CONTROLLER,    // 0x08       | 0x00     | 0x20
    GENERIC_8237_DMA_CONTROLLER,      // 0x08       | 0x01     | 0x00
    ISA_DMA_CONTROLLER,               // 0x08       | 0x01     | 0x01
    EISA_DMA_CONTROLLER,              // 0x08       | 0x01     | 0x02
    GENERIC_8254_SYSTEM_TIMER,        // 0x08       | 0x02     | 0x00
    ISA_SYSTEM_TIMER,                 // 0x08       | 0x02     | 0x01
    EISA_SYSTEM_TIMER,                // 0x08       | 0x02     | 0x02
    GENERIC_RTC_CONTROLLER,           // 0x08       | 0x03     | 0x00
    ISA_RTC_CONTROLLER,               // 0x08       | 0x03     | 0x01
    GENERIC_PCI_HOT_PLUG_CONTROLLER,  // 0x08       | 0x04     | 0x00
    OTHER_SYSTEM_PERIPHERAL,          // 0x08       | 0x80     | 0x00

    KEYBOARD_CONTROLLER,              // 0x09       | 0x00     | 0x00
    DIGITIZER,                        // 0x09       | 0x01     | 0x00
    MOUSE_CONTROLLER,                 // 0x09       | 0x02     | 0x00
    SCANNER_CONTROLLER,               // 0x09       | 0x03     | 0x00
    GAMEPORT_CONTROLLER_GENERIC,      // 0x09       | 0x04     | 0x00
    GAMEPORT_CONTROLLER_LEGACY,       // 0x09       | 0x04     | 0x10
    OTHER_INPUT_CONTROLLER,           // 0x09       | 0x80     | 0x00

    GENERIC_DOCKING_STATION,          // 0x0A       | 0x00     | 0x00
    OTHER_DOCKING_STATION,            // 0x0A       | 0x80     | 0x00

    _386_PROCESSOR,                   // 0x0B       | 0x00     | 0x00
    _486_PROCESSOR,                   // 0x0B       | 0x01     | 0x00
    PENTIUM_PROCESSOR,                // 0x0B       | 0x02     | 0x00
    ALPHA_PROCESSOR,                  // 0x0B       | 0x10     | 0x00
    POWERPC_PROCESSOR,                // 0x0B       | 0x20     | 0x00
    MIPS_PROCESSOR,                   // 0x0B       | 0x30     | 0x00
    CO_PROCESSOR,                     // 0x0B       | 0x40     | 0x00

    IEEE_1349_CONTROLLER_FIREWIRE,    // 0x0C       | 0x00     | 0x00
    IEEE_1349_CONTROLLER_OPENHCI,     // 0x0C       | 0x00     | 0x10
    ACCESS_BUS,                       // 0x0C       | 0x01     | 0x00
    SSA,                              // 0x0C       | 0x02     | 0x00
    USB_UNIVERSAL_HOST_CONTROLLER,    // 0x0C       | 0x03     | 0x00
    USB_OPEN_HOST_CONTROLLER,         // 0x0C       | 0x03     | 0x10
    USB2_HOST_CONTROLLER,             // 0x0C       | 0x03     | 0x20
    USB,                              // 0x0C       | 0x03     | 0x80
    USB_NOT_HOST_CONTROLLER,          // 0x0C       | 0x03     | 0xFE
    FIBRE_CHANNEL,                    // 0x0C       | 0x04     | 0x00
    SMBUS,                            // 0x0C       | 0x05     | 0x00
    INFINIBAND,                       // 0x0C       | 0x06     | 0x00
    IPMI_SMIC_INTERFACE,              // 0x0C       | 0x07     | 0x00
    IPMI_KYBD_CONTROLLER_STYLE_INT,   // 0x0C       | 0x07     | 0x01
    IPMI_BLOCK_TRANSFER_INTERFACE,    // 0x0C       | 0x07     | 0x02
    SERCOS_INTERFACE_STANDARD,        // 0x0C       | 0x08     | 0x00
    CANBUS,                           // 0x0C       | 0x09     | 0x00

    IRDA_CONTROLLER,                  // 0x0D       | 0x00     | 0x00
    CONSUMER_IR_CONTROLLER,           // 0x0D       | 0x01     | 0x00
    RF_CONTROLLER,                    // 0x0D       | 0x10     | 0x00
    BLUETOOTH_CONTROLLER,             // 0x0D       | 0x11     | 0x00
    BROADBAND_CONTROLLER,             // 0x0D       | 0x12     | 0x00
    ETHERNET_CONTROLLER_802_11A,      // 0x0D       | 0x20     | 0x00
    ETHERNET_CONTROLLER_802_11B,      // 0x0D       | 0x21     | 0x00
    OTHER_WIRELESS_CONTROLLER,        // 0x0D       | 0x80     | 0x00

    I20_ARCHITECTURE,                 // 0x0E       | 0x00     | 0x--
    MESSAGE_FIFO,                     // 0x0E       | 0x00     | 0x00

    TV_CONTROLLER,                    // 0x0F       | 0x01     | 0x00
    AUDIO_CONTROLLER,                 // 0x0F       | 0x02     | 0x00
    VOICE_CONTROLLER,                 // 0x0F       | 0x03     | 0x00
    DATA_CONTROLLER,                  // 0x0F       | 0x04     | 0x00

    NETWORK_COMPUTING_ENCRYPT_DECRYPT,// 0x10       | 0x00     | 0x00
    ENTERTAINMENT_ENCRYPT_DECRYPT,    // 0x10       | 0x10     | 0x00
    OTHER_ENTCRYPT_DECRYPT,           // 0x10       | 0x00     | 0x00

    DPIO_MODULES,                     // 0x11       | 0x00     | 0x00
    PERFORMANCE_COUNTERS,             // 0x11       | 0x01     | 0x00
    A_LOT_OF_SHIT,                    // 0x11       | 0x10     | 0x00  | Communications Synchronization Plus Time and Frequency Test/Measurment
    MANAGEMENT_CARD,                  // 0x11       | 0x20     | 0x00
    OTHER_DATA_ACQUISITION_CONTROLLER // 0x11       | 0x80     | 0x00  | /Signal Processing Controller
};

#endif
