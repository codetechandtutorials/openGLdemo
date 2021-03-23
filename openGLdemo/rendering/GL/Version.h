#pragma once
#include <glad/glad.h>
#include <stdio.h>
#include "../../Utilities.h"

void printGLinfo()
{
	const GLubyte* vendor = glGetString(GL_VENDOR);
	write_log("GL Vendor : ", vendor);

	const GLubyte* renderer = glGetString(GL_RENDERER);
	write_log("GL Renderer : ", renderer);
	
	const GLubyte* version = glGetString(GL_VERSION);
	write_log("GL Version (string) : ", version);
	
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	write_log("GL Version (integer) : ", major, minor);
	
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	write_log("GLSL Version : ", glslVersion);
}
