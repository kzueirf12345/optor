#include <cmath>

#include "optics/Camera.hpp"
#include "common/ErrorHandler.hpp"
#include "hui/Vector.hpp"
#include "common/Utils.hpp"

namespace 
{
    constexpr double INIT_YAW   = -90.0;
    constexpr double INIT_PITCH = 0.0;
    constexpr double MAX_PITCH  = 89.0;
    constexpr double MIN_PITCH  = -89.0;
}

optor::Camera::Camera(const hui::Vector3d& position, const hui::Vector3d& target, double fov)
    :   position_{position}, 
        front_{hui::Vector3d(0, 0, -1)}, 
        up_{hui::Vector3d(0, 1, 0)}, 
        right_{hui::Vector3d(1, 0, 0)}, 
        worldUp_{hui::Vector3d(0, 1, 0)},
        yaw_{INIT_YAW},
        pitch_{INIT_PITCH},
        fov_{fov}
{
    if (target != front_) {
        front_ = !(target - position_);
        ERROR_HANDLE(&optor::Camera::UpdateVectors, this);
    }
}

void optor::Camera::Move(MoveDirection direction, double speed) {
    switch (direction) {
        case MoveDirection::FORWARD:
            position_ += front_ * speed;
            break;
        case MoveDirection::BACKWARD:
            position_ -= front_ * speed;
            break;
        case MoveDirection::LEFT:
            position_ -= right_ * speed;
            break;
        case MoveDirection::RIGHT:
            position_ += right_ * speed;
            break;
        case MoveDirection::UP:
            position_ += worldUp_ * speed;
            break;
        case MoveDirection::DOWN:
            position_ -= worldUp_ * speed;
            break;
    }
}

void optor::Camera::Rotate(RotateDirection direction, double speed) {

    switch (direction) {
        case RotateDirection::LEFT:
            yaw_ -= speed;
            break;
        case RotateDirection::RIGHT:
            yaw_ += speed;
            break;
        case RotateDirection::UP:
            pitch_ += speed;
            break;
        case RotateDirection::DOWN:
            pitch_ -= speed;
            break;
    }

    pitch_ = std::clamp(pitch_, MIN_PITCH, MAX_PITCH);

    ERROR_HANDLE(&optor::Camera::UpdateVectors, this);
}

void optor::Camera::SetPosition(const hui::Vector3d& position) noexcept {
    position_ = position;
}

void optor::Camera::SetYaw(double yaw) noexcept {
    yaw_ = yaw;
    ERROR_HANDLE(&optor::Camera::UpdateVectors, this);
}

void optor::Camera::SetPitch(double pitch) noexcept {
    pitch_ = pitch;
    ERROR_HANDLE(&optor::Camera::UpdateVectors, this);
}

void optor::Camera::SetFov(double fov) noexcept {
    fov_ = fov;
}

hui::Vector3d optor::Camera::GetPosition() const noexcept {
    return position_;
}

hui::Vector3d optor::Camera::GetFront() const noexcept {
    return front_;
}

hui::Vector3d optor::Camera::GetRight() const noexcept {
    return right_;
}

hui::Vector3d optor::Camera::GetUp() const noexcept {
    return up_;
}

double optor::Camera::GetYaw() const noexcept {
    return yaw_;
}

double optor::Camera::GetPitch() const noexcept {
    return pitch_;
}

double optor::Camera::GetFov() const noexcept {
    return fov_;
}

hui::Vector3d optor::Camera::GetRay(const hui::Vector2d& pixel, const hui::Vector2d& screenSize) const {
    double normalizedX = (2.0 * pixel.x) / screenSize.x - 1.0;
    double normalizedY = 1.0 - (2.0 * pixel.y) / screenSize.y;
    
    double aspectRatio = screenSize.x / screenSize.y;
    
    double scale = std::tan(common::Deg2Rad(fov_ / 2.0));
    
    hui::Vector3d rayDirection;
    rayDirection.x = normalizedX * aspectRatio * scale;
    rayDirection.y = normalizedY * scale;
    rayDirection.z = -1.0;
    
    hui::Vector3d worldRayDirection = 
        right_ * rayDirection.x + 
        up_    * rayDirection.y + 
        front_ * rayDirection.z;
    
    return !worldRayDirection;
}

void optor::Camera::UpdateVectors() {
    hui::Vector3d newFront;
    newFront.x = std::cos(common::Deg2Rad(yaw_)) * std::cos(common::Deg2Rad(pitch_));
    newFront.y = std::sin(common::Deg2Rad(pitch_));
    newFront.z = std::sin(common::Deg2Rad(yaw_)) * std::cos(common::Deg2Rad(pitch_));
    
    front_ = !newFront;
    
    right_ = !(front_ * worldUp_);
    up_    = !(right_ * front_);
}