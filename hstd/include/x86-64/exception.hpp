#ifndef __EXCEPTIONS__
#define __EXCEPTIONS__

#include <HStdTypes>
#include <HString>
#include <HSystemInfos>

class HException
{
public:
    HException();
    HException(ulong id, ulong code, HString info, Registers &regs);
    ~HException() = default;

    auto IsExceptionHandled() const -> bool;

	auto GetId() const -> ulong;
	auto GetCode() const -> ulong;
    auto GetDescription() const -> const HString &;
	auto GetRegisters() const -> const Registers &;

	void Handled(bool handled);

protected:
	ulong except_id;
    ulong except_code;
    HString except_info;
	Registers except_registers;
    bool except_handled;
};

#endif
