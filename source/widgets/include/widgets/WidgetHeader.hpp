#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_HEADER_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_HEADER_HPP

#include <memory>

#include "dr4/texture.hpp"
#include "dr4/window.hpp"

#include "widgets/Textable.hpp"
#include "widgets/Widget.hpp"

namespace optor 
{

class WidgetHeader : public Widget, public Textable {
public:
    WidgetHeader(dr4::Window* window, std::unique_ptr<optor::Widget> widget, const std::string& title);

    virtual void Draw       (dr4::Texture& srcTexture) override;
    
    virtual bool OnMouseMove      (const dr4::Event& event) override;
    virtual bool OnMousePress     (const dr4::Event& event) override;
    virtual bool OnMouseRelease   (const dr4::Event& event) override;
    virtual bool OnKeyboardPress  (const dr4::Event& event) override;
    virtual bool OnKeyboardRelease(const dr4::Event& event) override;
    virtual void OnIdle           () override;
    
    void SetTitle(const std::string& title);
    optor::Widget* GetWidget() const;

    [[nodiscard]] virtual std::string GetTypeName() const override {return "WidgetHeader"; };

protected:
    std::unique_ptr<dr4::Texture> texture_;
    std::unique_ptr<optor::Widget> widget_;

    dr4::Rectangle closeRect_;

private:
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_HEADER_HPP*/