#include "../include/int_manager.hpp"

auto HInterruptHandler::GetInterruptId() const -> uint
{
    return int_id;
}


HInterruptManager::HInterruptManager() :
    HSystem::Manager(HSystem::Manager::TERMINAL)
{
}
