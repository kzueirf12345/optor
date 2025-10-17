#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_CAMERA_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_CAMERA_HPP

#include "hui/Vector.hpp"

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
        explicit Camera(const hui::Vector3d& position = hui::Vector3d(0, 0, 0), 
                        const hui::Vector3d& target   = hui::Vector3d(0, 0, -1),
                        double fov = 90.0);

        virtual ~Camera() = default;

        void Move  (  MoveDirection direction, double speed);
        void Rotate(RotateDirection direction, double speed);

        void SetPosition(const hui::Vector3d& position) noexcept;
        void SetYaw     (double yaw)                    noexcept;
        void SetPitch   (double pitch)                  noexcept;
        void SetFov     (double fov)                    noexcept;

        [[nodiscard]] hui::Vector3d GetPosition() const noexcept;
        [[nodiscard]] hui::Vector3d GetFront()    const noexcept;
        [[nodiscard]] hui::Vector3d GetRight()    const noexcept;
        [[nodiscard]] hui::Vector3d GetUp()       const noexcept;
        [[nodiscard]] double        GetYaw()      const noexcept;
        [[nodiscard]] double        GetPitch()    const noexcept;
        [[nodiscard]] double        GetFov()      const noexcept;

        [[nodiscard]] hui::Vector3d GetRay(const hui::Vector2d& pixel, const hui::Vector2d& screenSize) const;
    
    private:
        void UpdateVectors();

        hui::Vector3d position_;
        
        hui::Vector3d front_;
        hui::Vector3d up_;
        hui::Vector3d right_;
        hui::Vector3d worldUp_;
        
        double yaw_;
        double pitch_;
        double fov_; 
    };

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_CAMERA_HPP*/