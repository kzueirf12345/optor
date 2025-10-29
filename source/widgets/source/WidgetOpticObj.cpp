#include <cassert>

#include "hui/Renderer.hpp"
#include "optics/Material.hpp"
#include "widgets/Widget.hpp"
#include "widgets/WidgetOpticObj.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"

optor::WidgetOpticObj::WidgetOpticObj(const hui::Vector2d& size, optor::WidgetsState* state, 
                                      optor::OpticObj* obj) 
    :   optor::Widget(size, state), obj_{obj}, desc_{}, objNum_(counter_++), renderer_(size),
        textAlign_(hui::Text::Align::CenterLeft), textOffset_({0, 0})
{
    ERROR_HANDLE([this](){SetIsDraggable(false);});
    
    ERROR_HANDLE([this](){
        desc_.SetFont(FONT);
        desc_.SetFillColor(optor::color::TextPrimary);
    });

    const optor::Material material = obj->GetMaterial();

    std::string descStr = {};

    descStr += "obj" + std::to_string(objNum_) + " | ";

    descStr += /*"ambient "       +*/ std::to_string(hui::Color(material.GetAmbientColor()).GetInt())  + ", ";
    descStr += /*"diffuse "       +*/ std::to_string(hui::Color(material.GetDiffuseColor()).GetInt())  + ", ";
    descStr += /*"specular "      +*/ std::to_string(hui::Color(material.GetSpecularColor()).GetInt()) + ", ";
    descStr += /*"shininess "     +*/ std::to_string((uint32_t)material.GetShininess())                + ", ";
    descStr += /*"reflectivity "  +*/ std::to_string((uint32_t)material.GetReflectivity())             + ", ";
    descStr += /*"refractivity "  +*/ std::to_string((uint32_t)material.GetRefractivity())             + ", ";
    descStr += /*"transparency "  +*/ std::to_string((uint32_t)material.GetTransparency());

    ERROR_HANDLE(&hui::Text::SetString, desc_, descStr);
}

void optor::WidgetOpticObj::SetTextAlign(hui::Text::Align align) noexcept {
    textAlign_ = align;
}

void optor::WidgetOpticObj::SetTextOffset(const hui::Vector2d& offset) noexcept {
    textOffset_ = offset;
}

hui::Vector2d optor::WidgetOpticObj::GetTextPosition() const {
    const hui::Vector2d buttonSize = texture_.GetSize();
    const hui::Vector2d textSize   = desc_.GetSize();
    hui::Vector2d pos;

    switch (textAlign_) {
        case hui::Text::Align::TopLeft:
            pos = {0, 0};
            break;
        case hui::Text::Align::TopCenter:
            pos = {(buttonSize.x - textSize.x) / 2.0, 0};
            break;
        case hui::Text::Align::TopRight:
            pos = {buttonSize.x - textSize.x, 0};
            break;
        case hui::Text::Align::CenterLeft:
            pos = {0, (buttonSize.y - textSize.y) / 2.0};
            break;
        case hui::Text::Align::Center:
            pos = {(buttonSize.x - textSize.x) / 2.0, (buttonSize.y - textSize.y) / 2.0};
            break;
        case hui::Text::Align::CenterRight:
            pos = {buttonSize.x - textSize.x, (buttonSize.y - textSize.y) / 2.0};
            break;
        case hui::Text::Align::BottomLeft:
            pos = {0, buttonSize.y - textSize.y};
            break;
        case hui::Text::Align::BottomCenter:
            pos = {(buttonSize.x - textSize.x) / 2.0, buttonSize.y - textSize.y};
            break;
        case hui::Text::Align::BottomRight:
            pos = {buttonSize.x - textSize.x, buttonSize.y - textSize.y};
            break;
    }

    return pos + textOffset_;
}

void optor::WidgetOpticObj::Draw(hui::Renderer* renderer) {
    assert(renderer);

    const hui::Vector2d pos = sprite_.GetPosition();

    sprite_.SetPosition({0, 0});
    ERROR_HANDLE([this](){
        optor::Widget::Draw(&renderer_);
    });
    sprite_.SetPosition(pos);

    if (state_->selectedObj == obj_) {
        desc_.SetFillColor(optor::color::Success);
    } else {
        desc_.SetFillColor(optor::color::TextPrimary);
    }

    desc_.SetPosition(GetTextPosition());

    ERROR_HANDLE([this](){
        renderer_.Draw(desc_);
    });

    ERROR_HANDLE([this](){
        renderer_.Display();
    });

    hui::Sprite sprite = ERROR_HANDLE([this](){
        return hui::Sprite(ERROR_HANDLE(&hui::Renderer::GetTexture, renderer_));
    });

    ERROR_HANDLE(&hui::Sprite::SetPosition, &sprite, pos);

    ERROR_HANDLE(&hui::Renderer::Draw, renderer, sprite);
}

