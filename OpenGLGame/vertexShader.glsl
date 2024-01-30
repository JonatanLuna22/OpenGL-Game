#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;

out vec4 vertexColor;

//Exercise 2: Horizontal offset
//uniform float xOffset;

void main()

{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	//Exercise 1: Triangles upside down
	//gl_Position = vec4(-aPos.x, -aPos.y, -aPos.z, 1.0);
	vertexColor = aCol;
}