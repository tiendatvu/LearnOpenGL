#version 330

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

uniform mat4 transform;

out vec4 ourColor;

void main() {
    gl_Position = transform * vec4(aPosition, 1.0f);
    ourColor = vec4(aColor, 1.0f);
}