#version 330 core

in vec2 v_textureCoord;

out vec4 fragColour;

uniform vec3 u_baseColour;

void main() {
    vec3 colour = u_baseColour;
    
    fragColour = vec4(colour, 1.0);
}
