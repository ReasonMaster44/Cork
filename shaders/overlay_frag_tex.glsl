#version 330 core

in vec2 v_texCoords;

out vec4 fragColour;

uniform sampler2D u_texture;

void main() {
    vec4 textureColour = texture(u_texture, (v_texCoords));

    vec4 colour = textureColour;

    fragColour = colour;
}
