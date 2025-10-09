#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_DRAWABLE_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_DRAWABLE_HPP

#include <memory>

#include <SFML/Graphics/Shape.hpp>

namespace hui 
{

class DrawableImpl;

class Drawable {
    public:
        Drawable();
        virtual ~Drawable();

        [[nodiscard]] virtual const void* GetImplAs() const noexcept;
        [[nodiscard]] virtual       void* GetImplAs()       noexcept;
    
    private:
        std::unique_ptr<hui::DrawableImpl> impl_;
};

}

#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_DRAWABLE_HPP*/