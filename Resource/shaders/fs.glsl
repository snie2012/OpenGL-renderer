#version 330 core
precision mediump float;

out vec3 color;

in vec3 worldPosition;
in vec3 worldNormal;
in vec2 uv;

uniform sampler2D uSampler;

const int MAX_LIGHTS = 20;
uniform float lightsCount;
uniform vec3 lightPositions[MAX_LIGHTS];
uniform vec3 lightKa[MAX_LIGHTS];
uniform vec3 lightKd[MAX_LIGHTS];
uniform vec3 lightKs[MAX_LIGHTS];

uniform vec3 mtlKa;
uniform vec3 mtlKd;
uniform vec3 mtlKs;

uniform float shininess;
uniform float tFlag;

void main() {
    vec3 finalLight;;

    vec3 ka, kd, ks;

    if (tFlag > 0.0) {
        ka = vec3(0.2, 0.2, 0.2);
        kd = texture(uSampler, uv).rgb;
        ks = vec3(0.1, 0.1, 0.1);
    } else {
        ka = mtlKa;
        kd = mtlKd;
        ks = mtlKs;
    }

    float shine;
    if (shininess < 0.0) {
        shine = 10.0;
    } else {
        shine = shininess;
    };

    vec3 viewDirection = normalize(-worldPosition);

    for (int i = 0; i < int(lightsCount); i++) {
        vec3 lightDirection = normalize(lightPositions[i] - worldPosition);
        float lambert = max(dot(lightDirection, worldNormal), 0.0);

        vec3 ambient = ka * lightKa[i];
        vec3 diffuse = (kd * vec3(lambert)) * lightKd[i];
        vec3 specular = vec3(0.0);
        
        if (lambert > 0.0) {
            vec3 halfVector = normalize(lightDirection + viewDirection);
            float specularCoeff = pow(max(dot(halfVector, worldNormal), 0.0), shine);
            specular = ks * vec3(specularCoeff) * lightKs[i];
        }
        
        finalLight += (ambient + diffuse + specular);
    }

    color = finalLight;
}


















