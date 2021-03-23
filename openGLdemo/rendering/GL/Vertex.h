#pragma once
struct Vertex
{
	Vertex(float posx, float posy, float posz, float colorr, float colorg, float colorb) 
	{
		pos[0] = posx;
		pos[1] = posy;
		pos[2] = posz;
		color[0] = colorr;
		color[1] = colorg;
		color[2] = colorb;
	};
	float pos[3];
	float color[3];
};