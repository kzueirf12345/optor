// #include <chrono>
// #include <cstdlib>
// #include <ctime>
// #include <memory>
// #include <cassert>

// #include "hui/Vector.hpp"
// #include "hui/Window.hpp"
// #include "common/ErrorHandler.hpp"
// // #include "optics/Camera.hpp"
// #include "optics/Light.hpp"
// #include "widgets/SceneWidget.hpp"
// #include "widgets/ScrollBar.hpp"
// #include "widgets/Widget.hpp"
// #include "global/Global.hpp"
// #include "widgets/WidgetButtonMoveOpticObj.hpp"
// #include "widgets/WidgetChildable.hpp"
// #include "widgets/WidgetManager.hpp"
// #include "optics/Sphere.hpp" 
// #include "optics/Plane.hpp"
// #include "optics/Triangle.hpp"
// #include "optics/TriangleMesh.hpp"
// #include "optics/FinitPlane.hpp"
// #include "widgets/WidgetButtonCamera.hpp"
// #include "widgets/WidgetOpticObjs.hpp"

// */

// static void CreateScene(optor::WidgetManager* manager);
// static void CreateCameraButtons(optor::WidgetManager* manager, optor::SceneWidget* sceneWidget);
// static void CreateObjsList(optor::WidgetManager* manager, optor::SceneWidget* sceneWidget);

// int main() {
//     auto window = ERROR_HANDLE([](){
//         return optor::Window({optor::PROGRAM_WIDTH, optor::PROGRAM_HEIGHT}, "Optor (0xCEBAEBA1DEDA)");
//     });

//     ERROR_HANDLE(&optor::Window::SetFrameLimit, &window, optor::FRAME_LIMIT);

//     auto manager = ERROR_HANDLE([](){
//         return optor::WidgetManager();
//     });

//     ERROR_HANDLE(CreateScene, &manager);

//     int start = clock();
//     size_t cnt = 0;
    
//     while (ERROR_HANDLE(&optor::Window::isOpen, window)) {

//         ERROR_HANDLE(&optor::WidgetManager::HandleEvents, &manager, &window);

//         ERROR_HANDLE(&optor::Window::Clear, &window, optor::color::ProgramBackground);

//         ERROR_HANDLE(&optor::WidgetManager::Draw, &manager, &window);

//         ERROR_HANDLE(&optor::Window::Display, &window);

//         ++cnt;

//         if ((clock() - start) / (CLOCKS_PER_SEC) > 1) {
//             std::cerr << cnt << std::endl;
//             start = clock();
//             cnt = 0;
//         }
//     }

//     return EXIT_SUCCESS;
// }

// void CreateScene(optor::WidgetManager* manager) {
//     assert(manager);

//     auto* sceneWidget = dynamic_cast<optor::SceneWidget*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         manager->GetDesktop(), 
//         std::make_unique<optor::SceneWidget>(
//             optor::Vector2d{1200, 700},
//             manager->GetState()
//         )
//     ));

//     ERROR_HANDLE(&optor::Widget::SetPosition, sceneWidget, optor::Vector2d(100, 100));

//     ERROR_HANDLE(&CreateCameraButtons, manager, sceneWidget);

//     auto* sphere1 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
//         return sceneWidget->AddObj(std::make_unique<optor::Sphere>(2, optor::Vector3d(-3, 0, 26), optor::materials::IVORY));
//     }));

//     auto* sphere2 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
//         return sceneWidget->AddObj(std::make_unique<optor::Sphere>(2, optor::Vector3d(-1, -1.5, 22), optor::materials::GLASS));
//     }));

//     auto* sphere3 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
//         return sceneWidget->AddObj(std::make_unique<optor::Sphere>(3, optor::Vector3d(1.5, -0.5, 28), optor::materials::RED_RUBBER));
//     }));

//     auto* sphere4 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
//         return sceneWidget->AddObj(std::make_unique<optor::Sphere>(4, optor::Vector3d(7, 5, 28), optor::materials::MIRROR));
//     }));

//     auto* light1 = dynamic_cast<optor::Light*>(ERROR_HANDLE([sceneWidget](){
//         return sceneWidget->AddObj(std::make_unique<optor::Light>(1, optor::Vector3d(-20, 20, -10), optor::materials::LIGHT, optor::color::White.GetNormalized()));
//     }));

