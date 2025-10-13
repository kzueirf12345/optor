#include "optics/Sphere.hpp"
#include "common/ErrorHandler.hpp"
#include "global/Global.hpp"
#include "hui/RectDouble.hpp"
#include "hui/Texture.hpp"

optor::Sphere::Sphere(double radius)
    :   optor::Sphere::Sphere(radius, {0, 0})
{}

optor::Sphere::Sphere(double radius, const hui::Vector2d& position)
    :   box_{{2*radius, 2*radius}, position}, 
        radius_{radius},
        texture_(ERROR_HANDLE([this](){
            return hui::Texture(box_.GetSize());
        })),
        pixelBuffer_(box_.GetWidth() * box_.GetHeight()),
        sprite_{}
{

    ERROR_HANDLE([this](){
        sprite_.SetTexture(texture_);
    });
    
    ERROR_HANDLE(&optor::Sphere::Update, this);
}

const void* optor::Sphere::GetImpl() const noexcept {
    return sprite_.GetImpl();
}

void* optor::Sphere::GetImpl() noexcept {
    return sprite_.GetImpl();
}

void optor::Sphere::Update() {
    
    for (size_t y = 0; y < (size_t)box_.GetHeight(); ++y) {
        for (size_t x = 0; x < (size_t)box_.GetWidth(); ++x) {
            if (x*x + y *y <= radius_ * radius_) {
                pixelBuffer_[y*box_.GetWidth() + x] = (optor::color::TextPrimary.GetInt());
            } else {
                pixelBuffer_[y*box_.GetWidth() + x] = (optor::color::Transparent.GetInt());
            }
        }
    }

    ERROR_HANDLE([this](){
        texture_.Update(pixelBuffer_);
    });
}