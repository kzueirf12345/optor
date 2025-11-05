#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_HIDE_BUTTON_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_HIDE_BUTTON_HPP

#include <memory>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

#include "widgets/Widget.hpp"
#include "widgets/WidgetButton.hpp"

namespace optor 
{

class HideButton: public WidgetButton {
    public:
        HideButton(const dr4::Vec2f& size, optor::WidgetsState* state, std::unique_ptr<optor::Widget> widget);

        virtual bool OnMousePress  (const ::dr4::Event& event) override;
        virtual bool OnMouseRelease(const ::dr4::Event& event) override;

        virtual void OnIdle() override;

        [[nodiscard]] virtual bool IsInderectedHovered() const override;

        virtual void SetPosition(const dr4::Vec2f& position) override;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "HideButton"; };

    protected:
        optor::Widget* widget_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_HIDE_BUTTON_HPP*/