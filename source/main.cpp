#include <cstdlib>
#include <memory>

#include "hui/RectangleShape.hpp"
#include "hui/Vector.hpp"
#include "hui/Window.hpp"
#include "common/ErrorHandler.hpp"
#include "optics/Scene.hpp"
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

    auto* sceneWindow = ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        manager.GetDesktop(), 
        std::make_unique<optor::RenderWidget>(
            hui::RectangleShape({500, 500}),
            manager.GetState()
        )
    );

    ERROR_HANDLE(&optor::Widget::SetPosition, sceneWindow, hui::Vector2d(100, 100));

    auto* scene = ERROR_HANDLE([sceneWindow](){
        const hui::Vector2d sceneWindowSize = ERROR_HANDLE(&optor::Widget::GetSize, sceneWindow);
        return dynamic_cast<optor::RenderWidget*>(sceneWindow)->AddItem(
            std::make_unique<optor::Scene>(
                sceneWindowSize
            )
        );
    });

    auto* sphere1 = ERROR_HANDLE([scene](){
        return dynamic_cast<optor::Scene*>(scene)->AddObj(
            std::make_unique<optor::Sphere>(
                1,
                hui::Vector3d(0, 1, -3)
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