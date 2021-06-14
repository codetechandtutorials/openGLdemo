#pragma once
#include "Utilities.h"
#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "rendering/GLSL/GLSLShader.h"
#include <memory>
#include <iostream>

extern std::unique_ptr<GLSLShader> cursor_shader;
extern std::unique_ptr<GLSLShader> _2d_shader;
extern float perspective_fov;
extern float perspective_near;
extern float perspective_far;
extern float ortho_near;
extern float ortho_far;
extern int last_vpwidth;
extern int last_vpheight;

void glfw_error_callback(int error, const char* description) {
  write_log(description);
  throw("glfw error");
}

void glfw_window_close_callback(GLFWwindow* window) {
  write_log("window closed");
}

void glfw_framebuffer_size_callback(GLFWwindow* window, int w, int h) {
  std::string the_log = "window size changed to: " + std::to_string(w) + "x" + std::to_string(h);
  write_log(the_log.c_str());
  _2d_shader->Use();
  float ASPECT_RATIO = (float)w/(float)h;
  _2d_shader->SetMat4("uProjectionMatrix", glm::perspective(perspective_fov, ASPECT_RATIO, perspective_near, perspective_far));
  //_2d_shader->SetVec2("uResolution", glm::vec2(w, h));

  float aspect = (float)w/h;
  //std::cout << "aspect ratio: " << aspect << std::endl;
  float half_height = h / 2.f; // also called ortho size
  float half_width = half_height * aspect;

  _2d_shader->SetMat4("uProjectionMatrix", glm::ortho(
    -half_width,
    half_width,
    -half_height,
    half_height,
    ortho_near,
    ortho_far));


  glViewport(0, 0, w, h);
  last_vpwidth = w;
  last_vpheight = h;
}

void glfw_mouse_movement_callback(GLFWwindow* window, double x, double y) {
  int width, height;
  glfwGetWindowSize(window, &width, &height);
  cursor_shader->Use();
#if _DEBUG
  printf("mouse pos: %f, %f\n", x, y);
  printf("to ogl screen space mouse pos: %f, %f\n", x, height - y);
#endif
  cursor_shader->SetVec2("uMousePos", glm::vec2(x, height - y));
}
