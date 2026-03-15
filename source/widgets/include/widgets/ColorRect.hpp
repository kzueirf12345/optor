#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_COLOR_RECT_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_COLOR_RECT_HPP

#include <functional>

#include "dr4/math/vec2.hpp"
#include "optics/OpticObj.hpp"
#include "optics/Vector.hpp"
#include "widgets/Widget.hpp"

namespace optor 
{

class ColorRect: public Widget {
    public:

        using GetT = std::function<Vector3d(OpticObj*)>;

    public:

        ColorRect(const dr4::Vec2f& size, optor::WidgetsState* state, GetT getAction, OpticObj* obj);

        virtual void OnIdle() override;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "ColorRect"; };
        
    protected:
    
        GetT getAction_;
        Vector3d color_;
        OpticObj* obj_;

    private:
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_COLOR_RECT_HPP*/