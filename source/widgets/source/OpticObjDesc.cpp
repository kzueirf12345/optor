#include <memory>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "common/Utils.hpp"
#include "dr4/math/color.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

#include "optics/Material.hpp"
#include "optics/OpticObj.hpp"
#include "optics/Vector.hpp"
#include "global/Global.hpp"
#include "widgets/OpticObjDesc.hpp"
#include "widgets/ChangeField.hpp"
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
    // const float strHeight = STRING_BLOCK_HEIGHT;

    // const std::array<std::string, 3> coordStrs = {
    //     "x: " + FormatDouble(coord.x),
    //     "y: " + FormatDouble(coord.y),
    //     "z: " + FormatDouble(coord.z)
    // };

    // for (const auto& str : coordStrs) {
    //     auto* textWidget = dynamic_cast<optor::WidgetText*>(coordList->AddChild(std::make_unique<optor::WidgetText>(
    //         dr4::Vec2f{list->GetSize().x, strHeight}, state_, str
    //     )));
    //     textWidget->SetIsDraggable(false);
    //     textWidget->GetText()->SetPos(INIT_WIDGET_BORDER_THICKNESS, textWidget->GetText()->GetPos().y);
    // }

    std::string str = "Position: ";
    std::unique_ptr<dr4::Text> text(state_->window->CreateText());
    text->SetText(str);
    text->SetFont(optor::FONT);

    auto* mainWidget = dynamic_cast<optor::WidgetChildable*>(coordList->AddChild(std::make_unique<optor::WidgetChildable>(
        dr4::Vec2f{list->GetSize().x, 1.5 * STRING_BLOCK_HEIGHT}, state_
    )));
    mainWidget->SetIsDraggable(false);

    auto* textWidget = dynamic_cast<optor::WidgetText*>(mainWidget->AddChild(std::make_unique<optor::WidgetText>(
        dr4::Vec2f{text->GetBounds().x, STRING_BLOCK_HEIGHT}, state_, str
    )));
    textWidget->SetOutlineThickness(0);
    textWidget->SetIsDraggable(false);
    // textWidget->GetText()->SetPos(INIT_WIDGET_BORDER_THICKNESS, textWidget->GetText()->GetPos().y);
    textWidget->SetPosition({INIT_WIDGET_BORDER_THICKNESS, (mainWidget->GetSize().y - textWidget->GetSize().y) / 2});
    

    auto* changeField = dynamic_cast<optor::ChangeField<Vector3d>*>(mainWidget->AddChild(std::make_unique<optor::ChangeField<Vector3d>>(
        dr4::Vec2f{list->GetSize().x - textWidget->GetSize().x - 2 * INIT_SCROLLBAR_WIDTH, optor::STRING_BLOCK_HEIGHT},
        state_,
        common::to_string(coord.x) + ", "
        + common::to_string(coord.y) + ", "
        + common::to_string(coord.z),
        &optor::OpticObj::SetCoord,
        &optor::OpticObj::GetCoord,
        obj_
    )));
    changeField->SetPosition({textWidget->GetSize().x, (mainWidget->GetSize().y - changeField->GetSize().y) / 2});

    return coordList;
}


