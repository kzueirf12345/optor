#include "widgets/OpticObjShort.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/DeleteObjButton.hpp"
#include "widgets/Textable.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetText.hpp"
#include <memory>

optor::OpticObjShort::OpticObjShort(optor::WidgetManager* manager, const dr4::Vec2f& size, optor::OpticObj* obj, size_t ind)
    :   optor::WidgetChildable(size, manager->GetState()),
        optor::Textable(obj->GetTypeName(), manager->GetWindow()),
        obj_(obj),
        desktop_(manager->GetDesktop()),
        desc_{dr4::Vec2f(400, 600), manager->GetState(), obj},
        descButton_(dr4::KEYCODE_E)
{
    // ERROR_HANDLE([this, &size](){
    //     const dr4::Vec2f localBounds = text_->GetBounds();
    //     text_->SetPos((size.x - localBounds.x) / 2,
    //                   (size.y - localBounds.y) / 2);
    // });

    auto* deleteButton = dynamic_cast<optor::DeleteObjButton*>(AddChild(std::make_unique<optor::DeleteObjButton>(
        dr4::Vec2f{size.y, size.y},
        state_,
        "󰆴",
        this
    )));

    deleteButton->SetPosition({size.x - size.y, 0});
    deleteButton->SetOutlineThickness(0);

    // auto* numWidget = dynamic_cast<optor::WidgetText*>(AddChild(std::make_unique<optor::WidgetText>(
    //     dr4::Vec2f{size.y, size.y},
    //     manager->GetState(),
    //     std::to_string(ind)
    // )));
    // numWidget->SetOutlineThickness(0);
}

void optor::OpticObjShort::OnIdle() {
    if (isHide_) return;
    
    if (state_->selectedWidget == this) {
        state_->selectedObj = obj_;
    }

    if (state_->selectedObj == obj_) {
        text_->SetColor(optor::color::Green);
    } else {
        text_->SetColor(optor::color::TextPrimary);
    }

    optor::WidgetChildable::OnIdle();
}

optor::OpticObj* optor::OpticObjShort::GetObj()
{
    return obj_;
}

bool optor::OpticObjShort::OnKeyboardPress (const dr4::Event& event) {
    if (isHide_) return false;

    if (state_->selectedObj == obj_ && event.key.sym == descButton_) {
        auto* descWidget = ERROR_HANDLE(desc_, desktop_);
        descWidget->SetPosition(dr4::Vec2f(AbsCoord() + dr4::Vec2f{GetSize().x, 0}));
        return true;
    }

    return optor::WidgetChildable::OnKeyboardPress(event);
}

void optor::OpticObjShort::Draw(dr4::Texture& srcTexture)
{
    if (isHide_) { return; }

    const dr4::Vec2f pos = rect_->GetPos();

    rect_->SetPos({0, 0});
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_->SetPos(pos);

    ERROR_HANDLE([this](){
        texture_->Draw(*text_);
    });

    for (const auto& child : children_) {
        ERROR_HANDLE([this, &child](){
            child->Draw(*texture_);
        });
    }

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_);
    });
}
