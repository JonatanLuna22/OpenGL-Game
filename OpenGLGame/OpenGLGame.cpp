
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

	Vertex vertices[]{
		//Up
		   Vertex{Vector3{0.0f, 1.0f, 0.0f}, Color::green },
		   Vertex{Vector3{0.5f, 0.0f, 0.0f}, Color::red },
		   Vertex{ Vector3{-0.5f,  0.0f, 0.0f}, Color::blue },
		//Down
		   Vertex{Vector3{-0.5f, 0.0f, 0.0f}, Color::red },
		   Vertex{Vector3{0.0f,  -1.0f, 0.0f}, Color::green },
		   Vertex{Vector3{0.5f, 0.0f, 0.0f}, Color::blue },
		//Left
		   Vertex{Vector3{-1.0f, 0.0f, 0.0f}, Color::green },
		   Vertex{Vector3{0.0f, 0.5f, 0.0f}, Color::red },
		   Vertex{Vector3{0.0f,  -0.5f, 0.0f}, Color::blue },
		//Right
		   Vertex{Vector3{0.0f, 0.5f, 0.0f}, Color::red },
		   Vertex{Vector3{1.0f, 0.0f, 0.0f}, Color::green },
		   Vertex{Vector3{0.0f, -0.5f, 0.0f}, Color::blue }
	};	   

	Mesh mesh1{vertices, size(vertices)};

	Vertex vertices2[]{

			Vertex{Vector3{0.0f, 0.5f, 0.0f}, Color::red },
			Vertex{Vector3{0.5f, 0.0f, 0.0f}, Color::green },
		    Vertex{Vector3{0.70f,  0.70f, 0.0f}, Color::blue },
			
		    Vertex{Vector3{0.5f, 0.0f, 0.0f}, Color::red },
		    Vertex{Vector3{0.70f, -0.70f, 0.0f}, Color::blue },
		    Vertex{Vector3{0.0f, -0.5f, 0.0f}, Color::green },
			
			Vertex{Vector3{0.0f, -0.5f, 0.0f}, Color::red },
			Vertex{Vector3{-0.70f, -0.70f, 0.0f}, Color::blue },
			Vertex{Vector3{-0.5f,  0.0f, 0.0f}, Color::green },
			
			Vertex{Vector3{-0.5f,  0.0f, 0.0f}, Color::red },
			Vertex{Vector3{-0.70f, 0.70f, 0.0f}, Color::blue },
			Vertex{Vector3{0.0f, 0.5f, 0.0f}, Color::green }

	};

	Mesh mesh2{ vertices2, size(vertices2) };

	Shader vertexShader{"vertexShader.glsl", GL_VERTEX_SHADER};
	
	Shader fragmentShader{
		"FragmentShader.glsl", GL_FRAGMENT_SHADER
	};

	// -------- Create Orange Shader Program (Render Pipeline) ---------
	Material material{vertexShader, fragmentShader};

	Triangle a{ &material, &mesh1 };
	a.red = 0.22;
	a.green = 55;
	a.blue = 0.0;
	Triangle b{ &material, &mesh2 };
	b.red = 0.22;
	b.green = 55;
	b.blue = 0.0;

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