#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_LINE_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_LINE_HPP

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

namespace optor
{
namespace dr4 
{

class Line final: public ::dr4::Line { 

public:

    Line();
    
    virtual void SetStart(::dr4::Vec2f start) override;
    virtual void SetEnd(::dr4::Vec2f end) override;
    virtual void SetColor(::dr4::Color color) override;
    virtual void SetThickness(float thickness) override;

    virtual ::dr4::Vec2f GetStart() const override;
    virtual ::dr4::Vec2f GetEnd() const override;
    virtual ::dr4::Color GetColor() const override;
    virtual float GetThickness() const override;

    virtual void DrawOn(::dr4::Texture& texture) const override;

    virtual void SetPos(::dr4::Vec2f pos) override;

    virtual ::dr4::Vec2f GetPos() const override;

protected:
private:
    sf::VertexArray vertices_;
    
    ::dr4::Vec2f start_;
    ::dr4::Vec2f end_;
    ::dr4::Vec2f pos_;
    float thickness_;

    ::dr4::Vec2f offset_;

    void UpdateOffset();
    void UpdateVertices();
};

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_LINE_HPP*/