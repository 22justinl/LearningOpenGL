#version 410 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;

out vec3 v_color;

uniform mat4 u_cameraViewMatrix;
uniform mat4 u_model;

void main() {
    v_color = color;
    vec4 newPosition = u_cameraViewMatrix * u_model * vec4(position.x, position.y, position.z, 1.0f);
    gl_Position = newPosition;
}
