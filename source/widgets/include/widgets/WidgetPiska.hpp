#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_PISKA_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_PISKA_HPP

#include <cstddef>
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
    virtual void OnIdle           () override;

    [[nodiscard]] virtual std::string GetTypeName() const override {return "WidgetPiska"; };

    virtual pp::ControlsTheme GetControlsTheme() const override;
    virtual pp::State* GetState() override;
    virtual size_t AddShape(pp::Shape *shape) override;
    virtual void DelShape(size_t ind) override;
    virtual dr4::Window *GetWindow() override;

protected:

    std::vector<std::unique_ptr<pp::Tool>> tools_;
    std::unordered_map<size_t, std::unique_ptr<pp::Shape>> shapes_;

    pp::State piskaState_;
    pp::ControlsTheme piskaTheme_;

};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_PISKA_HPP*/