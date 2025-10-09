#include <cstdlib>

#include "hui/Color.hpp"
#include "hui/Event.hpp"
#include "hui/RectangleShape.hpp"
#include "hui/Window.hpp"
#include "common/ErrorHandler.hpp"

int main() {

    hui::Window window(1400, 800, "Sosat america!");

    hui::RectangleShape rect({200, 500});

    ERROR_HANDLE(&hui::RectangleShape::SetFillColor, rect, hui::Color(0, 255, 0));

    while (ERROR_HANDLE(&hui::Window::isOpen, window)) {
        hui::Event event;
        while (ERROR_HANDLE(&hui::Window::PoolEvent, window, event)) {
            if (event.GetType() == hui::Event::Type::Closed) {
                ERROR_HANDLE(&hui::Window::Close, window);
            }
        }

        ERROR_HANDLE(&hui::Window::Clear, window);

        ERROR_HANDLE(&hui::Window::Draw, window, rect);

        ERROR_HANDLE(&hui::Window::Display, window);
    }

    return EXIT_SUCCESS;
}