//     // for (double i = 0; i < 40; ++i) {
//     //     ERROR_HANDLE([sceneWidget, i](){
//     //         return sceneWidget->AddObj(std::make_unique<optor::Sphere>(1, optor::Vector3d(7 + i, 5 - i, 28 - i), optor::materials::WOOD));
//     //     });
//     // }

//     auto* light2 = dynamic_cast<optor::Light*>(ERROR_HANDLE([sceneWidget](){
//         return sceneWidget->AddObj(std::make_unique<optor::Light>(0.2, optor::Vector3d(30, 50, 35), optor::materials::LIGHT, optor::color::White.GetNormalized()));
//     }));

//     auto* light3 = dynamic_cast<optor::Light*>(ERROR_HANDLE([sceneWidget](){
//         return sceneWidget->AddObj(std::make_unique<optor::Light>(0.2, optor::Vector3d(30, 20, 40), optor::materials::LIGHT, optor::color::White.GetNormalized()));
//     }));

//     auto* floorPlane = dynamic_cast<optor::Plane*>(ERROR_HANDLE([sceneWidget](){
//         return sceneWidget->AddObj(std::make_unique<optor::Plane>(optor::Vector3d(0, -4, 10), optor::Vector3d(0, 1, 0), optor::materials::WOOD));
//     }));

//     auto* triangle = dynamic_cast<optor::Triangle*>(ERROR_HANDLE([sceneWidget](){
//         return sceneWidget->AddObj(std::make_unique<optor::Triangle>(
//             optor::Vector3d(5, -1, 22),
//             optor::Vector3d(8, -1, 22),
//             optor::Vector3d(14, 5, 26),
//             optor::materials::STEEL
//         ));
//     }));

//     auto mesh = std::make_unique<optor::TriangleMesh>(optor::materials::FABRIC);

//     mesh->AddTriangle({{-2, -1, 8}, {-3, -3, 9}, {-1, -3, 9}});
//     mesh->AddTriangle({{-2, -1, 8}, {-1, -3, 9}, {-1, -3, 7}});
//     mesh->AddTriangle({{-2, -1, 8}, {-1, -3, 7}, {-3, -3, 7}});
//     mesh->AddTriangle({{-2, -1, 8}, {-3, -3, 7}, {-3, -3, 9}});
//     mesh->AddTriangle({{-3, -3, 9}, {-1, -3, 9}, {-1, -3, 7}});
//     mesh->AddTriangle({{-3, -3, 9}, {-1, -3, 7}, {-3, -3, 7}});

//     sceneWidget->AddObj(std::move(mesh));

//     auto* plane = dynamic_cast<optor::FinitPlane*>(ERROR_HANDLE([sceneWidget](){
//         return sceneWidget->AddObj(std::make_unique<optor::FinitPlane>(
//             optor::Vector3d(0, 20, 25),   
//             optor::Vector3d(0, -2, -1),     
//             optor::Vector2d(10, 20),
//             optor::materials::MIRROR
//         ));
//     }));

//     ERROR_HANDLE(&CreateObjsList, manager, sceneWidget);

//     // auto* tempMoveButton = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(ERROR_HANDLE(
//     //     &optor::WidgetChildable::AddChild, 
//     //     manager->GetDesktop(), 
//     //     std::make_unique<optor::WidgetButtonMoveOpticObj>(
//     //         optor::Vector2d{200, 100},
//     //         manager->GetState(),
//     //         "btn",
//     //         plane,
//     //         optor::MoveDirection::FORWARD
//     //     )
//     // ));

//     // ERROR_HANDLE(&optor::Widget::SetPosition, tempMoveButton, optor::Vector2d(0, 100));
// }

// static void CreateCameraButtons(optor::WidgetManager* manager, optor::SceneWidget* sceneWidget) {
//     assert(manager);
//     assert(sceneWidget);

//     auto* cameraButtons = dynamic_cast<optor::WidgetChildable*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         manager->GetDesktop(), 
//         std::make_unique<optor::WidgetChildable>(
//             optor::Vector2d{750, 400},
//             manager->GetState()
//         )
//     ));

