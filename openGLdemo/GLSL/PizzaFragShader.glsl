#version 430
out vec4 fragColor;
//uniform vec2 uResolution;
uniform vec2 uMousePos;

void main()
{
	float radius = 10;

	float dist = distance(uMousePos, gl_FragCoord.xy);
	if (dist > radius)
	  discard;

	vec3 color = vec3(1);

	fragColor = vec4(color, 1.0);
}