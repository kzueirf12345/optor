#include <cstdlib>
#include <memory>

#include "hui/Color.hpp"
#include "hui/Event.hpp"
#include "hui/RectangleShape.hpp"
#include "hui/Vector.hpp"
#include "hui/Window.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/Widget.hpp"
#include "global/Global.hpp"
#include "widgets/WidgetChildable.hpp"

int main() {

    hui::Window window(optor::PROGRAM_WIDTH, optor::PROGRAM_HEIGHT, "Optor (0xCEBAEBA1DEDA)");

    optor::WidgetChildable globWidget(hui::RectangleShape(window.GetSize()));
    ERROR_HANDLE(&optor::Widget::SetBackgroundColor, &globWidget, optor::color::ProgramBackground);

    auto* tempWidget = ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        &globWidget, 
        std::make_unique<optor::Widget>(
            hui::RectangleShape({500, 500})
        )
    );

    ERROR_HANDLE(&optor::Widget::SetPosition, tempWidget, hui::Vector2d(100, 100));

    while (ERROR_HANDLE(&hui::Window::isOpen, window)) {
        hui::Event event;
        while (ERROR_HANDLE(&hui::Window::PoolEvent, &window, &event)) {
            if (event.GetType() == hui::Event::Type::Closed) {
                ERROR_HANDLE(&hui::Window::Close, &window);
            }
        }

        ERROR_HANDLE(&hui::Window::Clear, &window);

        ERROR_HANDLE(&optor::Widget::Draw, globWidget, &window);

        ERROR_HANDLE(&hui::Window::Display, &window);
    }

    return EXIT_SUCCESS;
}