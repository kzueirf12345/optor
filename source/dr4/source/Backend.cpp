#include "dr4/Backend.hpp"
#include "dr4/Window.hpp"

const std::string &optor::dr4::Backend::GetName() const {
    return name_;
}

::dr4::Window *optor::dr4::Backend::CreateWindow() 
{
    return new optor::dr4::Window();
}

const std::string &optor::dr4::Backend::GetDescription() const {
    return desc_;
}
const cum::PluginVersion &optor::dr4::Backend::GetVersion() const {
    return version_;
}

std::vector<std::string> optor::dr4::Backend::GetDependencies() const {
    return {};
}
bool optor::dr4::Backend::IsCompatibleWith(const Plugin& other) const {
    return true;
}

::dr4::DR4Backend *optor::dr4::DR4_BACKEND_FUNCTION()
{
    return new optor::dr4::Backend();
}