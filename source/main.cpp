#include <cstdlib>
#include <dlfcn.h>
#include <linux/limits.h>
#include <memory>
#include <stdexcept>
#include <cassert>
#include <string>

#include "cum/ifc/dr4.hpp"
#include "cum/manager.hpp"
#include "dr4/math/color.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "global/Global.hpp"
#include "cum/ifc/pp.hpp"
#include "dr4/window.hpp"

#include "common/ErrorHandler.hpp"
#include "global/Global.hpp"
#include "optics/Vector.hpp"
#include "widgets/CreateObjButton.hpp"
#include "widgets/OpticObjShort.hpp"
#include "widgets/TopBar.hpp"
#include "widgets/Widget.hpp"
#include "widgets/WidgetHeader.hpp"
#include "widgets/WidgetScrolledList.hpp"
#include "widgets/WidgetManager.hpp"
#include "widgets/WidgetText.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/SceneWidget.hpp"
#include "widgets/WidgetButtonCamera.hpp"
#include "optics/FinitPlane.hpp"
#include "optics/Plane.hpp"
#include "optics/Light.hpp"
#include "optics/Triangle.hpp"
#include "optics/Sphere.hpp"

// FIXME refactor clipRect and draw texture
// TODO add optic obj
// TODO remove optic obj
// TODO change optic obj features
// TODO update optic obj features


::dr4::Font* optor::FONT = nullptr;


static void CreateScene(cum::DR4BackendPlugin* backend, optor::WidgetManager* manager);
static void CreateCameraButtons(cum::DR4BackendPlugin* backend, optor::WidgetManager* manager, optor::SceneWidget* sceneWidget);
static void CreateObjsList(optor::WidgetManager* manager, optor::SceneWidget* sceneWidget);
static void CreateAddList(optor::WidgetManager* manager, optor::SceneWidget* sceneWidget, optor::WidgetScrolledList* objList);

int main() {

    cum::Manager pluginsManager = {};

    auto* dr4Backend = dynamic_cast<cum::DR4BackendPlugin*>(ERROR_HANDLE([&pluginsManager](){
        return pluginsManager.LoadFromFile("./build/source/dr4Plugin/libdr4Plugin.so");
    }));

    // auto* dr4Backend = dynamic_cast<cum::DR4BackendPlugin*>(ERROR_HANDLE([&pluginsManager](){
    //     return pluginsManager.LoadFromFile("./plugins/dr4/v2/libDenchik.so");
    // }));

    dr4Backend->AfterLoad();

// ==========DR4===========
    

    std::unique_ptr<dr4::Window> window(dr4Backend->CreateWindow());

    if (!window) {
        delete dr4Backend;
        throw std::runtime_error("Can't get window");
    }

    ERROR_HANDLE([&window](){
        window->Open();
        window->SetSize({optor::PROGRAM_WIDTH, optor::PROGRAM_HEIGHT});
        window->SetTitle("0xCEBAEBA1DEDA");
        window->Open();
    });

    optor::FONT = window->CreateFont();

    if (!optor::FONT) {
        throw std::runtime_error("Can't get font");
    }

    ERROR_HANDLE([](){
        optor::FONT->LoadFromFile(optor::FONT_PATH);
    });

//==========DR4=================
//==========GeomPrim=================

    std::vector<cum::PPToolPlugin*> ppPlugins = {};

    ppPlugins.push_back(dynamic_cast<cum::PPToolPlugin*>(ERROR_HANDLE([&pluginsManager](){
        return pluginsManager.LoadFromFile("./plugins/pp/libDenchik.so");
    })));
    ppPlugins.push_back(dynamic_cast<cum::PPToolPlugin*>(ERROR_HANDLE([&pluginsManager](){
        return pluginsManager.LoadFromFile("./plugins/pp/libArtemLine.so");
    })));
    ppPlugins.push_back(dynamic_cast<cum::PPToolPlugin*>(ERROR_HANDLE([&pluginsManager](){
        return pluginsManager.LoadFromFile("./plugins/pp/libSeva.so");
    })));
    ppPlugins.push_back(dynamic_cast<cum::PPToolPlugin*>(ERROR_HANDLE([&pluginsManager](){
        return pluginsManager.LoadFromFile("./build/source/piska/libpiska.so");
    })));    

    ppPlugins.back()->AfterLoad();

//==========GeomPrim=================

    optor::WidgetManager manager(window.get(), ppPlugins);

    ERROR_HANDLE([dr4Backend, &manager](){
        CreateScene(dr4Backend, &manager);
    });

    auto* topbar = ERROR_HANDLE([&manager](){
        return manager.GetDesktop()->AddChild(std::make_unique<optor::TopBar>(
            &manager
        ));
    });


    while (ERROR_HANDLE(&dr4::Window::IsOpen, window)) {

        ERROR_HANDLE(&optor::WidgetManager::HandleEvents, &manager);

        if (!ERROR_HANDLE(&dr4::Window::IsOpen, window)) {
            break;
        }
        
        ERROR_HANDLE(&dr4::Window::Clear, window, optor::color::Poison);

        ERROR_HANDLE(&optor::WidgetManager::Draw, &manager);

        ERROR_HANDLE(&dr4::Window::Display, window);
    }
    
    return EXIT_SUCCESS;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        // ВОВА ГЕЙ + ПИДОР
}