//     ERROR_HANDLE(&optor::Widget::SetPosition, cameraButtons, optor::Vector2d(1350, 100));

//     auto* leftButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         cameraButtons, 
//         std::make_unique<optor::WidgetButtonCamera>(
//             optor::Vector2d{200, 100},
//             manager->GetState(),
//             "left",
//             &sceneWidget->GetCamera(),
//             optor::MoveDirection::LEFT
//         )
//     ));

//     ERROR_HANDLE(&optor::Widget::SetPosition, leftButton, optor::Vector2d(50, 150));

//     auto* rightButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         cameraButtons, 
//         std::make_unique<optor::WidgetButtonCamera>(
//             optor::Vector2d{200, 100},
//             manager->GetState(),
//             "right",
//             &sceneWidget->GetCamera(),
//             optor::MoveDirection::RIGHT
//         )
//     ));

//     ERROR_HANDLE(&optor::Widget::SetPosition, rightButton, optor::Vector2d(250, 150));

//     auto* upButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         cameraButtons, 
//         std::make_unique<optor::WidgetButtonCamera>(
//             optor::Vector2d{200, 100},
//             manager->GetState(),
//             "up",
//             &sceneWidget->GetCamera(),
//             optor::MoveDirection::UP
//         )
//     ));

//     ERROR_HANDLE(&optor::Widget::SetPosition, upButton, optor::Vector2d(150, 45));

//     auto* downButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         cameraButtons, 
//         std::make_unique<optor::WidgetButtonCamera>(
//             optor::Vector2d{200, 100},
//             manager->GetState(),
//             "down",
//             &sceneWidget->GetCamera(),
//             optor::MoveDirection::DOWN
//         )
//     ));

//     ERROR_HANDLE(&optor::Widget::SetPosition, downButton, optor::Vector2d(150, 255));

//     auto* forwardButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         cameraButtons, 
//         std::make_unique<optor::WidgetButtonCamera>(
//             optor::Vector2d{200, 100},
//             manager->GetState(),
//             "forward",
//             &sceneWidget->GetCamera(),
//             optor::MoveDirection::FORWARD
//         )
//     ));

//     ERROR_HANDLE(&optor::Widget::SetPosition, forwardButton, optor::Vector2d(500, 100));

//         auto* backwordButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         cameraButtons, 
//         std::make_unique<optor::WidgetButtonCamera>(
//             optor::Vector2d{200, 100},
//             manager->GetState(),
//             "backword",
//             &sceneWidget->GetCamera(),
//             optor::MoveDirection::BACKWARD
//         )
//     ));

//     ERROR_HANDLE(&optor::Widget::SetPosition, backwordButton, optor::Vector2d(500, 200));
// }

// static void CreateObjsList(optor::WidgetManager* manager, optor::SceneWidget* sceneWidget) {
//     auto* opticObjs = dynamic_cast<optor::WidgetOpticObjs*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         manager->GetDesktop(), 
//         std::make_unique<optor::WidgetOpticObjs>(
//             optor::Vector2d{800, 400},
//             manager->GetState(), 
//             sceneWidget->GetScene()
//         )
//     ));

//     ERROR_HANDLE(&optor::Widget::SetPosition, opticObjs, optor::Vector2d(1350, 600));

//     auto* opticObjsScroll = dynamic_cast<optor::ScrollBar*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         manager->GetDesktop(), 
//         std::make_unique<optor::ScrollBar>(
//             optor::Vector2d{800, 50},
//             manager->GetState(), 
//             [opticObjs](double percentage){return opticObjs->Scroll(percentage);}
//         )
//     ));

//     opticObjsScroll->SetPosition({1350, 550});
// }

#include <cstdlib>
#include <dlfcn.h>
#include <linux/limits.h>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <string>

#include "dr4/math/color.hpp"
#include "dr4/math/vec2.hpp"
#include "global/Global.hpp"
#include "misc/dr4_ifc.hpp"
#include "dr4/window.hpp"

