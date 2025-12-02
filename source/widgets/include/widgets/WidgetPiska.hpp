#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_PISKA_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_PISKA_HPP

#include <memory>
#include <unordered_map>

#include "dr4/texture.hpp"

#include "pp/canvas.hpp"

#include "pp/shape.hpp"
#include "pp/tool.hpp"
#include "widgets/WidgetChildable.hpp"

namespace optor 
{

class WidgetPiska final: public WidgetChildable, public pp::Canvas {

public:

    WidgetPiska(optor::WidgetsState* state);

    virtual void SetPosition(const dr4::Vec2f& position) override;

    virtual void Draw       (dr4::Texture& srcTexture) override;

    virtual bool OnMouseMove      (const dr4::Event& event) override;
    virtual bool OnMousePress     (const dr4::Event& event) override;
    virtual bool OnMouseRelease   (const dr4::Event& event) override;
    virtual bool OnKeyboardPress  (const dr4::Event& event) override;
    virtual bool OnKeyboardRelease(const dr4::Event& event) override;
    virtual bool OnTextInput      (const dr4::Event& event) override;
    virtual void OnIdle           () override;

    [[nodiscard]] virtual std::string GetTypeName() const override {return "WidgetPiska"; };

    virtual pp::ControlsTheme GetControlsTheme() const override;
    virtual void AddShape(pp::Shape *shape) override;
    virtual void DelShape(pp::Shape *shape) override;
    virtual void SetSelectedShape(pp::Shape *shape) override;
    virtual pp::Shape *GetSelectedShape() const override;
    virtual void ShapeChanged(pp::Shape *shape) override;
    virtual dr4::Window *GetWindow() override;

protected:

    std::vector<std::unique_ptr<pp::Tool>> tools_;
    std::unordered_map<pp::Shape*, std::unique_ptr<pp::Shape>> shapes_;

    pp::ControlsTheme piskaTheme_;
    pp::Tool* selectedTool_;
    pp::Shape* selectedShape_;

};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_PISKA_HPP*/