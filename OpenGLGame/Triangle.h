#pragma once

#include "Mesh.h"
#include "Material.h"

class Triangle
{
	
	Mesh* mesh;
	Material* material;

public:
	float red;
	float green;
	float blue;

	float offsetX;
	float offsetY;
	Triangle(Material* _material, Mesh* _mesh) {
		mesh = _mesh;
		material = _material;
	}

	void render() {
		material->use();

		int tintLocation = glGetUniformLocation(material->shaderProgram, "tintColor");
		glUniform4f(tintLocation, red, green, blue, 1);

		int offSetLocation = glGetUniformLocation(material->shaderProgram, "offset");
		glUniform2f(offSetLocation, offsetX, offsetY);

		mesh->render();
	}
};

