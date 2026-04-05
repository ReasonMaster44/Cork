#version 330 core

out vec4 fragColour;

flat in vec3 v_normal;
in vec3 v_fragPos;
in vec4 v_fragPosLight;
flat in vec3 v_colour;

uniform vec3 u_cameraPos;
uniform vec3 u_lightPos;
uniform vec3 u_baseColour;
uniform sampler2D u_shadowMap;

vec4 f = texture(u_shadowMap, vec2(0.0));

vec3 lightColour = vec3(1.0, 1.0, 1.0);

float ambientStrength = 1.;

float kernel[25] = float[](
    0.0037, 0.0146, 0.0256, 0.0146, 0.0037,
    0.0146, 0.0586, 0.0968, 0.0586, 0.0146,
    0.0256, 0.0968, 0.1502, 0.0968, 0.0256,
    0.0146, 0.0586, 0.0968, 0.0586, 0.0146,
    0.0037, 0.0146, 0.0256, 0.0146, 0.0037
);

float random(vec2 st) { return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123); }

float calculateShadow() {
    vec3 lightCoords = v_fragPosLight.xyz / v_fragPosLight.w;
    lightCoords = lightCoords * 0.5 + 0.5; 

    if (lightCoords.z > 1.0) { return 0.0; };

    vec2 texelSize = 1.0 / vec2(textureSize(u_shadowMap, 0));

    float shadow = 0.0;
    float bias = 0.05;
    float samples = 0.0;

    for (float x = -2.0; x <= 2.0; x++) {
        for (float y = -2.0; y <= 2.0; y++) {
            
            vec2 sampleOffset = vec2(x, y) * texelSize;//vec2(x + random(vec2(x, y)), y + random(vec2(x, y))) * texelSize;
            vec2 shadowUV = clamp(lightCoords.xy + sampleOffset, 0.001, 0.999); // Clamp UV
            
            float closestDepth = texture(u_shadowMap, shadowUV).r;
            float weight = kernel[int((x + 2.0) * 5.0 + (y + 2.0))];

            if (lightCoords.z > closestDepth + bias) {
                shadow += weight; // In shadow
            }
            samples++;
        }
    }

    return shadow;
}

float fogDist = 15.0;
void main() {
    vec3 baseColour = v_colour;
    vec3 normal = normalize(v_normal);
    vec3 ambient = ambientStrength * baseColour;

    vec3 lightDir = normalize(u_lightPos - v_fragPos);
    float diffuse = max(dot(normal, lightDir), 0.1);

    float shadow = calculateShadow();

    vec3 colour = (ambient + (1.0 - shadow)) * diffuse * baseColour;
    
    float fragToCamDist = distance(v_fragPos, u_cameraPos);
    if (fragToCamDist > fogDist) {
        colour = mix(colour, vec3(0.784, 0.851, 0.902), clamp((fragToCamDist - fogDist) * 0.03, 0.0, 1.0));
    }
    
    
    fragColour = vec4(colour, 1.0);
}