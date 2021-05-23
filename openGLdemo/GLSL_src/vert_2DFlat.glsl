#version 430
layout (location=0) in vec2 pos;
void main(){
	vec4 final_pos = vec4(pos, 0.0, 1.0);
	gl_Position = final_pos;
}