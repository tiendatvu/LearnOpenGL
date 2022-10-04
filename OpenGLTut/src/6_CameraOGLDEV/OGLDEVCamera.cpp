#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "OGLDEVCamera.h"
#include <OGLDEV/ogldev_math_3d.h>


static int MARGIN = 10;
static float EDGE_STEP = 1.0f;

OGLDEVCamera::OGLDEVCamera() {
    m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    m_target = glm::vec3(0.0f, 0.0f, 1.0f); // watch things along the +Z axis
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
}

OGLDEVCamera::OGLDEVCamera(int windowWidth, int windowHeight) {
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    m_target = glm::vec3(0.0f, 0.0f, 1.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    Init();
}

OGLDEVCamera::OGLDEVCamera(int windowWidth, int windowHeight, const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up) {
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    m_pos = pos;

    // normalize the passed in vectors
    m_target = glm::normalize(target);
    m_up = glm::normalize(up);

    Init();
}

// Init quartenion
void OGLDEVCamera::Init() {
    glm::vec3 hTarget(m_target.x, 0.0f, m_target.z);
    hTarget = glm::normalize(hTarget);

    float angle = glm::degrees(asin(abs(hTarget.z)));
    if (hTarget.z >= 0.0f)
    {
        if (hTarget.x >= 0.0f)
        {
            m_AngleH = 360.0f - angle;
        }
        else
        {
            m_AngleH = 180.0f + angle;
        }
    }
    else
    {
        if (hTarget.x >= 0.0f)
        {
            m_AngleH = angle;
        }
        else
        {
            m_AngleH = 180.0f - angle;
        }
    }

    m_AngleV = -glm::degrees(asin(m_target.y));

    m_OnUpperEdge = false;
    m_OnLowerEdge = false;
    m_OnLeftEdge = false;
    m_OnRightEdge = false;
    m_mousePos.x = m_windowWidth / 2;
    m_mousePos.y = m_windowHeight / 2;
}

void OGLDEVCamera::SetPosition(float x, float y, float z) {
    //m_pos = glm::vec3(x, y, z); // create new vec3
    m_pos.x = x; // just assign new value
    m_pos.y = y;
    m_pos.z = z;
}

void OGLDEVCamera::OnKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
//void OGLDEVCamera::OnKeyboard(unsigned char key) {

    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            m_pos += (m_target * m_speed);
            std::cout << "m_pos.x: " << m_pos.x << std::endl;
            std::cout << "m_pos.y: " << m_pos.y << std::endl;
            std::cout << "m_pos.z: " << m_pos.z << std::endl;
            break;

        case GLFW_KEY_DOWN:
            m_pos -= (m_target * m_speed);
            std::cout << "m_pos.x: " << m_pos.x << std::endl;
            std::cout << "m_pos.y: " << m_pos.y << std::endl;
            std::cout << "m_pos.z: " << m_pos.z << std::endl;
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

        case GLFW_KEY_EQUAL: //  = (shift = is +)
            m_speed += 0.01f;
            printf("Speed changed to %f\n", m_speed);
            break;
        case GLFW_KEY_MINUS:
            m_speed -= 0.01f;
            printf("Speed changed to %f\n", m_speed);
            break;
        default:
            break;
        }
    }
}

void OGLDEVCamera::OnMouse(double x, double y) {
    double deltaX = x - m_mousePos.x;
    double deltaY = y - m_mousePos.y;
    m_mousePos.x = x;
    m_mousePos.y = y;

    m_AngleH += (float)deltaX / 20.0f;
    m_AngleV += (float)deltaY / 50.0f;

    //std::cout << "deltaX: " << deltaX << "; deltaY: " << deltaY << std::endl;
    if (abs(deltaX) <= MARGIN) {
        if (x <= MARGIN) {
            m_OnLeftEdge = true;
        }
        else if (x >= (m_windowWidth - MARGIN)) {
            m_OnRightEdge = true;
        }
    }
    else {
        m_OnLeftEdge = false;
        m_OnRightEdge = false;
    }

    if (abs(deltaY) <= MARGIN) {
        if (y <= MARGIN) {
            m_OnUpperEdge = true;
        }
        else if (y >= (m_windowHeight - MARGIN)) {
            m_OnLowerEdge = true;
        }
    }
    else {
        m_OnUpperEdge = false;
        m_OnLowerEdge = false;
    }
    
    Update();
}

void OGLDEVCamera::OnRender()
{
    bool shouldUpdate = false;

    if (m_OnLeftEdge) {
        std::cout << "LEFT\n";
        m_AngleH -= EDGE_STEP;
        shouldUpdate = true;
    }
    else if (m_OnRightEdge) {
        std::cout << "RIGHT\n";
        m_AngleH += EDGE_STEP;
        shouldUpdate = true;
    }

    if (m_OnUpperEdge) {
        std::cout << "UPPER\n";
        if (m_AngleV > -90.0f) {
            m_AngleV -= EDGE_STEP;
            shouldUpdate = true;
        }
    }
    else if (m_OnLowerEdge) {
        std::cout << "LOWER\n";
        if (m_AngleV < 90.0f) {
            m_AngleV += EDGE_STEP;
            shouldUpdate = true;
        }
    }

    if (shouldUpdate) {
        Update();
    }
}

void OGLDEVCamera::Update()
{
    Vector3f Yaxis(0.0f, 1.0f, 0.0f);

    // Rotate the view vector by the horizontal angle around the vertical axis
    Vector3f View(1.0f, 0.0f, 0.0f);    
    View.Rotate(m_AngleH, Yaxis); // rotate using quaternion    
    View.Normalize();

    // Rotate the view vector by the vertical angle around the horizontal axis
    Vector3f U = Yaxis.Cross(View);
    U.Normalize();
    View.Rotate(m_AngleV, U);

    Vector3f normalizedView = View.Normalize();
    m_target = glm::vec3(View.x, View.y, View.z);

    Vector3f vector3fUp = normalizedView.Cross(U).Normalize();
    m_up = glm::vec3(vector3fUp.x, vector3fUp.y, vector3fUp.z);
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