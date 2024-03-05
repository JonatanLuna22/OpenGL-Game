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
   
    inline Vector3 Normalized() const {
        float mag = magnitude();
        return Vector3(x/mag, y / mag, z / mag);
    }

    static Vector3 Cross(Vector3& a, Vector3& b) {
        return Vector3(a.y * b.z - a.z * b.y,
                       a.z * b.x - a.x * b.z,
                       a.x * b.y - a.y * b.x);
    }

    static float Distance(const Vector3& a, const Vector3& b) {
        return sqrt((a.x - b.x) * (a.x - b.x) +
            (a.y - b.y) * (a.y - b.y) +
            (a.z - b.z) * (a.z - b.z));
    }

    static float Dot(const Vector3& a, const Vector3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

 
    
};
