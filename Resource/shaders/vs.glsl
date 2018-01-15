# version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normalPosition;

uniform mat4 MVP;

out vec2 uv;
out vec3 worldPosition;
out vec3 worldNormal;

void main() {
    vec4 tempP = MVP * vec4(vertexPosition, 1.0);
    worldPosition = vec3(tempP) / tempP.w;

    vec4 tempN = MVP * vec4(normalPosition, 0.0);
    worldNormal = normalize(vec3(tempN));

    uv = vertexUV;

    gl_Position = MVP * vec4(vertexPosition, 1.0);
}