#include <cstdlib>

#include <SFML/Window/Event.hpp>

#include "hui/Event.hpp"
#include "hui/Window.hpp"
#include "common/ErrorHandler.hpp"

int main() {

    hui::Window window(1400, 800, "Sosat america!");

    while (ERROR_HANDLE(&hui::Window::isOpen, window)) {
        hui::Event event;
        while (ERROR_HANDLE(&hui::Window::PoolEvent, window, event)) {
            if (event.GetType() == hui::Event::Type::Closed) {
                ERROR_HANDLE(&hui::Window::Close, window);
            }
        }

        ERROR_HANDLE(&hui::Window::Clear, window);

        ERROR_HANDLE(&hui::Window::Display, window);
    }

    return EXIT_SUCCESS;
}