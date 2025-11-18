#include <memory>

#include "cum/manager.hpp"
#include "piska/Plugin.hpp"
#include "piska/RectTool.hpp"

std::string_view optor::pp::PPToolPlugin::GetIdentifier() const {
    return "PPToolPlugin";
}

std::string_view optor::pp::PPToolPlugin::GetName() const {
    return "VovchikPPToolPluginName";
}

std::string_view optor::pp::PPToolPlugin::GetDescription() const {
    return "VovchikPPToolPluginDesc";
}

std::vector<std::string_view> optor::pp::PPToolPlugin::GetDependencies() const {
    return {"DR4BackendPlugin"};
}

std::vector<std::string_view> optor::pp::PPToolPlugin::GetConflicts() const {
    return {};
}

void optor::pp::PPToolPlugin::AfterLoad() {

}

std::vector<std::unique_ptr<::pp::Tool>> optor::pp::PPToolPlugin::CreateTools(::pp::Canvas *cvs) {
    std::vector<std::unique_ptr<::pp::Tool>> vec;
    vec.emplace_back(std::make_unique<optor::pp::RectTool>(cvs));
    return vec;
}

extern "C" cum::Plugin* cum::CREATE_PLUGIN_FUNC_NAME() {
    return new optor::pp::PPToolPlugin();
}