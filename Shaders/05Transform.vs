#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 vColor;
out vec2 tCoord;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
	gl_Position = projection * view * world * vec4(aPos, 1.0);
	vColor	= aColor;
	tCoord  = aTexCoord;
}