#include <stdexcept>
#include <vector/Vector.hpp>

void Mephi::TransformVector(Mephi::Vector2d& Vector, const Mephi::Transform Transform,
                            const float AngleRadians) {
    float RotateAngleRadians = NAN;

    switch (Transform) {
        case Mephi::Transform::ROTATE_CLKWISE:  RotateAngleRadians = AngleRadians; break;
        case Mephi::Transform::ROTATE_CCLKWISE: RotateAngleRadians = AngleRadians; break;
        case Mephi::Transform::NONE:            return;
        default:                                throw std::overflow_error("Unknown transform mode");
    }

    float cosA = std::cos(RotateAngleRadians);
    float sinA = std::sin(RotateAngleRadians);

    Vector = Mephi::Vector2d(
        Vector.x * cosA - Vector.y * sinA,
        Vector.x * sinA + Vector.y * cosA
    );
}

void Mephi::TransformVector(Mephi::Vector3d& Vector, const Mephi::Transform Transform, 
                            Mephi::Axis Axis, const float AngleRadians) {
    float RotateAngleRadians = NAN;

    switch (Transform) {
        case Mephi::Transform::ROTATE_CLKWISE:  RotateAngleRadians = AngleRadians; break;
        case Mephi::Transform::ROTATE_CCLKWISE: RotateAngleRadians = AngleRadians; break;
        case Mephi::Transform::NONE:            return;
        default:                                throw std::overflow_error("Unknown transform mode");
    }

    float cosA = std::cos(RotateAngleRadians);
    float sinA = std::sin(RotateAngleRadians);
    float x = Vector.x, y = Vector.y, z = Vector.z;

    switch (Axis) {
        case Mephi::Axis::X:
            Vector = Mephi::Vector3d(
                x,
                y * cosA - z * sinA,
                y * sinA + z * cosA
            );
            break;

        case Mephi::Axis::Y:
            Vector = Mephi::Vector3d(
                x * cosA + z * sinA,
                y,
                -x * sinA + z * cosA
            );
            break;

        case Mephi::Axis::Z:
            Vector = Mephi::Vector3d(
                x * cosA - y * sinA,
                x * sinA + y * cosA,
                z
            );
            break;

        default:
            throw std::overflow_error("Unknown axis");
    }
}