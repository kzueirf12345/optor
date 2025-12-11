#include <cassert>
#include <memory>

#include "dr4/texture.hpp"
#include "dr4/math/vec2.hpp"

#include "widgets/TopBar.hpp"
#include "global/Global.hpp"
#include "widgets/HideButton.hpp"
#include "widgets/HideCheckbox.hpp"
#include "widgets/Textable.hpp"
#include "widgets/Widget.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetHeader.hpp"
#include "widgets/WidgetList.hpp"
#include "widgets/WidgetText.hpp"
#include "common/ErrorHandler.hpp"

static dr4::Vec2f curAbsPosition;

optor::TopBarButton::TopBarButton(const dr4::Vec2f& size, optor::WidgetsState* state, 
                std::unique_ptr<optor::Widget> widget, const std::string& text, WidgetPos pos)
:   HideButton(size, state, std::move(widget)),
    Textable(text, state->window),
    texture_{state->window->CreateTexture()},
    widgetPos_(pos)
{
    ERROR_HANDLE([this](){
        texture_->SetSize(rect_->GetSize());
    });

    ERROR_HANDLE([this, &size](){
        const dr4::Vec2f localBounds = text_->GetBounds();
        text_->SetPos((size.x - localBounds.x) / 2,
                      (size.y - localBounds.y) / 2);
    });

    switch (pos) {
        case optor::TopBarButton::WidgetPos::BOTTOM:
            widget_->SetPosition(AbsCoord() + dr4::Vec2f(0, rect_->GetSize().y));
            break;

        case optor::TopBarButton::WidgetPos::RIGHT:
            widget_->SetPosition(AbsCoord() + dr4::Vec2f(rect_->GetSize().x, 0));
            break;

        case optor::TopBarButton::WidgetPos::BOTTOM_RIGHT:
            widget_->SetPosition(AbsCoord() + dr4::Vec2f(rect_->GetSize().x, rect_->GetSize().y));
            break;
    }
}

void optor::TopBarButton::SetPosition(const dr4::Vec2f& position) {
    optor::Widget::SetPosition(position);
    texture_->SetPos(position);
}

void optor::TopBarButton::Draw(dr4::Texture& srcTexture)
{
    if (isHide_) { return; }
    
    const dr4::Vec2f pos = rect_->GetPos();

    rect_->SetPos({0, 0});
    ERROR_HANDLE([this](){
        optor::HideButton::Draw(*texture_);
    });
    rect_->SetPos(pos);

    ERROR_HANDLE([this](){
        texture_->Draw(*text_);
    });

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_);
    });
}

optor::TopBarButton::WidgetPos optor::TopBarButton::GetWidgetPos() const
{
    return widgetPos_;
}

//==========================================TOPBAR==================================================

static std::unique_ptr<optor::Widget> CreateViewList(optor::WidgetManager* manager, const optor::WidgetChildable* parent);

optor::TopBar::TopBar(optor::WidgetManager* manager) 
    :   optor::WidgetChildable(
            dr4::Vec2f(
                manager->GetDesktop()->GetSize().x,
                manager->GetDesktop()->GetSize().y / 15.f
            ),
            manager->GetState()
        ),
        manager_(manager)
{
    curAbsPosition = {0, 0};

    auto* view = dynamic_cast<optor::TopBarButton*>(AddChild(std::make_unique<optor::TopBarButton>(
        dr4::Vec2f(std::string("view").size() * 20.f, rect_->GetSize().y),
        manager_->GetState(), 
        std::move(CreateViewList(manager_, manager_->GetDesktop())), 
        "view",
        optor::TopBarButton::WidgetPos::BOTTOM
    )));

    UpdatePositions(dynamic_cast<optor::WidgetList*>(view->GetWidget()), view->AbsCoord());
}

static void HandleChild(optor::Widget* child, optor::WidgetList* list, optor::WidgetManager* manager, float sizeX);

static std::unique_ptr<optor::Widget> CreateViewList(optor::WidgetManager* manager, const optor::WidgetChildable* parent)
{
    assert(manager);
    assert(parent);

    auto list = std::make_unique<optor::WidgetList>(
        manager->GetState()
    );

    const size_t childrenCount = parent->GetChildrenCount();

    std::unique_ptr<dr4::Text> textName(manager->GetWindow()->CreateText());
    textName->SetFont(optor::FONT);

    float maxSizeX = 0;
    for (size_t ind = 0; ind < childrenCount; ++ind) {

        auto* child = parent->GetChild(ind);

        std::optional<std::string> name = child->GetName();

        if (!name.has_value()) {
            name = child->GetTypeName();
        }

        textName->SetText(name.value());
        maxSizeX = std::max(textName->GetBounds().x, maxSizeX);
    }

    for (size_t ind = 0; ind < childrenCount; ++ind) {

        auto* child = parent->GetChild(ind);

        ERROR_HANDLE(HandleChild, child, list.get(), manager, maxSizeX);
    }

    return std::move(list);
}

