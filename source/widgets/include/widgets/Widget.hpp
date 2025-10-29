#ifndef OPTOR_SOURCE_WINDOWS_INCLUDE_WINDOWS_WIDNOW_HPP
#define OPTOR_SOURCE_WINDOWS_INCLUDE_WINDOWS_WIDNOW_HPP

#include "hui/Event.hpp"
#include "hui/Texture.hpp"
#include "hui/Vector.hpp"
#include "widgets/WidgetManager.hpp"
#include "hui/Sprite.hpp"

namespace optor 
{

class Widget {
    public:
        Widget(const hui::Vector2d& size, optor::WidgetsState* state);

        virtual ~Widget() = default;

        virtual void Draw       (hui::Renderer* renderer);
        virtual void SetPosition(const hui::Vector2d& position);
        
        virtual bool OnMouseMove      (const hui::Event& event);
        virtual bool OnMousePress     (const hui::Event& event);
        virtual bool OnMouseRelease   (const hui::Event& event);
        virtual bool OnKeyboardPress  (const hui::Event& event);
        virtual bool OnKeyboardRelease(const hui::Event& event);
        virtual void OnIdle           ();

        void SetBackgroundColor (const hui::Color& color);
        // void SetBorderColor     (const hui::Color& color);
        // void SetOutlineThickness(double thickness);
        void SetParent          (optor::Widget* parent)                     noexcept;  
        void SetIsDraggable     (const bool isDraggable)                    noexcept;
        void SetIsFreeDraggable (const bool isFreeDraggable)                noexcept;
        void SetDragButton      (hui::Event::MouseButton dragButton)        noexcept;
        void SetIsSelectable    (const bool isSelectable)                   noexcept;
        void SetSelectButton    (hui::Event::MouseButton selectButton)      noexcept;
        void SetUnselectButton  (hui::Event::KeyboardButton unselectButton) noexcept;
        
        [[nodiscard]] hui::Vector2d AbsCoord() const;  

        [[nodiscard]] hui::Vector2d GetSize() const;
        [[nodiscard]] hui::Vector2d GetPosition() const;

    protected:
        hui::Texture texture_;
        hui::Sprite sprite_;
        bool spriteIsValid_;

        optor::Widget* parent_;
        optor::WidgetsState* const state_;

        bool isDraggable_;
        hui::Event::MouseButton dragButton_;
        bool isFreeDraggable_;

        bool isSelectable_;
        hui::Event::MouseButton selectButton_;
        hui::Event::KeyboardButton unselectButton_;

        bool OnMe(const hui::Vector2d& absCoord) const;
        void Drag(const hui::Vector2d& shift);

    private:
};

}

#endif /*OPTOR_SOURCE_WINDOWS_INCLUDE_WINDOWS_WIDNOW_HPP*/