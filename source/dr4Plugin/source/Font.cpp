#include <stdexcept>

#include "dr4Plugin/Font.hpp"

#include "common/ErrorHandler.hpp"

optor::dr4::Font::Font()
    :   font_{}
{
    try {
        LoadFromFile("/usr/share/fonts/TTF/CaskaydiaCoveNerdFontMono-Regular.ttf");
    } catch(const std::runtime_error& e) {

    }
}

void optor::dr4::Font::LoadFromFile(const std::string& path)
{
    ERROR_HANDLE([this, &path](){
        if (!font_.loadFromFile(path)) {
            throw std::runtime_error("Can't load font from file");
        }
    });
}

void optor::dr4::Font::LoadFromBuffer(const void *buffer, size_t size) {
        ERROR_HANDLE([this, buffer, &size](){
        if (!font_.loadFromMemory(buffer, size)) {
            throw std::runtime_error("Can't load font from buffer");
        }
    });
}

float optor::dr4::Font::GetAscent(float fontSize) const {
    sf::Uint32 character = 'H';
    
    const sf::Glyph& glyph = font_.getGlyph(character, fontSize, false);
    
    return -glyph.bounds.top;
}

float optor::dr4::Font::GetDescent(float fontSize) const {
    sf::Uint32 character = 'g';
    
    const sf::Glyph& glyph = font_.getGlyph(character, fontSize, false);
    
    float bottom = glyph.bounds.top + glyph.bounds.height;
    return std::max(0.0f, bottom);
}

optor::dr4::Font::Font(sf::Font font)
    :   font_{std::move(font)}
{}