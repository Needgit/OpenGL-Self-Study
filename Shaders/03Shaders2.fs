#version 330 core

in  vec3 vColor;
out vec4 fColor;

void main(void)
{
	fColor = vec4(vColor, 1.0f);
}