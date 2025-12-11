#include "optics/OpticObj.hpp"
#include "optics/Material.hpp"

optor::OpticObj::OpticObj()
    :   material_(),
        mustRemoved_(false)
{}

optor::OpticObj::OpticObj(const Material& material)
    :   material_(material),
        mustRemoved_(false)
{}

bool optor::OpticObj::GetMustRemoved() const {
    return mustRemoved_;
}
void optor::OpticObj::SetMustRemoved(bool mustRemoved) {
    mustRemoved_ = mustRemoved;
}