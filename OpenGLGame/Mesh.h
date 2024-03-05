#pragma once

#include "glad/glad.h"
#include <cstddef>
#include "../Maths/Vector3.h"
#include <algorithm>

struct Vector2 {
	float x, y;
};

struct Color {

	static const Color red; 
	static const Color green;
	static const Color blue;
	static const Color yellow;

	float r, g, b, a;
};

struct Vertex {
	Vector3 pos; //position
	Color col{ 1,1,1,1 };
	Vector2 uv; //texture coordinates
};

class Mesh

{
	unsigned int VAO;
	size_t vertexCount;

const static Vertex quadVertices[6];

static Mesh* quadMesh;

public:

	
	static const Mesh* createQuad() {
		if (quadMesh == nullptr) {
			quadMesh = new Mesh{ Mesh::quadVertices, std::size(Mesh::quadVertices) };
		}
		return quadMesh; 
	}
	

	void render() const {
		glBindVertexArray(VAO);
		// This is to see the lines but not the volumes.
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	}

	Mesh(const Vertex* vertices, size_t count) {
		vertexCount = count;
		// ----- Create Vertex Array Object, which makes changing between VBOs easier -----
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// ----- Create Array Buffer on the GPU and copy our vertices to GPU -------
		unsigned int VBO; // variable to store buffer id
		glGenBuffers(1, &VBO); // ask open gl to create a buffer
		glBindBuffer(GL_ARRAY_BUFFER, VBO); // tell gl to use this buffer
		glBufferData(GL_ARRAY_BUFFER, // copy our vertices to the buffer
			sizeof(Vertex) * count, vertices, GL_STATIC_DRAW);

		// ------ configure vertex attribute(s) (currently it's just one, the position) -----
		// so the vertex shader understands, where to find the input attributes, in this case position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		glEnableVertexAttribArray(2);
	}
};

