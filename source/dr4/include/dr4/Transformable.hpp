#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_TRANSFORMABLE_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_TRANSFORMABLE_HPP

#include <memory>

#include "hui/Vector.hpp"

namespace hui 
{

class TransformableImpl;

class Transformable {
    public:
        Transformable();
        virtual ~Transformable();

        Transformable           (const Transformable&) = delete;
        Transformable& operator=(const Transformable&) = delete;
        
        Transformable           (Transformable&& other) noexcept;
        Transformable& operator=(Transformable&& other) noexcept;

        [[nodiscard]] virtual const void* GetImpl() const noexcept;
        [[nodiscard]] virtual       void* GetImpl()       noexcept;

        virtual void SetPosition(const hui::Vector2d& position);
        virtual hui::Vector2d GetPosition() const;
    
    private:
        std::unique_ptr<hui::TransformableImpl> impl_;
};

}

#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_TRANSFORMABLE_HPP*/