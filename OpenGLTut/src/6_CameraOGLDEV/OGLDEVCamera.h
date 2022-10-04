#ifndef OGLDEV_CAMERA_H
#define OGLDEV_CAMERA_H

#include <glm\glm.hpp>
#include <GLFW\glfw3.h>

class OGLDEVCamera {
public:
    OGLDEVCamera();

    OGLDEVCamera(int windowWidth, int windowHeight);

    OGLDEVCamera(int windowWidth, int windowHeight, const glm::vec3& Pos, const glm::vec3& Target, const glm::vec3& Up);

    void SetPosition(float x, float y, float z);

    void OnKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
    //void OnKeyboard(unsigned char key);

    void OnMouse(double x, double y);

    void OnRender();

    glm::mat4 GetMatrix();

private:
    void Init();
    void Update();

    glm::vec3 m_pos;
    glm::vec3 m_target;
    glm::vec3 m_up;
    float m_speed = 0.1f;

    int m_windowWidth;
    int m_windowHeight;

    float m_AngleH;
    float m_AngleV;

    bool m_OnUpperEdge;
    bool m_OnLowerEdge;
    bool m_OnLeftEdge;
    bool m_OnRightEdge;

    glm::ivec2 m_mousePos;

    glm::mat4 InitCameraTransform(const glm::vec3 &target, const glm::vec3 &up);
    glm::mat4 InitCameraTransform(const glm::vec3 &pos, const glm::vec3 &target, const glm::vec3 &up);
};

#endif