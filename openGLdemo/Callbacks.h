#pragma once
#include "Utilities.h"
#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "rendering/GLSL/GLSLShader.h"
#include "cursor/cursor.h"
#include <memory>
#include <iostream>

extern std::unique_ptr<GLSLShader> cursor_shader;
extern std::unique_ptr<GLSLShader> _2d_shader;
extern float perspective_fov;
extern float perspective_near;
extern float perspective_far;
extern float ortho_near;
extern float ortho_far;

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
  float aspect_ratio = (float)w/h;
  //_2d_shader->SetMat4("uProjectionMatrix", glm::perspective(perspective_fov, aspect_ratio, perspective_near, perspective_far));
  
  float half_height = h / 2.f; // also called ortho size
  float half_width = half_height * aspect_ratio;
  _2d_shader->SetMat4("uProjectionMatrix", glm::ortho(
    -half_width,
    half_width,
    -half_height,
    half_height,
    ortho_near,
    ortho_far));

  glViewport(0, 0, w, h);
}

void glfw_mouse_movement_callback(GLFWwindow* window, double x, double y) {
  cursor::Update(x, y);
}
