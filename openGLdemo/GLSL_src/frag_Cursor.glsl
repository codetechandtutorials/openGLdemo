#version 430
out vec4 fragColor;
uniform vec2 uMousePos;
uniform float uRadius;
// draw a 1/8 circle to terribly emulate a mouse cursor - todo(anyone): make this cooler
void main()
{
  
  float color_val = 0;

  // skip 3 directional quadrents and part of the 4th quadrent
  vec2 dir = gl_FragCoord.xy - uMousePos;
  if (dir.x < 0 || dir.y > 0 || dir.x > -dir.y)
    discard;

  // color within radius of leftover directional quadrent
  float dist = distance(uMousePos, gl_FragCoord.xy);
  if (dist > uRadius)
    discard;
  else if (dist > uRadius)
    color_val = 0;
  else 
    color_val = 1;

  vec3 color = vec3(color_val);
  fragColor = vec4(color, 1.0);
}
