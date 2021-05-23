#pragma once
#include "Utilities.h"
#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "rendering/GLSL/GLSLShader.h"
#include <memory>

extern std::unique_ptr<GLSLShader> cursor_shader;
extern std::unique_ptr<GLSLShader> demo_shader;
extern float FOV;
extern float NEAR;
extern float FAR;

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
  glViewport(0, 0, w, h);
  demo_shader->Use();
  float ASPECT_RATIO = (float)w/(float)h;
  demo_shader->SetMat4("uProjectionMatrix", glm::perspective(FOV, ASPECT_RATIO, NEAR, FAR));
  demo_shader->SetVec2("uResolution", glm::vec2(w, h));

}

void glfw_mouse_movement_callback(GLFWwindow* window, double x, double y) {
  int width, height;
  glfwGetWindowSize(window, &width, &height);
  cursor_shader->Use();
  cursor_shader->SetVec2("uMousePos", glm::vec2(x, height - y));
}