void CreateScene(cum::DR4BackendPlugin* backend, optor::WidgetManager* manager) {
    assert(manager);
    assert(backend);

    auto* sceneWidgetWithHeader = dynamic_cast<optor::WidgetHeader*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild,
        manager->GetDesktop(),
        std::make_unique<optor::WidgetHeader>(
            std::make_unique<optor::SceneWidget>(
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
    
    ERROR_HANDLE(&CreateCameraButtons, backend, manager, sceneWidget);

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
            optor::Vector3d(0, 20, 25),   
            optor::Vector3d(0, -2, -1),     
            optor::Vector2d(10, 20),
            optor::materials::MIRROR
        ));
    }));

    ERROR_HANDLE(&CreateObjsList, manager, sceneWidget);
}

static void CreateCameraButtons(cum::DR4BackendPlugin* backend, optor::WidgetManager* manager, optor::SceneWidget* sceneWidget) {
    assert(manager);
    assert(sceneWidget);
    assert(backend);

    auto cameraButtons = std::make_unique<optor::WidgetChildable>(
        dr4::Vec2f{750, 400},
        manager->GetState()
    );

    ERROR_HANDLE(&optor::Widget::SetPosition, cameraButtons, dr4::Vec2f(1450, 650));

    cameraButtons->SetName("Camera buttons");

    auto* leftButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
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
            std::move(cameraButtons),
            "Camera",
            optor::WidgetHeader::CloseMode::HIDE
        )
    ));
}

static void CreateObjsList(optor::WidgetManager* manager, optor::SceneWidget* sceneWidget) {
    auto list = std::make_unique<optor::WidgetScrolledList>(
        dr4::Vec2f(400, 400),
        manager->GetState()
    );

    list->SetName("Objects list");

    const auto& objs = sceneWidget->GetScene().GetObjs();

    for (size_t ind = 0; ind < objs.size(); ++ind) {

        auto* obj = objs[ind].get();

        auto listElem = std::make_unique<optor::OpticObjShort>(
            manager,
            dr4::Vec2f{list->GetSize().x - optor::INIT_SCROLLBAR_WIDTH, optor::STRING_BLOCK_HEIGHT},
            obj,
            ind
        );

        ERROR_HANDLE(&optor::WidgetChildable::AddChild, list, std::move(listElem));
    }

    auto listWithHeader  = std::make_unique<optor::WidgetHeader>(
        std::move(list),
        list->GetName().value(),
        optor::WidgetHeader::CloseMode::HIDE
    );

    listWithHeader->SetPosition({50, 100});

    auto* listWithHeaderPtr = dynamic_cast<optor::WidgetHeader*>(ERROR_HANDLE(&optor::WidgetChildable::AddChild, manager->GetDesktop(), std::move(listWithHeader)));

    ERROR_HANDLE(&CreateAddList, manager, sceneWidget, dynamic_cast<optor::WidgetScrolledList*>(listWithHeaderPtr->GetWidget()));
}

