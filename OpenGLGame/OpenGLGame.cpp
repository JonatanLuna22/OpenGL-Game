
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Triangle.h"
#include "stb_image.h"


using namespace std;

void processInput(GLFWwindow*);

int main() {

	Window window{ 800,600 };

	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	unsigned int textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	

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

	Vertex vertices3[]{
		// positions          // colors           // texture coords
				Vertex{Vector3{ 0.5f,  0.5f, 0.0f},   Color::red,   Vector2{1.0f, 1.0f}},   // top right
				Vertex{Vector3{ 0.5f, -0.5f, 0.0f},   Color::green,   Vector2{1.0f, 0.0f}},   // bottom right
				Vertex{Vector3{-0.5f, -0.5f, 0.0f},   Color::blue,   Vector2{0.0f, 0.0f}},   // bottom left
				
				Vertex{Vector3{-0.5f,  0.5f, 0.0f},   Color::yellow,   Vector2{0.0f, 1.0f}},   // top left 
				Vertex{Vector3{-0.5f, -0.5f, 0.0f},   Color::blue,   Vector2{0.0f, 0.0f}},   // bottom left
				Vertex{Vector3{ 0.5f,  0.5f, 0.0f},   Color::red,   Vector2{1.0f, 1.0f}}   // top right


	};

	Mesh mesh3{ vertices3, size(vertices3) };


	Shader vertexShader{"vertexShader.glsl", GL_VERTEX_SHADER};
	//Shader vertexShader{ "offSetShader.glsl", GL_VERTEX_SHADER };
	//Shader vertexShader{ "upSideDownShader.glsl", GL_VERTEX_SHADER };
	
	Shader fragmentShader{ "FragmentShader.glsl", GL_FRAGMENT_SHADER};
	Shader textureFragmentShader{ "textureFragmentShader.glsl", GL_FRAGMENT_SHADER };


	// -------- Create Orange Shader Program (Render Pipeline) ---------
	Material material{vertexShader, fragmentShader};
	Material textureMaterial{ vertexShader, textureFragmentShader };

	Triangle a{ &material, &mesh1 };
	a.red = 0.22;
	a.green = 55;
	a.blue = 0.0;

	a.offsetX = 0.5f;
	a.offsetY = 0.5f;
	
	Triangle b{ &material, &mesh2 };
	b.red = 0.22;
	b.green = 55;
	b.blue = 0.0;

	b.offsetX = 0.5f;
	b.offsetY = 0.5f;

	Triangle c{ &textureMaterial, &mesh3 };


	// While the User doesn't want to Quit (X Button, Alt+F4)
	while (!window.shouldClose()) // window -> window.window
	{
		window.processInput();

		window.clear();

		a.render();
		b.render();
		c.render();

		window.present();
	}
	// Cleans up all the GLFW stuff
	glfwTerminate();
	return 0;
}