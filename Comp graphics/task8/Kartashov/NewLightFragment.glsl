#version 330 core
out vec4 color;
uniform vec3 pathColor;
void main() {
	color = vec4(pathColor, 1.0f);
}