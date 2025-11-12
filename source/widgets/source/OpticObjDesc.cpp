#include <memory>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "dr4/math/color.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

#include "optics/Material.hpp"
#include "optics/OpticObj.hpp"
#include "optics/Vector.hpp"
#include "global/Global.hpp"
#include "widgets/OpticObjDesc.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetHeader.hpp"
#include "widgets/WidgetScrolledList.hpp"
#include "widgets/WidgetList.hpp"
#include "widgets/WidgetText.hpp"
#include "widgets/WidgetButtonMoveOpticObj.hpp"

optor::OpticObjDesc::OpticObjDesc(const dr4::Vec2f& size, 
                                  optor::WidgetsState* state, optor::OpticObj* obj)
    : size_{size}, state_{state}, obj_{obj}
{}


optor::WidgetHeader* optor::OpticObjDesc::operator()(optor::WidgetChildable* parent)
{
    auto list = std::make_unique<optor::WidgetScrolledList>(size_, state_);

    AddCoordInfo(list.get());
    AddColorInfo(list.get());
    AddMaterialFeatures(list.get());
    AddMoveButtons(list.get());

    return dynamic_cast<optor::WidgetHeader*>(parent->AddChild(std::make_unique<optor::WidgetHeader>(
        std::move(list),
        obj_->GetTypeName(),
        optor::WidgetHeader::CloseMode::REMOVE
    )));
}


std::string optor::OpticObjDesc::FormatDouble(double value)
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << value;
    return stream.str();
}

optor::WidgetList* optor::OpticObjDesc::AddCoordInfo(optor::WidgetScrolledList* list)
{
    auto* coordList = dynamic_cast<optor::WidgetList*>(list->AddChild(std::make_unique<optor::WidgetList>(state_)));

    const optor::Vector3d coord = obj_->GetCoord();
    const float strHeight = dr4::Text{.text = "x:", .fontSize = 40, .font = optor::FONT}.GetBounds().size.y;//FIXME

    const std::array<std::string, 3> coordStrs = {
        "x: " + FormatDouble(coord.x),
        "y: " + FormatDouble(coord.y),
        "z: " + FormatDouble(coord.z)
    };

    for (const auto& str : coordStrs) {
        auto* textWidget = dynamic_cast<optor::WidgetText*>(coordList->AddChild(std::make_unique<optor::WidgetText>(
            dr4::Vec2f{list->GetSize().x, strHeight}, state_, str
        )));
        textWidget->GetText()->pos.x = INIT_WIDGET_BORDER_THICKNESS;
    }

    return coordList;
}


optor::WidgetList* optor::OpticObjDesc::AddColorInfo(optor::WidgetScrolledList* list)
{
    auto* colorList = dynamic_cast<optor::WidgetList*>(list->AddChild(std::make_unique<optor::WidgetList>(state_)));

    const optor::Material& material = obj_->GetMaterial();
    const optor::Vector3d amb = material.GetAmbientColor() * 255.0;
    const optor::Vector3d dif = material.GetDiffuseColor() * 255.0;
    const optor::Vector3d spec = material.GetSpecularColor() * 255.0;

    const dr4::Color ambColor(amb.x, amb.y, amb.z, 255);
    const dr4::Color difColor(dif.x, dif.y, dif.z, 255);
    const dr4::Color specColor(spec.x, spec.y, spec.z, 255);

    struct ColorInfo {
        std::string label;
        dr4::Color color;
        optor::Vector3d rgb;
    } infos[] = {
        {"Ambient", ambColor, amb},
        {"Diffuse", difColor, dif},
        {"Specular", specColor, spec}
    };

    const float strHeight = dr4::Text{.text = "Color", .fontSize = 40, .font = optor::FONT}.GetBounds().size.y; //FIXME

    for (auto& info : infos) {
        std::string colorStr = info.label + ": { "
            + std::to_string((int)info.rgb.x) + ", "
            + std::to_string((int)info.rgb.y) + ", "
            + std::to_string((int)info.rgb.z) + " }";

        auto* colorWidget = dynamic_cast<optor::WidgetChildable*>(colorList->AddChild(std::make_unique<optor::WidgetChildable>(
            dr4::Vec2f{list->GetSize().x, strHeight}, state_
        )));

        auto* textWidget = dynamic_cast<optor::WidgetText*>(colorWidget->AddChild(std::make_unique<optor::WidgetText>(
            dr4::Text{.text = colorStr, .fontSize = 40, .font = optor::FONT}.GetBounds().size, state_, colorStr //FIXME
        )));
        textWidget->SetOutlineThickness(0);

        auto* colorRect = dynamic_cast<optor::Widget*>(colorWidget->AddChild(std::make_unique<optor::Widget>(
            dr4::Vec2f{strHeight, strHeight}, state_
        )));
        colorRect->SetBackgroundColor(info.color);
        colorRect->SetPosition({list->GetSize().x - 2 * INIT_SCROLLBAR_WIDTH, 0});
    }

    return colorList;
}


