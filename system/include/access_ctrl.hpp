#ifndef __SYSTEM_ACCESS_CONTROL__
#define __SYSTEM_ACCESS_CONTROL__

#include "../std/data_types.hpp"
#include "../std/bits.hpp"
#include "../std/memory.hpp"
//#include "../std/vector.hpp"

enum AccessArea
{
    ACCESS_MEMORY   = 0x1,
    ACCESS_SECURITY = 0x2,
    ACCESS_TERMINAL = 0x4,
    ACCESS_NORMAL   = 0x4,
    ACCESS_SYSTEM   = 0xFFFFFFFF,
};

enum AccessControlBit
{
    ACC_CON_MEMORY,
    ACC_CON_SECURITY,
    ACC_CON_TERMINAL
};

struct AccessSpecifier
{
    inline AccessSpecifier(uint access_rights);

    inline uint GetAccessRights();

private:
    uint as_access_rights;
    uint as_unique_id;
};

class System;

class AccessControl
{
public:
    AccessControl();
    ~AccessControl();

    inline bool IsOperationPermitted(uint module_type_bit);

    inline uint GetAccessRights();
    inline void SetAccessRights(uint access_rights);

private:
//    std::Vector<AccessSpecifier> ac_access_specifiers;
    uint current_access_rights;
    size_t number_of_instances;
};

// ~ AccessSpecifier

AccessSpecifier::AccessSpecifier(uint access_rights) : as_access_rights(access_rights)
{

}

uint AccessSpecifier::GetAccessRights()
{
    return as_access_rights;
}

// ~ AccessControl

bool AccessControl::IsOperationPermitted(uint module_type_bit)
{
    return std::IsBitSet(current_access_rights, module_type_bit);
}

uint AccessControl::GetAccessRights()
{
    return current_access_rights;
}

void AccessControl::SetAccessRights(uint access_rights)
{
    current_access_rights = access_rights;
}


#endif // __SYSTEM_ACCESS_CONTROL__
