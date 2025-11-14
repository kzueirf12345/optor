#include <cassert>
#include <cstddef>

#include "geomprim/Backend.hpp"
#include "geomprim/Circle.hpp"
#include "geomprim/Rect.hpp"

hui::GeomPrim* optor::geomprim::Backend::CreateGeomPrim(size_t geomPrimType, dr4::Window* dr4Window) {
    assert(dr4Window);
    
    if (geomPrimType == (size_t)optor::geomprim::ObjType::RECTANGLE) {
        return new optor::geomprim::Rect(dr4Window);
    }

    if (geomPrimType == (size_t)optor::geomprim::ObjType::CIRCLE) {
        return new optor::geomprim::Circle(dr4Window);
    }

    return nullptr;
}

const std::string &optor::geomprim::Backend::GetName() const {
    return name_;
}

const std::string &optor::geomprim::Backend::GetDescription() const {
    return desc_;
}
const cum::PluginVersion &optor::geomprim::Backend::GetVersion() const {
    return version_;
}

std::vector<std::string> optor::geomprim::Backend::GetDependencies() const {
    return {"dr4"};
}
bool optor::geomprim::Backend::IsCompatibleWith(const Plugin& other) const {
    return true;
}

hui::GeomPrimBackend *optor::geomprim::CreateGeomPrimBackend()
{
    return new optor::geomprim::Backend();
}