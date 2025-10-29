#include <chrono>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <cassert>

#include "hui/Vector.hpp"
#include "hui/Window.hpp"
#include "common/ErrorHandler.hpp"
// #include "optics/Camera.hpp"
#include "optics/Light.hpp"
#include "widgets/SceneWidget.hpp"
#include "widgets/ScrollBar.hpp"
#include "widgets/Widget.hpp"
#include "global/Global.hpp"
#include "widgets/WidgetButtonMoveOpticObj.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetManager.hpp"
#include "optics/Sphere.hpp" 
// #include "optics/Plane.hpp"
// #include "optics/Triangle.hpp"
// #include "optics/TriangleMesh.hpp"
#include "optics/FinitPlane.hpp"
#include "widgets/WidgetButtonCamera.hpp"
#include "widgets/WidgetOpticObjs.hpp"

/*!SECTION
// TODO самоветящийся объект (когда попадает луч, тогда увеличивать яркость)
// TODO прокручиваемый список объектов. Там выбираем объект и можем его двигать тооже на кнопки

*/

static void CreateScene(optor::WidgetManager* manager);
static void CreateCameraButtons(optor::WidgetManager* manager, optor::SceneWidget* sceneWidget);
static void CreateObjsList(optor::WidgetManager* manager, optor::SceneWidget* sceneWidget);

int main() {
    auto window = ERROR_HANDLE([](){
        return hui::Window({optor::PROGRAM_WIDTH, optor::PROGRAM_HEIGHT}, "Optor (0xCEBAEBA1DEDA)");
    });

    ERROR_HANDLE(&hui::Window::SetFrameLimit, &window, optor::FRAME_LIMIT);

    auto manager = ERROR_HANDLE([](){
        return optor::WidgetManager();
    });

    ERROR_HANDLE(CreateScene, &manager);

    int start = clock();
    size_t cnt = 0;
    
    while (ERROR_HANDLE(&hui::Window::isOpen, window)) {

        ERROR_HANDLE(&optor::WidgetManager::HandleEvents, &manager, &window);

        ERROR_HANDLE(&hui::Window::Clear, &window, optor::color::ProgramBackground);

        ERROR_HANDLE(&optor::WidgetManager::Draw, &manager, &window);

        ERROR_HANDLE(&hui::Window::Display, &window);

        ++cnt;

        if ((clock() - start) / (CLOCKS_PER_SEC) > 1) {
            std::cerr << cnt << std::endl;
            start = clock();
            cnt = 0;
        }
    }

    return EXIT_SUCCESS;
}

