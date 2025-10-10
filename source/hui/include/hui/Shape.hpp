#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_SHAPE_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_SHAPE_HPP

#include <memory>

#include "hui/Drawable.hpp"
#include "hui/Color.hpp"
#include "hui/Vector.hpp"

namespace hui 
{

class ShapeImpl;

class Shape: public hui::Drawable {
    public:
        Shape();
        virtual ~Shape();

        Shape           (const Shape&) = delete;
        Shape& operator=(const Shape&) = delete;
        
        Shape           (Shape&& other) noexcept;
        Shape& operator=(Shape&& other) noexcept;

        void SetFillColor       (const hui::Color& color);
        void SetOutlineColor    (const hui::Color& color);
        void SetOutlineThickness(double thickness);
        void SetPosition(const hui::Vector2d& position);
        hui::Vector2d GetPosition() const;

        [[nodiscard]] virtual const void* GetImpl() const noexcept override;
        [[nodiscard]] virtual       void* GetImpl()       noexcept override;

    private:
        std::unique_ptr<hui::ShapeImpl> impl_;
};

}

#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_SHAPE_HPP*/