#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;

out vec4 vertexColor;
uniform vec2 offset;

void main()

{
	gl_Position = (vec4(aPos.x, aPos.y, aPos.z, 1.0) + vec4(offset.xy,0,0));

	vertexColor = aCol;
}