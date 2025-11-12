#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_CHILDABLE_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_CHILDABLE_HPP

#include <deque>
#include <memory>

#include "dr4/event.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "widgets/Widget.hpp"

namespace optor 
{

class WidgetChildable: public Widget {
    public:
        WidgetChildable(const dr4::Vec2f& size, optor::WidgetsState* state);

        WidgetChildable           (const WidgetChildable&) = delete;
        WidgetChildable& operator=(const WidgetChildable&) = delete;
        WidgetChildable           (WidgetChildable&&)      = delete;
        WidgetChildable& operator=(WidgetChildable&&)      = delete;

        virtual ~WidgetChildable() = default;

        virtual void SetPosition(const dr4::Vec2f& position) override;

        virtual void Draw(dr4::Texture& srcTexture) override;

        virtual bool OnMouseMove      (const dr4::Event& event) override;
        virtual bool OnMousePress     (const dr4::Event& event) override;
        virtual bool OnMouseRelease   (const dr4::Event& event) override;
        virtual bool OnKeyboardPress  (const dr4::Event& event) override;
        virtual bool OnKeyboardRelease(const dr4::Event& event) override;
        virtual void OnIdle           ()                        override;

        virtual optor::Widget* AddChild(std::unique_ptr<Widget> child);

        optor::Widget* GetChild(size_t ind) const;

        size_t GetChildrenCount() const;

        [[nodiscard]] virtual bool IsInderectedHovered() const override;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "WidgetChildable"; };

    protected:

        std::unique_ptr<dr4::Texture> texture_;

        std::deque<std::unique_ptr<Widget>> children_;

    private:
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_CHILDABLE_HPP*/