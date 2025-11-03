#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_FONT_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_FONT_HPP

#include <SFML/Graphics/Font.hpp>

#include "dr4/Texture.hpp"

namespace optor
{
namespace dr4 
{

class Font : public ::dr4::Font { 

public:
    friend ::dr4::Text;
    friend optor::dr4::Texture;

    virtual void loadFromFile(const std::string& path) override;

protected:
private:

    sf::Font font_;
};

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_FONT_HPP*/