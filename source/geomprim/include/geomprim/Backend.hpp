#ifndef OPTOR_SOURCE_GEOMPRIM_INCLUDE_GEOMPRIM_BACKEND_HPP
#define OPTOR_SOURCE_GEOMPRIM_INCLUDE_GEOMPRIM_BACKEND_HPP

#include "cum/geomprim_ifc.hpp"
#include "cum/version.hpp"

namespace optor
{
namespace geomprim 
{

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