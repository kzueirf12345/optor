#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_RECTANGLE_SHAPE_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_RECTANGLE_SHAPE_HPP

#include <memory>

#include "hui/Shape.hpp"
#include "hui/Vector.hpp"

namespace hui 
{

class RectangleShapeImpl;

class RectangleShape : public hui::Shape {
    public:
        explicit RectangleShape(const hui::Vector2d& size);
        ~RectangleShape();

        RectangleShape           (const RectangleShape&) = delete;
        RectangleShape& operator=(const RectangleShape&) = delete;
        
        RectangleShape           (RectangleShape&& other) noexcept;
        RectangleShape& operator=(RectangleShape&& other) noexcept;

        [[nodiscard]] virtual const void* GetImpl() const noexcept override final;
        [[nodiscard]] virtual       void* GetImpl()       noexcept override final;

        [[nodiscard]] const hui::Vector2d GetSize() const;

    private:
        std::unique_ptr<RectangleShapeImpl> impl_;
};

}

#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_RECTANGLE_SHAPE_HPP*/