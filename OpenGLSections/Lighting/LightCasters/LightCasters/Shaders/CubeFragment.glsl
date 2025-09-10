#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

// material of frag shader
struct Material {
    sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

void main()
{
	//ambient lighting
	vec3 ambientLight = light.ambient * texture(material.diffuse, TexCoords).rgb;

	//diffuse lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-light.direction); // frag position to light 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * light.diffuse * texture(material.diffuse, TexCoords).rgb;

	//specular lighting
	vec3 viewDir = normalize(-FragPos); // viewer always at (0,0,0) in view space, so viewSpace - FragPos = -FragPos
	vec3 reflectDir = reflect(-lightDir, norm); // negate light direction so its pointing from light to frag position
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * light.specular * texture(material.specular, TexCoords).rgb;


	// Apply phong shading
	vec3 result = ambientLight + diffuse + specular;
	FragColor = vec4(result, 1.0);
}