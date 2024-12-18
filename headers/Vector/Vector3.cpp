#include "Vector3.h"

Vector3::Vector3(float _x, float _y, float _z): x(_x), y(_y), z(_z)
{
}

Vector3::~Vector3()
{
}

Vector3 Vector3::operator+(const Vector3 &other)
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator+(const float& other)
{
    return Vector3(x + other, y + other, z + other);
}

Vector3 Vector3::operator-(const Vector3 &other)
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator-(const float &other)
{
    return Vector3(x - other, y - other, z - other);
}

Vector3 Vector3::operator*(const Vector3 &other)
{
    return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator*(const float &other)
{
    return Vector3(x * other, y * other, z * other);
}

Vector3 Vector3::operator/(const Vector3 &other)
{
    return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator/(const float& other)
{
    return Vector3(x / other, y / other, z / other);
}

bool Vector3::operator==(const Vector3 &other) const
{
    return (x == other.x && y == other.y && z == other.z);
}

float Vector3::dot(Vector3 &other)
{
    return (x * other.x) + (y * other.y) + (z * other.z);
}

Vector3 Vector3::cross(Vector3 &other)
{
    return Vector3(
        (y * other.z) - (other.y * z), 
        (z * other.x) - (other.z * x),
        (x * other.y) - (other.x - y)
    );
}

Vector3 Vector3::rand()
{
    return Vector3(float(std::rand() % 100)/ 100, float(std::rand() % 100)/ 100, float(std::rand() % 100)/ 100);
}

Vector3 Vector3::sqrt(const Vector3 &a)
{
    return Vector3(sqrtf(a.x), sqrtf(a.y), sqrtf(a.z));
}

std::string Vector3::to_string_f(Vector3 a)
{
    return std::string(std::to_string(a.x) + " " + std::to_string(a.y) + " " + std::to_string(a.z));
}

std::string Vector3::to_string_i(Vector3 a)
{
    return std::string(std::to_string((int)a.x) + " " + std::to_string((int)a.y) + " " + std::to_string((int)a.z));
}