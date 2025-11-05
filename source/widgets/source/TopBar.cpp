#include <cassert>
#include <memory>

#include "dr4/texture.hpp"
#include "dr4/math/vec2.hpp"

#include "widgets/TopBar.hpp"
#include "global/Global.hpp"
#include "widgets/HideButton.hpp"
#include "widgets/Textable.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetHeader.hpp"
#include "widgets/WidgetList.hpp"
#include "widgets/WidgetText.hpp"
#include "common/ErrorHandler.hpp"

optor::TopBarButton::TopBarButton(dr4::Window* window, const dr4::Vec2f& size, optor::WidgetsState* state, 
                std::unique_ptr<optor::Widget> widget, const std::string& text, enum WidgetPos pos)
:   HideButton(size, state, std::move(widget)),
    Textable(text),
    texture_{window->CreateTexture()}
{
    ERROR_HANDLE([this](){
        texture_->SetSize(rect_.rect.size);
    });

    ERROR_HANDLE([this, &size](){
        const dr4::Vec2f localBounds = text_.GetBounds().size;
        text_.pos.x = (size.x - localBounds.x) / 2;
        text_.pos.y = (size.y - localBounds.y) / 2;
    });

    switch (pos) {
        case optor::TopBarButton::WidgetPos::BOTTOM:
            widget_->SetPosition(AbsCoord() + dr4::Vec2f(0, size.y));
            break;

        case optor::TopBarButton::WidgetPos::RIGHT:
            widget_->SetPosition(AbsCoord() + dr4::Vec2f(size.x, 0));
            break;

        case optor::TopBarButton::WidgetPos::BOTTOM_RIGHT:
            widget_->SetPosition(AbsCoord() + dr4::Vec2f(size.x, size.y));
            break;
    }
}

void optor::TopBarButton::Draw(dr4::Texture& srcTexture)
{
    if (isHide_) { return; }
    
    const dr4::Vec2f pos = rect_.rect.pos;

    rect_.rect.pos = {0, 0};
    ERROR_HANDLE([this](){
        optor::HideButton::Draw(*texture_);
    });
    rect_.rect.pos = pos;

    ERROR_HANDLE([this](){
        texture_->Draw(text_);
    });

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_, rect_.rect.pos);
    });
}

//==========================================TOPBAR==================================================

static std::unique_ptr<optor::Widget> CreateViewList(optor::WidgetManager* manager, const optor::WidgetChildable* parent);

optor::TopBar::TopBar(optor::WidgetManager* manager) 
    :   optor::WidgetChildable(
            dr4::Vec2f(
                manager->GetDesktop()->GetSize().x,
                manager->GetDesktop()->GetSize().y / 15.f
            ),
            manager->GetState(),
            manager->GetWindow()
        ),
        texture_{manager->GetWindow()->CreateTexture()},
        manager_(manager)
{
    ERROR_HANDLE([this](){
        texture_->SetSize(rect_.rect.size);
    });

    auto view = std::make_unique<optor::TopBarButton>(
        manager->GetWindow(),
        dr4::Vec2f(dr4::Text{.text = "view", .fontSize = 40, .font = optor::FONT}.GetBounds().size.x, rect_.rect.size.y), 
        manager_->GetState(), 
        std::move(CreateViewList(manager_, manager_->GetDesktop())), 
        "view",
        optor::TopBarButton::WidgetPos::BOTTOM
    );

    AddChild(std::move(view));
}

static std::unique_ptr<optor::Widget> CreateViewList(optor::WidgetManager* manager, const optor::WidgetChildable* parent)
{
    assert(manager);

    auto list = std::make_unique<optor::WidgetList>(
        manager->GetWindow(),
        manager->GetState()
    );

    const size_t childrenCount = parent->GetChildrenCount();
    for (size_t ind = 0; ind < childrenCount; ++ind) {
        const auto* child = parent->GetChild(ind);
        const auto* headerChild = dynamic_cast<const optor::WidgetHeader*>(child);

        if (headerChild) {
            child = headerChild->GetWidget();
        }

        std::optional<std::string> name = child->GetName();

        if (!name.has_value()) {
            name = child->GetTypeName();
        }

        dr4::Vec2f size = dr4::Text{.text = name.value(), .fontSize = 40, .font = optor::FONT}.GetBounds().size;

        const auto* childableChild = dynamic_cast<const optor::WidgetChildable*>(child);

        if (childableChild) {
            auto sublist = std::move(CreateViewList(manager, childableChild));

            list->AddChild(std::make_unique<optor::TopBarButton>(
                manager->GetWindow(),
                size, 
                manager->GetState(), 
                std::move(sublist), 
                name.value(),
                optor::TopBarButton::WidgetPos::RIGHT
            ));

        } else {
            list->AddChild(std::make_unique<optor::WidgetText>(
                manager->GetWindow(),
                size,
                manager->GetState(),
                name.value()
            ));
        }

        dynamic_cast<optor::Textable*>(list->GetChild(list->GetChildrenCount() - 1))->GetText()->pos.x = 0;

    }

    return std::move(list);
}