void CreateScene(optor::WidgetManager* manager) {
    assert(manager);

    auto* sceneWidget = dynamic_cast<optor::SceneWidget*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        manager->GetDesktop(), 
        std::make_unique<optor::SceneWidget>(
            hui::Vector2d{1200, 700},
            manager->GetState()
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, sceneWidget, hui::Vector2d(100, 100));

    ERROR_HANDLE(&CreateCameraButtons, manager, sceneWidget);

    auto* sphere1 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Sphere>(2, hui::Vector3d(-3, 0, 26), optor::materials::IVORY));
    }));

    auto* sphere2 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Sphere>(2, hui::Vector3d(-1, -1.5, 22), optor::materials::GLASS));
    }));

    auto* sphere3 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Sphere>(3, hui::Vector3d(1.5, -0.5, 28), optor::materials::RED_RUBBER));
    }));

    auto* sphere4 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Sphere>(4, hui::Vector3d(7, 5, 28), optor::materials::MIRROR));
    }));

    auto* light1 = dynamic_cast<optor::Light*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Light>(1, hui::Vector3d(-20, 20, -10), optor::materials::LIGHT, optor::color::White.GetNormalized()));
    }));

    // auto* light2 = dynamic_cast<optor::Light*>(ERROR_HANDLE([sceneWidget](){
    //     return sceneWidget->AddObj(std::make_unique<optor::Light>(0.2, hui::Vector3d(30, 50, 35), optor::materials::LIGHT, optor::color::White.GetNormalized()));
    // }));

    // auto* light3 = dynamic_cast<optor::Light*>(ERROR_HANDLE([sceneWidget](){
    //     return sceneWidget->AddObj(std::make_unique<optor::Light>(0.2, hui::Vector3d(30, 20, 40), optor::materials::LIGHT, optor::color::White.GetNormalized()));
    // }));

    // auto* floorPlane = dynamic_cast<optor::Plane*>(ERROR_HANDLE([sceneWidget](){
    //     return sceneWidget->AddObj(std::make_unique<optor::Plane>(hui::Vector3d(0, -4, 10), hui::Vector3d(0, 1, 0), optor::materials::WOOD));
    // }));

    // auto* triangle = dynamic_cast<optor::Triangle*>(ERROR_HANDLE([sceneWidget](){
    //     return sceneWidget->AddObj(std::make_unique<optor::Triangle>(
    //         hui::Vector3d(5, -1, 22),
    //         hui::Vector3d(8, -1, 22),
    //         hui::Vector3d(14, 5, 26),
    //         optor::materials::STEEL
    //     ));
    // }));

    // auto mesh = std::make_unique<optor::TriangleMesh>(optor::materials::FABRIC);

    // mesh->AddTriangle({{-2, -1, 8}, {-3, -3, 9}, {-1, -3, 9}});
    // mesh->AddTriangle({{-2, -1, 8}, {-1, -3, 9}, {-1, -3, 7}});
    // mesh->AddTriangle({{-2, -1, 8}, {-1, -3, 7}, {-3, -3, 7}});
    // mesh->AddTriangle({{-2, -1, 8}, {-3, -3, 7}, {-3, -3, 9}});
    // mesh->AddTriangle({{-3, -3, 9}, {-1, -3, 9}, {-1, -3, 7}});
    // mesh->AddTriangle({{-3, -3, 9}, {-1, -3, 7}, {-3, -3, 7}});

    // sceneWidget->AddObj(std::move(mesh));

    auto* plane = dynamic_cast<optor::FinitPlane*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::FinitPlane>(
            hui::Vector3d(0, 20, 25),   
            hui::Vector3d(0, -2, -1),     
            hui::Vector2d(10, 20),
            optor::materials::MIRROR
        ));
    }));

    ERROR_HANDLE(&CreateObjsList, manager, sceneWidget);

    // auto* tempMoveButton = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(ERROR_HANDLE(
    //     &optor::WidgetChildable::AddChild, 
    //     manager->GetDesktop(), 
    //     std::make_unique<optor::WidgetButtonMoveOpticObj>(
    //         hui::Vector2d{200, 100},
    //         manager->GetState(),
    //         "btn",
    //         plane,
    //         optor::MoveDirection::FORWARD
    //     )
    // ));

    // ERROR_HANDLE(&optor::Widget::SetPosition, tempMoveButton, hui::Vector2d(0, 100));
}

static void CreateCameraButtons(optor::WidgetManager* manager, optor::SceneWidget* sceneWidget) {
    assert(manager);
    assert(sceneWidget);

    auto* cameraButtons = dynamic_cast<optor::WidgetChildable*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        manager->GetDesktop(), 
        std::make_unique<optor::WidgetChildable>(
            hui::Vector2d{750, 400},
            manager->GetState()
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, cameraButtons, hui::Vector2d(1350, 100));

    auto* leftButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            hui::Vector2d{200, 100},
            manager->GetState(),
            "left",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::LEFT
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, leftButton, hui::Vector2d(50, 150));

    auto* rightButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            hui::Vector2d{200, 100},
            manager->GetState(),
            "right",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::RIGHT
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, rightButton, hui::Vector2d(250, 150));

    auto* upButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            hui::Vector2d{200, 100},
            manager->GetState(),
            "up",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::UP
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, upButton, hui::Vector2d(150, 45));

    auto* downButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            hui::Vector2d{200, 100},
            manager->GetState(),
            "down",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::DOWN
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, downButton, hui::Vector2d(150, 255));

    auto* forwardButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            hui::Vector2d{200, 100},
            manager->GetState(),
            "forward",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::FORWARD
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, forwardButton, hui::Vector2d(500, 100));

        auto* backwordButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            hui::Vector2d{200, 100},
            manager->GetState(),
            "backword",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::BACKWARD
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, backwordButton, hui::Vector2d(500, 200));
}

static void CreateObjsList(optor::WidgetManager* manager, optor::SceneWidget* sceneWidget) {
    auto* opticObjs = dynamic_cast<optor::WidgetOpticObjs*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        manager->GetDesktop(), 
        std::make_unique<optor::WidgetOpticObjs>(
            hui::Vector2d{800, 400},
            manager->GetState(), 
            sceneWidget->GetScene()
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, opticObjs, hui::Vector2d(1350, 600));

    auto* opticObjsScroll = dynamic_cast<optor::ScrollBar*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        manager->GetDesktop(), 
        std::make_unique<optor::ScrollBar>(
            hui::Vector2d{800, 50},
            manager->GetState(), 
            [opticObjs](double percentage){return opticObjs->Scroll(percentage);}
        )
    ));

    opticObjsScroll->SetPosition({1350, 550});
}