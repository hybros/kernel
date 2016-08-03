#include "error_handler.hpp"
#include "../system/system.hpp"
#include "../std/data_extract.hpp"
#include "../std/string.hpp"
using namespace kernel;

const char *error_cause_class[] =
{
    "System",
    "PhysicalMemoryManager",
    "VirtualMemoryManager",
    "HeapMemoryManager",
    "LocalAPIC"
};

const char *error_cause_function[]
{
    "InitPhysicalMemoryManager",
    "AllocateBlock",
    "AllocateBlocks",
    "FreeBlock",
    "FreeBlocks"
};

char error_cause_string[1024];

ErrorHandler::ErrorHandler(System &system_ref) : system(system_ref) {}

ErrorHandler::~ErrorHandler() {}

void ErrorHandler::AddError(ErrorInfo &info)
{
    errors.PushLastElement(info);
    HandleError(info);
}

ErrorInfo &ErrorHandler::GetLastError()
{
    return errors.GetLastElement();
}

void ErrorHandler::HandleError(ErrorInfo &info)
{
    InformUser(info);
    errors.EraseElement(errors.GetPosition(info));
}

void ErrorHandler::InformUser(ErrorInfo &info)
{
    std::String error_string(error_cause_string, sizeof(error_cause_string));
    error_string += "ErrorHandler -> Error occured in ";

    ushort error_cause_id_class = std::ExtractWord(info.error_cause_id, 0);         // Append called class name
    error_string += error_cause_class[error_cause_id_class];

    error_string += "::";

    ushort error_cause_id_function = std::ExtractWord(info.error_cause_id, 1);      // Append called function name
    error_string += error_cause_function[error_cause_id_function];

    system << error << error_string << video::endl;
}
