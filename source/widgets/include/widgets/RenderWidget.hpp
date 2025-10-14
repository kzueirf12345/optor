#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_RENDER_WIDGET_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_RENDER_WIDGET_HPP

#include "hui/Renderer.hpp"
#include "hui/TexturedShape.hpp"
#include "hui/Window.hpp"
#include "widgets/Widget.hpp"
#include <memory>

namespace optor 
{

class RenderWidget: public optor::Widget {
    public:
        RenderWidget(hui::RectangleShape rect, optor::WidgetsState* state);
        
        virtual void Draw(hui::Window* window) override final;
        
        virtual void OnIdle() override final;
        
        hui::TexturedShape* AddItem(std::unique_ptr<hui::TexturedShape> item);
        
    protected:
        std::vector<std::unique_ptr<hui::TexturedShape>> items_;

        hui::Renderer renderer_;

    private:
};

}


#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_RENDER_WIDGET_HPP*/