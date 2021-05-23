#pragma once
#include <glad/glad.h>
#include <stdio.h>

void printGLinfo() {
  const GLubyte* vendor = glGetString(GL_VENDOR);
  printf("GL Vendor : %s\n", vendor);

  const GLubyte* renderer = glGetString(GL_RENDERER);
  printf("GL Renderer : %s\n", renderer);

  const GLubyte* version = glGetString(GL_VERSION);
  printf("GL Version (string) : %s\n", version);

  GLint major, minor;
  glGetIntegerv(GL_MAJOR_VERSION, &major);
  glGetIntegerv(GL_MINOR_VERSION, &minor);
  printf("GL Version (integer) : %d.%d\n", major, minor);

  const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
  printf("GLSL Version : %s\n", glslVersion);
}
