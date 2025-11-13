#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_RECTANGLE_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_RECTANGLE_HPP


#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

namespace optor
{
namespace dr4 
{

class Rectangle final: public ::dr4::Rectangle { 

public:

    Rectangle();
    
    virtual void SetSize(::dr4::Vec2f size) override;
    virtual void SetFillColor(::dr4::Color color) override;
    virtual void SetBorderThickness(float thickness) override;
    virtual void SetBorderColor(::dr4::Color color) override;

    virtual ::dr4::Vec2f GetSize() const override;
    virtual ::dr4::Color GetFillColor() const override;
    virtual float GetBorderThickness() const override;
    virtual ::dr4::Color GetBorderColor() const override;

    virtual void DrawOn(::dr4::Texture& texture) const override;

    virtual void SetPos(::dr4::Vec2f pos) override;

    virtual ::dr4::Vec2f GetPos() const override;

protected:
private:
    sf::RectangleShape rect_;
};

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_RECTANGLE_HPP*/