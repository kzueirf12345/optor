#include <cstdlib>
#include <memory>

#include "hui/RectangleShape.hpp"
#include "hui/Vector.hpp"
#include "hui/Window.hpp"
#include "common/ErrorHandler.hpp"
#include "optics/Light.hpp"
#include "optics/Material.hpp"
#include "widgets/SceneWidget.hpp"
#include "widgets/Widget.hpp"
#include "global/Global.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetManager.hpp"
#include "optics/Sphere.hpp" 
#include "optics/Plane.hpp"
#include "optics/Triangle.hpp"
#include "optics/TriangleMesh.hpp"

const optor::Material LIGHT          ({1, 1, 1},          {0, 0, 0},       {0, 0, 0},          0,      0,   0,   0);
const optor::Material IVORY          ({0.1, 0.1, 0.1},    {0.4, 0.4, 0.3}, {1.0, 1.0, 1.0},    50.0,   0.1, 1.0, 0.0);
const optor::Material GLASS          ({0.05, 0.05, 0.05}, {0.6, 0.7, 0.8}, {1.0, 1.0, 1.0},    125.0,  0.1, 1.5, 0.8);
const optor::Material RED_RUBBER     ({0.05, 0.01, 0.01}, {0.3, 0.1, 0.1}, {0.3, 0.3, 0.3},    10.0,   0.0, 1.0, 0.0);
const optor::Material MIRROR         ({0.05, 0.05, 0.05}, {1.0, 1.0, 1.0}, {1.0, 1.0, 1.0},    1425.0, 0.8, 1.0, 0.0);
const optor::Material WOOD           ({0.05, 0.03, 0.01}, {0.4, 0.25, 0.1},{0.2, 0.2, 0.2},    25.0,   0.0, 1.0, 0.0);
const optor::Material STEEL          ({0.1, 0.1, 0.1},    {0.5, 0.5, 0.5}, {0.7, 0.7, 0.7},    200.0,  0.6, 1.0, 0.0);
const optor::Material PLASTIC        ({0.02, 0.02, 0.02}, {0.3, 0.3, 0.3}, {0.1, 0.1, 0.1},    15.0,   0.0, 1.0, 0.0);
const optor::Material FABRIC         ({0.03, 0.02, 0.02}, {0.4, 0.2, 0.2}, {0.05, 0.05, 0.05}, 5.0,    0.0, 1.0, 0.0);
const optor::Material MATTE_GLASS    ({0.05, 0.05, 0.05}, {0.5, 0.5, 0.55},{0.3, 0.3, 0.3},    50.0,   0.1, 1.3, 0.5);

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
            hui::RectangleShape({1200, 700}),
            manager.GetState()
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, sceneWidget, hui::Vector2d(100, 100));

    auto* sphere1 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Sphere>(2, hui::Vector3d(-3, 0, 16), IVORY));
    }));

    auto* sphere2 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Sphere>(2, hui::Vector3d(-1, -1.5, 12), GLASS));
    }));

    auto* sphere3 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Sphere>(3, hui::Vector3d(1.5, -0.5, 18), RED_RUBBER));
    }));

    auto* sphere4 = dynamic_cast<optor::Sphere*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Sphere>(4, hui::Vector3d(7, 5, 18), MIRROR));
    }));

    auto* light1 = dynamic_cast<optor::Light*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Light>(1, hui::Vector3d(-20, 20, -20), LIGHT, optor::color::White.GetNormalized()));
    }));

    auto* light2 = dynamic_cast<optor::Light*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Light>(0.2, hui::Vector3d(30, 50, 25), LIGHT, optor::color::White.GetNormalized()));
    }));

    auto* light3 = dynamic_cast<optor::Light*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Light>(0.2, hui::Vector3d(30, 20, 30), LIGHT, optor::color::White.GetNormalized()));
    }));

    auto* floorPlane = dynamic_cast<optor::Plane*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Plane>(hui::Vector3d(0, -4, 0), hui::Vector3d(0, 1, 0), WOOD));
    }));

    auto* triangle = dynamic_cast<optor::Triangle*>(ERROR_HANDLE([sceneWidget](){
        return sceneWidget->AddObj(std::make_unique<optor::Triangle>(
            hui::Vector3d(5, -1, 12),
            hui::Vector3d(8, -1, 12),
            hui::Vector3d(14, 5, 16),
            STEEL
        ));
    }));

    auto mesh = std::make_unique<optor::TriangleMesh>(FABRIC);

    mesh->AddTriangle({{-2, -1, -2}, {-3, -3, -1}, {-1, -3, -1}});
    mesh->AddTriangle({{-2, -1, -2}, {-1, -3, -1}, {-1, -3, -3}});
    mesh->AddTriangle({{-2, -1, -2}, {-1, -3, -3}, {-3, -3, -3}});
    mesh->AddTriangle({{-2, -1, -2}, {-3, -3, -3}, {-3, -3, -1}});
    mesh->AddTriangle({{-3, -3, -1}, {-1, -3, -1}, {-1, -3, -3}});
    mesh->AddTriangle({{-3, -3, -1}, {-1, -3, -3}, {-3, -3, -3}});

    sceneWidget->AddObj(std::move(mesh));


    while (ERROR_HANDLE(&hui::Window::isOpen, window)) {

        ERROR_HANDLE(&optor::WidgetManager::HandleEvents, &manager, &window);

        ERROR_HANDLE(&hui::Window::Clear, &window, optor::color::ProgramBackground);

        ERROR_HANDLE(&optor::WidgetManager::Draw, &manager, &window);

        ERROR_HANDLE(&hui::Window::Display, &window);
    }

    return EXIT_SUCCESS;
}