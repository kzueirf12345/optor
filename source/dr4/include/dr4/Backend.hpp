#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_BACKEND_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_BACKEND_HPP

#include "cum/dr4_ifc.hpp"
#include "cum/version.hpp"

namespace optor
{
namespace dr4 
{

class Backend : public ::dr4::DR4Backend
{ 

public:

    virtual const std::string &GetName() const override;
    virtual ::dr4::Window *CreateWindow() override;

    virtual const std::string &GetDescription() const override;
    virtual const cum::PluginVersion &GetVersion() const override;

    virtual std::vector<std::string> GetDependencies() const override;
    virtual bool IsCompatibleWith(const Plugin& other) const override;

protected:
private:
    std::string name_ = "$$$VovchikDR4Plugin$$$";
    std::string desc_ = "Eto description plugina '" + name_ + "'. Proshu vseh vstat'. Zvuchit gimn.";
    cum::PluginVersion version_ = {.major = 1, .minor = 1, .patch = 0};
    
};

extern "C" ::dr4::DR4Backend* DR4_BACKEND_FUNCTION();

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_BACKEND_HPP*/