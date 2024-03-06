#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "../Maths/Matrix4x4.h"
#include "../Maths/Vector3.h" // Incluimos la clase Vector3 para utilizar sus métodos

class GameObject
{
	const Mesh* mesh;
	Material* material;
	Texture* texture;

public:
	float red;
	float green;
	float blue;

	Vector3 position = Vector3(0, 0, 0);
	Vector3 rotation = Vector3(0, 0, 0);

	GameObject(Material* _material, const Mesh* _mesh, Texture* _texture = nullptr) {
		mesh = _mesh;
		material = _material;
		texture = _texture;
		position = Vector3(0, 0, 0);

		red = 0.22f;
		green = 0.5f;
		blue = 0.5f;

	}

	void render() const {
		material->use();

		int tintLocation = glGetUniformLocation(material->shaderProgram, "tintColor");
		glUniform4f(tintLocation, red, green, blue + 1, 1);

		Matrix4x4 matTranslation = Matrix4x4::Translation(position);
		Matrix4x4 matRotation = Matrix4x4::Rotation(rotation);
		Matrix4x4 transform = matTranslation * matRotation;

		int transformLocation = glGetUniformLocation(material->shaderProgram, "transform");
		glUniformMatrix4fv(transformLocation, 1, GL_TRUE, &transform.m11);

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

	// Función para verificar si un punto está dentro de un triángulo
	bool isPointInsideTriangle(const Vector3& point, const Vector3& v0, const Vector3& v1, const Vector3& v2) {
		Vector3 edge1 = v1 - v0;
		Vector3 edge2 = v2 - v0;
		Vector3 normal = Vector3::Cross(edge1, edge2);
		Vector3 pointToVertex = point - v0;

		float dotNormalPointToVertex = Vector3::Dot(normal, pointToVertex);
		if (dotNormalPointToVertex < 0)
			return false;

		Vector3 projEdge1 = Vector3::Cross(pointToVertex, edge2);
		float dotNormalProjEdge1 = Vector3::Dot(normal, projEdge1);
		if (dotNormalProjEdge1 < 0)
			return false;

		Vector3 projEdge2 = Vector3::Cross(projEdge1, edge1);
		float dotNormalProjEdge2 = Vector3::Dot(normal, projEdge2);
		if (dotNormalProjEdge2 < 0)
			return false;

		return true;
	}

	void updateColorOnMouseHover(double mouseX, double mouseY, int windowWidth, int windowHeight) {

		double normalizedX = (mouseX / static_cast<double>(windowWidth)) * 2 - 1;
		double normalizedY = 1 - (mouseY / static_cast<double>(windowHeight)) * 2;

		// Triángulo superior
		if (isPointInsideTriangle(Vector3(mouseX, mouseY, 0.0f), Vector3(0.0f, 0.5f, 0.0f), Vector3(0.25f, 0.0f, 0.0f), Vector3(-0.25f, 0.0f, 0.0f))) {
			red = 1.0f; // Cambia esto al color deseado
			green = 0.0f;
			blue = 0.0f;
		}
		// Triángulo inferior
		else if (isPointInsideTriangle(Vector3(mouseX, mouseY, 0.0f), Vector3(-0.25f, 0.0f, 0.0f), Vector3(0.0f, -0.5f, 0.0f), Vector3(0.25f, 0.0f, 0.0f))) {
			red = 0.0f;
			green = 1.0f; // Cambia esto al color deseado
			blue = 0.0f;
		}
		// Triángulo izquierdo
		else if (isPointInsideTriangle(Vector3(mouseX, mouseY, 0.0f), Vector3(-0.5f, 0.0f, 0.0f), Vector3(0.0f, 0.25f, 0.0f), Vector3(0.0f, -0.25f, 0.0f))) {
			red = 0.0f;
			green = 0.0f;
			blue = 1.0f; // Cambia esto al color deseado
		}
		// Triángulo derecho
		else if (isPointInsideTriangle(Vector3(mouseX, mouseY, 0.0f), Vector3(0.0f, 0.25f, 0.0f), Vector3(0.5f, 0.0f, 0.0f), Vector3(0.0f, -0.25f, 0.0f))) {
			red = 1.0f; // Cambia esto al color deseado
			green = 1.0f;
			blue = 0.0f;
		}
		else {
			// Restaura el color original del objeto
			red = 0.22f;
			green = 0.5f;
			blue = 0.5f;
		}
	}
};

