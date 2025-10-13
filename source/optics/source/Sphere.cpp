#include "optics/Sphere.hpp"
#include "common/ErrorHandler.hpp"
#include "hui/RectDouble.hpp"
#include "hui/Texture.hpp"

optor::Sphere::Sphere(hui::RectDouble box, double radius)
    :   box_{std::move(box)}, 
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
    
    //TODO call update
}

const void* optor::Sphere::GetImpl() const noexcept {
    return sprite_.GetImpl();
}

void* optor::Sphere::GetImpl() noexcept {
    return sprite_.GetImpl();
}