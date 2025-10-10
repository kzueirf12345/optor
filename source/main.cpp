#include <cstdlib>
#include <memory>

#include "hui/Event.hpp"
#include "hui/RectangleShape.hpp"
#include "hui/Vector.hpp"
#include "hui/Window.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/Widget.hpp"
#include "global/Global.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetManager.hpp"

int main() {

    auto window = ERROR_HANDLE([](){
        return hui::Window(optor::PROGRAM_WIDTH, optor::PROGRAM_HEIGHT, "Optor (0xCEBAEBA1DEDA)");
    });

    auto manager = ERROR_HANDLE([](){
        return optor::WidgetManager();
    });

    auto* tempWidget = ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        manager.GetDesktop(), 
        std::make_unique<optor::Widget>(
            hui::RectangleShape({500, 500})
        )
    );

    ERROR_HANDLE(&optor::Widget::SetPosition, tempWidget, hui::Vector2d(100, 100));

    while (ERROR_HANDLE(&hui::Window::isOpen, window)) {

        auto event = ERROR_HANDLE([](){ return hui::Event(); });
        while (ERROR_HANDLE(&hui::Window::PoolEvent, &window, &event)) {
            if (event.GetType() == hui::Event::Type::Closed) {
                ERROR_HANDLE(&hui::Window::Close, &window);
            }
        }

        ERROR_HANDLE(&hui::Window::Clear, &window);

        ERROR_HANDLE(&optor::WidgetManager::Draw, &manager, &window);

        ERROR_HANDLE(&hui::Window::Display, &window);
    }

    return EXIT_SUCCESS;
}