#include "common/ErrorHandler.hpp"
#include "global/Global.hpp"
#include "optics/Vector.hpp"
#include "widgets/HideButton.hpp"
#include "widgets/TopBar.hpp"
#include "widgets/Widget.hpp"
#include "widgets/WidgetHeader.hpp"
#include "widgets/WidgetScrolledList.hpp"
#include "widgets/WidgetManager.hpp"
#include "widgets/WidgetText.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/SceneWidget.hpp"
#include "widgets/WidgetButtonCamera.hpp"
#include "widgets/WidgetList.hpp"
#include "optics/FinitPlane.hpp"
#include "optics/Plane.hpp"
#include "optics/Light.hpp"
#include "optics/Triangle.hpp"
#include "optics/Sphere.hpp"
#include "widgets/WidgetCheckbox.hpp"

::dr4::Font* optor::FONT = nullptr;

static void CreateScene(dr4::Window* window, dr4::DR4Backend* backend, optor::WidgetManager* manager);
static void CreateCameraButtons(dr4::Window* window, dr4::DR4Backend* backend, optor::WidgetManager* manager, optor::SceneWidget* sceneWidget);
static void CreateObjsList(optor::WidgetManager* manager, optor::SceneWidget* sceneWidget);

int main() {
    void* libdr4 = dlopen("./build/source/dr4/libdr4.so", RTLD_LAZY);
    
    if (!libdr4) {
        std::cerr << "error" << dlerror();
        throw std::runtime_error("Can't open lib");
    }

    dr4::DR4Backend* backend = reinterpret_cast<dr4::DR4Backend*(*)()>(dlsym(libdr4, dr4::DR4BackendFunctionName))();

    if (!backend) {
        throw std::runtime_error("Can't get backend");
    }

    dr4::Window* window = backend->CreateWindow();

    if (!window) {
        delete backend;
        throw std::runtime_error("Can't get window");
    }

    optor::FONT = backend->CreateFont();

    if (!optor::FONT) {
        delete backend;
        delete window;
        throw std::runtime_error("Can't get font");
    }

    ERROR_HANDLE([](){
        optor::FONT->loadFromFile(optor::FONT_PATH);
    });

try 
{
    ERROR_HANDLE([window](){
        window->SetSize({optor::PROGRAM_WIDTH, optor::PROGRAM_HEIGHT});
        window->SetTitle("0xCEBAEBA1DEDA");
        window->Open();
    });

    optor::WidgetManager manager(window);

    ERROR_HANDLE([backend, window, &manager](){
        CreateScene(window, backend, &manager);
    });

    auto* topbar = ERROR_HANDLE([&manager](){
        return manager.GetDesktop()->AddChild(std::make_unique<optor::TopBar>(
            &manager
        ));
    });

    while (ERROR_HANDLE(&dr4::Window::IsOpen, window)) {
        
        ERROR_HANDLE(&optor::WidgetManager::HandleEvents, &manager);
        
        ERROR_HANDLE(&dr4::Window::Clear, window, optor::color::Poison);
        
        ERROR_HANDLE(&optor::WidgetManager::Draw, &manager);

        ERROR_HANDLE(&dr4::Window::Display, window);
    }
} 
catch(...) 
{
    std::cerr << "Something went wrong\n";
    delete backend;
    delete window;

    throw;
}

    delete backend;
    delete window;
    
    return EXIT_SUCCESS;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        // ВОВА ГЕЙ + ПИДОР
}

