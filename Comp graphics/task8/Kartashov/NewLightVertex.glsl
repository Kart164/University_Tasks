#version 330 core
layout (location = 0) in vec3 position;
uniform mat4 clipView;
void main() {
	gl_Position = clipView * vec4(position, 1.0);
}