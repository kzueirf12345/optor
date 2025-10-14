#include "widgets/RenderWidget.hpp"
#include "hui/Renderer.hpp"
#include "hui/Sprite.hpp"
#include "hui/TexturedShape.hpp"
#include "widgets/Widget.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"

optor::RenderWidget::RenderWidget(hui::RectangleShape rect, optor::WidgetsState* state) 
    :   optor::Widget{std::move(rect), state},
        renderer_{rect_.GetSize()},
        items_{}
{}

hui::TexturedShape* optor::RenderWidget::AddItem(std::unique_ptr<hui::TexturedShape> item) {
    ERROR_HANDLE([this, &item](){
        items_.push_back(std::move(item));
    });
    return items_.back().get();
}

void optor::RenderWidget::Draw(hui::Window* window) {
    ERROR_HANDLE([this, window](){
        optor::Widget::Draw(window);
    });

    ERROR_HANDLE([this](){
        renderer_.Clear(optor::color::WindowBackground);
    });

    std::cerr << "i'm in draw render widget\n";

    for (auto& item : items_) {
        ERROR_HANDLE([this, &item](){
            renderer_.Draw(*item);
        });
    }

    ERROR_HANDLE([this](){
        renderer_.Display();
    });

    hui::Sprite sprite = ERROR_HANDLE([this](){
        return hui::Sprite(ERROR_HANDLE(&hui::Renderer::GetTexture, renderer_));
    });

    ERROR_HANDLE(&hui::Sprite::SetPosition, &sprite, AbsCoord());

    ERROR_HANDLE(&hui::Window::Draw, window, sprite);
}

void optor::RenderWidget::OnIdle() {
    ERROR_HANDLE([this](){
        optor::Widget::OnIdle();
    });
    
    for (auto& item : items_) {
        ERROR_HANDLE([&item](){
            item->Update();
        });
    }
}