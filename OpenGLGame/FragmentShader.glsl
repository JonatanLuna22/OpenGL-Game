#version 330 core
out vec4 FragColor;
uniform vec4 tintColor;
in vec4 vertexColor;
void main()
{
	//FragColor = vertexColor;
	FragColor = tintColor;
}