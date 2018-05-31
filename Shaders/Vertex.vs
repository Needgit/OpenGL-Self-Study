#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 vNormal;
out vec3 vFragment;
out vec2 tCoord;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;


void main(void)
{
	gl_Position = projection * view * world * vec4(aPos, 1.0);
	
	// The fragment position is calculated in world space:
	vFragment = vec3(world * vec4(aPos, 1.0));
	
	vNormal	= mat3(transpose(inverse(world))) * aNormal; 
	tCoord  = aTexCoord;
}
