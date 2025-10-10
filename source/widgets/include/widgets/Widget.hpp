#ifndef OPTOR_SOURCE_WINDOWS_INCLUDE_WINDOWS_WIDNOW_HPP
#define OPTOR_SOURCE_WINDOWS_INCLUDE_WINDOWS_WIDNOW_HPP

#include "hui/RectangleShape.hpp"
#include "hui/Window.hpp"

namespace optor 
{
    
class Widget {
    public:
        explicit Widget(hui::RectangleShape rect);

        virtual ~Widget() = default;

        virtual void Draw       (hui::Window* window);
        virtual void SetPosition(const hui::Vector2d& position);

        void SetBackgroundColor (const hui::Color& color);
        void SetBorderColor     (const hui::Color& color);
        void SetOutlineThickness(double thickness);
        void SetParent          (optor::Widget* parent)  noexcept;  

        [[nodiscard]] hui::Vector2d AbsCoord() const;      

    protected:
        hui::RectangleShape rect_;
        optor::Widget* parent_;
    
    private:
};

}

#endif /*OPTOR_SOURCE_WINDOWS_INCLUDE_WINDOWS_WIDNOW_HPP*/