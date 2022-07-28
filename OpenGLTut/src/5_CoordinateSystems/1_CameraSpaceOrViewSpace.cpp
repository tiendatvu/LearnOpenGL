//#include <glad\glad.h>
//#include <GLFW\glfw3.h>
//#include <stb_image.h>
//
//#include <glm\glm.hpp>
//#include <glm\gtc\matrix_transform.hpp>
//#include <glm\gtc\type_ptr.hpp>
//
//#include <ShaderClass\Shader.h>
//
//#include <iostream>
//#include <ctime>
//
//void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//void ProcessInput(GLFWwindow *window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//std::string solDir = _SOLUTION_DIR;
//
//static float translateX = 0.0f;
//static float translateY = 0.0f;
//static float translateZ = 5.0f;
//
//void InitConfigure();
//GLFWwindow *InitGLFWwindow();
//unsigned int ConfigureVertexArrays();
//unsigned int ConfigureVertexBuffers();
//unsigned int ConfigureIndexBuffers();
//
//int main() {
//    // Init random engine
//    time_t seconds = time(NULL);
//    srand(seconds);
//
//    // glfw: init and configure
//    InitConfigure();
//
//    // glfw window creation
//    GLFWwindow *window = InitGLFWwindow();
//    if (window == NULL)
//    {
//        return -1;
//    }
//
//    // glad: load all OPENGL function pointers
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to init GLAD" << std::endl;
//        return -1;
//    }
//
//    // build and compile shader program
//    std::string vsFile1 = solDir + "OpenGLTut/src/1_HelloTriangle/ShaderFiles/Shader1.vs";
//    std::string frsFile1 = solDir + "OpenGLTut/src/1_HelloTriangle/ShaderFiles/Shader1.frs";
//
//    Shader ourShader(vsFile1, frsFile1);
//    ourShader.use();
//
//    // setup vertex data and buffer
//    unsigned int VAO = ConfigureVertexArrays();
//    unsigned int VBO = ConfigureVertexBuffers();
//    unsigned int EBO = ConfigureIndexBuffers();
//
//    // not that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object.
//    // so afterwards we can safely unbind
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    // you can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO,
//    // but this rarely happens. Modifying other VAOs requires a call to glBindVertexArray anyway so we generally don't unbind VAOs (nor VBOs)
//    // when it's not directlty necessary.
//    glBindVertexArray(0);
//
//    static float scale = 0.0f;
//
//    // clock wise set up face culling
//    glEnable(GL_CULL_FACE);
//    glFrontFace(GL_CW); // set load indices as ClockWise
//    glCullFace(GL_BACK);
//
//    glEnable(GL_DEPTH_TEST);
//
//    while (!glfwWindowShouldClose(window))
//    {
//        // input 
//        ProcessInput(window);
//
//        // render
//        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        //--------------------------------------------------------------------------------
//        scale += 0.0002f;
//        
//        // create transformation
//
//        // 1. scale
//        
//        // 2. rotate
//        glm::mat4 rotationMatrix(
//            cosf(scale), 0.0f, -sinf(scale), 0.0f,
//            0.0f,        1.0f, 0.0f,         0.0f,
//            sinf(scale), 0.0f, cosf(scale),  0.0f,
//            0.0f,        0.0f, 0.0f,         1.0f
//        );
//        rotationMatrix = glm::transpose(rotationMatrix);
//
//        // 3. translate
//        glm::mat4 translationMatrix (
//            1.0f, 0.0f, 0.0f, translateX,
//            0.0f, 1.0f, 0.0f, translateY,
//            0.0f, 0.0f, 1.0f, translateZ,
//            0.0f, 0.0f, 0.0f, 1.0f
//        );
//        translationMatrix = glm::transpose(translationMatrix);
//
//        // -> local space to world space transformation
//        glm::mat4 worldMatrix = translationMatrix * rotationMatrix;
//
//        // world space to camera space transformation
//        glm::vec3 cameraPos(2.0f, 1.0f, 0.0f);
//        glm::vec3 u(1.0f, 0.0f, 0.0f);
//        glm::vec3 v(0.0f, 1.0f, 0.0f);
//        glm::vec3 n(0.0f, 0.0f, 1.0f);
//        glm::mat4 cameraMatrix(
//            u.x,  u.y,  u.z,  -cameraPos.x,
//            v.x,  v.y,  v.z,  -cameraPos.y,
//            n.x,  n.y,  n.z,  -cameraPos.z,
//            0.0f, 0.0f, 0.0f, 1.0f
//        );
//        cameraMatrix = glm::transpose(cameraMatrix);
//
//        // init projection of the camera
//        float VFOV = 90.0f;
//        float tanHalfVFOV = tanf(glm::radians(VFOV / 2.0f));
//        float d = 1 / tanHalfVFOV;
//        float aspectRatio = (float)SCR_WIDTH / (float)SCR_HEIGHT;
//        float NearZ = 1.0f;
//        float FarZ = 100.0f;
//        float zRange = NearZ - FarZ;
//        float A = (-FarZ - NearZ) / zRange;
//        float B = 2.0f * FarZ * NearZ / zRange;
//        glm::mat4 perspectiveProjectionMatrix(
//            d / aspectRatio, 0.0f, 0.0f, 0.0f,
//            0.0f,            d,    0.0f, 0.0f,
//            0.0f,            0.0f, A,    B,
//            0.0f,            0.0f, 1.0f, 0.0f
//        );
//        perspectiveProjectionMatrix = glm::transpose(perspectiveProjectionMatrix);
//
//        if (true) {
//            glm::mat4 transform = perspectiveProjectionMatrix * cameraMatrix * worldMatrix; // Matrix4f WVP (world-view-projection)
//
//            ourShader.use();
//            unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");            
//            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
//        }
//        else {
//            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//            glm::mat4 view = glm::mat4(1.0f);
//            glm::mat4 projection = glm::mat4(1.0f);
//            //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//            model = glm::rotate(model, (float)glm::sin(glfwGetTime()), glm::vec3(1.0f, 1.0f, 0.0f));
//            view = glm::translate(view, glm::vec3(translateX, translateY, -translateZ));
//            glm::mat4 projectionMatrix1 = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 1.0f, 100.0f);
//
//            glm::mat4 transform = projectionMatrix1 * view * model;
//
//            ourShader.use();
//            unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
//            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
//        }
//
//        //--------------------------------------------------------------------------------
//
//        // render container
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//
//        // glfw: swap and poll IO events
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purposes
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//
//    // glfw: terminate, clearing all previously allocated GLFW resources
//    glfwTerminate();
//    return 0;
//}
//
//void InitConfigure() {
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif // __APPLE__
//}
//
//GLFWwindow *InitGLFWwindow() {
//    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL_PerspecticeProjection1", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return NULL;
//    }
//
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    return window;
//}
//
//struct Vertex {
//    glm::vec3 pos;
//    glm::vec3 color;
//
//    Vertex() {}
//
//    Vertex(float x, float y, float z) {
//        // init position
//        this->pos = glm::vec3(x, y, z);
//        // init color
//        float red = (float)rand() / (float)RAND_MAX;
//        float green = (float)rand() / (float)RAND_MAX;
//        float blue = (float)rand() / (float)RAND_MAX;
//        this->color = glm::vec3(red, green, blue);
//    }
//};
//
//unsigned int ConfigureVertexArrays() {
//    unsigned int VAO;
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//    return VAO;
//}
//
//unsigned int ConfigureVertexBuffers() {
//    unsigned int VBO;
//
//    Vertex vertices[8];
//    int i = 0;
//    vertices[0] = Vertex(0.5f, 0.5f, 0.5f);
//    vertices[1] = Vertex(-0.5f, 0.5f, -0.5f);
//    vertices[2] = Vertex(-0.5f, 0.5f, 0.5f);
//    vertices[3] = Vertex(0.5f, -0.5f, -0.5f);
//    vertices[4] = Vertex(-0.5f, -0.5f, -0.5f);
//    vertices[5] = Vertex(0.5f, 0.5f, -0.5f);
//    vertices[6] = Vertex(0.5f, -0.5f, 0.5f);
//    vertices[7] = Vertex(-0.5f, -0.5f, 0.5f);
//
//    glGenBuffers(1, &VBO); // Assign buffer to an address in the memory
//    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Assign the type of the buffer: vertex buffer object
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // static draw: data not changed much
//
//                                                                               // position attributes
//    int posLocation = 0;
//    int colorLocation = 1;
//    glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(posLocation);
//
//    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(colorLocation);
//
//    return VBO;
//}
//
//
//unsigned int ConfigureIndexBuffers() {
//    unsigned int EBO;
//    unsigned int indices[] = {
//        0, 1, 2,
//        1, 3, 4,
//        5, 6, 3,
//        7, 3, 6,
//        2, 4, 7,
//        0, 7, 6,
//        0, 5, 1,
//        1, 5, 3,
//        5, 0, 6,
//        7, 4, 3,
//        2, 1, 4,
//        0, 2, 7
//    };
//
//    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    return EBO;
//}
//
//void ProcessInput(GLFWwindow *window) {
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//    {
//        glfwSetWindowShouldClose(window, true);
//    }
//
//    float scale = 0.01f;
//    float oldZ = translateZ;
//    float oldX = translateX;
//    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
//    {
//        translateZ += scale;
//    }
//    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
//    {
//        translateZ -= scale;
//    }
//
//    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
//    {
//        translateX += scale;
//    }
//    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
//    {
//        translateX -= scale;
//    }
//
//    if (oldZ != translateZ)
//    {
//        std::cout << "translateZ: " << translateZ << std::endl;
//    }
//    if (oldX != translateX)
//    {
//        std::cout << "translateX: " << translateX << std::endl;
//    }
//}
//
//void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
//    glViewport(0, 0, width, height);
//}