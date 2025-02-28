#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	float ambientStrength = 0.1f;
	vec3 ambientLight = ambientStrength * lightColor;
	vec3 result = ambientLight * objectColor;

	FragColor = vec4(result, 1.0);
}