#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "ConstantShaders.h"
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    return true;
}

bool isKeyPressed(GLFWwindow* window, int key)
{
    if (glfwGetKey(window, key) == GLFW_PRESS)
        return true;

    return false;
}

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        std::cout << argv[1] << std::endl;
    }
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSourcePurple, NULL);
    glCompileShader(fragmentShader2);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (success == 0)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR COMPILING VERTEX SHADER! Error log: \n" << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (success == 0)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR COMPILING FRAGMENT SHADER! Error log: \n" << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);

    if (success == 0)
    {
        glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
        std::cout << "ERROR COMPILING FRAGMENT SHADER2! Error log: \n" << infoLog << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);

    if (success == 0)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR COMPILING SHADER PROGRAM! Error log: \n" << infoLog << std::endl;
    }

    unsigned int shaderProgramPurple;
    shaderProgramPurple = glCreateProgram();
    glAttachShader(shaderProgramPurple, vertexShader);
    glAttachShader(shaderProgramPurple, fragmentShader2);
    glLinkProgram(shaderProgramPurple);

    glGetProgramiv(shaderProgramPurple, GL_COMPILE_STATUS, &success);

    if (success == 0)
    {
        glGetProgramInfoLog(shaderProgramPurple, 512, NULL, infoLog);
        std::cout << "ERROR COMPILING SHADER PROGRAM2! Error log: \n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);

    float vertices[] = {
        // positions            // colors
         0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,     1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,     1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,     0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f,     0.0f, 1.0f // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    float vertices2[] = {
     -0.9f,  0.9f, 0.0f, // top left
     -0.9f, 0.5f, 0.0f, // bottom right
    -0.5f, 0.9f, 0.0f//,  // bottom left
    //-0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices2[] = {
        0, 1, 2//,
        //1, 2, 3
    };

    unsigned int VBO2;
    glGenBuffers(1, &VBO2);

    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);

    unsigned int EBO2;
    glGenBuffers(1, &EBO2);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    float time = glfwGetTime();
    float greenValue = (std::sin(time) / 2.0f) + 0.5f;
    int vertexOurColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexOurColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    
    Shader testShader("Resources/TestVertex.vert", "Resources/TestFrag.frag", "TestingShader");

    /* --- LOADING TEXTURES --- */

    int width, height, channelAmount;
    unsigned char* image = stbi_load("Resources/container.jpg", &width, &height, &channelAmount, 0);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(image);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        float r = 0.0f, g = 0.0f, b = 0.0f;

        if (isKeyPressed(window, GLFW_KEY_1))
            r = 1.0f;

        if (isKeyPressed(window, GLFW_KEY_2))
            g = 1.0f;

        if (isKeyPressed(window, GLFW_KEY_3))
            b = 1.0f;

        if (isKeyPressed(window, GLFW_KEY_4))
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glUseProgram(shaderProgram);
        testShader.SetAsCurrent();

        /*float time = glfwGetTime();
        float greenValue = (std::sin(time * 5.0f) / 2.0f) + 0.5f;
        int vertexOurColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexOurColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/

        
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

        /*glUseProgram(shaderProgramPurple);
        glBindVertexArray(VAO2);
        glDrawElements(GL_TRIANGLES, sizeof(indices2), GL_UNSIGNED_INT, 0);*/

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}