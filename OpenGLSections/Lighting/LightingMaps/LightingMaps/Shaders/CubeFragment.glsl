#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;
in vec2 TexCoords;

out vec4 FragColor;

// material of frag shader
struct Material {
    sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light {
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
	vec3 lightDir = normalize(LightPos - FragPos); // frag position to light
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * light.diffuse * texture(material.diffuse, TexCoords).rgb;

	//specular lighting
	vec3 viewDir = normalize(-FragPos); // viewer always at (0,0,0) in view space, so viewSpace - FragPos = -FragPos
	vec3 reflectDir = reflect(-lightDir, norm); // negate light direction so its pointing from light to frag position
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * light.specular * texture(material.specular, TexCoords).rgb;

	// show emission on black surface
	vec3 emission = vec3(0.0f, 0.0f, 0.0f);
	if (texture(material.specular, TexCoords).rgb == emission)
	{
		emission = texture(material.emission, TexCoords).rgb;
	}

	// Apply phong shading
	vec3 result = ambientLight + diffuse + specular + emission;
	FragColor = vec4(result, 1.0);
}