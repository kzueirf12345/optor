#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP

#include "hui/Drawable.hpp"
#include "hui/RectDouble.hpp"
#include "hui/Sprite.hpp"
#include "hui/Texture.hpp"
#include "hui/Vector.hpp"

namespace optor 
{

class Sphere: public hui::Drawable {
    public:
        Sphere(double radius);
        Sphere(double radius, const hui::Vector2d& position);

        [[nodiscard]] virtual const void* GetImpl() const noexcept override final;
        [[nodiscard]] virtual       void* GetImpl()       noexcept override final;

        void Update();

    protected:

    private:
        hui::RectDouble box_;
        double radius_;

        hui::Texture texture_;
        hui::Sprite sprite_;
        std::vector<uint32_t> pixelBuffer_;
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP*/