optor::WidgetList* optor::OpticObjDesc::AddColorInfo(optor::WidgetScrolledList* list)
{
    auto* colorList = dynamic_cast<optor::WidgetList*>(list->AddChild(std::make_unique<optor::WidgetList>(state_)));

    const optor::Material& material = obj_->GetMaterial();
    const optor::Vector3d amb = material.GetAmbientColor() * 255.;
    const optor::Vector3d dif = material.GetDiffuseColor() * 255.;
    const optor::Vector3d spec = material.GetSpecularColor() * 255.;

    const dr4::Color ambColor(amb.x, amb.y, amb.z, 255);
    const dr4::Color difColor(dif.x, dif.y, dif.z, 255);
    const dr4::Color specColor(spec.x, spec.y, spec.z, 255);

    struct ColorInfo {
        std::string label;
        dr4::Color color;
        optor::Vector3d rgb;
        optor::ChangeField<Vector3d>::SetT setAction;
        optor::ChangeField<Vector3d>::GetT getAction;
    } infos[] = {
        {"Ambient", ambColor, material.GetAmbientColor(), &optor::OpticObj::SetAmbientColor, &optor::OpticObj::GetAmbientColor},
        {"Diffuse", difColor, material.GetDiffuseColor(), &optor::OpticObj::SetDiffuseColor, &optor::OpticObj::GetDiffuseColor},
        {"Specular", specColor, material.GetSpecularColor(), &optor::OpticObj::SetSpecularColor, &optor::OpticObj::GetSpecularColor}
    };

    for (auto& info : infos) {
        // std::string colorStr = info.label + ": [ "
        //     + std::to_string((int)info.rgb.x) + ", "
        //     + std::to_string((int)info.rgb.y) + ", "
        //     + std::to_string((int)info.rgb.z) + " }";

        std::string str = info.label + ": ";
        std::unique_ptr<dr4::Text> text(state_->window->CreateText());
        text->SetText(str);
        text->SetFont(optor::FONT);

        auto* mainWidget = dynamic_cast<optor::WidgetChildable*>(colorList->AddChild(std::make_unique<optor::WidgetChildable>(
            dr4::Vec2f{list->GetSize().x, 1.5 * STRING_BLOCK_HEIGHT}, state_
        )));
        mainWidget->SetIsDraggable(false);

        auto* textWidget = dynamic_cast<optor::WidgetText*>(mainWidget->AddChild(std::make_unique<optor::WidgetText>(
            dr4::Vec2f{text->GetBounds().x, STRING_BLOCK_HEIGHT}, state_, str
        )));
        textWidget->SetOutlineThickness(0);
        textWidget->SetIsDraggable(false);
        // textWidget->GetText()->SetPos(INIT_WIDGET_BORDER_THICKNESS, textWidget->GetText()->GetPos().y);
        textWidget->SetPosition({INIT_WIDGET_BORDER_THICKNESS, (mainWidget->GetSize().y - textWidget->GetSize().y) / 2});
        

        auto* changeField = dynamic_cast<optor::ChangeField<Vector3d>*>(mainWidget->AddChild(std::make_unique<optor::ChangeField<Vector3d>>(
            dr4::Vec2f{list->GetSize().x - textWidget->GetSize().x - 2 * INIT_SCROLLBAR_WIDTH, optor::STRING_BLOCK_HEIGHT},
            state_,
            common::to_string(info.rgb.x) + ", "
          + common::to_string(info.rgb.y) + ", "
          + common::to_string(info.rgb.z),
            info.setAction,
            info.getAction,
            obj_
        )));
        changeField->SetPosition({textWidget->GetSize().x, (mainWidget->GetSize().y - changeField->GetSize().y) / 2});

        auto* colorRect = dynamic_cast<optor::Widget*>(mainWidget->AddChild(std::make_unique<optor::Widget>(
            dr4::Vec2f{STRING_BLOCK_HEIGHT, STRING_BLOCK_HEIGHT}, state_
        )));
        colorRect->SetIsDraggable(false);
        colorRect->SetBackgroundColor(info.color);
        colorRect->SetPosition({list->GetSize().x - 2 * INIT_SCROLLBAR_WIDTH - STRING_BLOCK_HEIGHT, (mainWidget->GetSize().y - colorRect->GetSize().y) / 2});
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
        optor::ChangeField<double>::SetT setAction;
        optor::ChangeField<double>::GetT getAction;
    } features[] = {
        {"Shininess", material.GetShininess(), &OpticObj::SetShininess, &OpticObj::GetShininess},
        {"Reflectivity", material.GetReflectivity(), &OpticObj::SetReflectivity, &OpticObj::GetReflectivity},
        {"Transparency", material.GetTransparency(), &OpticObj::SetTransparency, &OpticObj::GetTransparency},
        {"Refractivity", material.GetRefractivity(), &OpticObj::SetRefractivity, &OpticObj::GetRefractivity}
    };

//         list->AddChild(std::make_unique<optor::ChangeField>(
//         dr4::Vec2f{list->GetSize().x, optor::STRING_BLOCK_HEIGHT},
//         state_,
//         std::to_string(obj_->GetMaterial().GetReflectivity()),
//         &OpticObj::SetReflectivity,
//         obj_
// ));

    for (auto& f : features) {

        auto* mainWidget = dynamic_cast<optor::WidgetChildable*>(featuresList->AddChild(std::make_unique<optor::WidgetChildable>(
            dr4::Vec2f{list->GetSize().x, 1.5 * STRING_BLOCK_HEIGHT}, state_
        )));
        mainWidget->SetIsDraggable(false);

        std::string str = f.name + ": ";
        std::unique_ptr<dr4::Text> text(state_->window->CreateText());
        text->SetText(str);
        text->SetFont(optor::FONT);

        auto* textWidget = dynamic_cast<optor::WidgetText*>(mainWidget->AddChild(std::make_unique<optor::WidgetText>(
            dr4::Vec2f{text->GetBounds().x, STRING_BLOCK_HEIGHT}, state_, str
        )));
        textWidget->SetOutlineThickness(0);
        textWidget->SetIsDraggable(false);
        textWidget->SetPosition({INIT_WIDGET_BORDER_THICKNESS, (mainWidget->GetSize().y - textWidget->GetSize().y) / 2});

        auto* changeField = dynamic_cast<optor::ChangeField<double>*>(mainWidget->AddChild(std::make_unique<optor::ChangeField<double>>(
            dr4::Vec2f{list->GetSize().x - textWidget->GetSize().x - 2 * INIT_SCROLLBAR_WIDTH, optor::STRING_BLOCK_HEIGHT},
            state_,
            common::to_string(f.value),
            f.setAction,
            f.getAction,
            obj_
        )));
        changeField->SetPosition({textWidget->GetSize().x, (mainWidget->GetSize().y - changeField->GetSize().y) / 2});
    }

    return featuresList;
}


