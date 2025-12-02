#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_HPP

#include <memory>

#include "dr4/event.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/mouse_buttons.hpp"
#include "dr4/texture.hpp"
#include "dr4/math/vec2.hpp"

#include "widgets/WidgetsState.hpp"

namespace optor 
{

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
        virtual bool OnTextInput      (const dr4::Event& event);
        virtual void OnIdle           ();

        void SetBackgroundColor (const dr4::Color& color);
        void SetBorderColor     (const dr4::Color& color);
        void SetOutlineThickness(double thickness);
        void SetParent          (optor::Widget* parent);  
        void SetIsDraggable     (const bool isDraggable);
        void SetIsFreeDraggable (const bool isFreeDraggable);
        void SetDragButton      (dr4::MouseButtonType dragButton);
        void SetIsSelectable    (const bool isSelectable);
        void SetSelectButton    (dr4::MouseButtonType selectButton);
        void SetUnselectButton  (dr4::KeyCode unselectButton);
        void SetMustRemoved     (const bool mustRemoved);
        void SetName            (const std::string& name);
        void SetIsHide          (const bool isHide);
        
        [[nodiscard]] dr4::Vec2f AbsCoord() const;  

        [[nodiscard]] dr4::Vec2f                 GetSize            () const;
        [[nodiscard]] dr4::Vec2f                 GetPosition        () const;
        [[nodiscard]] optor::WidgetsState*       GetState           () const;
        [[nodiscard]] dr4::Color                 GetBackgroundColor () const;
        [[nodiscard]] dr4::Color                 GetBorderColor     () const;
        [[nodiscard]] double                     GetOutlineThickness() const;
        [[nodiscard]] optor::Widget*             GetParent          () const;
        [[nodiscard]] bool                       GetIsDraggable     () const;
        [[nodiscard]] bool                       GetIsFreeDraggable () const;
        [[nodiscard]] dr4::MouseButtonType             GetDragButton      () const;
        [[nodiscard]] bool                       GetIsSelectable    () const;
        [[nodiscard]] dr4::MouseButtonType             GetSelectButton    () const;
        [[nodiscard]] dr4::KeyCode               GetUnselectButton  () const;
        [[nodiscard]] bool                       GetMustRemoved     () const;
        [[nodiscard]] std::optional<std::string> GetName            () const;
        [[nodiscard]] bool                       GetIsHide          () const;
        
        [[nodiscard]] virtual bool IsInderectedHovered() const;

        [[nodiscard]] virtual std::string GetTypeName() const {return "Widget"; };
    protected:
        std::unique_ptr<dr4::Rectangle> rect_;

        optor::Widget* parent_;
        optor::WidgetsState* const state_;

        bool isDraggable_;
        dr4::MouseButtonType dragButton_;
        bool isFreeDraggable_;

        bool isSelectable_;
        dr4::MouseButtonType selectButton_;
        dr4::KeyCode  unselectButton_;

        bool mustRemoved_;
        bool isHide_;

        std::optional<std::string> name_;

        bool OnMe(const dr4::Vec2f& absCoord) const;
        void Drag(const dr4::Vec2f& shift);

    private:
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_HPP*/