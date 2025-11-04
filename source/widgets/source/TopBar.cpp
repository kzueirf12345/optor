#include <cassert>
#include <memory>

#include "dr4/texture.hpp"
#include "dr4/math/vec2.hpp"

#include "widgets/TopBar.hpp"
#include "global/Global.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetList.hpp"
#include "widgets/WidgetText.hpp"

optor::TopBarButton::TopBarButton(dr4::Window* window, const dr4::Vec2f& size, optor::WidgetsState* state, 
                std::unique_ptr<optor::Widget> widget, const std::string& text)
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
    widget_->SetPosition(AbsCoord() + dr4::Vec2f(0, size.y));
}

void optor::TopBarButton::Draw(dr4::Texture& srcTexture)
{
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

static std::unique_ptr<optor::Widget> CreateViewList(optor::WidgetManager* manager);

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
        std::move(CreateViewList(manager_)), 
        "view"
    );

    // view

    AddChild(std::move(view));
}

static std::unique_ptr<optor::Widget> CreateViewList(optor::WidgetManager* manager)
{
    assert(manager);

    auto list = std::make_unique<optor::WidgetList>(
        manager->GetWindow(),
        dr4::Vec2f(300, 500),
        manager->GetState()
    );

    list->AddChild(std::make_unique<optor::WidgetText>(
        manager->GetWindow(),
        dr4::Vec2f(list->GetSize().x, dr4::Text{.text = "Scene", .fontSize = 40, .font = optor::FONT}.GetBounds().size.y),
        manager->GetState(),
        "Scene"
    ));

    list->AddChild(std::make_unique<optor::WidgetText>(
        manager->GetWindow(),
        dr4::Vec2f(list->GetSize().x, dr4::Text{.text = "Camera", .fontSize = 40, .font = optor::FONT}.GetBounds().size.y),
        manager->GetState(),
        "Camera"
    ));

    list->AddChild(std::make_unique<optor::WidgetText>(
        manager->GetWindow(),
        dr4::Vec2f(list->GetSize().x, dr4::Text{.text = "List", .fontSize = 40, .font = optor::FONT}.GetBounds().size.y),
        manager->GetState(),
        "List"
    ));

    return std::move(list);
}