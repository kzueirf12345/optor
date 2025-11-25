#include "dr4Plugin/Backend.hpp"
#include "dr4Plugin/Window.hpp"
#include <dlfcn.h>

const std::string &optor::dr4::Backend::Name() const 
{
    static std::string name = "SOSAT_PENISES";
    return name;
}

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

optor::dr4::Backend::~Backend() {
    dlclose(GetSOHandle());
}

extern "C" cum::Plugin* CreatePlugin() {
    return new optor::dr4::Backend();
}