#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_TEXT_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_TEXT_HPP

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Text.hpp>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

namespace optor
{
namespace dr4 
{

class Text final: public ::dr4::Text {

public:

    Text();

    virtual void SetText(const std::string &text) override;
    virtual void SetColor(::dr4::Color color) override;
    virtual void SetFontSize(float size) override;
    virtual void SetVAlign(::dr4::Text::VAlign align) override;
    virtual void SetFont(const ::dr4::Font *font) override;

    virtual ::dr4::Vec2f         GetBounds() const override;
    virtual const std::string   &GetText() const override;
    virtual ::dr4::Color         GetColor() const override;
    virtual float                GetFontSize() const override;
    virtual ::dr4::Text::VAlign  GetVAlign() const override;
    virtual const ::dr4::Font   *GetFont() const override;

    virtual void DrawOn(::dr4::Texture& texture) const override;

    virtual void SetPos(::dr4::Vec2f pos) override;

    virtual ::dr4::Vec2f GetPos() const override;

private:
    sf::Text text_;

    ::dr4::Vec2f offset_;
    ::dr4::Text::VAlign valign_;

    std::string str_;
};

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_TEXT_HPP*/