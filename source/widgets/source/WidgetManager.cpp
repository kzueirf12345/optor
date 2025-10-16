#include <memory>
#include <cassert>

#include "widgets/WidgetManager.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"
#include "hui/Event.hpp"
#include "hui/RectangleShape.hpp"
#include "hui/Window.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/Widget.hpp"
#include "widgets/WidgetChildable.hpp"

optor::WidgetManager::WidgetManager()
{
    desktop_ = ERROR_HANDLE(
        std::make_unique<optor::WidgetChildable, hui::RectangleShape, optor::WidgetsState*>, 
        hui::RectangleShape({optor::PROGRAM_WIDTH, optor::PROGRAM_HEIGHT}),
        &state_
    );
    ERROR_HANDLE(&optor::Widget::SetBackgroundColor, desktop_, optor::color::ProgramBackground);
    ERROR_HANDLE(&optor::Widget::SetIsDraggable, desktop_, false);

    state_.hoveredWidget = desktop_.get();
    state_.draggedWidget = nullptr;
    state_.selectedWidget = nullptr;
    state_.prevMouseCoord = {0, 0}; // TODO normal
}

void optor::WidgetManager::Draw(hui::Window* window) {
    assert(window);

    ERROR_HANDLE(&optor::WidgetChildable::Draw, desktop_, window);
}

void optor::WidgetManager::HandleEvents(hui::Window* window) {
    assert(window);

    auto event = ERROR_HANDLE([](){ return hui::Event(); });

    while (ERROR_HANDLE(&hui::Window::PoolEvent, window, &event)) {
        switch (ERROR_HANDLE(&hui::Event::GetType, event)) {
            case hui::Event::Type::Closed:
                ERROR_HANDLE(&hui::Window::Close, window);
                break;

            case hui::Event::Type::MouseMoved:
                ERROR_HANDLE(&optor::WidgetChildable::OnMouseMove, desktop_, event);
                state_.prevMouseCoord = event.GetMouseCoord();
                break;

            case hui::Event::Type::MouseButtonPressed:
                ERROR_HANDLE(&optor::WidgetChildable::OnMousePress, desktop_, event);
                break;

            case hui::Event::Type::MouseButtonReleased:
                ERROR_HANDLE(&optor::WidgetChildable::OnMouseRelease, desktop_, event);
                break;

            default:
                break;
        }
    }

    ERROR_HANDLE(&optor::WidgetChildable::OnIdle, desktop_);
}

optor::WidgetChildable* optor::WidgetManager::SetDesktop(std::unique_ptr<optor::WidgetChildable> desktop) noexcept {
    desktop_ = std::move(desktop);
    state_.hoveredWidget = desktop_.get();
    return desktop_.get();
}
const optor::WidgetChildable* optor::WidgetManager::GetDesktop() const noexcept {
    return desktop_.get();
}

optor::WidgetChildable* optor::WidgetManager::GetDesktop() noexcept {
    return desktop_.get();
}

const optor::WidgetsState* optor::WidgetManager::GetState() const noexcept {
    return &state_;
}

optor::WidgetsState* optor::WidgetManager::GetState() noexcept {
    return &state_;
}