optor::WidgetList* optor::OpticObjDesc::AddMaterialFeatures(optor::WidgetScrolledList* list)
{
    auto* featuresList = dynamic_cast<optor::WidgetList*>(list->AddChild(std::make_unique<optor::WidgetList>(state_)));

    const optor::Material& material = obj_->GetMaterial();

    struct Feature {
        std::string name;
        double value;
    } features[] = {
        {"Shininess", material.GetShininess()},
        {"Reflectivity", material.GetReflectivity()},
        {"Transparency", material.GetTransparency()},
        {"Refractivity", material.GetRefractivity()}
    };

    const float strHeight = dr4::Text{.text = "0", .fontSize = 40, .font = optor::FONT}.GetBounds().size.y;

    for (auto& f : features) {
        std::string str = f.name + ": " + FormatDouble(f.value);
        auto* widget = dynamic_cast<optor::WidgetText*>(featuresList->AddChild(std::make_unique<optor::WidgetText>(
            dr4::Vec2f{list->GetSize().x, strHeight}, state_, str
        )));
        widget->GetText()->pos.x = INIT_WIDGET_BORDER_THICKNESS;
    }

    return featuresList;
}


optor::WidgetChildable* optor::OpticObjDesc::AddMoveButtons(optor::WidgetScrolledList* list)
{
    const float panelHeight = std::max(list->GetSize().y * 0.25f, 120.0f);

    auto movePanel = std::make_unique<optor::WidgetChildable>(
        dr4::Vec2f{list->GetSize().x, panelHeight},
        state_
    );

    constexpr float CENTER_OFFSET = 0.32f;

    const float buttonSize = panelHeight * 0.25f;
    const float spacing = buttonSize * 0.3f;

    const float diamondCenterX = movePanel->GetSize().x * CENTER_OFFSET; 
    const float diamondCenterY = movePanel->GetSize().y * 0.5f;

    const float forwardOffsetX = movePanel->GetSize().x * (1 - CENTER_OFFSET) - diamondCenterX;

    struct ButtonInfo {
        std::string text;
        dr4::Vec2f offset;
        MoveDirection dir;
    };

    std::vector<ButtonInfo> moveButtons = {
        {"up",       {0.0f, -(buttonSize + spacing)}, MoveDirection::UP},
        {"down",     {0.0f,  (buttonSize + spacing)}, MoveDirection::DOWN},
        {"left",     {-(buttonSize + spacing), 0.0f}, MoveDirection::LEFT},
        {"right",    { (buttonSize + spacing), 0.0f}, MoveDirection::RIGHT},
        {"forward",  { forwardOffsetX, -2 * spacing}, MoveDirection::FORWARD},
        {"backward", { forwardOffsetX,  2 * spacing}, MoveDirection::BACKWARD}
    };

    for (const auto& info : moveButtons) {
        auto* button = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(movePanel->AddChild(
            std::make_unique<optor::WidgetButtonMoveOpticObj>(
                dr4::Vec2f{3.f * buttonSize, buttonSize},
                state_,
                info.text,
                obj_,
                info.dir
            )
        ));

        button->SetPosition({
            diamondCenterX + info.offset.x - buttonSize,
            diamondCenterY + info.offset.y - buttonSize / 2.0f
        });
    }

    // movePanel->SetPosition(dr4::Vec2f((size_.x - movePanel->GetSize().x) / 2.f, 0));

    return dynamic_cast<optor::WidgetChildable*>(list->AddChild(std::move(movePanel)));
}
