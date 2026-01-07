#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 colour;

flat out vec3 v_normal;
out vec3 v_fragPos;
out vec4 v_fragPosLight;
flat out vec3 v_colour;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform mat4 u_lightProjection;
uniform mat4 u_lightView;

void main() {
    v_normal = normalize(mat3(u_model) * normal);
    
    v_fragPos = vec3(u_model * vec4(pos, 1.0)); // Transform vertex position;

    v_fragPosLight = u_lightProjection * vec4(v_fragPos, 1.0);

    v_colour = colour;

    vec4 position = u_projection * u_view * vec4(v_fragPos, 1.0);

    gl_Position = position;
}