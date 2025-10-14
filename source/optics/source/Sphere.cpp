#include "optics/Sphere.hpp"
#include "common/ErrorHandler.hpp"
#include "global/Global.hpp"
#include "hui/TexturedShape.hpp"

optor::Sphere::Sphere(double radius)
    :   optor::Sphere::Sphere(radius, {0, 0, 0})
{}

optor::Sphere::Sphere(double radius, const hui::Vector3d& center)
    :   hui::TexturedShape({2*radius, 2*radius}, {center.x - radius, center.y - radius}), 
        radius_{radius},
        center_{center}
{
    ERROR_HANDLE(&optor::Sphere::Update, this);
}

void optor::Sphere::Update() {
    std::cerr << "i'm in Update sphere\n";

    for (size_t y = 0; y < (size_t)boxSize_.y; ++y) {
        for (size_t x = 0; x < (size_t)boxSize_.x; ++x) {
            if ((x - radius_) * (x - radius_) + (y - radius_) * (y - radius_) <= radius_ * radius_) {
                pixelBuffer_[y*boxSize_.x + x] = (optor::color::TextPrimary.GetInt());
            } else {
                pixelBuffer_[y*boxSize_.x + x] = (optor::color::Transparent.GetInt());
            }
        }
    }

    ERROR_HANDLE([this](){
        hui::TexturedShape::Update();
    });
}