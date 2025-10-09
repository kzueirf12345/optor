#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_RECT_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_RECT_HPP

#include <memory>

#include "hui/Shape.hpp"
#include "hui/Vector.hpp"

namespace hui 
{

class RectangleShapeImpl;

class RectangleShape : public hui::Shape {
    public:
         RectangleShape(const hui::Vector2d& size);
        ~RectangleShape();

        [[nodiscard]] virtual const void* GetImplAs() const noexcept override final;
        [[nodiscard]] virtual       void* GetImplAs()       noexcept override final;

    private:
        std::unique_ptr<RectangleShapeImpl> impl_;
};

}

#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_RECT_HPP*/