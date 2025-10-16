#ifndef OPTOR_SOURCE_WINDOWS_INCLUDE_WINDOWS_WIDNOW_HPP
#define OPTOR_SOURCE_WINDOWS_INCLUDE_WINDOWS_WIDNOW_HPP

#include "hui/Event.hpp"
#include "hui/RectangleShape.hpp"
#include "hui/Vector.hpp"
#include "hui/Window.hpp"
#include "widgets/WidgetManager.hpp"
#include <SFML/Window/Event.hpp>

namespace optor 
{

    class Widget {
    public:
        explicit Widget(hui::RectangleShape rect, optor::WidgetsState* state);

        virtual ~Widget() = default;

        virtual void Draw       (hui::Window* window);
        virtual void SetPosition(const hui::Vector2d& position);
        
        virtual bool OnMouseMove   (const hui::Event& event);
        virtual bool OnMousePress  (const hui::Event& event);
        virtual bool OnMouseRelease(const hui::Event& event);
        virtual void OnIdle        ();

        void SetBackgroundColor (const hui::Color& color);
        void SetBorderColor     (const hui::Color& color);
        void SetOutlineThickness(double thickness);
        void SetParent          (optor::Widget* parent)                     noexcept;  
        void SetIsDraggable     (const bool isDraggable)                    noexcept;
        void SetIsFreeDraggable (const bool isFreeDraggable)                noexcept;
        void SetDraggableButton (hui::Event::MouseButton draggableButton)   noexcept;
        
        [[nodiscard]] hui::Vector2d AbsCoord() const;  

        [[nodiscard]] hui::Vector2d GetSize() const;
    protected:
        hui::RectangleShape rect_;
        optor::Widget* parent_;
        optor::WidgetsState* const state_;

        bool isDraggable_;
        hui::Event::MouseButton draggableButton_;
        bool isFreeDraggable_;

        bool OnMe(const hui::Vector2d& absCoord) const;
        void Drag(const hui::Vector2d& shift);

    private:
};

}

#endif /*OPTOR_SOURCE_WINDOWS_INCLUDE_WINDOWS_WIDNOW_HPP*/