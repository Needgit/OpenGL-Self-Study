#version 330 core

struct Material {
    vec3  ambient;
    vec3  diffuse;
    vec3  specular;
    float shininess;
    
    sampler2D textureDiffuse;
}; 

in  vec3 vNormal;
in  vec3 vFragment;
in  vec2 tCoord;

out vec4 fColor;

uniform Material material;

uniform vec3 lightPos;  
uniform vec3 lightColor;

void main(void)
{
	vec3 norm     = normalize(vNormal);
	vec3 lightDir = normalize(lightPos - vFragment);
	float diff    = max(dot(norm, lightDir), 0.0);
	vec3 diffuse  = diff * lightColor;
	
	vec3 light =  material.ambient + diffuse;

	fColor = texture(material.textureDiffuse, tCoord) * vec4(light, 1.0);
}