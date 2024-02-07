#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Texture.h"


class Triangle
{
	Mesh* mesh;
	Material* material;
	Texture* texture;

public:
	float red;
	float green;
	float blue;

	float offsetX;
	float offsetY;

	Triangle(Material* _material, Mesh* _mesh, Texture* _texture = nullptr) {
		mesh = _mesh;
		material = _material;
		texture = _texture;
	}

	void render() {
		material->use();

		int tintLocation = glGetUniformLocation(material->shaderProgram, "tintColor");
		glUniform4f(tintLocation, red, green, blue, 1);

		int offSetLocation = glGetUniformLocation(material->shaderProgram, "offset");
		glUniform2f(offSetLocation, offsetX, offsetY);

		int diffuseLocation = glGetUniformLocation(material->shaderProgram, "diffuseTexture");
		glUniform1i(diffuseLocation, 0);
		glActiveTexture(GL_TEXTURE0);
		if (texture != nullptr)
			glBindTexture(GL_TEXTURE_2D, texture->textureId);
		else
			glBindTexture(GL_TEXTURE_2D, 0);

		int blendLocation = glGetUniformLocation(material->shaderProgram, "blendTexture");
		glUniform1i(blendLocation, 1);



		mesh->render();
	}
};

