#include "optics/OpticObj.hpp"

optor::OpticObj::OpticObj() 
    :   ambientColor_{},
        diffColor_{},
        specColor_{}
{}

hui::Color optor::OpticObj::GetAmbientColor() const noexcept {
    return hui::Color(ambientColor_);
}

hui::Color optor::OpticObj::GetDiffColor() const noexcept {
    return hui::Color(diffColor_);
}

hui::Color optor::OpticObj::GetSpecColor() const noexcept {
    return hui::Color(specColor_);
}

double optor::OpticObj::GetShininess() const noexcept {
    return shininess_;
}

void optor::OpticObj::SetAmbientColor(const hui::Color& color) {
    ambientColor_ = color.GetNormalized();
}

void optor::OpticObj::SetDiffColor(const hui::Color& color) {
    diffColor_ = color.GetNormalized();
}

void optor::OpticObj::SetSpecColor(const hui::Color& color) {
    specColor_ = color.GetNormalized();
}

void optor::OpticObj::SetShininess(const double shininess) {
    shininess_ = shininess;
}