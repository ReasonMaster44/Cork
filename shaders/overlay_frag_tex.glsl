#version 330 core

in vec2 v_textureCoord;

out vec4 fragColour;

uniform sampler2D u_texture;

void main() {
    vec3 textureColour = texture(u_texture, (v_textureCoord)).xyz;

    fragColour = vec4(textureColour, 1.0);
}
