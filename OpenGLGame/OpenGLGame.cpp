
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Triangle.h"

using namespace std;

void processInput(GLFWwindow*);

int main() {

	Window window{ 800,600 };

	float vertices[]{
		   -1.0f, -0.5f, 0.0f,
			0.0f, -0.5f, 0.0f,
		   -0.5f,  0.5f, 0.0f,
		   - 1.0f, -0.5f, 0.0f,
		   -0.5f,  0.5f, 0.0f,
		   -1.0f, 0.5f, 0.0f
	};

	Mesh mesh1{vertices, size(vertices)};

	float vertices2[]{
		0.0f, -0.5f, 0.0f,
		1.0f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f
	};

	Mesh mesh2{ vertices2, size(vertices2) };

	Shader vertexShader{"vertexShader.glsl", GL_VERTEX_SHADER};
	
	Shader fragmentShader{
		"orangeFragmentShader.glsl", GL_FRAGMENT_SHADER
	};

	// -------- Create Orange Shader Program (Render Pipeline) ---------
	Material material{vertexShader, fragmentShader};

	Triangle a{ &material, &mesh1 };
	a.red = 0.22;
	a.green = 0;
	a.blue = 0.55;
	Triangle b{ &material, &mesh2 };
	b.red = 15;
	b.green = 0.25;
	b.blue = 0.35;

	// While the User doesn't want to Quit (X Button, Alt+F4)
	while (!window.shouldClose()) // window -> window.window
	{
		window.processInput();

		window.clear();

		a.render();
		b.render();

		window.present();
	}
	// Cleans up all the GLFW stuff
	glfwTerminate();
	return 0;
}