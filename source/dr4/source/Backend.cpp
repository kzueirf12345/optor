#include "cum/manager.hpp"

#include "dr4/Backend.hpp"
#include "dr4/Window.hpp"


::dr4::Window *optor::dr4::Backend::CreateWindow() 
{
    return new optor::dr4::Window();
}

std::string_view optor::dr4::Backend::GetIdentifier() const {
    return "DR4BackendPlugin";
}

std::string_view optor::dr4::Backend::GetName() const {
    return "DR4BackendPluginName";
}

std::string_view optor::dr4::Backend::GetDescription() const {
    return "DR4BackendPluginDesc";
}

std::vector<std::string_view> optor::dr4::Backend::GetDependencies() const {
    return {};
}
    
std::vector<std::string_view> optor::dr4::Backend::GetConflicts() const {
    return {};
}

void optor::dr4::Backend::AfterLoad() {

}

extern "C" cum::Plugin* cum::CREATE_PLUGIN_FUNC_NAME() {
    return new optor::dr4::Backend();
}