void CreateScene(dr4::Window* window, dr4::DR4Backend* backend, optor::WidgetManager* manager) {
    assert(manager);
    assert(window);
    assert(backend);

    auto* sceneWidgetWithHeader = dynamic_cast<optor::WidgetHeader*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild,
        manager->GetDesktop(),
        std::make_unique<optor::WidgetHeader>(
            window,
            std::make_unique<optor::SceneWidget>(
                window,
                backend,
                dr4::Vec2f{1750, 900},
                manager->GetState()
            ),
            "Scene",
            optor::WidgetHeader::CloseMode::HIDE
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, sceneWidgetWithHeader, dr4::Vec2f(500, 100));

    auto* sceneWidget = dynamic_cast<optor::SceneWidget*>(sceneWidgetWithHeader->GetWidget());

    sceneWidget->SetName("Scene");
    
    ERROR_HANDLE(&CreateCameraButtons, window, backend, manager, sceneWidget);

    auto* sphere1 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Sphere>(2, optor::Vector3d(-3, 0, 26), optor::materials::IVORY));
    }));

    auto* sphere2 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Sphere>(2, optor::Vector3d(-1, -1.5, 22), optor::materials::GLASS));
    }));

    auto* sphere3 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Sphere>(3, optor::Vector3d(1.5, -0.5, 28), optor::materials::RED_RUBBER));
    }));

    auto* sphere4 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Sphere>(4, optor::Vector3d(7, 5, 28), optor::materials::MIRROR));
    }));

    auto* light1 = dynamic_cast<optor::Light*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Light>(1, optor::Vector3d(-20, 20, -10), optor::materials::LIGHT, optor::Vector3d{optor::color::White}));
    }));

    // for (double i = 0; i < 40; ++i) {
    //     ERROR_HANDLE([sceneWidget, i](){
    //         return sceneWidget->AddObj(std::make_unique<optor::Sphere>(1, optor::Vector3d(7 + i, 5 - i, 28 - i), optor::materials::WOOD));
    //     });
    // }

    // auto* light2 = dynamic_cast<optor::Light*>(ERROR_HANDLE([sceneWidget](){
    //     return sceneWidget->AddObj(std::make_unique<optor::Light>(0.2, optor::Vector3d(30, 50, 35), optor::materials::LIGHT, optor::Vector3d{optor::color::White}));
    // }));

    // auto* light3 = dynamic_cast<optor::Light*>(ERROR_HANDLE([sceneWidget](){
    //     return sceneWidget->AddObj(std::make_unique<optor::Light>(0.2, optor::Vector3d(30, 20, 40), optor::materials::LIGHT, optor::Vector3d{optor::color::White}));
    // }));

    auto* floorPlane = dynamic_cast<optor::Plane*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Plane>(optor::Vector3d(0, -4, 10), optor::Vector3d(0, 1, 0), optor::materials::WOOD));
    }));

    auto* triangle = dynamic_cast<optor::Triangle*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Triangle>(
            optor::Vector3d(5, -1, 22),
            optor::Vector3d(8, -1, 22),
            optor::Vector3d(14, 5, 26),
            optor::materials::STEEL
        ));
    }));

    auto mesh = std::make_unique<optor::TriangleMesh>(optor::materials::FABRIC);

    mesh->AddTriangle({{-2, -1, 8}, {-3, -3, 9}, {-1, -3, 9}});
    mesh->AddTriangle({{-2, -1, 8}, {-1, -3, 9}, {-1, -3, 7}});
    mesh->AddTriangle({{-2, -1, 8}, {-1, -3, 7}, {-3, -3, 7}});
    mesh->AddTriangle({{-2, -1, 8}, {-3, -3, 7}, {-3, -3, 9}});
    mesh->AddTriangle({{-3, -3, 9}, {-1, -3, 9}, {-1, -3, 7}});
    mesh->AddTriangle({{-3, -3, 9}, {-1, -3, 7}, {-3, -3, 7}});

    sceneWidget->AddObj(std::move(mesh));

    auto* plane = dynamic_cast<optor::FinitPlane*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::FinitPlane>(
            optor::Vector3d(0, 20, 25),   
            optor::Vector3d(0, -2, -1),     
            optor::Vector2d(10, 20),
            optor::materials::MIRROR
        ));
    }));

    // auto* checkBox = dynamic_cast<optor::WidgetCheckbox*>(ERROR_HANDLE(
    //     &optor::WidgetChildable::AddChild,
    //     manager->GetDesktop(),
    //     std::make_unique<optor::WidgetCheckbox>(
    //         window, 
    //         dr4::Vec2f(100, 100),
    //         manager->GetState(),
    //         [sceneWidgetWithHeader](bool isPresssed) { sceneWidgetWithHeader->SetIsHide(!isPresssed); }
    //     )
    // ));

    // checkBox->SetPosition({500, 500});

    ERROR_HANDLE(&CreateObjsList, manager, sceneWidget);
}

