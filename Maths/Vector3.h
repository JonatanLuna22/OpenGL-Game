#pragma once
#include <corecrt_math.h>
class Vector3
{
public:
    float x, y, z;
    Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } { }

    bool operator==(const Vector3& other) const {
        // fix the equal operator implementation
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vector3& other) const {
        // fix the equal operator implementation
        return x != other.x || y != other.y || z != other.z;
    }

    Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    float magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }

    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }
};
