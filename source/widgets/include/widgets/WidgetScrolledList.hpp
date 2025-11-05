#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_SCROLLED_LIST_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_SCROLLED_LIST_HPP

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "widgets/ScrollBar.hpp"
#include "widgets/WidgetChildable.hpp"
#include <memory>

namespace optor 
{

class WidgetScrolledList : public WidgetChildable {
    public:
        WidgetScrolledList(dr4::Window* window, const dr4::Vec2f& size, optor::WidgetsState* state);

        virtual void Scroll(float percentage);

        virtual void Draw(dr4::Texture& srcTexture) override;

        virtual optor::Widget* AddChild(std::unique_ptr<Widget> child) override;

        virtual bool OnMouseMove      (const dr4::Event& event) override;
        virtual bool OnMousePress     (const dr4::Event& event) override;
        virtual bool OnMouseRelease   (const dr4::Event& event) override;
        virtual bool OnKeyboardPress  (const dr4::Event& event) override;
        virtual bool OnKeyboardRelease(const dr4::Event& event) override;
        virtual void OnIdle           ()                        override;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "WidgetScrooledList"; };

    protected:
        std::unique_ptr<optor::ScrollBar> scrollbar_;

        float baseOffset_;

        float GetListSize() const;

};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_SCROLLED_LIST_HPP*/