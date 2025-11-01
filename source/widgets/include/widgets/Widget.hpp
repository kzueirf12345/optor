#ifndef OPTOR_SOURCE_WINDOWS_INCLUDE_WINDOWS_WIDNOW_HPP
#define OPTOR_SOURCE_WINDOWS_INCLUDE_WINDOWS_WIDNOW_HPP

#include "dr4/event.hpp"
#include "dr4/texture.hpp"
#include "dr4/math/vec2.hpp"



namespace optor 
{

class WidgetManager;
class WidgetsState;

class Widget {
    public:
        Widget(const dr4::Vec2f& size, optor::WidgetsState* state);

        virtual ~Widget() = default;

        virtual void Draw       (dr4::Texture& srcTexture);
        virtual void SetPosition(const dr4::Vec2f& position);
        
        virtual bool OnMouseMove      (const dr4::Event& event);
        virtual bool OnMousePress     (const dr4::Event& event);
        virtual bool OnMouseRelease   (const dr4::Event& event);
        virtual bool OnKeyboardPress  (const dr4::Event& event);
        virtual bool OnKeyboardRelease(const dr4::Event& event);
        virtual void OnIdle           ();

        void SetBackgroundColor (const dr4::Color& color);
        void SetBorderColor     (const dr4::Color& color);
        void SetOutlineThickness(double thickness);
        void SetParent          (optor::Widget* parent)                     noexcept;  
        void SetIsDraggable     (const bool isDraggable)                    noexcept;
        void SetIsFreeDraggable (const bool isFreeDraggable)                noexcept;
        void SetDragButton      (dr4::Event::MouseButton dragButton)        noexcept;
        void SetIsSelectable    (const bool isSelectable)                   noexcept;
        void SetSelectButton    (dr4::Event::MouseButton selectButton)      noexcept;
        void SetUnselectButton  (dr4::Event::KeyEvent  unselectButton)      noexcept;
        
        [[nodiscard]] dr4::Vec2f AbsCoord() const;  

        [[nodiscard]] dr4::Vec2f GetSize() const;
        [[nodiscard]] dr4::Vec2f GetPosition() const;

    protected:
        dr4::Rectangle rect_;
        bool spriteIsValid_;

        optor::Widget* parent_;
        optor::WidgetsState* const state_;

        bool isDraggable_;
        dr4::Event::MouseButton dragButton_;
        bool isFreeDraggable_;

        bool isSelectable_;
        dr4::Event::MouseButton selectButton_;
        dr4::Event::KeyEvent  unselectButton_;

        bool OnMe(const dr4::Vec2f& absCoord) const;
        void Drag(const dr4::Vec2f& shift);

    private:
};

}

#endif /*OPTOR_SOURCE_WINDOWS_INCLUDE_WINDOWS_WIDNOW_HPP*/