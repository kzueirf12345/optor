#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_SCROLL_BAR_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_SCROLL_BAR_HPP

#include <functional>
#include <memory>

#include "dr4/keycodes.hpp"
#include "dr4/mousecodes.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "dr4/event.hpp"
#include "dr4/window.hpp"

#include "widgets/Widget.hpp"
#include "widgets/WidgetButton.hpp"

namespace optor 
{

class ScrollBar: public Widget {
    public:
        static const dr4::MouseCode  CONTROL_BUTTON_         = dr4::MouseCode::MOUSECODE_LEFT;
        static const dr4::KeyCode    INC_KEYBOARD_BUTTON_    = dr4::KeyCode::KEYCODE_UP;
        static const dr4::KeyCode    DEC_KEYBOARD_BUTTON_    = dr4::KeyCode::KEYCODE_DOWN;
        static const dr4::KeyCode    ZERO_KEYBOARD_BUTTON_   = dr4::KeyCode::KEYCODE_NUMPAD2;
        static const dr4::KeyCode    FULL_KEYBOARD_BUTTON_   = dr4::KeyCode::KEYCODE_NUMPAD8;

        using ActionT = std::function<void(float)>; 

        ScrollBar(dr4::Window* window, const dr4::Vec2f& size, optor::WidgetsState* state, 
                  ActionT action, bool isHorizontal = false);

        virtual void Draw(dr4::Texture& srcTexture) override;

        virtual bool OnMouseMove      (const dr4::Event& event) override;
        virtual bool OnMousePress     (const dr4::Event& event) override;
        virtual bool OnMouseRelease   (const dr4::Event& event) override;
        virtual bool OnKeyboardPress  (const dr4::Event& event) override;
        virtual bool OnKeyboardRelease(const dr4::Event& event) override;
        virtual void OnIdle           ()                        override;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "ScrollBar"; };

    private:
        using HandleButtonsT = std::function<bool(optor::WidgetButton&, const dr4::Event&)>;
        bool Propagate(const dr4::Event& event, HandleButtonsT handler);

    private:
        static constexpr float BUTTON_SIZE_PERCENT_ = 0.1; 
        static constexpr float MIN_SHIFT_ = 0.05;

        std::unique_ptr<dr4::Texture> texture_;
    
        ActionT action_;
        
        float percentage_;
        bool isHorizontal_;
        const dr4::Vec2f buttonSize_;
        WidgetButton incButton_, decButton_, thumbButton_;

        bool isPressedInc_;
        bool isPressedDec_;

        void Move(float shiftPercent);
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_SCROLL_BAR_HPP*/