#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP

#include "hui/TexturedShape.hpp"
#include "hui/Vector.hpp"

namespace optor 
{

class Sphere: public hui::TexturedShape {
    public:
        Sphere(double radius);
        Sphere(double radius, const hui::Vector3d& center);

        virtual void Update() override final;

    protected:
        hui::Vector3d center_;
        double radius_;

};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP*/