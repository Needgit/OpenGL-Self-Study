#version 330 core

in  vec3 vColor;
in  vec2 tCoord;

out vec4 fColor;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

void main(void)
{
    fColor = mix(texture(uTexture1, tCoord), texture(uTexture2, tCoord), 1);
}