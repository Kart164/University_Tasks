#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 fragPos; // координаты точки
out vec3 fragNorm; // координаты нормали в точке

uniform mat4 clipView;
uniform mat4 modelView;
uniform mat4 modelInv;

void main() {
fragPos = vec3(modelView * vec4(position, 1.0));
fragNorm = mat3(modelInv) * normal;
gl_Position = clipView * vec4(position, 1.0);
}