#pragma once

#include <string>

class Vector2
{
private:
    
public:
    Vector2(float x, float y);
    ~Vector2();

    float m_x;
    float m_y;

    Vector2 operator+(const Vector2& other);
    Vector2 operator-(const Vector2& other);
    Vector2 operator*(const Vector2& other);
    Vector2 operator/(const Vector2& other);

    float dot(const Vector2& other);
    float det(Vector2& other);

    static std::string to_string(Vector2 a);
};