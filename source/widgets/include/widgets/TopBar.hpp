#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_TOP_BAR_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_TOP_BAR_HPP

#include <memory>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "dr4/window.hpp"

#include "widgets/HideButton.hpp"
#include "widgets/Textable.hpp"
#include "widgets/Widget.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetManager.hpp"
#include "widgets/WidgetList.hpp"

namespace optor 
{

class TopBarButton: public HideButton, public Textable {
public:
    enum class WidgetPos {
        BOTTOM, 
        RIGHT,
        BOTTOM_RIGHT
    };

    TopBarButton(dr4::Window* window, const dr4::Vec2f& size, optor::WidgetsState* state, 
                 std::unique_ptr<optor::Widget> widget, const std::string& text, WidgetPos pos);

    void Draw(dr4::Texture& srcTexture) override;

    WidgetPos GetWidgetPos() const;

    [[nodiscard]] virtual std::string GetTypeName() const override {return "TopBarButton"; };

protected:
    std::unique_ptr<dr4::Texture> texture_;

    WidgetPos widgetPos_;
};

class TopBar: public WidgetChildable {
public:
    TopBar(optor::WidgetManager* manager);

    [[nodiscard]] virtual std::string GetTypeName() const override {return "TopBar"; };

private:
    std::unique_ptr<dr4::Texture> texture_;

    optor::WidgetManager* const manager_;

    void UpdatePositions(optor::WidgetList* list, dr4::Vec2f absCoord);
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_TOP_BAR_HPP*/