#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_BACKEND_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_BACKEND_HPP

#include "cum/ifc/dr4.hpp"

namespace optor
{
namespace dr4 
{

class Backend final: public ::cum::DR4BackendPlugin
{ 

public:

    virtual std::string_view GetIdentifier() const override;

    virtual std::string_view GetName() const override;

    virtual std::string_view GetDescription() const override;

    virtual std::vector<std::string_view> GetDependencies() const override;
    
    virtual std::vector<std::string_view> GetConflicts() const override;

    virtual void AfterLoad() override;

    virtual ::dr4::Window *CreateWindow() override;

    ~Backend();

protected:
private:
    
};

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_BACKEND_HPP*/