static void CreateCameraButtons(dr4::Window* window, dr4::DR4Backend* backend, optor::WidgetManager* manager, optor::SceneWidget* sceneWidget) {
    assert(manager);
    assert(sceneWidget);
    assert(window);
    assert(backend);

    auto cameraButtons = std::make_unique<optor::WidgetChildable>(
        dr4::Vec2f{750, 400},
        manager->GetState(),
        window
    );

    ERROR_HANDLE(&optor::Widget::SetPosition, cameraButtons, dr4::Vec2f(1450, 650));

    cameraButtons->SetName("Camera buttons");

    auto* leftButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            window,
            dr4::Vec2f{200, 100},
            manager->GetState(),
            "left",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::LEFT
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, leftButton, dr4::Vec2f(50, 150));

    auto* rightButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            window,
            dr4::Vec2f{200, 100},
            manager->GetState(),
            "right",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::RIGHT
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, rightButton, dr4::Vec2f(250, 150));

    auto* upButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            window,
            dr4::Vec2f{200, 100},
            manager->GetState(),
            "up",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::UP
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, upButton, dr4::Vec2f(150, 45));

    auto* downButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            window,
            dr4::Vec2f{200, 100},
            manager->GetState(),
            "down",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::DOWN
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, downButton, dr4::Vec2f(150, 255));

    auto* forwardButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            window,
            dr4::Vec2f{200, 100},
            manager->GetState(),
            "forward",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::FORWARD
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, forwardButton, dr4::Vec2f(500, 100));

        auto* backwordButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            window,
            dr4::Vec2f{200, 100},
            manager->GetState(),
            "backword",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::BACKWARD
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, backwordButton, dr4::Vec2f(500, 200));

    auto* cameraButtonsWithHeader = dynamic_cast<optor::WidgetHeader*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        manager->GetDesktop(), 
        std::make_unique<optor::WidgetHeader> (
            window,
            std::move(cameraButtons),
            "Camera",
            optor::WidgetHeader::CloseMode::HIDE
        )
    ));
}

static void CreateObjsList(optor::WidgetManager* manager, optor::SceneWidget* sceneWidget) {
    auto list = std::make_unique<optor::WidgetScrolledList>(
        manager->GetWindow(),
        dr4::Vec2f(400, 900),
        manager->GetState()
    );

    list->SetName("Optical Oblects list");

    const auto& objs = sceneWidget->GetScene().GetObjs();

    for (size_t ind = 0; ind < objs.size(); ++ind) {

        auto* obj = objs[ind].get();

        const std::string name = obj->GetTypeName();

        const dr4::Vec2f size = dr4::Text{.text = name, .fontSize = 40, .font = optor::FONT}.GetBounds().size;

        auto nameWidget = std::make_unique<optor::WidgetText>(
            manager->GetWindow(),
            dr4::Vec2f{list->GetSize().x - optor::INIT_SCROLLBAR_WIDTH - size.y, size.y},
            manager->GetState(),
            name
        );

        nameWidget->SetOutlineThickness(0);
        nameWidget->SetPosition({size.y, 0});

        auto numWidget = std::make_unique<optor::WidgetText>(
            manager->GetWindow(),
            dr4::Vec2f{size.y, size.y},
            manager->GetState(),
            std::to_string(ind)
        );

        numWidget->SetOutlineThickness(0);

        auto listElem = std::make_unique<optor::WidgetChildable> (
            dr4::Vec2f(nameWidget->GetSize().x + size.y, size.y),
            manager->GetState(),
            manager->GetWindow()
        );

        ERROR_HANDLE(&optor::WidgetChildable::AddChild, listElem, std::move(numWidget));
        ERROR_HANDLE(&optor::WidgetChildable::AddChild, listElem, std::move(nameWidget));

        ERROR_HANDLE(&optor::WidgetChildable::AddChild, list, std::move(listElem));
    }

    auto listWithHeader  = std::make_unique<optor::WidgetHeader>(
        manager->GetWindow(),
        std::move(list),
        list->GetName().value(),
        optor::WidgetHeader::CloseMode::HIDE
    );

    listWithHeader->SetPosition({50, 100});

    ERROR_HANDLE(&optor::WidgetChildable::AddChild, manager->GetDesktop(), std::move(listWithHeader));
}