optor::WidgetChildable* optor::OpticObjDesc::AddMoveButtons(optor::WidgetScrolledList* list)
{
    const dr4::Vec2f buttonSize = {100, 2 * optor::STRING_BLOCK_HEIGHT};
    const float offset = 20;

    auto movePanel = std::make_unique<optor::WidgetChildable>(
        dr4::Vec2f{list->GetSize().x - optor::INIT_SCROLLBAR_WIDTH, 3 * buttonSize.y},
        state_
    );
    const dr4::Vec2f panelSize = movePanel->GetSize();

    struct ButtonInfo {
        std::string text;
        dr4::Vec2f offset;
        MoveDirection dir;
    };

    std::vector<ButtonInfo> moveButtons = {
        {"up",       {offset + buttonSize.x / 2          , 0},                    MoveDirection::UP},
        {"down",     {offset + buttonSize.x / 2          , 2 * buttonSize.y},     MoveDirection::DOWN},
        {"left",     {offset                             , buttonSize.y},         MoveDirection::LEFT},
        {"right",    {offset + buttonSize.x              , buttonSize.y},         MoveDirection::RIGHT},
        {"forward",  {panelSize.x - offset - buttonSize.x, buttonSize.y / 2},     MoveDirection::FORWARD},
        {"backward", {panelSize.x - offset - buttonSize.x, buttonSize.y * 3 / 2}, MoveDirection::BACKWARD}
    };

    for (const auto& info : moveButtons) {
        auto* button = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(movePanel->AddChild(
            std::make_unique<optor::WidgetButtonMoveOpticObj>(
                buttonSize,
                state_,
                info.text,
                obj_,
                info.dir
            )
        ));

        button->SetPosition(info.offset);
    }

    // movePanel->SetPosition(dr4::Vec2f((size_.x - movePanel->GetSize().x) / 2.f, 0));

    return dynamic_cast<optor::WidgetChildable*>(list->AddChild(std::move(movePanel)));
}
