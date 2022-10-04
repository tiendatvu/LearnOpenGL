#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OGLDEVCamera.h"
#include "OGLDEVWorldTransform.h"
#include <OGLDEV/ogldev_math_3d.h>
#include <ShaderClass/Shader.h>

#include <iostream>
#include <ctime>

#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080

const static std::string solDir = _SOLUTION_DIR;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void ProcessInput(GLFWwindow *window);
void InitConfigure();
GLFWwindow *InitGLFWwindow();
unsigned int ConfigureVertexArrays();
unsigned int ConfigureVertexBuffers();
unsigned int ConfigureIndexBuffers();

float FOV = 45.0f;
float zNear = 1.0f;
float zFar = 10.0f;

PersProjInfo persProjInfo = { FOV, SCR_WIDTH, SCR_HEIGHT, zNear, zFar };
OGLDEVWorldTransform cubeWorldTransform;
glm::vec3 cameraPos(0.0f, 0.0f, -1.0f);
glm::vec3 cameraTarget(0.0f, 0.0f, 1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
OGLDEVCamera gameCamera(SCR_WIDTH, SCR_HEIGHT, cameraPos, cameraTarget, cameraUp);

static float translateX = 0.0f;
static float translateY = 0.0f;
static float translateZ = 0.0f;

int main() {
    // Init random engine
    time_t seconds = time(NULL);
    srand(seconds);

    // glfw: init and configure
    InitConfigure();

    // glfw window creation
    GLFWwindow *window = InitGLFWwindow();
    if (window == NULL)
    {
        return -1;
    }

    // glad: load all OPENGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD" << std::endl;
        return -1;
    }

    // build and compile shader program
    std::string vsFile1 = solDir + "OpenGLTut/src/1_HelloTriangle/ShaderFiles/Shader1.vs";
    std::string frsFile1 = solDir + "OpenGLTut/src/1_HelloTriangle/ShaderFiles/Shader1.frs";


    Shader ourShader(vsFile1, frsFile1);
    ourShader.use();

    // setup vertex data and buffer
    unsigned int VAO = ConfigureVertexArrays();
    unsigned int VBO = ConfigureVertexBuffers();
    unsigned int EBO = ConfigureIndexBuffers();

    // not that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object.
    // so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // you can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO,
    // but this rarely happens. Modifying other VAOs requires a call to glBindVertexArray anyway so we generally don't unbind VAOs (nor VBOs)
    // when it's not directlty necessary.
    glBindVertexArray(0);

    // clockwise setup face culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW); // set load indices as clockwise
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    float yRotationAngle = 0.1f;
    cubeWorldTransform.SetPosition(0.0f, 0.0f, 5.0f);
    while (!glfwWindowShouldClose(window))
    {
        // input
        ProcessInput(window);

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        gameCamera.OnRender();
        // Get the transformations of (world space/ view space/ projection)
        cubeWorldTransform.Rotate(0.0f, yRotationAngle, 0.0f); // keep rotating the cube around the y axis with the pace yRotationAngle
        glm::mat4 world = cubeWorldTransform.GetMatrix();
        glm::mat4 view = gameCamera.GetMatrix();
        glm::mat4 projection = Matrix4f::InitPersProjTransform(persProjInfo);

        glm::mat4 transform = projection * view * world;
        // ourShader.ID: id of the program
        // "transform": name of the uniform, used in a shader source file
        // glGetUniformLocation would return the location of the uniform (in the program)
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

        // render container
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // glfw: swap and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void InitConfigure() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__
}

GLFWwindow *InitGLFWwindow() {
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL_MovingTheCamera", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;

    Vertex() {}

    Vertex(float x, float y, float z) {
        // init position
        this->pos = glm::vec3(x, y, z);
        // init color
        float red = (float)rand() / (float)RAND_MAX;
        float green = (float)rand() / (float)RAND_MAX;
        float blue = (float)rand() / (float)RAND_MAX;
        this->color = glm::vec3(red, green, blue);
    }
};

unsigned int ConfigureVertexArrays() {
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    return VAO;
}

unsigned int ConfigureVertexBuffers() {
    unsigned int VBO;
    Vertex vertices[8];
    int i = 0;
    // defnie 8 vertices in 8 indices -> forming a cube
    vertices[0] = Vertex(0.5f, 0.5f, 0.5f);
    vertices[1] = Vertex(-0.5f, 0.5f, -0.5f);
    vertices[2] = Vertex(-0.5f, 0.5f, 0.5f);
    vertices[3] = Vertex(0.5f, -0.5f, -0.5f);
    vertices[4] = Vertex(-0.5f, -0.5f, -0.5f);
    vertices[5] = Vertex(0.5f, 0.5f, -0.5f);
    vertices[6] = Vertex(0.5f, -0.5f, 0.5f);
    vertices[7] = Vertex(-0.5f, -0.5f, 0.5f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attributes
    int posLocation = 0;
    int colorLocation = 1;
    glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(posLocation);

    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(colorLocation);

    return VBO;
}

unsigned int ConfigureIndexBuffers() {
    unsigned int EBO;
    unsigned int indices[] = {
        0, 1, 2,
        1, 3, 4,
        5, 6, 3,
        7, 3, 6,
        2, 4, 7,
        0, 7, 6,
        0, 5, 1,
        1, 5, 3,
        5, 0, 6,
        7, 4, 3,
        2, 1, 4,
        0, 2, 7
    };

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    return EBO;
}

void ProcessInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    gameCamera.OnKeyboard(window, key, scancode, action, mods);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    //std::cout << "xposIn: " << xposIn << "; yposIn: " << yposIn << std::endl;
    gameCamera.OnMouse(xposIn, yposIn);
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}