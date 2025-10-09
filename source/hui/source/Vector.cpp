#include <stdexcept>

#include <hui/Vector.hpp>

void hui::TransformVector(hui::Vector2d& Vector, const hui::Transform Transform,
                            const float AngleRadians) {
    float RotateAngleRadians = NAN;

    switch (Transform) {
        case hui::Transform::ROTATE_CLKWISE:  RotateAngleRadians = AngleRadians; break;
        case hui::Transform::ROTATE_CCLKWISE: RotateAngleRadians = AngleRadians; break;
        case hui::Transform::NONE:            return;
        default:                              throw std::overflow_error("Unknown transform mode");
    }

    float cosA = std::cos(RotateAngleRadians);
    float sinA = std::sin(RotateAngleRadians);

    Vector = hui::Vector2d(
        Vector.x * cosA - Vector.y * sinA,
        Vector.x * sinA + Vector.y * cosA
    );
}

void hui::TransformVector(hui::Vector3d& Vector, const hui::Transform Transform, 
                            hui::Axis Axis, const float AngleRadians) {
    float RotateAngleRadians = NAN;

    switch (Transform) {
        case hui::Transform::ROTATE_CLKWISE:  RotateAngleRadians = AngleRadians; break;
        case hui::Transform::ROTATE_CCLKWISE: RotateAngleRadians = AngleRadians; break;
        case hui::Transform::NONE:            return;
        default:                              throw std::overflow_error("Unknown transform mode");
    }

    float cosA = std::cos(RotateAngleRadians);
    float sinA = std::sin(RotateAngleRadians);
    float x = Vector.x, y = Vector.y, z = Vector.z;

    switch (Axis) {
        case hui::Axis::X:
            Vector = hui::Vector3d(
                x,
                y * cosA - z * sinA,
                y * sinA + z * cosA
            );
            break;

        case hui::Axis::Y:
            Vector = hui::Vector3d(
                x * cosA + z * sinA,
                y,
                -x * sinA + z * cosA
            );
            break;

        case hui::Axis::Z:
            Vector = hui::Vector3d(
                x * cosA - y * sinA,
                x * sinA + y * cosA,
                z
            );
            break;

        default:
            throw std::overflow_error("Unknown axis");
    }
}