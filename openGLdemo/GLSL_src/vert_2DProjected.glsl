#version 430
layout (location=0) in vec2 pos;
//layout (location=1) in vec2 texuv;

out vec2 pass_texuv;

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

void main(){
//	pass_texuv = clamp(pos, 0.0, 1.0);
    pass_texuv = vec2((pos.x+1.0)/2.0, 1-(pos.y+1.0)/2.0);
	vec4 final_pos = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(pos, 0.0, 1.0);
	gl_Position = final_pos;
}
