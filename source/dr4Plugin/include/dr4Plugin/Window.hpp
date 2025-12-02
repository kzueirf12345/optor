#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_WINDOW_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_WINDOW_HPP

#include "SFML/Graphics/RenderWindow.hpp"

#include "dr4/window.hpp"
#include <SFML/System/Vector2.hpp>
#include <chrono>

namespace optor
{
namespace dr4 
{

class Window final: public ::dr4::Window
{ 
public:

    Window();

    virtual void SetTitle(const std::string &title) override;
    virtual const std::string &GetTitle() const override;

    virtual ::dr4::Vec2f GetSize() const override;
    virtual void SetSize(::dr4::Vec2f size) override;

    virtual void Open() override;
    virtual bool IsOpen() const override;
    virtual void Close() override;

    virtual void Clear(::dr4::Color color) override;
    virtual void Draw(const ::dr4::Texture &texture) override;
    virtual void Display() override;

    virtual double GetTime() override;
    virtual void Sleep(double time) override;

    virtual ::dr4::Texture   *CreateTexture()   override;
    virtual ::dr4::Image     *CreateImage()     override;
    virtual ::dr4::Font      *CreateFont()      override;
    virtual ::dr4::Line      *CreateLine()      override;
    virtual ::dr4::Circle    *CreateCircle()    override;
    virtual ::dr4::Rectangle *CreateRectangle() override;
    virtual ::dr4::Text      *CreateText()      override;

    virtual void StartTextInput() override;
    virtual void StopTextInput() override;

    virtual std::optional<::dr4::Event> PollEvent() override;

protected:
private:
    sf::RenderWindow window_;
    std::string title_;
    sf::Vector2u size_;

    std::chrono::time_point<std::chrono::high_resolution_clock> ctorTime_;

    char utf8_buffer_[5];
};

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_WINDOW_HPP*/