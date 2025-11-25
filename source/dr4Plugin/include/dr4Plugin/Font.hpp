#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_FONT_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_FONT_HPP

#include <SFML/Graphics/Font.hpp>

#include "dr4Plugin/Text.hpp"
#include "dr4Plugin/Texture.hpp"

namespace optor
{
namespace dr4 
{

class Font final: public ::dr4::Font { 

    friend optor::dr4::Text;

public:

    Font();

    virtual void LoadFromFile(const std::string &path) override;
    virtual void LoadFromBuffer(const void *buffer, size_t size) override;

    virtual float GetAscent (float fontSize) const override;
    virtual float GetDescent(float fontSize) const override;

protected:
private:

    sf::Font font_;

private:

    explicit Font(sf::Font font);
};

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_FONT_HPP*/