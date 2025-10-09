#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_SHAPE_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_SHAPE_HPP

#include <memory>

#include "hui/Drawable.hpp"
#include "hui/Color.hpp"

namespace hui 
{

class ShapeImpl;

class Shape: public hui::Drawable {
    public:
        Shape();
        virtual ~Shape();

        void SetFillColor       (const hui::Color& color);
        void SetOutlineColor    (const hui::Color& color);
        void SetOutlineThickness(double thickness);

        [[nodiscard]] virtual const void* GetImplAs() const noexcept override;
        [[nodiscard]] virtual       void* GetImplAs()       noexcept override;

    private:
        std::unique_ptr<hui::ShapeImpl> impl_;
};

}

#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_SHAPE_HPP*/