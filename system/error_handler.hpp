#ifndef __ERROR_HANDLER__
#define __ERROR_HANDLER__

#include "error_codes.hpp"
#include "../std/data_types.hpp"
#include "../std/list.hpp"

namespace kernel
{

class System;

class ErrorHandler
{
public:
    ErrorHandler(System &system_ref);
    ~ErrorHandler();

    void AddError(ErrorInfo &info);

    ErrorInfo &GetLastError();

protected:
    void HandleError(ErrorInfo &info);
    void InformUser(ErrorInfo &info);

private:
    System &system;
    std::List<ErrorInfo> errors;
};

}
#endif // __ERROR_HANDLER__
