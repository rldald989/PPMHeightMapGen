#pragma once

#include <string>
#include <cmath>

class Vector2
{
private:
    
public:
    Vector2(float x, float y);
    ~Vector2();

    float m_x;
    float m_y;

    Vector2 operator+(const Vector2& other);
    Vector2 operator+(const float& other);
    Vector2 operator-(const Vector2& other);
    Vector2 operator*(const Vector2& other);
    Vector2 operator/(const Vector2& other);
    bool operator==(const Vector2& other);

    float dot(const Vector2& other);
    float det(Vector2& other);

    static float distance(const Vector2& a, const Vector2&b);
    static float atan(const Vector2& a, const Vector2& b);

    static std::string to_string(Vector2 a);
};