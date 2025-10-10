#ifndef OPTOR_SOURCE_WINDOWS_INCLUDE_WINDOWS_WIDNOW_HPP
#define OPTOR_SOURCE_WINDOWS_INCLUDE_WINDOWS_WIDNOW_HPP

#include "hui/Event.hpp"
#include "hui/RectangleShape.hpp"
#include "hui/Vector.hpp"
#include "hui/Window.hpp"

namespace optor 
{
    
class Widget {
    public:
        explicit Widget(hui::RectangleShape rect, const optor::Widget** hoveredWidget);

        virtual ~Widget() = default;

        virtual void Draw       (hui::Window* window);
        virtual void SetPosition(const hui::Vector2d& position);
        
        virtual bool OnMouseMove(const hui::Event& event);

        void SetBackgroundColor (const hui::Color& color);
        void SetBorderColor     (const hui::Color& color);
        void SetOutlineThickness(double thickness);
        void SetParent          (optor::Widget* parent)  noexcept;  
        
        [[nodiscard]] hui::Vector2d AbsCoord() const;  


    protected:
        hui::RectangleShape rect_;
        optor::Widget* parent_;
        const optor::Widget** const hoveredWidget_;

        bool OnMe(const hui::Vector2d& absCoord) const;

    private:
};

}

#endif /*OPTOR_SOURCE_WINDOWS_INCLUDE_WINDOWS_WIDNOW_HPP*/