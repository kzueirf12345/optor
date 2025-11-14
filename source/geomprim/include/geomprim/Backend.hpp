#ifndef OPTOR_SOURCE_GEOMPRIM_INCLUDE_GEOMPRIM_BACKEND_HPP
#define OPTOR_SOURCE_GEOMPRIM_INCLUDE_GEOMPRIM_BACKEND_HPP

#include "cum/geomprim_ifc.hpp"
#include "cum/version.hpp"
#include <cstddef>

namespace optor
{
namespace geomprim 
{

enum class ObjType: size_t {
    RECTANGLE = 1
};

inline static const ::dr4::Color FillColor(0x20, 0x21, 0x2d, 0xff);
inline static const ::dr4::Color BorderColor(0xd7, 0x46, 0x4e, 0xff);
inline static const ::dr4::Color TransparentColor(0x0, 0x00, 0x0, 0x00);

inline static constexpr float OutlineThickness = 5;
inline static const dr4::Vec2f OutlineThicknessVec = {
    optor::geomprim::OutlineThickness,
    optor::geomprim::OutlineThickness
};

class Backend final: public hui::GeomPrimBackend
{ 

public:

    virtual hui::GeomPrim* CreateGeomPrim(size_t geomPrimType, dr4::Window* dr4Window) override;

    virtual const std::string &GetName() const override;

    virtual const std::string &GetDescription() const override;
    virtual const cum::PluginVersion &GetVersion() const override;

    virtual std::vector<std::string> GetDependencies() const override;
    virtual bool IsCompatibleWith(const Plugin& other) const override;

protected:
private:
    std::string name_ = "$$$VovchikGeomPrimPlugin$$$";
    std::string desc_ = "Eto description plugina '" + name_ + "'. Proshu vseh vstat'. Zvuchit gimn.";
    cum::PluginVersion version_ = {.major = 1, .minor = 1, .patch = 0};
    
};

extern "C" hui::GeomPrimBackend* GEOM_PRIM_BACKEND_FUNCTION();

}
}

#endif /*OPTOR_SOURCE_GEOMPRIM_INCLUDE_GEOMPRIM_BACKEND_HPP*/