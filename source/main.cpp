#include <cstdlib>
#include <memory>

#include "hui/Color.hpp"
#include "hui/RectangleShape.hpp"
#include "hui/Sprite.hpp"
#include "hui/Texture.hpp"
#include "hui/Vector.hpp"
#include "hui/Window.hpp"
#include "common/ErrorHandler.hpp"
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

    auto* tempWidget = ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        manager.GetDesktop(), 
        std::make_unique<optor::Widget>(
            hui::RectangleShape({500, 500}),
            manager.GetState()
        )
    );

    optor::Sphere sphere = ERROR_HANDLE([](){
        return optor::Sphere(
            100
        );
    });

    ERROR_HANDLE(&optor::Widget::SetPosition, tempWidget, hui::Vector2d(100, 100));

    while (ERROR_HANDLE(&hui::Window::isOpen, window)) {

        ERROR_HANDLE(&optor::WidgetManager::HandleEvents, &manager, &window);

        ERROR_HANDLE(&hui::Window::Clear, &window, optor::color::ProgramBackground);

        ERROR_HANDLE(&optor::WidgetManager::Draw, &manager, &window);
        ERROR_HANDLE(&hui::Window::Draw, &window, sphere);

        ERROR_HANDLE(&hui::Window::Display, &window);
        
        ERROR_HANDLE(&optor::Sphere::Update, &sphere);
    }

    return EXIT_SUCCESS;
}