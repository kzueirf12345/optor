#ifndef OPTOR_SOURCE_GEOMPRIM_INCLUDE_GEOMPRIM_RECT_HPP
#define OPTOR_SOURCE_GEOMPRIM_INCLUDE_GEOMPRIM_RECT_HPP

#include "cum/dr4_ifc.hpp"
#include "dr4/texture.hpp"

#include "hui/geomprim.hpp"
#include <memory>

namespace optor 
{
namespace geomprim 
{

class Rect final: public hui::GeomPrim {

public:

    Rect(dr4::DR4Backend* backend);

    hui::EventResult OnMouseMove()    override;
    hui::EventResult OnMouseDown()    override;
    hui::EventResult OnMouseRelease() override;

    virtual void DrawOn(dr4::Texture& texture) const override;

    virtual void SetPos(dr4::Vec2f pos) override;

    virtual dr4::Vec2f GetPos() const override;

private:
    std::unique_ptr<dr4::Rectangle> rect_;


    
};

}
}

#endif /*OPTOR_SOURCE_GEOMPRIM_INCLUDE_GEOMPRIM_RECT_HPP*/