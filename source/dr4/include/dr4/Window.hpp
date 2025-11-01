#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_WINDOW_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_WINDOW_HPP

#include "SFML/Graphics/RenderWindow.hpp"

#include "dr4/window.hpp"
#include <SFML/System/Vector2.hpp>

namespace optor
{
namespace dr4 
{

class Window : public ::dr4::Window
{ 
public:

    virtual void SetTitle(const std::string &title) override;
    virtual const std::string &GetTitle() const override;

    virtual ::dr4::Vec2f GetSize() const override;
    virtual void SetSize(const ::dr4::Vec2f& size) override;

    virtual void Open() override;
    virtual bool IsOpen() const override;
    virtual void Close() override;

    virtual void Clear(const ::dr4::Color &color) override;
    virtual void Draw(const ::dr4::Texture &texture, ::dr4::Vec2f pos) override;
    virtual void Display() override;

    virtual ::dr4::Texture *CreateTexture() override;

    virtual std::optional<::dr4::Event> PollEvent() override;

protected:
private:
    sf::RenderWindow window_;
    std::string title_;
    sf::Vector2u size_;
};

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_WINDOW_HPP*/