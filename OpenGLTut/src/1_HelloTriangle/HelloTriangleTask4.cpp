//// self_task:
//// - Use 2 different program -> draw different colors
//// - Draw a word: "PS5"
//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//const unsigned int VERTEX_ATTRIB_LOCATION = 0; // from 0-15 in this system
//
//// assign location value as VERTEX_ATTRIB_LOCATION
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//const char* fragmentShader1Source = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n\0";
//const char* fragmentShader2Source = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"  FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
//"}\n\0";
//
//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HelloTriangleTask4", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;        
//    }
//
//    // build and compile our shader program
//    // ------------------------------------
//    // we skipped compile log checks this time for readability (if you do encounter issues, add the compile-checks! see previous code samples)
//    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
//    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
//    unsigned int shaderProgram1 = glCreateProgram();
//    unsigned int shaderProgram2 = glCreateProgram();
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//    // check for shader compile errors
//    int success;
//    char infoLog[512];
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//
//    glShaderSource(fragmentShader1, 1, &fragmentShader1Source, NULL);
//    glCompileShader(fragmentShader1);
//    // check for shader compile errors
//    glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::FRAGMENT1::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//
//    glShaderSource(fragmentShader2, 1, &fragmentShader2Source, NULL);
//    glCompileShader(fragmentShader2);
//    // check for shader compile errors
//    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::FRAGMENT2::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//
//    // link the first program object
//    glAttachShader(shaderProgram1, vertexShader);
//    glAttachShader(shaderProgram1, fragmentShader1);
//    glLinkProgram(shaderProgram1);
//    // check for linking errors
//    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
//    if (!success) {
//        glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::PROGRAM1::LINKING_FAILED\n" << infoLog << std::endl;
//    }
//
//    // then link the second program object using a different fragment shader (but same vertex shader)
//    // this is perfectly allowed since the inputs and outputs of both the vertex and fragment shaders are equally matched.
//    glAttachShader(shaderProgram2, vertexShader);
//    glAttachShader(shaderProgram2, fragmentShader2);
//    glLinkProgram(shaderProgram2);
//    // check for linking errors
//    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
//    if (!success) {
//        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::PROGRAM2::LINKING_FAILED\n" << infoLog << std::endl;
//    }
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float vertices1[]={
//        -0.9f, -0.9f, 0.0f,
//        -0.9f,  0.9f, 0.0f,
//        -0.7f, -0.9f, 0.0f,
//        -0.7f,  0.9f, 0.0f,
//        -0.2f,  0.9f, 0.0f,
//        -0.7f,  0.7f, 0.0f,
//        -0.2f,  0.7f, 0.0f,
//    };
//    unsigned int indices1[]={
//        0, 1, 2,
//        1, 2, 3,
//        3, 4, 5,
//        4, 5, 6
//    };
//    int numIndices1 = *(&indices1 + 1) - indices1;
//
//    float vertices2[] = {
//        0.0f, -0.5f, 0.0f,  // left
//        0.9f, -0.5f, 0.0f,  // right
//        0.45f, 0.5f, 0.0f   // top 
//    };
//    unsigned int indices2[] = {
//        0, 1, 2
//    };
//    int numIndices2 = *(&indices2 + 1) - indices2;
//
//    unsigned int EBOs[2], VBOs[2], VAOs[2];
//    glGenVertexArrays(2, VAOs);
//    glGenBuffers(2, VBOs);
//    glGenBuffers(2, EBOs);
//
//    int i = 0;
//    // First vertices setup
//    glBindVertexArray(VAOs[i]);
//    glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
//    glVertexAttribPointer(VERTEX_ATTRIB_LOCATION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(VERTEX_ATTRIB_LOCATION);
//    // glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
//    // Second vertices setup
//    i++;
//    glBindVertexArray(VAOs[i]);
//    glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
//    glVertexAttribPointer(VERTEX_ATTRIB_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//    glEnableVertexAttribArray(VERTEX_ATTRIB_LOCATION);
//    // glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)
//
//    // uncomment this call to draw in wireframe polygons.
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        int j = 0;
//        // draw our first triangle
//        glUseProgram(shaderProgram1);
//        glBindVertexArray(VAOs[j]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized        
//        glDrawElements(GL_TRIANGLES, numIndices1, GL_UNSIGNED_INT, 0);
//        // glBindVertexArray(0); // no need to unbind it every time 
//
//        // draw our first triangle
//        glUseProgram(shaderProgram2);
//        glBindVertexArray(VAOs[++j]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized        
//        glDrawElements(GL_TRIANGLES, numIndices2, GL_UNSIGNED_INT, 0);
//        // glBindVertexArray(0); // no need to unbind it every time 
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();       
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(2, VAOs);
//    glDeleteBuffers(2, VBOs);
//    glDeleteBuffers(2, EBOs);
//    glDeleteProgram(shaderProgram1);
//    glDeleteProgram(shaderProgram2);
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