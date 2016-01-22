#include "pci.hpp"
#include "system.hpp"
#include "system_asm.hpp"
#include "../std/bits.hpp"
#include "../std/helper.hpp"
using namespace kernel;
using namespace kernel::pci;
using namespace kernel::video;

PCIController::PCIController() : system(System::GetInstance()), conifg_data(reinterpret_cast<pci::HeaderType00*>(CONFIG_DATA))
{
    uchar header_type = GetHeaderType(0, 0, 0);
    if(std::IsBitSet(header_type, 7) == false)
    {
        system << info << "It exists a single PCI host controller." << endl;
        CheckBus(0);
    }
    else
    {
        system << info << "It exist multiple PCI host controller." << endl;
        for(uchar function = 0; function < 8; function++)
        {
            if(GetVendorId(0, 0, function) != 0xFFFF)
                break;

            CheckBus(function);
        }
    }

//    for(int bus = 0; bus < 256; bus++)
//        CheckBus(bus);
}

PCIController::~PCIController()
{
    current_bus = 0;
    current_device = 0;
    current_function = 0;
    current_register = 0;
}

// Creates the CONFIG_ADDRESS
// Bits: 31         | 30-24    | 23-16      | 15-11         | 10-8            | 7-2             | 1-0
//       Enable bit | Reserved | Bus number | Device number | Function number | Register number | 00
uint PCIController::CreateConfigAddress(uchar bus, uchar device, uchar function, uchar reg)
{
//    return reinterpret_cast<uint>((bus << 16) | (device << 11) | (function << 8) | (reg << 2) | reinterpret_cast<uint>(0x80000000));
    return reinterpret_cast<uint>((bus << 16) | (device << 11) | (function << 8) | (reg & 0xFC) | 0x80000000);
}

template<typename T, T HeaderType00::* P>
T PCIController::ReadRegister(uint config_address)
{
    WritePort(CONFIG_ADDRESS, config_address);
//    uint address = CONFIG_DATA + OffsetOf(HeaderType01, P);
    system << info << "Config address: " << std::bin << config_address << endl;
    return ReadPort<T>(CONFIG_DATA);
}

template<typename T, T HeaderType01::* P>
T PCIController::ReadRegister(uint config_address)
{
    WritePort(CONFIG_ADDRESS, config_address);
    uint address = CONFIG_DATA + OffsetOf(pci::HeaderType01, P);
    system << info << "Register address: " << std::hex << address << endl;
    return ReadPort<T>(address);
}

//uchar PCIController::ReadConfigByte(uchar bus, uchar device, uchar function, uchar reg, uchar byte)
//{
//    uint address = CreateConfigAddress(bus, device, function, reg);
//    outl(CONFIG_ADDRESS, address);
//    if(byte == 1)
//        return std::GetBits(inb(CONFIG_DATA), 0xFF, 0);
//    else if(byte == 2)
//        return std::GetBits(inl(CONFIG_DATA), 0xFF, 16);
//    else if(byte == 3)
//        return std::GetBits(inl(CONFIG_DATA), 0xFF, 14);
//    else
//        return std::GetBits(inl(CONFIG_DATA), 0xFF, 25);
//}

//ushort PCIController::ReadConfigWord(uchar bus, uchar device, uchar function, uchar reg, bool first)
//{
//    uint address = CreateConfigAddress(bus, device, function, reg);
//    outl(CONFIG_ADDRESS, address);
////  ((reg & 2) * 8) == 0 will choose the first word of the 32 bits register
//    if(first == true)
//        return static_cast<ushort>(std::GetBits(inl(CONFIG_DATA), 0xFFFF, 0));
//    else
//        return static_cast<ushort>(std::GetBits(inl(CONFIG_DATA), 0xFFFF, 16));
//}

ushort PCIController::GetDeviceId(uchar bus, uchar device, uchar function)
{
    return ReadRegister<ushort, &HeaderType00::device_id>(CreateConfigAddress(bus, device, function, 0x00));
}

ushort PCIController::GetVendorId(uchar bus, uchar device, uchar function)
{
    return ReadRegister<ushort, &HeaderType00::vendor_id>(CreateConfigAddress(bus, device, function, 0x00));
}

uchar PCIController::GetHeaderType(uchar bus, uchar device, uchar function)
{
    return ReadRegister<uchar, &HeaderType00::header_type>(CreateConfigAddress(bus, device, function, 0x0C));
}

uchar PCIController::GetClassCode(uchar bus, uchar device, uchar function)
{
    return ReadRegister<uchar, &HeaderType00::class_code>(CreateConfigAddress(bus, device, function, 0x08));
}

uchar PCIController::GetSubClass(uchar bus, uchar device, uchar function)
{
    return ReadRegister<uchar, &HeaderType00::subclass>(CreateConfigAddress(bus, device, function, 0x08));
}

uchar PCIController::GetSecondaryBus(uchar bus, uchar device, uchar function)
{
    return ReadRegister<uchar, &HeaderType01::secondary_bus_number>(CreateConfigAddress(bus, device, function, 0x18));
}

void PCIController::CheckBus(uchar bus)
{
    current_bus = bus;

    system << info << "Check bus " << bus << " now..." << endl;
    for(uchar device = 0; device < 32; device++)
        CheckDevice(device);
}

bool PCIController::CheckDevice(uchar device)
{
    current_device = device;

    uchar function = 0;
//    ushort vendor_id = GetVendorId(current_bus, current_device, function);
//    if(vendor_id == 0xFFFF)
//    {
//        system << warning << "Not existing device!" << endl;
//        return false;
//    }
//    system << info << "Vendor id: " << std::hex << vendor_id << endl;

//    CheckFunction(function);

    uchar header_type = GetHeaderType(current_bus, current_device, function);
    if(std::IsBitSet(header_type, 7) == true)
    {
 //       system << info << "Found multi-function device." << endl;
        for(function = 1; function < 8; function++)
        {
            if(GetVendorId(current_bus, current_device, function) != 0xFFFF)
                CheckFunction(function);
        }
    }
    else
        CheckFunction(0);

    return true;
}

bool PCIController::CheckFunction(uchar function)
{
    current_function = function;

    uchar base_class = GetClassCode(current_bus, current_device, current_function);
    uchar sub_class  = GetSubClass(current_bus, current_device, current_function);
    system << info << std::hex << "Base class: " << base_class << ", sub class: " << sub_class << endl;
    if((base_class == 0x06) && (sub_class == 0x04))
    {
        system << info << "PCI-to-PCI bridge found." << endl;
        CheckBus(GetSecondaryBus(current_bus, current_device, current_function));
    }
    else if(base_class != 0x00)
    {
        system << info << std::hex << "Base class: " << base_class << ", sub class: " << sub_class << endl;
    }


    return true;
}
