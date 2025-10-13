#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_SPRITE_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_SPRITE_HPP

#include <memory>

#include "hui/Drawable.hpp"
#include "hui/Texture.hpp"

namespace hui 
{

class SpriteImpl;

class Sprite: public hui::Drawable {
    public:
        Sprite();
        explicit Sprite(const hui::Texture& texture);

        Sprite           (const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;
        
        Sprite           (Sprite&& other) noexcept;
        Sprite& operator=(Sprite&& other) noexcept;
        
        virtual ~Sprite();

        [[nodiscard]] virtual const void* GetImpl() const noexcept;
        [[nodiscard]] virtual       void* GetImpl()       noexcept;

        void SetTexture(const hui::Texture& texture);

    private:
        std::unique_ptr<SpriteImpl> impl_;
};

}



#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_SPRITE_HPP*/