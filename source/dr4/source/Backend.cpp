#include "dr4/Backend.hpp"
#include "dr4/Window.hpp"
#include "dr4/Image.hpp"

const std::string &optor::dr4::Backend::Name() const 
{
    static std::string name = "SOSAT_PENISES";
    return name;
}

::dr4::Window *optor::dr4::Backend::CreateWindow() 
{
    return new optor::dr4::Window();
}

::dr4::Image  *optor::dr4::Backend::CreateImage()
{
    return new optor::dr4::Image();
}

::dr4::DR4Backend* optor::dr4::DR4_BACKEND_FUNCTION()
{
    return new optor::dr4::Backend();
}