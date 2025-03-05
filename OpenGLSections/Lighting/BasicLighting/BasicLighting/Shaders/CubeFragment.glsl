#version 330 core

in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

out vec4 FragColor;

void main()
{
	//ambient lighting
	float ambientStrength = 0.1f;
	vec3 ambientLight = ambientStrength * lightColor;

	//diffuse lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;


	vec3 result = (ambientLight + diffuse) * objectColor;
	FragColor = vec4(result, 1.0);
}