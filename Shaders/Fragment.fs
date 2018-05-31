#version 330 core

struct Material {
    sampler2D  diffuse;
    sampler2D  specular;
    float      shininess;
}; 

struct Light {
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

in  vec3 vNormal;
in  vec3 vFragment;
in  vec2 tCoord;

out vec4 fColor;

#define NR_POINT_LIGHTS 2  
uniform Light    pointLight[NR_POINT_LIGHTS];
uniform Material material;

uniform vec3 viewPos;


vec3 ambient(Light light)
{
	return light.ambient * vec3(texture(material.diffuse, tCoord));
}

vec3 diffuse(Light light, vec3 norm, vec3 lightDir)
{
	float  diff = max(dot(norm, lightDir), 0.0);
	return light.diffuse * (diff * vec3(texture(material.diffuse, tCoord)));
}

vec3 specular(Light light, vec3 norm, vec3 lightDir)
{
	vec3 viewDir = normalize(viewPos - vFragment);
	vec3 reflectDir = reflect(-lightDir, norm);
	
	float  spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	return light.specular * (spec * vec3(texture(material.specular, tCoord))); 
}

vec3 calcPointLight(Light light, vec3 norm)
{
	vec3 lightDir = normalize(light.position - vFragment);
	
	float distance    = length(light.position - vFragment);
	float attenuation = 1.0 / (light.constant + light.linear * distance + 
			light.quadratic * (distance * distance));    
	
	vec3 ambient  = attenuation * ambient(light);
	vec3 diffuse  = attenuation * diffuse (light, norm, lightDir);
	vec3 specular = attenuation * specular(light, norm, lightDir);
	
	return (ambient + diffuse + specular);
}


void main(void)
{
	vec3 norm = normalize(vNormal);
	
	vec3 lightColor = vec3(0.0);
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
        lightColor += calcPointLight(pointLight[i], norm); 
	
	fColor = /*texture(material.diffuse, tCoord) **/ vec4(lightColor, 1.0);
}
