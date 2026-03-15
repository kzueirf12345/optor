#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_DELETE_OBJ_BUTTON_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_DELETE_OBJ_BUTTON_HPP

#include <memory>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

#include "widgets/OpticObjShort.hpp"
#include "widgets/WidgetButton.hpp"
#include "widgets/Textable.hpp"

namespace optor 
{

class DeleteObjButton: public WidgetButton, public Textable {
    public:
        DeleteObjButton(const dr4::Vec2f& size, optor::WidgetsState* state, 
                        const std::string& text, optor::OpticObjShort* desc);

        virtual void SetPosition(const dr4::Vec2f& position) override;
        
        virtual bool OnMousePress(const ::dr4::Event &event) override;
        virtual void OnIdle() override;

        virtual void Draw(dr4::Texture &srcTexture) override;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "DeleteObjButton"; };

    private:
        std::unique_ptr<dr4::Texture> texture_;
        optor::OpticObjShort* desc_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_DELETE_OBJ_BUTTON_HPP*/