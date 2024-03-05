#include "Mesh.h"
const Color Color::red{ 1,0,0,1 };
const Color Color::green{ 0,1,0,1 };
const Color Color::blue{ 0,0,1,1 };
const Color Color::yellow{ 1,1,0,1 };

const Vertex Mesh::quadVertices[6]{
	// positions          // colors           // texture coords
			Vertex{Vector3{ 0.5f,  0.5f, 0.0f},   Color::red,   Vector2{1.0f, 1.0f}},   // top right
			Vertex{Vector3{ 0.5f, -0.5f, 0.0f},   Color::green,   Vector2{1.0f, 0.0f}},   // bottom right
			Vertex{Vector3{-0.5f, -0.5f, 0.0f},   Color::blue,   Vector2{0.0f, 0.0f}},   // bottom left

			Vertex{Vector3{-0.5f,  0.5f, 0.0f},   Color::yellow,   Vector2{0.0f, 1.0f}},   // top left 
			Vertex{Vector3{-0.5f, -0.5f, 0.0f},   Color::blue,   Vector2{0.0f, 0.0f}},   // bottom left
			Vertex{Vector3{ 0.5f,  0.5f, 0.0f},   Color::red,   Vector2{1.0f, 1.0f}}   // top right

};

// NEW: initialize the quad mesh as null
Mesh* Mesh::quadMesh{ nullptr };

