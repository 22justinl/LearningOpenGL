#version 410 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;

out vec3 v_color;

void main() {
    v_color = color;
    vec4 newPosition = vec4(position.x, position.y, position.z, 1.0f);
    gl_Position = newPosition;
}
