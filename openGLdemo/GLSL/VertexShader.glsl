#version 430
layout (location=0) in vec3 pos;
uniform mat4 uModelMatrix;
void main(){
	vec4 final_pos = uModelMatrix * vec4(pos, 1.0);
	gl_Position = final_pos;
}