static void CreateAddList(optor::WidgetManager* manager, optor::SceneWidget* sceneWidget, optor::WidgetScrolledList* objList) {
    auto list = std::make_unique<optor::WidgetScrolledList>(
        dr4::Vec2f(400, 400),
        manager->GetState()
    );

    list->SetName("Add Object");

    auto listWithHeader  = std::make_unique<optor::WidgetHeader>(
        std::move(list),
        list->GetName().value(),
        optor::WidgetHeader::CloseMode::HIDE
    );

    listWithHeader->SetPosition({50, 600});

    auto* listWithHeaderPtr = dynamic_cast<optor::WidgetHeader*>(ERROR_HANDLE(&optor::WidgetChildable::AddChild, manager->GetDesktop(), std::move(listWithHeader)));

    auto* listPtr = dynamic_cast<optor::WidgetScrolledList*>(listWithHeaderPtr->GetWidget());

    std::cerr << listPtr << std::endl;

    listPtr->AddChild(std::make_unique<optor::CreateObjButton<optor::Sphere>>(
        manager,
         dr4::Vec2f(listPtr->GetSize().x - optor::INIT_SCROLLBAR_WIDTH, optor::STRING_BLOCK_HEIGHT), 
         "Sphere", 
         std::vector<optor::WidgetChildable*>{objList}, 
         sceneWidget
    ));
    listPtr->AddChild(std::make_unique<optor::CreateObjButton<optor::Triangle>>(
        manager,
         dr4::Vec2f(listPtr->GetSize().x - optor::INIT_SCROLLBAR_WIDTH, optor::STRING_BLOCK_HEIGHT), 
         "Triangle", 
         std::vector<optor::WidgetChildable*>{objList}, 
         sceneWidget
    ));
    listPtr->AddChild(std::make_unique<optor::CreateObjButton<optor::AABB>>(
        manager,
         dr4::Vec2f(listPtr->GetSize().x - optor::INIT_SCROLLBAR_WIDTH, optor::STRING_BLOCK_HEIGHT), 
         "AABB", 
         std::vector<optor::WidgetChildable*>{objList}, 
         sceneWidget
    ));
    listPtr->AddChild(std::make_unique<optor::CreateObjButton<optor::FinitPlane>>(
        manager,
         dr4::Vec2f(listPtr->GetSize().x - optor::INIT_SCROLLBAR_WIDTH, optor::STRING_BLOCK_HEIGHT), 
         "FinitPlane", 
         std::vector<optor::WidgetChildable*>{objList}, 
         sceneWidget
    ));
    listPtr->AddChild(std::make_unique<optor::CreateObjButton<optor::Light>>(
        manager,
         dr4::Vec2f(listPtr->GetSize().x - optor::INIT_SCROLLBAR_WIDTH, optor::STRING_BLOCK_HEIGHT), 
         "Light", 
         std::vector<optor::WidgetChildable*>{objList}, 
         sceneWidget
    ));
    listPtr->AddChild(std::make_unique<optor::CreateObjButton<optor::Plane>>(
        manager,
         dr4::Vec2f(listPtr->GetSize().x - optor::INIT_SCROLLBAR_WIDTH, optor::STRING_BLOCK_HEIGHT), 
         "Plane", 
         std::vector<optor::WidgetChildable*>{objList}, 
         sceneWidget
    ));
}