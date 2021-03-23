#pragma once
#include <glad/glad.h>

struct DrawDetails
{
	DrawDetails(GLuint v, GLuint e)
	{
		vao = v;
		numElements = e;
	}
	GLuint vao = 0;
	GLuint numElements = 0;
};
