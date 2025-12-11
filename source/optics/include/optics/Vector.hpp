#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_VECTOR_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_VECTOR_HPP

#include "dr4/math/color.hpp"
#include <cmath>
#include <sstream>
#include <string>

namespace optor
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
        [[nodiscard]] Vector2<T> Mirror(Axis axis) const noexcept;
        [[nodiscard]] Vector2<T> Clump(const Vector2<T>& minVec, 
                                       const Vector2<T>& maxVec) const;

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

typedef Vector2<float>  Vector2f;
typedef Vector2<double> Vector2d;
typedef Vector2<int>    Vector2i;

template <typename T>
T operator ^(const Vector2<T>& left, const Vector2<T>& right) noexcept {
    return left.x * right.x + left.y * right.y;
}

template <typename T>
Vector2<T> operator !(const Vector2<T>& right) {
    return Vector2<T>(right / right.Len());
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
T Vector2<T>::Len2() const noexcept {
    return (*this) ^ (*this);
}

template <typename T>
T Vector2<T>::Len() const {
    return std::sqrt(this->Len2());
}

template <typename T>
Vector2<T> Vector2<T>::Normal() const noexcept {
    return Vector2<T>(this->y, -this->x);
}

template <typename T>
Vector2<T> Vector2<T>::Mirror(Axis axis) const noexcept {
    return {
        axis == Axis::X ? -this->x : this->x,
        axis == Axis::Y ? -this->y : this->y
    };
}

template <typename T>
Vector2<T> Vector2<T>::Clump(const Vector2<T>& minVec, 
                                                      const Vector2<T>& maxVec) const {
    return {
        std::max(std::min(this->x, maxVec.x), minVec.x),
        std::max(std::min(this->y, maxVec.y), minVec.y)
    };
}

void TransformVector(Vector2d* Vector, const Transform Transform, 
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
        explicit Vector3(dr4::Color color) noexcept 
            :   x{color.r / 256.}, y{color.g / 256.}, z{color.b / 256.} 
        {};
        
        [[nodiscard]] T Len2() const noexcept;
        [[nodiscard]] T Len()  const;
        [[nodiscard]] Vector3<T> Mirror(Axis axis) const noexcept;
        [[nodiscard]] Vector3<T> Clamp(const Vector3<T>& minVec, 
                                       const Vector3<T>& maxVec) const;

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

typedef Vector3<float>  Vector3f;
typedef Vector3<double> Vector3d;
typedef Vector3<int>    Vector3i;

template <typename T>
T operator ^(const Vector3<T>& left, const Vector3<T>& right) noexcept {
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

template <typename T>
Vector3<T> operator !(const Vector3<T>& right) {
    return Vector3<T>(right / right.Len());
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
T Vector3<T>::Len2() const noexcept{
    return (*this) ^ (*this);
}

template <typename T>
T Vector3<T>::Len() const {
    return std::sqrt(this->Len2());
}

template <typename T>
Vector3<T> Vector3<T>::Mirror(Axis axis) const noexcept{
    return {
        axis == Axis::X ? -this->x : this->x,
        axis == Axis::Y ? -this->y : this->y,
        axis == Axis::Z ? -this->z : this->z
    };
}

template <typename T>
Vector3<T> Vector3<T>::Clamp(const Vector3<T>& minVec, 
                                                      const Vector3<T>& maxVec) const {
    return {
        std::max(std::min(this->x, maxVec.x), minVec.x),
        std::max(std::min(this->y, maxVec.y), minVec.y),
        std::max(std::min(this->z, maxVec.z), minVec.z)
    };
}

template <typename T>
Vector3<T> Product(const Vector3<T>& first, const Vector3<T>& second) {
    return {
        first.x * second.x,
        first.y * second.y,
        first.z * second.z
    };
}

template <typename T>
Vector3<T> Reflect(const Vector3<T>& incident, const Vector3<T>& normal) {
    return incident - 2 * (incident ^ normal) * normal;
}

void TransformVector(Vector3d* Vector, const Transform Transform, 
                     Axis Axis, const float AngleRadians = 0.01);

template <typename T>
Vector3<T> Vector3Parse(const std::string& input) {
    Vector3<T> result;
    std::stringstream ss(input);
    
    std::string trimmed = input;
    size_t start = trimmed.find_first_not_of(" \t");
    size_t end = trimmed.find_last_not_of(" \t");
    
    if (start != std::string::npos && end != std::string::npos) {
        trimmed = trimmed.substr(start, end - start + 1);
    }
    
    ss.str(trimmed);
    ss.clear();
    
    char comma1, comma2;
    
    T x, y, z;
    
    if (!(ss >> x >> comma1 >> y >> comma2 >> z)) {
        throw std::invalid_argument("Invalid input format for Vector3 parsing");
    }
    
    if ((comma1 != ',' && comma1 != ';') || (comma2 != ',' && comma2 != ';')) {
        throw std::invalid_argument("Invalid separator in Vector3 string");
    }
    
    result.x = x;
    result.y = y;
    result.z = z;
    
    return result;
}

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_VECTOR_HPP*/