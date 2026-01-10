#version 330 core

in vec2 v_texCoords;

out vec4 fragColour;

uniform sampler2D u_texture;

void main() {
    vec3 textureColour = texture(u_texture, (v_texCoords)).xyz;

    vec3 colour = textureColour;

    fragColour = vec4(colour, 1.0);
}
