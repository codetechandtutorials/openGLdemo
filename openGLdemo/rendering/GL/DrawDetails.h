#pragma once
#include <glad/glad.h>

struct DrawDetails {
  DrawDetails(GLuint v, GLuint e) {
    vao = v;
    numElements = e;
  }
  GLuint vao = 0;
  GLuint numElements = 0;
};

struct DrawStripDetails {
  DrawStripDetails(GLuint v, GLuint c) {
    vao = v;
    count = c;
  }
  GLuint vao = 0;
  GLuint count = 0;
};
