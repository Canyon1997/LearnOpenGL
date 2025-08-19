#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

uniform vec3 objectColor;
uniform vec3 lightColor;

out vec4 FragColor;

void main()
{
	//ambient lighting
	float ambientStrength = 0.1f;
	vec3 ambientLight = ambientStrength * lightColor;

	//diffuse lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos); // frag position to light
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	//specular lighting
	float specularStrength = 2.0f;
	vec3 viewDir = normalize(-FragPos); // viewer always at (0,0,0) in view space, so viewSpace - FragPos = -FragPos
	vec3 reflectDir = reflect(-lightDir, norm); // negate light direction so its pointing from light to frag position
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
	vec3 specular = specularStrength * spec * lightColor;

	// Apply phong shading
	vec3 result = (ambientLight + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0);
}