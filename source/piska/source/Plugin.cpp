#include <memory>

#include "piska/Plugin.hpp"
#include "piska/ArrowTool.hpp"
#include "piska/CircleTool.hpp"
#include "piska/RectTool.hpp"
#include "piska/TextTool.hpp"

optor::pp::PPToolPlugin::PPToolPlugin()  
{}

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
    vec.emplace_back(std::make_unique<optor::pp::CircleTool>(cvs));
    vec.emplace_back(std::make_unique<optor::pp::ArrowTool>(cvs));
    vec.emplace_back(std::make_unique<optor::pp::TextTool>(cvs));
    return vec;
}

extern "C" cum::Plugin* CreatePlugin() {
    return new optor::pp::PPToolPlugin();
}