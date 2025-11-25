#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_CIRCLE_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_CIRCLE_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

namespace optor
{
namespace dr4 
{

class Circle final: public ::dr4::Circle { 

public:

    Circle();
    
    virtual void SetCenter(::dr4::Vec2f center) override;
    virtual void SetRadius(::dr4::Vec2f radius) override;
    virtual void SetFillColor(::dr4::Color color) override;
    virtual void SetBorderColor(::dr4::Color color) override;
    virtual void SetBorderThickness(float thickness) override;

    virtual ::dr4::Vec2f GetCenter() const override;
    virtual ::dr4::Vec2f GetRadius() const override;
    virtual ::dr4::Color GetFillColor() const override;
    virtual ::dr4::Color GetBorderColor() const override;
    virtual float GetBorderThickness() const override;

    virtual void DrawOn(::dr4::Texture& texture) const override;

    virtual void SetPos(::dr4::Vec2f pos) override;

    virtual ::dr4::Vec2f GetPos() const override;

protected:
private:
    sf::CircleShape circle_;
};

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_CIRCLE_HPP*/