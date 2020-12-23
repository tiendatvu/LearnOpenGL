//// Task 1_material: Can you simulate some of the real-world objects by defining their respective materials like we've seen at the start of this chapter
//
//#include <glad\glad.h>
//#include <GLFW\glfw3.h>
//
//#include <glm\glm.hpp>
//#include <glm\gtc\matrix_transform.hpp>
//#include <glm\gtc\type_ptr.hpp>
//
//#include <ShaderClass\Shader1.h>
//#include <CameraClass\Camera.h>
//
//#include <iostream>
//#include <windows.h>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//// lighting
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//int main()
//{
//    // glfw init and configure
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL_Matertials", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell glfw to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // glad: Load all OPENGL function pointers
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to init GLAD" << std::endl;
//        return -1;
//    }
//
//    // configure global opengl state
//    glEnable(GL_DEPTH_TEST);
//
//    // build and compile our shader program
//    const unsigned int maxDir = 260;
//    char currentDir[maxDir];
//    GetCurrentDirectoryA(maxDir, currentDir);
//    std::string vsFile1 = "/src/9_Materials/ShaderFiles/e1_materials.vs";
//    std::string frsFile1 = "/src/9_Materials/ShaderFiles/e1_materials.frs";
//    Shader lightingShader(currentDir + vsFile1, currentDir + frsFile1);
//    std::string vsFile2 = "/src/9_Materials/ShaderFiles/e1_light_cube.vs";
//    std::string frsFile2 = "/src/9_Materials/ShaderFiles/e1_light_cube.frs";
//    Shader lightCubeShader(currentDir + vsFile2, currentDir + frsFile2);
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float vertices[] = {
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//    };
//    // first, configure the cube's VAO (and VBO)
//    unsigned int VBO, cubeVAO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &VBO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindVertexArray(cubeVAO);
//
//    // position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    // normal attribute
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    // second, configure the light's VAO (VBO stays the same; the vertices are them same for the light object which is also A 3D CUBE)
//    unsigned int lightCubeVAO;
//    glGenVertexArrays(1, &lightCubeVAO);
//    glBindVertexArray(lightCubeVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // render loop
//    while (!glfwWindowShouldClose(window))
//    {
//        // per-frame time logic
//        // --------------------
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // be sure to activate shader when setting uniforms/drawing objects
//        //float curTime = glfwGetTime();
//        //lightPos = glm::vec3(3 * glm::sin(curTime), lightPos.y, 3 * glm::cos(curTime));
//        lightingShader.use();
//        lightingShader.setVec3("light.position", lightPos);
//        lightingShader.setVec3("viewPos", camera.Position);
//
//        // light properties
//        glm::vec3 lightColor;
//        lightColor.x = sin(glfwGetTime() * 2.0f);
//        lightColor.y = sin(glfwGetTime() * 0.7f);
//        lightColor.z = sin(glfwGetTime() * 1.3f);
//        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // decrease the influence
//        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
//        lightingShader.setVec3("light.ambient", ambientColor);
//        lightingShader.setVec3("light.diffuse", diffuseColor);
//        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
//
//        // light properties
//        //lightingShader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f); // note that all light colors are set at full intensity
//        //lightingShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
//        //lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
//
//        // material properties
//        lightingShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
//        lightingShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
//        lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
//        lightingShader.setFloat("material.shininess", 32.0f);
//
//        // view/projection transformations
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        lightingShader.setMat4("projection", projection);
//        lightingShader.setMat4("view", view);
//
//        // world transformation
//        glm::mat4 model = glm::mat4(1.0f);
//        lightingShader.setMat4("model", model);
//
//        // render the cube
//        glBindVertexArray(cubeVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//        float curTime = (float)glfwGetTime();
//        glm::vec3 rotateAxis = glm::vec3(1.0f, 0.2f, 0.45f);
//        // also draw the lamp object
//        lightCubeShader.use();
//        lightCubeShader.setMat4("projection", projection);
//        lightCubeShader.setMat4("view", view);
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, lightPos);
//        model = glm::rotate(model, glm::radians(40.0f * curTime), rotateAxis);
//        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
//        lightCubeShader.setMat4("model", model);
//
//        glm::mat4 model1 = glm::mat4(1.0f);
//        model1 = glm::translate(model1, lightPos);
//        model1 = glm::scale(model1, glm::vec3(0.2f)); // a smaller cube
//        model1 = glm::rotate(model1, glm::radians(40.0f * curTime), rotateAxis);
//
//        glBindVertexArray(lightCubeVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteVertexArrays(1, &lightCubeVAO);
//    glDeleteBuffers(1, &VBO);
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow *window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//    lastX = xpos;
//    lastY = ypos;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(yoffset);
//}