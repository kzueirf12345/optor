#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_PISKA_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_PISKA_HPP

#include "dr4/texture.hpp"
#include "hui/geomprim.hpp"
#include "widgets/Widget.hpp"
#include <memory>

namespace optor 
{

class WidgetPiska : public Widget {
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

    protected:

        std::unique_ptr<dr4::Texture> texture_;

        std::vector<std::unique_ptr<hui::GeomPrim>> prims_;

};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_PISKA_HPP*/