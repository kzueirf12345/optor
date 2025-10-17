#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_RENDER_WIDGET_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_RENDER_WIDGET_HPP

#include "hui/Renderer.hpp"
#include "hui/Vector.hpp"
#include "hui/Window.hpp"
#include "optics/Scene.hpp"
#include "widgets/Widget.hpp"

namespace optor 
{

class SceneWidget: public optor::Widget {
    public:
        SceneWidget(hui::RectangleShape rect, optor::WidgetsState* state);
        
        virtual void Draw(hui::Window* window) override final;
        
        virtual bool OnMouseMove   (const hui::Event& event) override;
        virtual bool OnKeyboardPress  (const hui::Event& event) override;
        virtual bool OnKeyboardRelease(const hui::Event& event) override;
        virtual void OnIdle() override final;

        optor::OpticObj* AddObj(std::unique_ptr<optor::OpticObj> obj);
        
    protected:
        optor::Scene scene_;

        hui::Renderer renderer_;

        void RotateCamera(const hui::Vector2d& mouseOffset);

    private:
};

}


#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_RENDER_WIDGET_HPP*/