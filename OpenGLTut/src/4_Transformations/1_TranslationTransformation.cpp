#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ShaderClass/Shader.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
static std::string solDir = _SOLUTION_DIR;

void InitConfigure();
GLFWwindow *InitGLFWwindow();
void ConfigureVertexAttributes(unsigned int &VBO, unsigned int &VAO, unsigned int &EBO);
//void ConfigureTexture(unsigned int (&texture)[2]); // pass an array with 2 elements
unsigned int ConfigureTexture(GLint warppingS,
                              GLint warppingT,
                              GLint minFilter,
                              GLint magFilter,
                              std::string imagePath); // pass an array with pointer to the first element. lose size info


int main()
{
    // glfw: init and configure
    InitConfigure();

    // glfw window creation
    GLFWwindow* window = InitGLFWwindow();
    if (window == NULL)
    {
        return -1;
    }

    // glad: load all OPENGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader programe
    std::string vsFile1 = solDir + "OpenGLTut/src/4_Transformations/ShaderFiles/Shader1.vs";
    std::string frsFile1 = solDir + "OpenGLTut/src/4_Transformations/ShaderFiles/shader1.frs";

    Shader ourShader(vsFile1, frsFile1);

    // set up vertex data and buffer, then configure vertex attributes
    unsigned int VBO, VAO, EBO;
    ConfigureVertexAttributes(VBO, VAO, EBO);

    std::string textureImg1 = solDir + "OpenGLTut/Resources/imgs/container.jpg";
    std::string textureImg2 = solDir + "OpenGLTut/Resources/imgs/awesomeface.png";
    unsigned int texture1 = ConfigureTexture(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, textureImg1);
    unsigned int texture2 = ConfigureTexture(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, textureImg2);
    if (texture1 < 0)
    {
        std::cout << "Cannot read the image with path" + textureImg1 << std::endl;
        return -1;
    }
    if (texture2 < 0)
    {
        std::cout << "Cannot read the image with path" + textureImg2 << std::endl;
        return -1;
    }

    // tell OpenGL for each sampler to which texture unit it belongs to (only has to be done once)
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    // reder loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // Create transformation
        glm::mat4 transform = glm::mat4(1.0f);; // init with identity matrix
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate on Z axis with angle changed by time

        // get matrix's uniform location and set matrix
        ourShader.use();
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // render container
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (key pressed/released, mouse move)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources
    glfwTerminate();
    return 0;
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL_Transformation_Translate", NULL, NULL);
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

void ConfigureVertexAttributes(unsigned int &VBO, unsigned int &VAO, unsigned int &EBO) {
    float vertices[] = {
        // positions        // texture coords
        0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

unsigned int ConfigureTexture(GLint warppingS,
                              GLint warppingT,
                              GLint minFilter,
                              GLint magFilter,
                              std::string imagePath) {
    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    // set the texture wrapping param
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, warppingS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, warppingT);
    // set texture filtering param
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis
    unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        if (nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 4)
        {

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            return -1;
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return textureId;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}