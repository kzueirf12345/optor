#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_TOP_BAR_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_TOP_BAR_HPP

#include <memory>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "dr4/window.hpp"

#include "widgets/HideButton.hpp"
#include "widgets/Textable.hpp"
#include "widgets/Widget.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetManager.hpp"

namespace optor 
{

class TopBarButton: public HideButton, public Textable {
public:
    TopBarButton(dr4::Window* window, const dr4::Vec2f& size, optor::WidgetsState* state, 
                 std::unique_ptr<optor::Widget> widget, const std::string& text);

    void Draw(dr4::Texture& srcTexture) override;

protected:
    std::unique_ptr<dr4::Texture> texture_;
};

class TopBar: public WidgetChildable {
public:
    TopBar(optor::WidgetManager* manager);


private:
    std::unique_ptr<dr4::Texture> texture_;

    optor::WidgetManager* const manager_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_TOP_BAR_HPP*/