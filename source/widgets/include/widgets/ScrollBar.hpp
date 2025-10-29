#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_SCROLL_BAR_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_SCROLL_BAR_HPP

#include "hui/Vector.hpp"
#include "widgets/Widget.hpp"
#include "widgets/WidgetButton.hpp"
#include "hui/Event.hpp"

namespace optor 
{

class ScrollBar: public Widget {
    public:
        static const hui::Event::MouseButton    CONTROL_BUTTON_         = hui::Event::MouseButton::Left;
        static const hui::Event::KeyboardButton INC_KEYBOARD_BUTTON_    = hui::Event::KeyboardButton::Up;
        static const hui::Event::KeyboardButton DEC_KEYBOARD_BUTTON_    = hui::Event::KeyboardButton::Down;
        static const hui::Event::KeyboardButton ZERO_KEYBOARD_BUTTON_   = hui::Event::KeyboardButton::Numpad2;
        static const hui::Event::KeyboardButton FULL_KEYBOARD_BUTTON_   = hui::Event::KeyboardButton::Numpad8;

        using ActionT = std::function<void(double)>; 

        ScrollBar(const hui::Vector2d& pos, optor::WidgetsState* state, ActionT action, 
                  bool isHorizontal = true);

        virtual void Draw(hui::Renderer* renderer) override;

        virtual bool OnMouseMove      (const hui::Event& event) override;
        virtual bool OnMousePress     (const hui::Event& event) override;
        virtual bool OnMouseRelease   (const hui::Event& event) override;
        virtual bool OnKeyboardPress  (const hui::Event& event) override;
        virtual bool OnKeyboardRelease(const hui::Event& event) override;
        virtual void OnIdle           ()                        override;

    private:
        using HandleButtonsT = std::function<bool(optor::WidgetButton&, const hui::Event&)>;
        bool Propagate(const hui::Event& event, HandleButtonsT handler);

    private:
        static constexpr double BUTTON_SIZE_PERCENT_ = 0.1; 
        static constexpr double MIN_SHIFT_ = 0.05;

        hui::Renderer renderer_;
    
        ActionT action_;
        
        double percentage_;
        bool isHorizontal_;
        const hui::Vector2d buttonSize_;
        WidgetButton incButton_, decButton_, thumbButton_;

        bool isPressedInc_;
        bool isPressedDec_;

        void Move(double shiftPercent);
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_SCROLL_BAR_HPP*/