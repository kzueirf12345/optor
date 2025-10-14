#include <cstdlib>
#include <memory>

#include "hui/RectangleShape.hpp"
#include "hui/Vector.hpp"
#include "hui/Window.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/RenderWidget.hpp"
#include "widgets/Widget.hpp"
#include "global/Global.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetManager.hpp"
#include "optics/Sphere.hpp"

int main() {

    auto window = ERROR_HANDLE([](){
        return hui::Window({optor::PROGRAM_WIDTH, optor::PROGRAM_HEIGHT}, "Optor (0xCEBAEBA1DEDA)");
    });

    auto manager = ERROR_HANDLE([](){
        return optor::WidgetManager();
    });

    auto* scene = ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        manager.GetDesktop(), 
        std::make_unique<optor::RenderWidget>(
            hui::RectangleShape({500, 500}),
            manager.GetState()
        )
    );

    ERROR_HANDLE(&optor::Widget::SetPosition, scene, hui::Vector2d(100, 100));

    auto* sphere = ERROR_HANDLE([scene](){
        return dynamic_cast<optor::RenderWidget*>(scene)->AddItem(
            std::make_unique<optor::Sphere>(
                100,
                hui::Vector3d(20, 20, 0)
            )
        );
    });

    while (ERROR_HANDLE(&hui::Window::isOpen, window)) {

        ERROR_HANDLE(&optor::WidgetManager::HandleEvents, &manager, &window);

        ERROR_HANDLE(&hui::Window::Clear, &window, optor::color::ProgramBackground);

        ERROR_HANDLE(&optor::WidgetManager::Draw, &manager, &window);

        ERROR_HANDLE(&hui::Window::Display, &window);
    }

    return EXIT_SUCCESS;
}