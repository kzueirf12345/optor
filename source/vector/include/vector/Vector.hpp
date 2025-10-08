#ifndef OPTOR_SOURCE_VECTOR_INCLUDE_VECTOR_VECTOR_HPP
#define OPTOR_SOURCE_VECTOR_INCLUDE_VECTOR_VECTOR_HPP

#include <cmath>

namespace Mephi
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

        Vector2() : x{}, y{} {}
        Vector2(T x, T y) : x{x}, y{y} {}

        [[nodiscard]] T Len2() const;
        [[nodiscard]] T Len()  const;
        [[nodiscard]] Vector2<T> Normal() const;
        [[nodiscard]] Vector2<T> Mirror(Mephi::Axis axis) const;
        [[nodiscard]] Vector2<T> Clump(const Mephi::Vector2<T>& minVec, 
                                       const Mephi::Vector2<T>& maxVec) const;

        Vector2<T> operator-() const {
            return Vector2<T>(-this->x, -this->y);
        }

        Vector2<T>& operator+=(const Vector2<T>& other) {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }

        Vector2<T>& operator-=(const Vector2<T>& other) {
            this->x -= other.x;
            this->y -= other.y;
            return *this;
        }

        Vector2<T>& operator*=(T scalar) {
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

typedef Mephi::Vector2<float>  Vector2f;
typedef Mephi::Vector2<double> Vector2d;
typedef Mephi::Vector2<int>    Vector2i;

template <typename T>
T operator ^(const Mephi::Vector2<T>& left, const Mephi::Vector2<T>& right) {
    return left.x * right.x + left.y * right.y;
}

template <typename T>
Mephi::Vector2<T> operator !(const Mephi::Vector2<T>& right) {
    return Mephi::Vector2<T>(right / right.Len());
}

template <typename T>
Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right) {
    return Vector2<T>(left.x + right.x, left.y + right.y);
}

template <typename T>
Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right) {
    return Vector2<T>(left.x - right.x, left.y - right.y);
}

template <typename T>
Vector2<T> operator*(const Vector2<T>& left, T right) {
    return Vector2<T>(left.x * right, left.y * right);
}

template <typename T>
Vector2<T> operator*(T left, const Vector2<T>& right) {
    return Vector2<T>(right.x * left, right.y * left);
}

template <typename T>
Vector2<T> operator/(const Vector2<T>& left, T right) {
    return Vector2<T>(left.x / right, left.y / right);
}

template <typename T>
bool operator==(const Vector2<T>& left, const Vector2<T>& right) {
    return left.x == right.x && left.y == right.y;
}

template <typename T>
bool operator!=(const Vector2<T>& left, const Vector2<T>& right) {
    return !(left == right);
}

template <typename T>
Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right) {
    left.x += right.x;
    left.y += right.y;
    return left;
}

template <typename T>
T Mephi::Vector2<T>::Len2() const {
    return (*this) ^ (*this);
}

template <typename T>
T Mephi::Vector2<T>::Len() const {
    return std::sqrt(this->Len2());
}

template <typename T>
Mephi::Vector2<T> Mephi::Vector2<T>::Normal() const {
    return Vector2<T>(this->y, -this->x);
}

template <typename T>
Vector2<T> Mephi::Vector2<T>::Mirror(Mephi::Axis axis) const {
    return {
        axis == Mephi::Axis::X ? -this->x : this->x,
        axis == Mephi::Axis::Y ? -this->y : this->y
    };
}

template <typename T>
Vector2<T> Mephi::Vector2<T>::Clump(const Mephi::Vector2<T>& minVec, 
                                                      const Mephi::Vector2<T>& maxVec) const {
    return {
        std::max(std::min(this->x, maxVec.x), minVec.x),
        std::max(std::min(this->y, maxVec.y), minVec.y)
    };
}

void TransformVector(Mephi::Vector2d& Vector, const Mephi::Transform Transform, 
                     const float AngleRadians = 0.01);

//--------------------------------------------------------------------------------------------------

template <typename T>
class Vector3 {
    private:
    public:
        T x;
        T y;
        T z;
        Vector3(): x{}, y{}, z{} {}
        Vector3(T x, T y, T z) : x{x}, y{y}, z{z} {};
        
        [[nodiscard]] T Len2() const;
        [[nodiscard]] T Len()  const;
        [[nodiscard]] Vector3<T> Mirror(Mephi::Axis axis) const;
        [[nodiscard]] Vector3<T> Clump(const Mephi::Vector3<T>& minVec, 
                                       const Mephi::Vector3<T>& maxVec) const;

        Vector3<T> operator-() const {
            return Vector3<T>(-this->x, -this->y, -this->z);
        }

        Vector3<T>& operator+=(const Vector3<T>& other) {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
        }

        Vector3<T>& operator-=(const Vector3<T>& other) {
            this->x -= other.x;
            this->y -= other.y;
            this->z -= other.z;
            return *this;
        }

        Vector3<T>& operator*=(T scalar) {
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

typedef Mephi::Vector3<float>  Vector3f;
typedef Mephi::Vector3<double> Vector3d;
typedef Mephi::Vector3<int>    Vector3i;

template <typename T>
T operator ^(const Mephi::Vector3<T>& left, const Mephi::Vector3<T>& right) {
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

template <typename T>
Mephi::Vector3<T> operator !(const Mephi::Vector3<T>& right) {
    return Mephi::Vector3<T>(right / right.Len());
}

template <typename T>
Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right) {
    return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

template <typename T>
Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right) {
    return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

template <typename T>
Vector3<T> operator*(const Vector3<T>& left, T right) {
    return Vector3<T>(left.x * right, left.y * right, left.z * right);
}

template <typename T>
Vector3<T> operator*(T left, const Vector3<T>& right) {
    return Vector3<T>(right.x * left, right.y * left, right.z * left);
}

template <typename T>
Vector3<T> operator/(const Vector3<T>& left, T right) {
    return Vector3<T>(left.x / right, left.y / right, left.z / right);
}

template <typename T>
bool operator==(const Vector3<T>& left, const Vector3<T>& right) {
    return left.x == right.x && left.y == right.y && left.z == right.z;
}

template <typename T>
bool operator!=(const Vector3<T>& left, const Vector3<T>& right) {
    return !(left == right);
}

template <typename T>
T Mephi::Vector3<T>::Len2() const {
    return (*this) ^ (*this);
}

template <typename T>
T Mephi::Vector3<T>::Len() const {
    return std::sqrt(this->Len2());
}

template <typename T>
Vector3<T> Mephi::Vector3<T>::Mirror(Mephi::Axis axis) const {
    return {
        axis == Mephi::Axis::X ? -this->x : this->x,
        axis == Mephi::Axis::Y ? -this->y : this->y,
        axis == Mephi::Axis::Z ? -this->z : this->z
    };
}

template <typename T>
Vector3<T> Mephi::Vector3<T>::Clump(const Mephi::Vector3<T>& minVec, 
                                                      const Mephi::Vector3<T>& maxVec) const {
    return {
        std::max(std::min(this->x, maxVec.x), minVec.x),
        std::max(std::min(this->y, maxVec.y), minVec.y),
        std::max(std::min(this->z, maxVec.z), minVec.z)
    };
}

void TransformVector(Mephi::Vector3d& Vector, const Mephi::Transform Transform, 
                     Mephi::Axis Axis, const float AngleRadians = 0.01);

}

#endif /*OPTOR_SOURCE_VECTOR_INCLUDE_VECTOR_VECTOR_HPP*/