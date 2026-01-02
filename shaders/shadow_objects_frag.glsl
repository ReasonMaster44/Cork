#version 330 core

out vec4 fragColour;

flat in vec3 v_normal;
flat in vec3 v_fragPos;
in vec4 v_fragPosLight;

uniform vec3 u_lightPos;
uniform vec3 u_cameraPos;
vec3 lightColour = vec3(1.0, 1.0, 1.0);
uniform vec3 u_baseColour;

uniform sampler2D u_shadowMap;

float kernel[25] = float[](
    0.0037, 0.0146, 0.0256, 0.0146, 0.0037,
    0.0146, 0.0586, 0.0968, 0.0586, 0.0146,
    0.0256, 0.0968, 0.1502, 0.0968, 0.0256,
    0.0146, 0.0586, 0.0968, 0.0586, 0.0146,
    0.0037, 0.0146, 0.0256, 0.0146, 0.0037
);

float random(vec2 st)
{
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

float calculateShadow(vec3 lightCoords, vec3 lightDir) {
    lightCoords = (lightCoords + 1.0) / 2.0;

    if (lightCoords.z > 1.0) { return 0.0; };

    vec2 texelSize = 1.0 / vec2(textureSize(u_shadowMap, 0));

    float shadow = 0.0;
    float bias = max(0.001 * (1.0 - dot(normalize(v_normal), lightDir)), 0.002);
    float samples = 0.0;


    // Soft shadow sampling (7x7 grid)
    for (float x = -2.0; x <= 2.0; x++) {
        for (float y = -2.0; y <= 2.0; y++) {
            
            vec2 sampleOffset = vec2(x + random(vec2(x, y)), y + random(vec2(x, y))) * texelSize;
            vec2 shadowUV = clamp(lightCoords.xy + sampleOffset, 0.001, 0.999); // Clamp UV
            
            float closestDepth = texture(u_shadowMap, shadowUV).r;
            float weight = kernel[int((x + 2.0) * 5.0 + (y + 2.0))];

            if (lightCoords.z > closestDepth + bias) {
                shadow += weight; // In shadow
            }
            samples++;
        }
    }

    return 1.0 - (shadow * 0.6);
}

vec3 palette(float t) {
    vec3 colors[5];  // Define an array of colors
    colors[0] = vec3(0.929, 0.918, 0.655);  // Yellowish
    colors[1] = vec3(0.58, 0.812, 0.533);  // Light green
    colors[2] = vec3(0.314, 0.459, 0.282);  // Dark green
    colors[3] = vec3(0.275, 0.282, 0.29);   // Dark Grayish
    colors[4] = vec3(0.886, 0.898, 0.91);   // Light Grayish
    
    int numColors = 5;
    float segment = 1.0 / float(numColors - 1);  // Divide range into segments
    int index = int(floor(t / segment));  // Find the segment index
    float localT = (t - index * segment) / segment;  // Normalize t within segment

    return mix(colors[index], colors[index + 1], localT);
}

float ambientStrength = 1.;
float fogDist = 60.0;
vec3 fogColour = vec3(0.867, 0.882, 0.902);

void main() {
    vec3 lightCoords = v_fragPosLight.xyz / v_fragPosLight.w;

    vec3 normal = normalize(v_normal);
    vec3 lightDir = normalize(u_lightPos - v_fragPos);

    float diffuse = max(dot(normal, lightDir), 0.5);
    
    vec3 ambient = ambientStrength * lightColour;

    float shadow = calculateShadow(lightCoords, lightDir);

    vec3 baseColour = palette(clamp((v_fragPos.y - 6.0) / 10.0, 0.0, 1.0));

    vec3 colour = ambient * diffuse * baseColour * shadow;

    float distFromCam = distance(v_fragPos.xz, u_cameraPos.xz);

    if (distFromCam > fogDist) {
        colour = mix(colour, fogColour, clamp((distFromCam - fogDist) * 0.0, 0.0, 1.0));
    }
    
    fragColour = vec4(colour, 1.0);
}