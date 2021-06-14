#version 430
out vec4 fragColor;

uniform vec3 uColor;

void main() {
    fragColor = vec4(uColor, 1.0);
}