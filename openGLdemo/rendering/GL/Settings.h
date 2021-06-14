#pragma once
#include <glad/glad.h>
#include <cstdarg>

/// <summary>
/// Sets the OpenGL context draw background color for areas were nothing is drawn.
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="w"></param>
void SetClearColor(const float x, const float y, const float z, const float w) {
  glClearColor(x, y, z, w);
}

/// <summary>
/// Toggles OpenGL multisampling to on or off.
/// </summary>
/// <param name="desired_status"></param>
void SetMSAA(const bool desired_status) {
  if (desired_status)
   glEnable(GL_MULTISAMPLE);
  else
   glDisable(GL_MULTISAMPLE);
}

/// <summary>
/// Toggles OpenGL Alpha Blending to on or off.
/// </summary>
/// <param name="desired_status"></param>
void SetBlend(const bool desired_status) {
  if (desired_status){
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
  } else {
    glDisable(GL_BLEND);
  }
}