#include "Vector3.hpp"

ALfloat Vector3::Length() const noexcept
{
    return std::sqrt(X*X + Y*Y + Z*Z);
}

ALfloat Vector3::CalculateDistance(const Vector3 &pos) const noexcept
{
    return (pos - *this).Length();
}

Vector3 Vector3::operator-(const Vector3 &rhs) const noexcept
{
    return Vector3{ X - rhs.X, Y - rhs.Y, Z - rhs.Z };
}

void Vector3::SetValue(ALfloat X, ALfloat Y, ALfloat Z)
{
    this->X = X;
    this->Y = Y;
    this->Z = Z;
}