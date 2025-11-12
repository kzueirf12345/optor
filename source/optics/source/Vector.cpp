#include <cassert>
#include <stdexcept>

#include <optics/Vector.hpp>

void optor::TransformVector(optor::Vector2d* Vector, const optor::Transform Transform,
                            const float AngleRadians) {
    assert(Vector);

    float RotateAngleRadians = NAN;

    switch (Transform) {
        case optor::Transform::ROTATE_CLKWISE:  RotateAngleRadians = AngleRadians; break;
        case optor::Transform::ROTATE_CCLKWISE: RotateAngleRadians = AngleRadians; break;
        case optor::Transform::NONE:            return;
        default:                              throw std::overflow_error("Unknown transform mode");
    }

    float cosA = std::cos(RotateAngleRadians);
    float sinA = std::sin(RotateAngleRadians);

    *Vector = optor::Vector2d(
        Vector->x * cosA - Vector->y * sinA,
        Vector->x * sinA + Vector->y * cosA
    );
}

void optor::TransformVector(optor::Vector3d* Vector, const optor::Transform Transform, 
                            optor::Axis Axis, const float AngleRadians) {
    assert(Vector);

    float RotateAngleRadians = NAN;

    switch (Transform) {
        case optor::Transform::ROTATE_CLKWISE:  RotateAngleRadians = AngleRadians; break;
        case optor::Transform::ROTATE_CCLKWISE: RotateAngleRadians = AngleRadians; break;
        case optor::Transform::NONE:            return;
        default:                              throw std::overflow_error("Unknown transform mode");
    }

    float cosA = std::cos(RotateAngleRadians);
    float sinA = std::sin(RotateAngleRadians);
    float x = Vector->x, y = Vector->y, z = Vector->z;

    switch (Axis) {
        case optor::Axis::X:
            *Vector = optor::Vector3d(
                x,
                y * cosA - z * sinA,
                y * sinA + z * cosA
            );
            break;

        case optor::Axis::Y:
            *Vector = optor::Vector3d(
                x * cosA + z * sinA,
                y,
                -x * sinA + z * cosA
            );
            break;

        case optor::Axis::Z:
            *Vector = optor::Vector3d(
                x * cosA - y * sinA,
                x * sinA + y * cosA,
                z
            );
            break;

        default:
            throw std::overflow_error("Unknown axis");
    }
}