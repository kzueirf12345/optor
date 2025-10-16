#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_CHILDABLE_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_CHILDABLE_HPP

#include <deque>
#include <memory>

#include "widgets/Widget.hpp"
#include "hui/RectangleShape.hpp"

namespace optor 
{

class WidgetChildable: public Widget {
    public:
        explicit WidgetChildable(hui::RectangleShape rect, optor::WidgetsState* state);

        WidgetChildable           (const WidgetChildable&) = delete;
        WidgetChildable& operator=(const WidgetChildable&) = delete;
        WidgetChildable           (WidgetChildable&&)      = delete;
        WidgetChildable& operator=(WidgetChildable&&)      = delete;

        virtual ~WidgetChildable() = default;

        virtual void Draw(hui::Window* window) override;

        virtual bool OnMouseMove      (const hui::Event& event) override;
        virtual bool OnMousePress     (const hui::Event& event) override;
        virtual bool OnMouseRelease   (const hui::Event& event) override;
        virtual bool OnKeyboardPress  (const hui::Event& event) override;
        virtual bool OnKeyboardRelease(const hui::Event& event) override;
        virtual void OnIdle           ()                        override;

        optor::Widget* AddChild(std::unique_ptr<Widget> child);

        [[nodiscard]]       Widget& operator[](size_t ind)       noexcept;
        [[nodiscard]] const Widget& operator[](size_t ind) const noexcept;


    protected:
        std::deque<std::unique_ptr<Widget>> children_;

    private:
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_CHILDABLE_HPP*/