#include "ogldev_math_3d.h"


glm::mat4 Matrix4f::InitPersProjTransform(const PersProjInfo& p)
{
    float ar = p.height / p.width; // aspect ratio
    float zRange = p.zNear - p.zFar;
    float tanHalfFOV = tanf(glm::radians(p.fov / 2.0f));

    glm::mat4 m = glm::mat4();
    m[0][0] = 1 / tanHalfFOV; m[1][0] = 0.0f;                     m[2][0] = 0.0f;                         m[3][0] = 0.0f;
    m[0][1] = 0.0f;           m[1][1] = 1.0f / (tanHalfFOV * ar); m[2][1] = 0.0f;                         m[3][1] = 0.0f;
    m[0][2] = 0.0f;           m[1][2] = 0.0f;                     m[2][2] = (-p.zNear - p.zFar) / zRange; m[3][2] = 2.0f * p.zFar * p.zNear / zRange;
    m[0][3] = 0.0f;           m[1][3] = 0.0f;                     m[2][3] = 1.0f;                         m[3][3] = 0.0f;

#ifdef USE_GLM
    glm::mat4 Projection = glm::perspectiveFovLH(glm::radians(p.FOV), p.Width, p.Height, p.zNear, p.zFar);

    m[0][0] = Projection[0][0]; m[0][1] = Projection[1][0]; m[0][2] = Projection[2][0]; m[0][3] = Projection[3][0];
    m[1][0] = Projection[0][1]; m[1][1] = Projection[1][1]; m[1][2] = Projection[2][1]; m[1][3] = Projection[3][1];
    m[2][0] = Projection[0][2]; m[2][1] = Projection[1][2]; m[2][2] = Projection[2][2]; m[2][3] = Projection[3][2];
    m[3][0] = Projection[0][3]; m[3][1] = Projection[1][3]; m[3][2] = Projection[2][3]; m[3][3] = Projection[3][3];
#endif

    return m;
}

Vector3f Vector3f::Cross(const Vector3f& v) const
{
    const float _x = y * v.z - z * v.y;
    const float _y = z * v.x - x * v.z;
    const float _z = x * v.y - y * v.x;

    return Vector3f(_x, _y, _z);
}

Vector3f& Vector3f::Normalize()
{
    float len = Length();

    assert(len != 0);

    x /= len;
    y /= len;
    z /= len;

    return *this;
}

void Vector3f::Rotate(float angle, const Vector3f& v)
{
    Quaternion RotationQ(angle, v);

    Quaternion ConjugateQ = RotationQ.Conjugate();

    Quaternion W = RotationQ * (*this) * ConjugateQ;

    x = W.x;
    y = W.y;
    z = W.z;
}

Quaternion::Quaternion(float Angle, const Vector3f& V)
{
    float HalfAngleInRadians = glm::radians(Angle / 2);

    float SineHalfAngle = sinf(HalfAngleInRadians);
    float CosHalfAngle = cosf(HalfAngleInRadians);

    x = V.x * SineHalfAngle;
    y = V.y * SineHalfAngle;
    z = V.z * SineHalfAngle;
    w = CosHalfAngle;
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

void Quaternion::Normalize()
{
    float Length = sqrtf(x * x + y * y + z * z + w * w);

    x /= Length;
    y /= Length;
    z /= Length;
    w /= Length;
}


Quaternion Quaternion::Conjugate() const
{
    Quaternion ret(-x, -y, -z, w);
    return ret;
}


Quaternion operator*(const Quaternion& q, const Vector3f& v)
{
    float w = -(q.x * v.x) - (q.y * v.y) - (q.z * v.z);
    float x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
    float y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
    float z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

    Quaternion ret(x, y, z, w);

    return ret;
}


Quaternion operator*(const Quaternion& l, const Quaternion& r)
{
    float w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
    float x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
    float y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
    float z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);

    Quaternion ret(x, y, z, w);

    return ret;
}

Vector3f Quaternion::ToDegrees()
{
    float f[3];

    f[0] = atan2(x * z + y * w, x * w - y * z);
    f[1] = acos(-x * x - y * y - z * z - w * w);
    f[2] = atan2(x * z - y * w, x * w + y * z);

    f[0] = glm::degrees(f[0]);
    f[1] = glm::degrees(f[1]);
    f[2] = glm::degrees(f[2]);

    return Vector3f(f);
}