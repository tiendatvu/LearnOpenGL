#ifndef OGLDEV_CAMERA_H
#define OGLDEV_CAMERA_H

#include <glm\glm.hpp>
#include <GLFW\glfw3.h>

class OGLDEVCamera {
public:
    OGLDEVCamera();

    void SetPosition(float x, float y, float z);

    void OnKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
    //void OnKeyboard(unsigned char key);

    glm::mat4 GetMatrix();

private:
    glm::vec3 m_pos;
    glm::vec3 m_target;
    glm::vec3 m_up;
    float m_speed = 0.1f;

    glm::mat4 InitCameraTransform(const glm::vec3 &target, const glm::vec3 &up);
    glm::mat4 InitCameraTransform(const glm::vec3 &pos, const glm::vec3 &target, const glm::vec3 &up);
};

#endif