#ifndef OGLDEV_WORLD_TRANSFORM
#define OGLDEV_WORLD_TRANSFORM

#include <glm\glm.hpp>

class OGLDEVWorldTransform {
public:
    OGLDEVWorldTransform() {}

    void SetScale(float scale);
    void SetRotation(float x, float y, float z);
    void SetPosition(float x, float y, float z);

    void Rotate(float x, float y, float z);

    glm::mat4 GetMatrix();
private:
    float m_scale = 1.0f;
    glm::vec3 m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_pos = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::mat4 InitScaleTransform(float scaleX, float scaleY, float scaleZ);
    glm::mat4 InitRotateTransform(float rotateX, float rotateY, float rotateZ);
    glm::mat4 InitRotationX(float x);
    glm::mat4 InitRotationY(float y);
    glm::mat4 InitRotationZ(float z);
    glm::mat4 InitTranslationTransform(float x, float y, float z);
    glm::mat4 InitTranslationTransform(const glm::vec3& pos);
};

#endif // !OGLDEVWorldTransform