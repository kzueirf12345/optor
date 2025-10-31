#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_DRAWABLE_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_DRAWABLE_HPP

#include <memory>

namespace hui 
{

class DrawableImpl;

class Drawable {
    public:
        Drawable();
        virtual ~Drawable();

        Drawable           (const Drawable&) = delete;
        Drawable& operator=(const Drawable&) = delete;
        
        Drawable           (Drawable&& other) noexcept;
        Drawable& operator=(Drawable&& other) noexcept;

        [[nodiscard]] virtual const void* GetImpl() const noexcept;
        [[nodiscard]] virtual       void* GetImpl()       noexcept;
    
    private:
        std::unique_ptr<hui::DrawableImpl> impl_;
};

}

#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_DRAWABLE_HPP*/