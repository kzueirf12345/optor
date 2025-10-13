#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP

#include "hui/Color.hpp"
#include "hui/Drawable.hpp"
#include "hui/RectDouble.hpp"
#include "hui/Sprite.hpp"
#include "hui/Texture.hpp"

namespace optor 
{

class Sphere: public hui::Drawable {
    public:
        Sphere(hui::RectDouble box, double radius);

        [[nodiscard]] virtual const void* GetImpl() const noexcept override final;
        [[nodiscard]] virtual       void* GetImpl()       noexcept override final;

    protected:

    private:
        hui::RectDouble box_;
        double radius_;

        hui::Texture texture_;
        hui::Sprite sprite_;
        std::vector<hui::Color> pixelBuffer_;
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP*/