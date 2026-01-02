#version 330 core

in vec2 v_texCoords;
out vec4 fragColour;

uniform sampler2D u_shadowMap;

void main() {
    float depth = texture(u_shadowMap, v_texCoords).r;
    fragColour = vec4(vec3(depth), 1.0); // Display depth as grayscale
}