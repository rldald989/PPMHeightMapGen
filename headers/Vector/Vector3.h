#pragma once

#include <string>
#include <cmath>
#include <math.h>

class Vector3
{
private:
    
public:
    Vector3(float _x, float _y, float _z);
    ~Vector3();

    float x;
    float y;
    float z;

    Vector3 operator+(const Vector3& other);
    Vector3 operator+(const float& other);
    Vector3 operator-(const Vector3& other);
    Vector3 operator-(const float& other);
    Vector3 operator*(const Vector3& other);
    Vector3 operator*(const float& other);
    Vector3 operator/(const Vector3& other);
    Vector3 operator/(const float& other);
    bool operator==(const Vector3& other) const;

    float dot(Vector3& other);
    Vector3 cross(Vector3& other);

    static Vector3 rand();
    static Vector3 sqrt(const Vector3& a);

    template <typename... Args>
    static Vector3 average(Args... args);

    static std::string to_string_f(Vector3 a);
    static std::string to_string_i(Vector3 a);
};

template <typename... Args>
inline Vector3 Vector3::average(Args... args)
{
    Vector3 sum = (args + ...); 
    return sum / sizeof...(args);
}
