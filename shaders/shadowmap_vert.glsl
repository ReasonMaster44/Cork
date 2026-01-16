#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 u_lightProjection;
uniform mat4 u_lightView;
uniform mat4 u_model;

void main() {
    vec3 fragPos = vec3(u_model * vec4(aPos, 1.0)); // Transform vertex position;

    gl_Position = u_lightProjection * u_lightView * vec4(fragPos, 1.0);
}