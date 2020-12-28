#pragma once

struct Vertex 
{
	Vertex(float x, float y, float z)
	{
		Pos[0] = x;
		Pos[1] = y;
		Pos[2] = z;
	}

	float Pos[3] = {0.f, 0.f, 0.f};  // x y z
};

struct DrawDetails
{
	DrawDetails(uint32_t v, uint32_t e)
	{
		vao = v;
		numElements = e;
	}
	uint32_t vao = 0;
	uint32_t numElements = 0;
};
