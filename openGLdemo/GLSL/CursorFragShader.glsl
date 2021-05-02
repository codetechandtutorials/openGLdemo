#version 430
out vec4 fragColor;
uniform vec2 uMousePos;

void main()
{
	float inner_radius = 2;
	float outer_radius = 2;
	float power = 0;

	float dist = distance(uMousePos, gl_FragCoord.xy);
	if (dist > inner_radius + outer_radius)
	  discard;
	else if (dist > inner_radius)
	  power = 0;
	else 
	  power = 1;

	vec3 color = vec3(power);
	fragColor = vec4(color, 1.0);
}