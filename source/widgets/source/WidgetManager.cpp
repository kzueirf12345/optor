#include <memory>
#include <cassert>

#include "widgets/WidgetManager.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"
#include "hui/RectangleShape.hpp"
#include "hui/Window.hpp"
#include "widgets/WidgetChildable.hpp"

optor::WidgetManager::WidgetManager()
{
    desktop_ = ERROR_HANDLE(
        std::make_unique<optor::WidgetChildable, hui::RectangleShape, const optor::Widget** const>, 
        hui::RectangleShape({optor::PROGRAM_WIDTH, optor::PROGRAM_HEIGHT}),
        &hoveredWidget_
    );
    ERROR_HANDLE(&optor::Widget::SetBackgroundColor, desktop_, optor::color::ProgramBackground);

    hoveredWidget_ = desktop_.get();
}

void optor::WidgetManager::Draw(hui::Window* window) {
    assert(window);

    ERROR_HANDLE(&optor::WidgetChildable::Draw, desktop_, window);
}

void optor::WidgetManager::HandleEvents(hui::Window* window) {
    assert(window);

    auto event = ERROR_HANDLE([](){ return hui::Event(); });

    while (ERROR_HANDLE(&hui::Window::PoolEvent, window, &event)) {
        switch (event.GetType()) {
            case hui::Event::Type::Closed:
                ERROR_HANDLE(&hui::Window::Close, window);
                break;

            case hui::Event::Type::MouseMoved:
                ERROR_HANDLE(&optor::WidgetChildable::OnMouseMove, desktop_, event);
                break;

            default:
                break;
        }
    }
}

optor::WidgetChildable* optor::WidgetManager::SetDesktop(std::unique_ptr<optor::WidgetChildable> desktop) noexcept {
    desktop_ = std::move(desktop);
    hoveredWidget_ = desktop_.get();
    return desktop_.get();
}

void optor::WidgetManager::SetHoveredWidget(const optor::Widget* hoveredWidget) noexcept {
    hoveredWidget_ = hoveredWidget;
}

const optor::WidgetChildable* optor::WidgetManager::GetDesktop() const noexcept {
    return desktop_.get();
}

optor::WidgetChildable* optor::WidgetManager::GetDesktop() noexcept {
    return desktop_.get();
}

const optor::Widget** optor::WidgetManager::GetHoveredWidget() noexcept {
    return &hoveredWidget_;
}