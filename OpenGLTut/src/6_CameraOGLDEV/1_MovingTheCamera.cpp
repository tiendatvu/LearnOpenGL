#include "OGLDEVCamera.h"
#include "OGLDEVWorldTransform.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <stb_image.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <ShaderClass\Shader.h>

#include <iostream>
#include <ctime>

#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080
const static std::string solDir = _SOLUTION_DIR;

OGLDEVWorldTransform CubeWorldTransform;
OGLDEVCamera GameCamera;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void ProcessInput(GLFWwindow *window);
void InitConfigure();
GLFWwindow *InitGLFWwindow();
unsigned int ConfigureVertexArrays();
unsigned int ConfigureVertexBuffers();
unsigned int ConfigureIndexBuffers();

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
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}