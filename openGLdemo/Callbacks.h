#pragma once
#include "Utilities.h"
#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "rendering/GLSL/GLSLShader.h"

extern GLSLShader *cursorShader;
extern GLSLShader *overlayerfragshader;

void glfw_error_callback(int error, const char* description)
{
	write_log(description);
	throw("glfw error");
}

void glfw_window_close_callback(GLFWwindow* window)
{
	write_log("window closed");
}

void glfw_framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	std::string the_log = "window size changed to: " + std::to_string(w) + "x" + std::to_string(h);
	write_log(the_log.c_str());
	glViewport(0, 0, w, h);
	overlayerfragshader->Use();
	overlayerfragshader->SetVec2("uResolution", glm::vec2(w, h));
}

void glfw_mouse_movement_callback(GLFWwindow* window, double x, double y)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	cursorShader->Use();
	cursorShader->SetVec2("uMousePos", glm::vec2(x, height - y));
}
