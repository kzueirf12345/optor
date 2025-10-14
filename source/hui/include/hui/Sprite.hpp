#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_SPRITE_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_SPRITE_HPP

#include <memory>

#include "hui/Drawable.hpp"
#include "hui/Texture.hpp"
#include "hui/Transformable.hpp"

namespace hui 
{

class SpriteImpl;

class Sprite: public hui::Drawable, public hui::Transformable {
    public:
        Sprite();
        explicit Sprite(const hui::Texture& texture);

        Sprite           (const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;
        
        Sprite           (Sprite&& other) noexcept;
        Sprite& operator=(Sprite&& other) noexcept;
        
        virtual ~Sprite();

        [[nodiscard]] virtual const void* GetImpl() const noexcept override final;
        [[nodiscard]] virtual       void* GetImpl()       noexcept override final;

        void SetTexture(const hui::Texture& texture);

        virtual void SetPosition(const hui::Vector2d& position) override final;
        virtual hui::Vector2d GetPosition() const override final;

    private:
        std::unique_ptr<SpriteImpl> impl_;
};

}



#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_SPRITE_HPP*/