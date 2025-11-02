#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_BACKEND_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_BACKEND_HPP

#include "misc/dr4_ifc.hpp"

namespace optor
{
namespace dr4 
{

class Backend : public ::dr4::DR4Backend
{ 
public:
    virtual const std::string &Name() const override;
    virtual ::dr4::Image  *CreateImage() override;
    virtual ::dr4::Window *CreateWindow() override;
protected:
private:
};

extern "C" ::dr4::DR4Backend* DR4_BACKEND_FUNCTION();

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_BACKEND_HPP*/