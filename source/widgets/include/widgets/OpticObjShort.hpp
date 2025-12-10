#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_OPTIC_OBJ_SHORT_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_OPTIC_OBJ_SHORT_HPP

#include "dr4/keycodes.hpp"
#include "optics/OpticObj.hpp"
#include "widgets/OpticObjDesc.hpp"
#include "widgets/Textable.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetManager.hpp"

namespace optor 
{

class OpticObjShort : public Textable, public WidgetChildable {
    public:
        OpticObjShort(optor::WidgetManager* manager, const dr4::Vec2f& size, optor::OpticObj* obj, size_t ind);

        virtual void OnIdle() override;
        virtual bool OnKeyboardPress(const dr4::Event& event) override;

        virtual void Draw(dr4::Texture& srcTexture) override;

        optor::OpticObj* GetObj();

        [[nodiscard]] virtual std::string GetTypeName() const override {return "OpticObjShort"; };

    private:

        optor::OpticObj* obj_;

        optor::WidgetChildable* desktop_;

        OpticObjDesc desc_;

        dr4::KeyCode descButton_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_OPTIC_OBJ_SHORT_HPP*/