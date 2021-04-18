#version 430
layout (location=0) in vec3 passColor;
out vec4 fragColor;
void main()
{
	fragColor = vec4(passColor, 1.0);
}