/*
#version 330 core

out vec4 fragColour;

flat in vec3 v_normal;

uniform vec3 u_baseColour;

void main() {
    vec3 n = normalize(v_normal);

    float factor;

    if (abs(n.x) > 0.9)
        factor = 0.9;   // ±X face
    else if (abs(n.y) > 0.9)
        factor = 1.1;   // ±Y face
    else
        factor = 1.0;   // ±Z face

    vec3 colour = u_baseColour * factor;

    fragColour = vec4(colour, 1.0);
}
*/

#version 330 core

out vec4 fragColour;

flat in vec3 v_normal;
in vec3 v_fragPos;
in vec4 v_fragPosLight;

uniform vec3 u_lightPos;
uniform vec3 u_baseColour;

vec3 lightColour = vec3(1.0, 1.0, 1.0);

float ambientStrength = 1.;

void main() {
    vec3 lightCoords = v_fragPosLight.xyz / v_fragPosLight.w;

    vec3 normal = normalize(v_normal);
    vec3 lightDir = normalize(u_lightPos - v_fragPos);

    float diffuse = max(dot(normal, lightDir), 0.5);
    vec3 ambient = ambientStrength * lightColour;

    vec3 colour = ambient * diffuse * u_baseColour;
    
    fragColour = vec4(colour, 1.0);
}