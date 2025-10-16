#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_VECTOR_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_VECTOR_HPP

#include <cmath>

namespace hui
{

enum class Axis {
    X = 0,
    Y = 1,
    Z = 2
};

enum Transform {
    NONE            = 0,
    ROTATE_CLKWISE  = 1,
    ROTATE_CCLKWISE = 2,
};

//--------------------------------------------------------------------------------------------------

template <typename T>
class Vector2 {
    private:
    public:
        T x;
        T y;

        Vector2() noexcept : x{}, y{} {}
        Vector2(T x, T y) noexcept : x{x}, y{y} {}

        [[nodiscard]] T Len2() const noexcept;
        [[nodiscard]] T Len()  const;
        [[nodiscard]] Vector2<T> Normal() const noexcept;
        [[nodiscard]] Vector2<T> Mirror(hui::Axis axis) const noexcept;
        [[nodiscard]] Vector2<T> Clump(const hui::Vector2<T>& minVec, 
                                       const hui::Vector2<T>& maxVec) const;

        Vector2<T> operator-() const noexcept {
            return Vector2<T>(-this->x, -this->y);
        }

        Vector2<T>& operator+=(const Vector2<T>& other) noexcept {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }

        Vector2<T>& operator-=(const Vector2<T>& other) noexcept {
            this->x -= other.x;
            this->y -= other.y;
            return *this;
        }

        Vector2<T>& operator*=(T scalar) noexcept {
            this->x *= scalar;
            this->y *= scalar;
            return *this;
        }

        Vector2<T>& operator/=(T scalar) {
            this->x /= scalar;
            this->y /= scalar;
            return *this;
        }
};

typedef hui::Vector2<float>  Vector2f;
typedef hui::Vector2<double> Vector2d;
typedef hui::Vector2<int>    Vector2i;

template <typename T>
T operator ^(const hui::Vector2<T>& left, const hui::Vector2<T>& right) noexcept {
    return left.x * right.x + left.y * right.y;
}

template <typename T>
hui::Vector2<T> operator !(const hui::Vector2<T>& right) {
    return hui::Vector2<T>(right / right.Len());
}

template <typename T>
Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right) noexcept {
    return Vector2<T>(left.x + right.x, left.y + right.y);
}

template <typename T>
Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right) noexcept {
    return Vector2<T>(left.x - right.x, left.y - right.y);
}

template <typename T>
Vector2<T> operator*(const Vector2<T>& left, T right) noexcept{
    return Vector2<T>(left.x * right, left.y * right);
}

template <typename T>
Vector2<T> operator*(T left, const Vector2<T>& right) noexcept {
    return Vector2<T>(right.x * left, right.y * left);
}

template <typename T>
Vector2<T> operator/(const Vector2<T>& left, T right) {
    return Vector2<T>(left.x / right, left.y / right);
}

template <typename T>
bool operator==(const Vector2<T>& left, const Vector2<T>& right) noexcept {
    return left.x == right.x && left.y == right.y;
}

template <typename T>
bool operator!=(const Vector2<T>& left, const Vector2<T>& right) noexcept {
    return !(left == right);
}

template <typename T>
Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right) noexcept {
    left.x += right.x;
    left.y += right.y;
    return left;
}

template <typename T>
T hui::Vector2<T>::Len2() const noexcept {
    return (*this) ^ (*this);
}

template <typename T>
T hui::Vector2<T>::Len() const {
    return std::sqrt(this->Len2());
}

template <typename T>
hui::Vector2<T> hui::Vector2<T>::Normal() const noexcept {
    return Vector2<T>(this->y, -this->x);
}

template <typename T>
Vector2<T> hui::Vector2<T>::Mirror(hui::Axis axis) const noexcept {
    return {
        axis == hui::Axis::X ? -this->x : this->x,
        axis == hui::Axis::Y ? -this->y : this->y
    };
}

template <typename T>
Vector2<T> hui::Vector2<T>::Clump(const hui::Vector2<T>& minVec, 
                                                      const hui::Vector2<T>& maxVec) const {
    return {
        std::max(std::min(this->x, maxVec.x), minVec.x),
        std::max(std::min(this->y, maxVec.y), minVec.y)
    };
}

