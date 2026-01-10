#version 330 core

out vec4 fragColour;

flat in vec3 v_normal;
in vec3 v_fragPos;
in vec4 v_fragPosLight;
flat in vec3 v_colour;

uniform vec3 u_lightPos;
uniform vec3 u_baseColour;
uniform sampler2D u_shadowMap;

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

float calculateShadowOld() {
    vec3 lightCoords = v_fragPosLight.xyz / v_fragPosLight.w;
    lightCoords = lightCoords * 0.5 + 0.5; 

    if (lightCoords.z > 1.0) { return 0.0; };

    vec2 texelSize = 1.0 / vec2(textureSize(u_shadowMap, 0));

    float shadow = 0.0;
    float bias = 0.002;
    float samples = 0.0;

    // Soft shadow sampling (7x7 grid)
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

float calculateShadow() {
    vec3 projCoords = v_fragPosLight.xyz / v_fragPosLight.w;
    projCoords = projCoords * 0.5 + 0.5; 
    float closestDepth = texture(u_shadowMap, projCoords.xy).r; 
    float currentDepth = projCoords.z;

    float bias = 0.005;
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    
    return shadow;
}

void main() {
    vec3 baseColour = v_colour;
    vec3 normal = normalize(v_normal);
    vec3 ambient = ambientStrength * baseColour;

    vec3 lightDir = normalize(u_lightPos - v_fragPos);
    float diffuse = max(dot(normal, lightDir), 0.1);

    float shadow = calculateShadowOld();//calculateShadow(lightCoords, lightDir);

    vec3 colour = (ambient + (1.0 - shadow)) * diffuse * baseColour;

    fragColour = vec4(colour, 1.0);
}