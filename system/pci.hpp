#ifndef __PCI_CONTROLLER__
#define __PCI_CONTROLLER__

#include "../std/data_types.hpp"
#include "pci_infos.hpp"
#include "terminal.hpp"

#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA    0xCFC

namespace kernel
{

class System;

class PCIController
{
public:
    PCIController();
    ~PCIController();

    void CheckBus(uchar bus);
    bool CheckDevice(uchar device);
    bool CheckFunction(uchar function);

//    template<typename T, T pci::HeaderType00::* P> inline T ReadRegister(uint config_address);
//    template<typename T, T pci::HeaderType01::* P> inline T ReadRegister(uint config_address);
    inline uint CreateConfigAddress(uchar bus, uchar device, uchar function, uchar reg);

    inline ushort GetDeviceId(uchar bus, uchar device, uchar function);
    inline ushort GetVendorId(uchar bus, uchar device, uchar function);
    inline uchar  GetHeaderType(uchar bus, uchar device, uchar function);
    inline uchar  GetClassCode(uchar bus, uchar device, uchar function);
    inline uchar  GetSubClass(uchar bus, uchar device, uchar function);
    inline uchar  GetSecondaryBus(uchar bus, uchar device, uchar function);

private:
    System &system;
    uchar current_bus, current_device, current_function, current_register;
    pci::HeaderType00 *conifg_data;
};

}


#define THIS *this

#endif // __PCI_CONTROLLER__
