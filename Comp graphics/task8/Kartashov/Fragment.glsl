#version 330 core

struct Light {
vec3 ambient;
vec3 diffuse;
vec3 specular;
};

struct Material {
vec3 ambient;
vec3 diffuse;
vec3 specular;
float shininess;
};

in vec3 fragPos;
in vec3 fragNorm;

out vec4 color;

uniform Material material;
uniform Light light;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
vec3 norm = normalize(fragNorm);
vec3 lightDir = normalize(lightPos - fragPos);
float cosTheta = max(dot(norm, lightDir), 0.0);

float powOfCos;
if (cosTheta > 0.0) {
vec3 viewDir = normalize(viewPos - fragPos);
vec3 lightDirR = reflect(-lightDir, norm);
powOfCos = pow(max(dot(viewDir, lightDirR), 0.0), material.shininess);
}
else
powOfCos = 0.0;

vec3 ambient = light.ambient * material.ambient;
vec3 diffuse = light.diffuse * cosTheta * material.diffuse;
vec3 specular = light.specular * powOfCos * material.specular;

vec3 result = ambient + diffuse + specular;
color = vec4(result, 1.0);
}