static void HandleChild(optor::Widget* child, optor::WidgetList* list, optor::WidgetManager* manager, float sizeX)
{
    assert(child);
    assert(list);
    assert(manager);

    auto* headerChild = dynamic_cast<optor::WidgetHeader*>(child);

    if (headerChild) {
        child = headerChild->GetWidget();
    }

    std::optional<std::string> name = child->GetName();

    if (!name.has_value()) {
        name = child->GetTypeName();
    }

    dr4::Text* textName = manager->GetWindow()->CreateText();

    textName->SetText(name.value());
    textName->SetFont(optor::FONT);
    // textName->SetFontSize(40);

    dr4::Vec2f size = {sizeX, optor::STRING_BLOCK_HEIGHT};

    delete textName;

    const auto* childableChild = dynamic_cast<const optor::WidgetChildable*>(child);

    std::unique_ptr<optor::Widget> textWidget;

    if (childableChild) {
        auto sublist = std::move(CreateViewList(manager, childableChild));

        textWidget = std::make_unique<optor::TopBarButton>(
            size, 
            manager->GetState(), 
            std::move(sublist), 
            name.value(),
            optor::TopBarButton::WidgetPos::RIGHT
        );

    } else {
        textWidget = std::make_unique<optor::WidgetText>(
            size,
            manager->GetState(),
            name.value()
        );
    }

    auto textableText = dynamic_cast<optor::Textable*>(textWidget.get())->GetText();

    textableText->SetPos(0, textableText->GetPos().y);
    
    ERROR_HANDLE([&textWidget, &size](){
        textWidget->SetPosition({size.y, 0});
    });

    textWidget->SetOutlineThickness(0);

    auto checkBox = std::make_unique<optor::HideCheckbox>(
        dr4::Vec2f{size.y, size.y},
        manager->GetState(),
        (headerChild ? headerChild : child)
    );

    checkBox->SetOutlineThickness(0);

    auto* listElem = dynamic_cast<optor::WidgetChildable*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild,
        list,
        std::make_unique<optor::WidgetChildable>(
            dr4::Vec2f({size.x + size.y, size.y}),
            manager->GetState()
        )
    ));

    ERROR_HANDLE(&optor::WidgetChildable::AddChild, listElem, std::move(textWidget));
    ERROR_HANDLE(&optor::WidgetChildable::AddChild, listElem, std::move(checkBox));

}

void optor::TopBar::UpdatePositions(optor::WidgetList* list, dr4::Vec2f absCoord)
{
    assert(list);

    for (size_t ind = 0; ind < list->GetChildrenCount(); ++ind)
    {
        auto* child = list->GetChild(ind);
        
        auto* hideButton = dynamic_cast<optor::TopBarButton*>(dynamic_cast<optor::WidgetChildable*>(child)->GetChild(0));

        if (hideButton) {

            // std::cerr << list->GetSize().x - hideButton->GetSize().x - 50 << std::endl;

            // hideButton->GetParent()->SetSize({list->GetSize().x - hideButton->GetSize().x , hideButton->GetParent()->GetPosition().y});

            switch (hideButton->GetWidgetPos()) {
                case optor::TopBarButton::WidgetPos::BOTTOM:
                    hideButton->GetWidget()->SetPosition(absCoord + dr4::Vec2f(0, child->GetPosition().y + child->GetSize().y));
                    break;

                case optor::TopBarButton::WidgetPos::RIGHT:
                    hideButton->GetWidget()->SetPosition(absCoord + dr4::Vec2f(list->GetSize().x, child->GetPosition().y));
                    break;

                case optor::TopBarButton::WidgetPos::BOTTOM_RIGHT:
                    hideButton->GetWidget()->SetPosition(absCoord + dr4::Vec2f(list->GetSize().x, child->GetPosition().y + child->GetSize().y));
                    break;
            }

            UpdatePositions(dynamic_cast<optor::WidgetList*>(hideButton->GetWidget()), hideButton->GetWidget()->GetPosition());
        }
    }
}