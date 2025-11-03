#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_CAMERA_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_CAMERA_HPP

#include "dr4/math/vec2.hpp"
#include "optics/Vector.hpp"

namespace optor
{

enum class MoveDirection {
    UNKNOWN = -1,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum class RotateDirection {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
    public:
        explicit Camera(const optor::Vector3d& position = optor::Vector3d(0, 0, 0), 
                        const optor::Vector3d& target   = optor::Vector3d(0, 0, -1),
                        double fov = 90.0);

        virtual ~Camera() = default;

        void Move  (  MoveDirection direction, double speed);
        void Rotate(RotateDirection direction, double speed);

        void SetPosition(const optor::Vector3d& position) noexcept;
        void SetYaw     (double yaw)                    noexcept;
        void SetPitch   (double pitch)                  noexcept;
        void SetFov     (double fov)                    noexcept;

        [[nodiscard]] optor::Vector3d GetPosition() const noexcept;
        [[nodiscard]] optor::Vector3d GetFront()    const noexcept;
        [[nodiscard]] optor::Vector3d GetRight()    const noexcept;
        [[nodiscard]] optor::Vector3d GetUp()       const noexcept;
        [[nodiscard]] double        GetYaw()      const noexcept;
        [[nodiscard]] double        GetPitch()    const noexcept;
        [[nodiscard]] double        GetFov()      const noexcept;

        [[nodiscard]] optor::Vector3d GetRay(const optor::Vector2d& pixel, const dr4::Vec2f& screenSize) const;
    
    private:
        void UpdateVectors();

        optor::Vector3d position_;
        
        optor::Vector3d front_;
        optor::Vector3d up_;
        optor::Vector3d right_;
        optor::Vector3d worldUp_;
        
        double yaw_;
        double pitch_;
        double fov_; 
    };

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_CAMERA_HPP*/