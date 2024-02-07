
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Triangle.h"
#include "stb_image.h"
#include "texture.h"

using namespace std;

void processInput(GLFWwindow*);

int main() {

	Window window{ 800,600 };

	Texture container{ "container.jpg", GL_TEXTURE0 };
	Texture wall{ "wall.jpg", GL_TEXTURE1 };

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


	//Shader vertexShader{"vertexShader.glsl", GL_VERTEX_SHADER};
	Shader vertexShader{ "offSetShader.glsl", GL_VERTEX_SHADER };
	//Shader vertexShader{ "upSideDownShader.glsl", GL_VERTEX_SHADER };
	
	Shader fragmentShader{ "FragmentShader.glsl", GL_FRAGMENT_SHADER};
	Shader textureFragmentShader{ "textureFragmentShader.glsl", GL_FRAGMENT_SHADER };
	Shader blendTextureFragmentShader{ "blendTextureFragmentShader.glsl", GL_FRAGMENT_SHADER }; 

	// -------- Create Orange Shader Program (Render Pipeline) ---------
	Material material{vertexShader, fragmentShader};
	//Material textureMaterial{ vertexShader, textureFragmentShader };
	Material textureMaterial1{ vertexShader, textureFragmentShader }; //Trying

	Triangle a{ &material, &mesh1 };
	a.red = 0.22;
	a.green = 0.5;
	a.blue = 0.5;

	a.offsetX = 0.5f;
	a.offsetY = 0.5f;
	
	Triangle b{ &material, &mesh2 };
	b.red = 0.43;
	b.green = 0.10;
	b.blue = 0.15;

	b.offsetX = 0.5f;
	b.offsetY = 0.5f;

	Triangle c{ &textureMaterial1, &mesh3, &container};
	c.offsetX = -0.5f;

	Triangle d{ &textureMaterial1, &mesh3, &wall };
	d.offsetX = 0.5f;


	// While the User doesn't want to Quit (X Button, Alt+F4)
	while (!window.shouldClose()) // window -> window.window
	{
		window.processInput();

		window.clear();

		a.render();
		b.render();
		c.render();
		d.render();

		window.present();
	}
	// Cleans up all the GLFW stuff
	glfwTerminate();
	return 0;
}