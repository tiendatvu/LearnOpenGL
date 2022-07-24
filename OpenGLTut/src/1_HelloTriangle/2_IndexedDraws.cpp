//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <stb_image.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <ShaderClass/Shader.h>
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
//static std::string solDir = _SOLUTION_DIR;
//
//void InitConfigure();
//GLFWwindow *InitGLFWwindow();
//void ConfigureVertexArrays(unsigned int &VAO);
//void ConfigureVertexBuffers(unsigned int &VBO);
//void ConfigureIndexBuffers(unsigned int &EBO);
//
//int main()
//{
//    // Init random engine
//    time_t seconds;
//    seconds = time(NULL);
//    srand(seconds); // set initial seed value to system clock
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
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // build and compile our shader programe
//    std::string vsFile1 = solDir + "OpenGLTut/src/1_HelloTriangle/ShaderFiles/Shader1.vs";
//    std::string frsFile1 = solDir + "OpenGLTut/src/1_HelloTriangle/ShaderFiles/Shader1.frs";
//
//    Shader ourShader(vsFile1, frsFile1);
//    ourShader.use();
//
//    // setup vertex data and buffer
//    unsigned int VBO, VAO, EBO;
//    ConfigureVertexArrays(VAO);
//    ConfigureVertexBuffers(VBO);
//    ConfigureIndexBuffers(EBO);
//
//    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//    glBindVertexArray(0);
//
//    while (!glfwWindowShouldClose(window))
//    {
//        // input
//        ProcessInput(window);
//
//        // render
//        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // create transformation
//        glm::mat4 transform = glm::mat4(1.0f); // init identity matrix
//
//        ourShader.use();
//        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
//        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
//
//        // render container
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, 54, GL_UNSIGNED_INT, 0);
//
//        // glfw: swap buffers and poll IO events
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purposes
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//
//    // glfw: Terminate, clearing all previously allocated GLFW resources
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
//    glfwWindow(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif // __APPLE__
//}
//
//GLFWwindow *InitGLFWwindow() {
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL_IndexedDraw", NULL, NULL);
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
///// 2 * vec3 (float, float, float) => 6 BYTES
//struct Vertex {
//    glm::vec3 pos;
//    glm::vec3 color;
//
//    Vertex() {};
//
//    Vertex(float x, float y)
//    {
//        // init position
//        this->pos = glm::vec3(x, y, 0.0f);
//        // init color
//        float red = ((float)rand() / (float)RAND_MAX);
//        float green = ((float)rand() / (float)RAND_MAX);
//        float blue = ((float)rand() / (float)RAND_MAX);
//        this->color = glm::vec3(red, green, blue);
//    }
//};
//
//void ConfigureVertexArrays(unsigned int &VAO) {
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//}
//
//void ConfigureVertexBuffers(unsigned int &VBO) {
//    Vertex vertices[19];
//
//    int i = 0;
//    // Center point
//    vertices[i++] = Vertex(0.0f, 0.0f);
//
//    // Top row
//    vertices[i++] = Vertex(-1.00f, 1.0f);
//    vertices[i++] = Vertex(-0.75f, 1.0f);
//    vertices[i++] = Vertex(-0.50f, 1.0f);
//    vertices[i++] = Vertex(-0.25f, 1.0f);
//    vertices[i++] = Vertex(0.00f, 1.0f);
//    vertices[i++] = Vertex(0.25f, 1.0f);
//    vertices[i++] = Vertex(0.50f, 1.0f);
//    vertices[i++] = Vertex(0.75f, 1.0f);
//    vertices[i++] = Vertex(1.00f, 1.0f);
//
//    // Bottom row
//    vertices[i++] = Vertex(-1.00f, -1.0f);
//    vertices[i++] = Vertex(-0.75f, -1.0f);
//    vertices[i++] = Vertex(-0.50f, -1.0f);
//    vertices[i++] = Vertex(-0.25f, -1.0f);
//    vertices[i++] = Vertex(0.00f, -1.0f);
//    vertices[i++] = Vertex(0.25f, -1.0f);
//    vertices[i++] = Vertex(0.50f, -1.0f);
//    vertices[i++] = Vertex(0.75f, -1.0f);
//    vertices[i++] = Vertex(1.00f, -1.0f);
//
//    glGenBuffers(1, &VBO); // Assign buffer to an address in the memory
//    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Assign the type of the buffer: vertex buffer object
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // static draw: drawn data not change much
//
//    // position attributes
//    int posLocation = 0; // layout location in shader file
//    int colorLocation = 1;
//    glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(posLocation);
//
//    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(colorLocation);
//}
//
//void ConfigureIndexBuffers(unsigned int &EBO) {
//    // 3 Points -> Form a triangle -> Counter-clockwise
//    unsigned int indices[] = {
//        // Top triangles
//        0, 2, 1,
//        0, 3, 2,
//        0, 4, 3,
//        0, 5, 4,
//        0, 6, 5,
//        0, 7, 6,
//        0, 8, 7,
//        0, 9, 8,
//
//        // Bottom triangles
//        0, 10, 11,
//        0, 11, 12,
//        0, 12, 13,
//        0, 13, 14,
//        0, 14, 15,
//        0, 15, 16,
//        0, 16, 17,
//        0, 17, 18,
//
//        // Left triangle
//        0, 1, 10,
//
//        // Right triangle
//        0, 18, 9
//    };
//
//    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//}
//
//void ProcessInput(GLFWwindow *window) {
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//    {
//        glfwSetWindowShouldClose(window, true);
//    }
//}
//
//void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
//    glViewport(0, 0, width, height);
//}