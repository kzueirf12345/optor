#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_HEADER_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_HEADER_HPP

#include <memory>

#include "dr4/event.hpp"
#include "dr4/texture.hpp"

#include "widgets/Textable.hpp"
#include "widgets/Widget.hpp"

namespace optor 
{

class WidgetHeader : public Widget, public Textable {
public:
    enum class CloseMode {
        HIDE,
        REMOVE
    };

    WidgetHeader(std::unique_ptr<optor::Widget> widget, const std::string& title, CloseMode closeMode);

    virtual void SetPosition(const dr4::Vec2f& position) override;

    virtual void Draw       (dr4::Texture& srcTexture) override;
    
    virtual bool OnMouseMove      (const dr4::Event& event) override;
    virtual bool OnMousePress     (const dr4::Event& event) override;
    virtual bool OnMouseRelease   (const dr4::Event& event) override;
    virtual bool OnKeyboardPress  (const dr4::Event& event) override;
    virtual bool OnKeyboardRelease(const dr4::Event& event) override;
    virtual bool OnTextInput      (const dr4::Event& event) override;
    virtual void OnIdle           () override;
    
    void SetTitle(const std::string& title);
    optor::Widget* GetWidget() const;

    [[nodiscard]] virtual std::string GetTypeName() const override {return "WidgetHeader"; };

protected:
    std::unique_ptr<dr4::Texture> texture_;
    std::unique_ptr<optor::Widget> widget_;

    std::unique_ptr<dr4::Rectangle> closeRect_;
    std::unique_ptr<dr4::Text> closeText_;

    CloseMode closeMode_;

private:
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_HEADER_HPP*/