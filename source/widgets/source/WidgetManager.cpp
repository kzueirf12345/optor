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
        std::make_unique<optor::WidgetChildable, hui::RectangleShape>, 
        hui::RectangleShape({optor::PROGRAM_WIDTH, optor::PROGRAM_HEIGHT})
    );

    ERROR_HANDLE(&optor::Widget::SetBackgroundColor, desktop_, optor::color::ProgramBackground);
}

void optor::WidgetManager::Draw(hui::Window* window) {
    assert(window);

    ERROR_HANDLE(&optor::WidgetChildable::Draw, desktop_, window);
}

optor::WidgetChildable* optor::WidgetManager::SetDesktop(std::unique_ptr<optor::WidgetChildable> desktop) noexcept {
    desktop_ = std::move(desktop);
    return desktop_.get();
}

const optor::WidgetChildable* optor::WidgetManager::GetDesktop() const noexcept {
    return desktop_.get();
}

optor::WidgetChildable* optor::WidgetManager::GetDesktop() noexcept {
    return desktop_.get();
}