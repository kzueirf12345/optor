#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_DRAWABLE_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_DRAWABLE_HPP

#include <memory>

namespace hui 
{

class DrawableImpl;

class Drawable {
    public:
        virtual ~Drawable();

        template<typename T>
        [[nodiscard]] const T* GetImplAs() const noexcept;
        
        template<typename T>
        [[nodiscard]]       T* GetImplAs()       noexcept;
    
    private:
        std::unique_ptr<hui::DrawableImpl> impl_;
};

}

#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_DRAWABLE_HPP*/