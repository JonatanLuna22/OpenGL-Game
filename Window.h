#pragma once

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

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
    
public:
    bool success;
    GLFWwindow* window;

	Window(int width, int height) {
        if (!glfwInit()) {
            std::cout << "Failed to int GLFW" << std::endl;
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        // Request window from Operating system
        window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
        if (window == nullptr)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);

        // Initialize GLAD (connects OpenGL Functions)
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        success = true;
	}
};

