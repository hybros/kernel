#ifndef __INTERRUPT_MANAGER__
#define __INTERRUPT_MANAGER__

#include <HSystemManager>
#include <HExceptions>
#include <HSystemInfos>

class HInterruptHandler
{
public:
    HInterruptHandler();
    HInterruptHandler(HException &);
    virtual ~HInterruptHandler();

    inline auto GetInterruptId() const -> uint;

    virtual void Handle(HException &actual_exception);
    virtual void CleanUp();

private:
    uint int_id;
};

class HInterruptManager : public HSystem::Manager
{
public:
    inline HInterruptManager();

    virtual auto GetFirstInterruptNumber() const -> uint = 0;
    virtual auto GetLastInterruptNumber() const -> uint = 0;

    virtual auto GetLastException() const -> HException = 0;
};

#endif
