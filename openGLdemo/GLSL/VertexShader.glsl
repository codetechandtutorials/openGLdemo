#version 430
layout (location=0) in vec3 pos;
layout (location=1) in vec3 color;
layout (location=0) out vec3 passColor;
uniform mat4 uModelMatrix;
void main()
{
	passColor = color;
	vec4 final_pos = uModelMatrix * vec4(pos, 1.0);
	gl_Position = final_pos;
}