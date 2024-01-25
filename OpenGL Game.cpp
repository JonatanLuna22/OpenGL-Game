

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"

// Triangle: 
// Mesh:
// Material:

using namespace std;

void processInput(GLFWwindow*);

int main() {
    
    Window window{ 800, 600 };
    
    float red = 0;

    // Create vertex array object, which makes changing between VBOs easier
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Aquí hay tres vortices para el puto triangulo, necesitas 6 para el ejercicio de los dos triangulos
    // Create array buffer on the GPU and copy our vertices to GPU
    float vertices[] = {
       -1, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };
    
    unsigned int VBO; 
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Create vertex array object, which makes changing between VBOs easier
    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    // Aquí hay tres vortices para el puto triangulo, necesitas 6 para el ejercicio de los dos triangulos
    // Create array buffer on the GPU and copy our vertices to GPU
    float vertices2[] = {
        0.0f, -0.5f, 0.0f,
        1, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f
    };

    unsigned int VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    // Configure vertex attribute(s) (currently itçs just one, the position)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    

    // Compile the fragment shader on the GPU
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "} \0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create shader program (Render Pipeline)
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Clean up shaders after they¡ve been linked into a program
    
    glDeleteShader(fragmentShader);

    const char* fragmentShaderSource2 = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "} \0";

    unsigned int fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    unsigned int shaderProgram2;
    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    glUseProgram(shaderProgram2);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader2);

    // While the user doesn't want to quit (X button, Alt + F4)
    while (!glfwWindowShouldClose(window.window))
    {
        // process input (e.g. close window on Esc)
        glfwPollEvents();
        processInput(window.window);
        red += 0.0001f;
        if (red > 1)
            red -= 1;

        // render (paint the current frame of the game)
        glClearColor(0.f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // present (send the current frame to the computer screen)
        glfwSwapBuffers(window.window); // ??
    }
    // Cleans up all the GLFW stuff
    glfwTerminate();
    return 0;


}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}