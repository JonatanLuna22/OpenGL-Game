#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;
layout (location = 2) in vec2 aTexCoord;

out vec4 vertexColor;
out vec2 texCoord;

uniform mat4 transform;

void main()

{
	gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	vertexColor = aCol;
	texCoord = aTexCoord;

}