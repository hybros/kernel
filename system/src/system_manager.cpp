#include "../include/system_manager.hpp"
#include "../include/system.hpp"

HSystem::Manager::Manager(Type type) : mgr_type(type), mgr_id(SYSTEM.GetCurrentManagerId(type)), mgr_currently_active(false) {}

bool HSystem::Manager::IsActive()
{
    return mgr_currently_active;
}

void HSystem::Manager::SetStatus(bool activate_manager)
{
    mgr_currently_active = activate_manager;
}

HSystem::Manager::operator HSystem &()
{
    return HSystem::GetInstance();
}
