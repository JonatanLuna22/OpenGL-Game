
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "GameObject.h"
#include "stb_image.h"
#include "texture.h"
#include <vector>

using namespace std;

void processInput(GLFWwindow*);

int main() {

	vector<GameObject> gameObjects;

	// Inicializar GLFW y crear una ventana
	if (!glfwInit()) {
		cout << "Failed to init GLFW" << endl;
		return -1;
	}

	Window window{ 800, 600, gameObjects }; // Corregido para pasar el vector de GameObjects

	// Verificar si la ventana se creó correctamente
	if (!window.success) {
		cout << "Failed to create window" << endl;
		glfwTerminate();
		return -1;
	}

	Texture container{ "container.jpg", GL_TEXTURE0 };
	Texture wall{ "wall.jpg", GL_TEXTURE1 };

	Vertex vertices[]{
		//Up
		   Vertex{Vector3{0.0f, 0.5f, 0.0f}, Color::green },
		   Vertex{Vector3{0.25f, 0.0f, 0.0f}, Color::red },
		   Vertex{ Vector3{-0.25f,  0.0f, 0.0f}, Color::blue },
		//Down
		   Vertex{Vector3{-0.25f, 0.0f, 0.0f}, Color::red },
		   Vertex{Vector3{0.0f,  -0.5f, 0.0f}, Color::green },
		   Vertex{Vector3{0.25f, 0.0f, 0.0f}, Color::blue },
		//Left
		   Vertex{Vector3{-0.5f, 0.0f, 0.0f}, Color::green },
		   Vertex{Vector3{0.0f, 0.25f, 0.0f}, Color::red },
		   Vertex{Vector3{0.0f,  -0.25f, 0.0f}, Color::blue },
		//Right
		   Vertex{Vector3{0.0f, 0.25f, 0.0f}, Color::red },
		   Vertex{Vector3{0.5f, 0.0f, 0.0f}, Color::green },
		   Vertex{Vector3{0.0f, -0.25f, 0.0f}, Color::blue }
	};	   

	Mesh mesh1{vertices, size(vertices)};

	Vertex vertices2[]{

			Vertex{Vector3{0.0f, 0.25f, 0.0f}, Color::red },
			Vertex{Vector3{0.25f, 0.0f, 0.0f}, Color::green },
		    Vertex{Vector3{0.35f,  0.35f, 0.0f}, Color::blue },
			
		    Vertex{Vector3{0.25f, 0.0f, 0.0f}, Color::red },
		    Vertex{Vector3{0.35f, -0.35f, 0.0f}, Color::blue },
		    Vertex{Vector3{0.0f, -0.25f, 0.0f}, Color::green },
			
			Vertex{Vector3{0.0f, -0.25f, 0.0f}, Color::red },
			Vertex{Vector3{-0.35f, -0.35f, 0.0f}, Color::blue },
			Vertex{Vector3{-0.25f,  0.0f, 0.0f}, Color::green },
			
			Vertex{Vector3{-0.25f,  0.0f, 0.0f}, Color::red },
			Vertex{Vector3{-0.35f, 0.35f, 0.0f}, Color::blue },
			Vertex{Vector3{0.0f, 0.25f, 0.0f}, Color::green }

	};

	Mesh mesh2{ vertices2, size(vertices2) };

	//Shader vertexShader{"vertexShader.glsl", GL_VERTEX_SHADER};
	Shader vertexShader{ "vertexShader.glsl", GL_VERTEX_SHADER };
	//Shader vertexShader{ "upSideDownShader.glsl", GL_VERTEX_SHADER };
	
	Shader fragmentShader{ "FragmentShader.glsl", GL_FRAGMENT_SHADER};
	Shader textureFragmentShader{ "textureFragmentShader.glsl", GL_FRAGMENT_SHADER };
	Shader blendTextureFragmentShader{ "blendTextureFragmentShader.glsl", GL_FRAGMENT_SHADER }; 

	// -------- Create Orange Shader Program (Render Pipeline) ---------
	Material material{vertexShader, fragmentShader};
	//Material textureMaterial{ vertexShader, textureFragmentShader };
	Material textureMaterial1{ vertexShader, textureFragmentShader }; //Trying

	GameObject a{ &material, &mesh1 };
	a.red = 0.22;
	a.green = 0.5;
	a.blue = 0.5;
	
	GameObject b{ &material, &mesh2 };
	b.red = 0.43;
	b.green = 0.10;
	b.blue = 0.15;

	GameObject c{ &textureMaterial1, Mesh::createQuad(), &container};
	c.position = Vector3(0.25, 0, 0);

	GameObject d{ &textureMaterial1, Mesh::createQuad(), &wall };
	c.position = Vector3(0.5, 0, 0);


	// While the User doesn't want to Quit (X Button, Alt+F4)
	while (!window.shouldClose()) // window -> window.window
	{
		//a.rotation.z = glfwGetTime();
		//b.rotation.z = -glfwGetTime();
		//a.rotation.y = glfwGetTime();
		//b.rotation.y = -glfwGetTime();
		//a.rotation.x = glfwGetTime();
		//b.rotation.x = -glfwGetTime();
		//d.rotation.y = glfwGetTime();
		//c.rotation.z = glfwGetTime();

		window.processInput();
		
			window.clear();

		a.render();
		b.render();
		//c.render();
		//d.render();

		window.present();
	}
	// Cleans up all the GLFW stuff
	glfwTerminate();
	return 0;
}