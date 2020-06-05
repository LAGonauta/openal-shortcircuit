#include <cmath>

#include "OpenALAPI.h"

class Vector3
{
private:
    Vector3 operator-(const Vector3 &rhs) const noexcept;

public:
    ALfloat X;
    ALfloat Y;
    ALfloat Z;

    ALfloat Length() const noexcept;
    ALfloat CalculateDistance(const Vector3 &pos) const noexcept;

    void SetValue(ALfloat X, ALfloat Y, ALfloat Z);
};