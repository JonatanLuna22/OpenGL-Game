#pragma once

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GameObject.h" 
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

        // Se inicializa el contexto de OpenGL y se crea la ventana GLFW
        window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);

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
        glfwSetCursorPosCallback(window, cursor_position_callback);
        glfwSetWindowUserPointer(window, this);

        // Se establece el viewport después de que se haya creado el contexto de OpenGL
        int framebufferWidth, framebufferHeight;
        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
        glViewport(0, 0, framebufferWidth, framebufferHeight);

        success = true;
    }

    bool shouldClose() {
        return glfwWindowShouldClose(window);
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

    void handleCursorMovement(double xpos, double ypos)
    {
        for (auto& obj : gameObjects) {
            obj.updateColorOnMouseHover(static_cast<int>(xpos), static_cast<int>(ypos), 800, 600);
        }
    }

    GLFWwindow* getGLFWwindow() const {
        return window;
    }
};


