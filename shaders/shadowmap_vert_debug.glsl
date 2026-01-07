#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 v_texCoords;


void main() {
    v_texCoords = 1.0 - aTexCoords;

    gl_Position = vec4((aPos - vec2(0.5)) * 2.0, 0.0, 1.0);
}