void TransformVector(hui::Vector2d* Vector, const hui::Transform Transform, 
                     const float AngleRadians = 0.01);

//--------------------------------------------------------------------------------------------------

template <typename T>
class Vector3 {
    private:
    public:
        T x;
        T y;
        T z;
        Vector3() noexcept: x{}, y{}, z{} {}
        Vector3(T x, T y, T z) noexcept : x{x}, y{y}, z{z} {};
        
        [[nodiscard]] T Len2() const noexcept;
        [[nodiscard]] T Len()  const;
        [[nodiscard]] Vector3<T> Mirror(hui::Axis axis) const noexcept;
        [[nodiscard]] Vector3<T> Clump(const hui::Vector3<T>& minVec, 
                                       const hui::Vector3<T>& maxVec) const;

        Vector3<T> operator-() const noexcept{
            return Vector3<T>(-this->x, -this->y, -this->z);
        }

        Vector3<T>& operator+=(const Vector3<T>& other) noexcept {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
        }

        Vector3<T>& operator-=(const Vector3<T>& other) noexcept {
            this->x -= other.x;
            this->y -= other.y;
            this->z -= other.z;
            return *this;
        }

        Vector3<T>& operator*=(T scalar) noexcept {
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
            return *this;
        }

        Vector3<T>& operator/=(T scalar) {
            this->x /= scalar;
            this->y /= scalar;
            this->z /= scalar;
            return *this;
        }
};

typedef hui::Vector3<float>  Vector3f;
typedef hui::Vector3<double> Vector3d;
typedef hui::Vector3<int>    Vector3i;

template <typename T>
T operator ^(const hui::Vector3<T>& left, const hui::Vector3<T>& right) noexcept {
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

template <typename T>
hui::Vector3<T> operator !(const hui::Vector3<T>& right) {
    return hui::Vector3<T>(right / right.Len());
}

template <typename T>
Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right) noexcept {
    return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

template <typename T>
Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right) noexcept {
    return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

template <typename T>
Vector3<T> operator*(const Vector3<T>& left, T right) noexcept {
    return Vector3<T>(left.x * right, left.y * right, left.z * right);
}

template <typename T>
Vector3<T> operator*(T left, const Vector3<T>& right) noexcept {
    return Vector3<T>(right.x * left, right.y * left, right.z * left);
}

template <typename T>
Vector3<T> operator/(const Vector3<T>& left, T right) {
    return Vector3<T>(left.x / right, left.y / right, left.z / right);
}

template <typename T>
bool operator==(const Vector3<T>& left, const Vector3<T>& right) noexcept {
    return left.x == right.x && left.y == right.y && left.z == right.z;
}

template <typename T>
bool operator!=(const Vector3<T>& left, const Vector3<T>& right) noexcept {
    return !(left == right);
}

template <typename T>
Vector3<T> operator*(const Vector3<T>& left, const Vector3<T>& right) noexcept {
    return Vector3<T>(
        left.y * right.z - left.z * right.y,
        left.z * right.x - left.x * right.z,  
        left.x * right.y - left.y * right.x
    );
}

template <typename T>
T hui::Vector3<T>::Len2() const noexcept{
    return (*this) ^ (*this);
}

template <typename T>
T hui::Vector3<T>::Len() const {
    return std::sqrt(this->Len2());
}

template <typename T>
Vector3<T> hui::Vector3<T>::Mirror(hui::Axis axis) const noexcept{
    return {
        axis == hui::Axis::X ? -this->x : this->x,
        axis == hui::Axis::Y ? -this->y : this->y,
        axis == hui::Axis::Z ? -this->z : this->z
    };
}

template <typename T>
Vector3<T> hui::Vector3<T>::Clump(const hui::Vector3<T>& minVec, 
                                                      const hui::Vector3<T>& maxVec) const {
    return {
        std::max(std::min(this->x, maxVec.x), minVec.x),
        std::max(std::min(this->y, maxVec.y), minVec.y),
        std::max(std::min(this->z, maxVec.z), minVec.z)
    };
}

void TransformVector(hui::Vector3d* Vector, const hui::Transform Transform, 
                     hui::Axis Axis, const float AngleRadians = 0.01);

}

#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_VECTOR_HPP*/