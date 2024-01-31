#version 330 core
out vec4 FragColor;

uniform vec4 tintColor;
uniform sampler2D diffuseTexture;


in vec4 vertexColor;
in vec2 texCoord;

void main()
{
	FragColor = texture(diffuseTexture, texCoord);
}