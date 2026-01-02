#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 textureCoord;

out vec2 v_textureCoord;

uniform mat4 u_model;
uniform mat4 u_projection;

void main() {
    v_textureCoord = textureCoord;

    vec4 position = u_projection * u_model * vec4(pos, 0.0, 1.0);

    gl_Position = position;
}