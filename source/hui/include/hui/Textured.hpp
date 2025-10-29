#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_TEXTURED_SHAPE_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_TEXTURED_SHAPE_HPP

#include "hui/Drawable.hpp"
#include "hui/Transformable.hpp"
#include "hui/Vector.hpp"
#include "hui/Texture.hpp"
#include "hui/Sprite.hpp"

namespace hui 
{

class Textured: public hui::Drawable, public hui::Transformable {
    public:
        explicit Textured(const hui::Vector2d& boxSize);
        Textured(const hui::Vector2d& boxSize, const hui::Vector2d& position);

        virtual ~Textured();

        [[nodiscard]] virtual const void* GetImpl() const noexcept override final;
        [[nodiscard]] virtual       void* GetImpl()       noexcept override final;

        virtual void Update();

        virtual void SetPosition(const hui::Vector2d& position) override final;
        virtual hui::Vector2d GetPosition() const override final;

    protected:
        hui::Vector2d boxSize_;

        hui::Texture texture_;
        hui::Sprite sprite_;
        std::vector<uint32_t> pixelBuffer_;

    private:
};

}

#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_TEXTURED_SHAPE_HPP*/