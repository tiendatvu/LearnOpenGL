#include "OGLDEVCamera.h"
#include <GLFW\glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

OGLDEVCamera::OGLDEVCamera() {
    m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    m_target = glm::vec3(0.0f, 0.0f, 1.0f); // watch things along the +Z axis
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void OGLDEVCamera::SetPosition(float x, float y, float z) {
    //m_pos = glm::vec3(x, y, z); // create new vec3
    m_pos.x = x; // just assign new value
    m_pos.y = y;
    m_pos.z = z;
}

void OGLDEVCamera::OnKeyboard(unsigned char key) {
    switch (key)
    {
    case GLFW_KEY_UP:
        m_pos += (m_target * m_speed);
        break;
    case GLFW_KEY_DOWN:
        m_pos -= (m_target * m_speed);
        break;

    case GLFW_KEY_LEFT:
        glm::vec3 left = glm::cross(m_target, m_up);
        left = glm::normalize(left);
        left *= m_speed;
        m_pos += left;
        break;
    case GLFW_KEY_RIGHT:
        glm::vec3 right = glm::cross(m_up, m_target);
        right = glm::normalize(right);
        right *= m_speed;
        m_pos += right;
        break;

    case GLFW_KEY_PAGE_UP:
        m_pos.y += m_speed;
        break;
    case GLFW_KEY_PAGE_DOWN:
        m_pos.y -= m_speed;
        break;

    case '+':
        m_speed += 0.01f;
        printf("Speed changed to %f\n", m_speed);
        break;
    case '-':
        m_speed -= 0.01f;
        printf("Speed changed to %f\n", m_speed);
        break;
    default:
        break;
    }
}

glm::mat4 OGLDEVCamera::GetMatrix() {
    glm::mat4 cameraTransformation = InitCameraTransform(m_pos, m_target, m_up);
    return cameraTransformation;
}

/// With the Target vector and Up vector -> we can init ROTATION transformation of the camera
glm::mat4 OGLDEVCamera::InitCameraTransform(const glm::vec3 &target, const glm::vec3 &up) {
    glm::vec3 N = glm::normalize(target);
    glm::vec3 upNorm = glm::normalize(up);
    // from target vector and up vector -> get the U vector
    glm::vec3 U = glm::normalize(glm::cross(upNorm, N));
    // from N vector and U vector -> get the V vector
    glm::vec3 V = glm::normalize(glm::cross(N, U));

    // camera transformation matrix
    glm::mat4 m = glm::mat4(1.0f);
    m[0][0] = U.x;   m[1][0] = U.y;   m[2][0] = U.z;   m[3][0] = 0.0f;
    m[0][1] = V.x;   m[1][1] = V.y;   m[2][1] = V.z;   m[3][1] = 0.0f;
    m[0][2] = N.x;   m[1][2] = N.y;   m[2][2] = N.z;   m[3][2] = 0.0f;
    m[0][3] = 0.0f;  m[1][3] = 0.0f;  m[2][3] = 0.0f;  m[3][3] = 1.0f;
    return m;
}

glm::mat4 OGLDEVCamera::InitCameraTransform(const glm::vec3 &pos, const glm::vec3 &target, const glm::vec3 &up) {
    glm::mat4 cameraTranslation = glm::translate(glm::mat4(1.0f), -pos);
    glm::mat4 cameraRotation = InitCameraTransform(target, up);
    // apply the translation of the camera first
    // We have the transformation of from world space to camera space
    // m[0][0] = U.x;   m[1][0] = U.y;   m[2][0] = U.z;   m[3][0] = -(U.x * pos.x + U.y * pos.y + U.z * pos.z);
    // m[0][1] = V.x;   m[1][1] = V.y;   m[2][1] = V.z;   m[3][1] = -(V.x * pos.x + V.y * pos.y + V.z * pos.z);
    // m[0][2] = N.x;   m[1][2] = N.y;   m[2][2] = N.z;   m[3][2] = -(N.x * pos.x + N.y * pos.y + N.z * pos.z);
    // m[0][3] = 0.0f;  m[1][3] = 0.0f;  m[2][3] = 0.0f;  m[3][3] = 1.0f;
    glm::mat4 m = cameraRotation * cameraTranslation;
    return m;
}