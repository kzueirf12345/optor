#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_RENDER_WIDGET_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_RENDER_WIDGET_HPP

#include "dr4/texture.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/window.hpp"

#include "optics/Scene.hpp"
#include "widgets/Widget.hpp"

namespace optor 
{

class SceneWidget: public optor::Widget {
    public:
        SceneWidget(dr4::Window* window, const dr4::Vec2f& size, optor::WidgetsState* state);
        
        virtual void Draw(dr4::Texture& srcTexture) override final;
        
        virtual bool OnMouseMove      (const dr4::Event& event) override;
        virtual bool OnMousePress     (const dr4::Event& event) override;
        virtual bool OnKeyboardPress  (const dr4::Event& event) override;
        virtual bool OnKeyboardRelease(const dr4::Event& event) override;
        virtual void OnIdle() override final;

        optor::OpticObj* AddObj(std::unique_ptr<optor::OpticObj> obj);

        [[nodiscard]] const optor::Camera& GetCamera() const ;
        [[nodiscard]]       optor::Camera& GetCamera()       ;
        [[nodiscard]] const optor::Scene&  GetScene()  const ;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "SceneWidget"; };
        
    protected:
        optor::Scene scene_;
        std::unique_ptr<dr4::Texture> texture_;

        void RotateCamera(const dr4::Vec2f& mouseOffset);

    private:
};

}


#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_RENDER_WIDGET_HPP*/