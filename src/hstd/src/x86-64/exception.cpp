#include "../../include/x86-64/exception.hpp"

#include <cMemory>

HException::HException() :
    except_code(0xFFFFFFFFFFFFFFFF),
    except_info("Unknown exception"),
    except_handled(false)
{
}

HException::HException(ulong id, ulong code, HString info, Registers &regs) :
	except_id(id),
    except_code(code),
    except_info(info),
    except_handled(false)
{
	memcpy(&except_registers, &regs, sizeof(Registers));
}

auto HException::IsExceptionHandled() const -> bool
{
    return except_handled;
}

auto HException::GetId() const -> ulong
{
	return except_id;
}

auto HException::GetCode() const -> ulong
{
    return except_code;
}

auto HException::GetDescription() const -> const HString &
{
    return except_info;
}

auto HException::GetRegisters() const -> const Registers &
{
	return except_registers;
}

void HException::Handled(bool handled)
{
	except_handled = handled;
}
