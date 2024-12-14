#include "Vector2.h"

Vector2::Vector2(float x, float y) : m_x(x), m_y(y)
{

}

Vector2::~Vector2()
{

}

Vector2 Vector2::operator+(const Vector2 &other)
{
    return Vector2(m_x + other.m_x, m_y + other.m_y);
}

Vector2 Vector2::operator-(const Vector2 &other)
{
    return Vector2(m_x - other.m_x, m_y - other.m_y);
}

Vector2 Vector2::operator*(const Vector2 &other)
{
    return Vector2(m_x * other.m_x, m_y * other.m_y);
}

Vector2 Vector2::operator/(const Vector2 &other)
{
    return Vector2(m_x / other.m_x, m_y / other.m_y);
}

float Vector2::dot(const Vector2 &other)
{
    return (m_x * other.m_x) + (m_y * other.m_y);
}

float Vector2::det(Vector2 &other)
{
    return (m_x * other.m_x) - (m_y * other.m_y);
}

std::string Vector2::to_string(Vector2 a)
{
    return std::string(std::to_string(a.m_x) + " " + std::to_string(a.m_y));
}