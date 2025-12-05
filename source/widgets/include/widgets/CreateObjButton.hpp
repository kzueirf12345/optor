#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_CREATE_OBJ_BUTTON_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_CREATE_OBJ_BUTTON_HPP

#include <memory>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

#include "widgets/WidgetButton.hpp"
#include "widgets/Textable.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetManager.hpp"
#include "widgets/SceneWidget.hpp"
#include "global/Global.hpp"
#include "optics/AABB.hpp"
#include "optics/FinitPlane.hpp"
#include "optics/Light.hpp"
#include "optics/Material.hpp"
#include "optics/OpticObj.hpp"
#include "optics/Plane.hpp"
#include "optics/Triangle.hpp"
#include "optics/Vector.hpp"
#include "widgets/OpticObjShort.hpp"
#include "widgets/WidgetScrolledList.hpp"

namespace optor 
{

template <typename ObjType>
class CreateObjButton: public WidgetButton, public Textable {
    public:
        CreateObjButton(optor::WidgetManager* manager, const dr4::Vec2f& size,
                     const std::string& text, std::vector<optor::WidgetChildable*> lists,
                     optor::SceneWidget* scene);

        virtual void SetPosition(const dr4::Vec2f& position) override;
        
        virtual bool OnMousePress(const ::dr4::Event &event) override;

        virtual void Draw(dr4::Texture &srcTexture) override;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "AddObjButton"; };

    private:
        std::unique_ptr<dr4::Texture> texture_;
        std::vector<optor::WidgetChildable*>  lists_;
        optor::SceneWidget* scene_;
        optor::WidgetManager* manager_;
};

}

template<typename ObjType>
optor::CreateObjButton<ObjType>::CreateObjButton(optor::WidgetManager* manager, const dr4::Vec2f& size,
                                           const std::string& text, std::vector<optor::WidgetChildable*> lists, 
                                           optor::SceneWidget* scene) 
    :   optor::WidgetButton(size, manager->GetState()),
        optor::Textable(text, manager->GetState()->window),
        texture_{manager->GetState()->window->CreateTexture()},
        lists_(lists),
        scene_(scene),
        manager_(manager)
{
    ERROR_HANDLE([this, &size](){
        texture_->SetSize(size);
    });

    
    ERROR_HANDLE([this, &size](){
        const dr4::Vec2f localBounds = text_->GetBounds();
        text_->SetPos((size.x - localBounds.x) / 2,
                      (size.y - localBounds.y) / 2);
    });
}

template<typename ObjType>
void optor::CreateObjButton<ObjType>::SetPosition(const dr4::Vec2f& position) {
    optor::Widget::SetPosition(position);
    texture_->SetPos(position);
}

template<typename ObjType>
bool optor::CreateObjButton<ObjType>::OnMousePress(const ::dr4::Event &event) {
    if (isHide_) return false;

    if (state_->hoveredWidget == this && event.mouseButton.button == dr4::MouseButtonType::LEFT) {
        isPressed_ = true;
        if (isSelectable_) { 
            state_->selectedWidget = this; 
        }
        rect_->SetFillColor(pressedColor_);

        state_->needUpdateScene = true;

        const optor::Material material = optor::materials::PLASTIC;

        optor::OpticObj* obj = nullptr;

        if constexpr (std::is_same_v<ObjType, optor::AABB>) {
            obj = scene_->AddObj(std::make_unique<optor::AABB>(
                std::array<optor::Vector3d, 8>({
                    {0, 0, 10},
                    {5, 0, 10},
                    {5, 5, 10},
                    {0, 5, 10},
                    {0, 0, 15},
                    {5, 0, 15},
                    {5, 5, 15},
                    {0, 5, 15}
                }),
                material
            ));
        }
        else if constexpr (std::is_same_v<ObjType, optor::FinitPlane>) {
            obj = scene_->AddObj(std::make_unique<optor::FinitPlane>(
                optor::Vector3d{0, 0, 10},
                optor::Vector3d{0, 0, 1},
                optor::Vector2d{10, 10},
                material
            ));
        }
        else if constexpr (std::is_same_v<ObjType, optor::Light>) {
            obj = scene_->AddObj(std::make_unique<optor::Light>(
                1.,
                optor::Vector3d{0, 0, 10},
                optor::materials::LIGHT,
                optor::Vector3d{0, 0, 0}
            ));
        }
        else if constexpr (std::is_same_v<ObjType, optor::Plane>) {
            obj = scene_->AddObj(std::make_unique<optor::Plane>(
                optor::Vector3d{0, 0, 0},
                optor::Vector3d{0, 0, 1},
                material
            ));
        }
        else if constexpr (std::is_same_v<ObjType, optor::Sphere>) {
            obj = scene_->AddObj(std::make_unique<optor::Sphere>(
                5,
                optor::Vector3d{0, 0, 10},
                material
            ));
        }
        else if constexpr (std::is_same_v<ObjType, optor::Triangle>) {
            obj = scene_->AddObj(std::make_unique<optor::Triangle>(
                optor::Vector3d{5, 0, 10},
                optor::Vector3d{0, 5, 10},
                optor::Vector3d{0, 0, 15},
                material
            ));
        }

        for (optor::WidgetChildable* parent : lists_) {
            parent->AddChild(std::make_unique<optor::OpticObjShort>(
                manager_,
                dr4::Vec2f{
                    parent->GetSize().x - (dynamic_cast<optor::WidgetScrolledList*>(parent) ? optor::INIT_SCROLLBAR_WIDTH : 0), 
                    optor::STRING_BLOCK_HEIGHT
                },
                obj,
                parent->GetChildrenCount()
            ));
        }
    }

    return false;
}


template<typename ObjType>
void optor::CreateObjButton<ObjType>::Draw(dr4::Texture &srcTexture) {
    if (isHide_) return;

    const dr4::Vec2f pos = rect_->GetPos();

    rect_->SetPos({0, 0});
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_->SetPos(pos);

    ERROR_HANDLE([this](){
        texture_->Draw(*text_);
    });

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_);
    });
}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_CREATE_OBJ_BUTTON_HPP*/