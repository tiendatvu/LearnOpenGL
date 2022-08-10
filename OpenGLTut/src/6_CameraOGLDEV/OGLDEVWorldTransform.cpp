#include "OGLDEVWorldTransform.h"

void OGLDEVWorldTransform::SetScale(float scale) {
    m_scale = scale;
}

void OGLDEVWorldTransform::SetRotation(float x, float y, float z) {
    m_rotation.x = x;
    m_rotation.y = y;
    m_rotation.z = z;
}

void OGLDEVWorldTransform::SetPosition(float x, float y, float z) {
    m_pos.x = x;
    m_pos.y = y;
    m_pos.z = z;
}

void OGLDEVWorldTransform::Rotate(float x, float y, float z) {
    m_rotation.x += x;
    m_rotation.y += y;
    m_rotation.z += z;
}

glm::mat4 OGLDEVWorldTransform::GetMatrix() {
    glm::mat4 scale = InitScaleTransform(m_scale, m_scale, m_scale);
    glm::mat4 rotation = InitRotateTransform(m_rotation.x, m_rotation.y, m_rotation.z);
    glm::mat4 translation = InitTranslationTransform(m_pos.x, m_pos.y, m_pos.z);

    glm::mat4 worldTransformation = translation * rotation * scale;

    return worldTransformation;
}

glm::mat4 OGLDEVWorldTransform::InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ)
{
    glm::mat4 m = glm::mat4();
    m[0][0] = ScaleX; m[1][0] = 0.0f;   m[2][0] = 0.0f;   m[3][0] = 0.0f;
    m[0][1] = 0.0f;   m[1][1] = ScaleY; m[2][1] = 0.0f;   m[3][1] = 0.0f;
    m[0][2] = 0.0f;   m[1][2] = 0.0f;   m[2][2] = ScaleZ; m[3][2] = 0.0f;
    m[0][3] = 0.0f;   m[1][3] = 0.0f;   m[2][3] = 0.0f;   m[3][3] = 1.0f;
    return m;
}

glm::mat4 OGLDEVWorldTransform::InitRotateTransform(float rotateX, float rotateY, float rotateZ) {
    // to radian
    float x = glm::radians(rotateX);
    float y = glm::radians(rotateY);
    float z = glm::radians(rotateZ);
    // get the rotation around X,Y,Z axis
    glm::mat4 rx = InitRotationX(x);
    glm::mat4 ry = InitRotationY(y);
    glm::mat4 rz = InitRotationZ(z);
    // apply rotation along 3 axes
    glm::mat4 m = rx * ry * rz;
    return m;
}

glm::mat4 OGLDEVWorldTransform::InitRotationX(float x)
{
    glm::mat4 m = glm::mat4();
    m[0][0] = 1.0f; m[1][0] = 0.0f;    m[2][0] = 0.0f;     m[3][0] = 0.0f;
    m[0][1] = 0.0f; m[1][1] = cosf(x); m[2][1] = -sinf(x); m[3][1] = 0.0f;
    m[0][2] = 0.0f; m[1][2] = sinf(x); m[2][2] = cosf(x);  m[3][2] = 0.0f;
    m[0][3] = 0.0f; m[1][3] = 0.0f;    m[2][3] = 0.0f;     m[3][3] = 1.0f;
    return m;
}


glm::mat4 OGLDEVWorldTransform::InitRotationY(float y)
{
    glm::mat4 m = glm::mat4();
    m[0][0] = cosf(y); m[1][0] = 0.0f; m[2][0] = -sinf(y); m[3][0] = 0.0f;
    m[0][1] = 0.0f;    m[1][1] = 1.0f; m[2][1] = 0.0f;     m[3][1] = 0.0f;
    m[0][2] = sinf(y); m[1][2] = 0.0f; m[2][2] = cosf(y);  m[3][2] = 0.0f;
    m[0][3] = 0.0f;    m[1][3] = 0.0f; m[2][3] = 0.0f;     m[3][3] = 1.0f;
    return m;
}


glm::mat4 OGLDEVWorldTransform::InitRotationZ(float z)
{
    glm::mat4 m = glm::mat4();
    m[0][0] = cosf(z); m[1][0] = -sinf(z); m[2][0] = 0.0f; m[3][0] = 0.0f;
    m[0][1] = sinf(z); m[1][1] = cosf(z);  m[2][1] = 0.0f; m[3][1] = 0.0f;
    m[0][2] = 0.0f;    m[1][2] = 0.0f;     m[2][2] = 1.0f; m[3][2] = 0.0f;
    m[0][3] = 0.0f;    m[1][3] = 0.0f;     m[2][3] = 0.0f; m[3][3] = 1.0f;
    return m;
}

glm::mat4 OGLDEVWorldTransform::InitTranslationTransform(float x, float y, float z) {
    glm::mat4 m = glm::mat4();
    m[0][0] = 1.0f; m[1][0] = 0.0f; m[2][0] = 0.0f; m[3][0] = x;
    m[0][1] = 0.0f; m[1][1] = 1.0f; m[2][1] = 0.0f; m[3][1] = y;
    m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f; m[3][2] = z;
    m[0][3] = 0.0f; m[1][3] = 0.0f; m[2][3] = 0.0f; m[3][3] = 1.0f;
    return m;
}

glm::mat4 OGLDEVWorldTransform::InitTranslationTransform(const glm::vec3& pos) {
    glm::mat4 m = InitTranslationTransform(pos.x, pos.y, pos.z);
    return m;
}