#include <cstdlib>
#include <memory>

#include "hui/RectangleShape.hpp"
#include "hui/Vector.hpp"
#include "hui/Window.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/SceneWidget.hpp"
#include "widgets/Widget.hpp"
#include "global/Global.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetManager.hpp"
#include "optics/Sphere.hpp"

int main() {

    auto window = ERROR_HANDLE([](){
        return hui::Window({optor::PROGRAM_WIDTH, optor::PROGRAM_HEIGHT}, "Optor (0xCEBAEBA1DEDA)");
    });

    ERROR_HANDLE(&hui::Window::SetFrameLimit, &window, optor::FRAME_LIMIT);

    auto manager = ERROR_HANDLE([](){
        return optor::WidgetManager();
    });

    auto* sceneWidget = dynamic_cast<optor::SceneWidget*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        manager.GetDesktop(), 
        std::make_unique<optor::SceneWidget>(
            hui::RectangleShape({500, 500}),
            manager.GetState()
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, sceneWidget, hui::Vector2d(100, 100));

    auto* sphere1 = ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(
            std::make_unique<optor::Sphere>(
                1,
                hui::Vector3d(0, 0, 3)
            )
        );
    });

    ERROR_HANDLE([sphere1](){
        dynamic_cast<optor::Sphere*>(sphere1)->SetColor(optor::color::AccentCyan);
    });

    auto* sphere2 = ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(
            std::make_unique<optor::Sphere>(
                0.5,
                hui::Vector3d(0, -2, 5)
            )
        );
    });

    ERROR_HANDLE([sphere2](){
        dynamic_cast<optor::Sphere*>(sphere2)->SetColor(optor::color::AccentRed);
    });

    while (ERROR_HANDLE(&hui::Window::isOpen, window)) {

        ERROR_HANDLE(&optor::WidgetManager::HandleEvents, &manager, &window);

        ERROR_HANDLE(&hui::Window::Clear, &window, optor::color::ProgramBackground);

        ERROR_HANDLE(&optor::WidgetManager::Draw, &manager, &window);

        ERROR_HANDLE(&hui::Window::Display, &window);
    }

    return EXIT_SUCCESS;
}