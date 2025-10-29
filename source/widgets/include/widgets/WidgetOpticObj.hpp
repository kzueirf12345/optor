#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_OPTIC_OBJ_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_OPTIC_OBJ_HPP

#include "optics/OpticObj.hpp"
#include "widgets/Widget.hpp"
#include "hui/Text.hpp"

namespace optor 
{

class WidgetOpticObj : public Widget {
    public:
        WidgetOpticObj(const hui::Vector2d& size, optor::WidgetsState* state, optor::OpticObj* obj);

        virtual void Draw(hui::Renderer* renderer) override;

        void SetTextAlign(hui::Text::Align align) noexcept;
        void SetTextOffset(const hui::Vector2d& offset) noexcept;

        const optor::OpticObj* GetObj() const noexcept;

    private:
        hui::Vector2d GetTextPosition() const;

    private:
        optor::OpticObj* obj_;
        hui::Text desc_;

        hui::Renderer renderer_;
        hui::Text::Align textAlign_;
        hui::Vector2d textOffset_;

        size_t objNum_;
        inline static size_t counter_ = 0;

};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_OPTIC_OBJ_HPP*/