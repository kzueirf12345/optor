#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

#include "dr4Plugin/Text.hpp"
#include "dr4Plugin/Font.hpp"
#include "dr4Plugin/Texture.hpp"

#include "common/ErrorHandler.hpp"
#include "dr4/texture.hpp"

optor::dr4::Text::Text()
    :   text_{},
        offset_{},
        valign_{::dr4::Text::VAlign::TOP}
{}

void optor::dr4::Text::SetText(const std::string &text) {
    str_ = text;
    ERROR_HANDLE([this, &text](){
        text_.setString(text);
    });
}

void optor::dr4::Text::SetColor(::dr4::Color color) {
    ERROR_HANDLE([this, &color](){
        text_.setFillColor({color.r, color.g, color.b, color.a});
    });
}

void optor::dr4::Text::SetFontSize(float size) {
    ERROR_HANDLE([this, &size](){
        text_.setCharacterSize(static_cast<unsigned>(size));
    });
}

void optor::dr4::Text::SetVAlign(::dr4::Text::VAlign align) {
    const ::dr4::Vec2f bounds = GetBounds();
    const sf::Vector2f prevPosSF = text_.getPosition() - sf::Vector2f{offset_.x, offset_.y};

    valign_ = align;

    switch(align) {
        case ::dr4::Text::VAlign::TOP: {
            break;
        }
        case ::dr4::Text::VAlign::MIDDLE: {
            offset_.y = -bounds.y / 2.;
            break;
        }
        case ::dr4::Text::VAlign::BASELINE: {
            offset_.y = -bounds.y / 2.; //FIXME
            break;
        }
        case ::dr4::Text::VAlign::BOTTOM: {
            offset_.y = -bounds.y;
            break;
        }    

        case ::dr4::Text::VAlign::UNKNOWN:
        default:
            throw std::overflow_error("Unknown vertical align");
    }

    text_.setPosition(prevPosSF + sf::Vector2f{offset_.x, offset_.y});
}

void optor::dr4::Text::SetFont(const ::dr4::Font *font) {
    ERROR_HANDLE([this, font](){
        text_.setFont(dynamic_cast<const optor::dr4::Font*>(font)->font_);
    });
}

::dr4::Vec2f optor::dr4::Text::GetBounds() const {
    sf::FloatRect boundsSF = ERROR_HANDLE([this](){
        return text_.getLocalBounds();
    });
    return ::dr4::Vec2f{boundsSF.width, 2 * boundsSF.height};
}

const std::string &optor::dr4::Text::GetText() const {
    return str_;
}

::dr4::Color optor::dr4::Text::GetColor() const {
    sf::Color colorSF = ERROR_HANDLE([this](){
        return text_.getFillColor();
    });
    return {colorSF.r, colorSF.g, colorSF.b, colorSF.a};
}

float optor::dr4::Text::GetFontSize() const {
    return ERROR_HANDLE([this](){
        return text_.getCharacterSize();
    });
}

::dr4::Text::VAlign  optor::dr4::Text::GetVAlign() const {
    return valign_;
}

const ::dr4::Font   *optor::dr4::Text::GetFont() const {
    const static optor::dr4::Font font(*text_.getFont());
    return &font;
}

void optor::dr4::Text::DrawOn(::dr4::Texture& texture) const {
    optor::dr4::Texture& myTexture = dynamic_cast<optor::dr4::Texture&>(texture);

    ERROR_HANDLE([this, &myTexture](){
        myTexture.renderTexture_.draw(
            text_,
            sf::RenderStates().transform.translate(
                myTexture.zero_.x, 
                myTexture.zero_.y
            )
        );
    });
}

void optor::dr4::Text::SetPos(::dr4::Vec2f pos) {
    text_.setPosition({pos.x + offset_.x, pos.y + offset_.y});
}

::dr4::Vec2f optor::dr4::Text::GetPos() const {
    const sf::Vector2f posSF = ERROR_HANDLE([this](){
        return text_.getPosition();
    });
    return {posSF.x - offset_.x, posSF.y - offset_.y}; 
}

