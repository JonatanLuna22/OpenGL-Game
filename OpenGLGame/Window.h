#pragma once

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GameObject.h" // Incluye la clase GameObject
#include <vector>

using namespace std;

class Window
{
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    static void error_callback(int error, const char* msg) {
        cerr << " [" << error << "] " << msg << endl;
    }

    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (instance != nullptr) {
            instance->handleCursorMovement(xpos, ypos);
        }
    }

    GLFWwindow* window;
    vector<GameObject>& gameObjects;

public:
    bool success{};

    Window(int width, int height, vector<GameObject>& objects) : gameObjects(objects)
    {
        glfwSetErrorCallback(error_callback);

        if (!glfwInit()) {
            cout << "Failed to init GLFW" << endl;
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);

        if (window == nullptr)
        {
            cout << "Failed to create GLFW window" << endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            cout << "Failed to initialize GLAD" << endl;
            glfwTerminate();
            return;
        }
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, cursor_position_callback); // Registra la función de devolución de llamada para el movimiento del cursor
        glfwSetWindowUserPointer(window, this); // Establece el puntero de usuario de la ventana a la instancia actual

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        success = true;
    }

    bool shouldClose() {
        return glfwWindowShouldClose(this->window);
    }

    void present() {
        glfwSwapBuffers(window);
    }

    void processInput()
    {
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void clear() {
        glClearColor(0.0f, 0.25f, 0.35f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    // Función para manejar el movimiento del cursor
    void handleCursorMovement(double xpos, double ypos, int windowWidth, int windowHeight)
    {
        for (auto& obj : gameObjects) {
            obj.updateColorOnMouseHover(xpos, ypos);
        }
    }

    

};


