#ifndef MATH_3D_H
#define MATH_3D_H

#include <glm/glm.hpp>

struct PersProjInfo
{
    float fov; // field of view
    float width;
    float height;
    float zNear;
    float zFar;

};

class Matrix4f {
public:
    static glm::mat4 InitPersProjTransform(const PersProjInfo& p);
};

struct Vector3f {
    union {
        float x;
        float r;
    };

    union {
        float y;
        float g;
    };

    union {
        float z;
        float b;
    };

    Vector3f() {}

    Vector3f(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Vector3f(const float* pFloat)
    {
        x = pFloat[0];
        y = pFloat[1];
        z = pFloat[2];
    }

    float Length() const
    {
        float len = sqrtf(x * x + y * y + z * z);
        return len;
    }

    Vector3f Cross(const Vector3f& v) const;

    Vector3f& Normalize();
    void Rotate(float Angle, const Vector3f& Axis);
};

struct Quaternion
{
    float x, y, z, w;

    Quaternion(float Angle, const Vector3f& V);

    Quaternion(float _x, float _y, float _z, float _w);

    void Normalize();

    Quaternion Conjugate() const;

    Vector3f ToDegrees();
};


Quaternion operator*(const Quaternion& l, const Quaternion& r);

Quaternion operator*(const Quaternion& q, const Vector3f& v);
#endif