#version 430
out vec4 fragColor;

in vec2 pass_texuv;

uniform sampler2D uTexture; 

void main() {
    fragColor = texture(uTexture, pass_texuv);
}