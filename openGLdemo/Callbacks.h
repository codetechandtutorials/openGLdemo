#pragma once
#include "Utilities.h"
#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void glfw_error_callback(int error, const char* description)
{
	write_log(description);
	throw("glfw error");
}

static void glfw_window_close_callback(GLFWwindow* window)
{
	write_log("window closed");
}

static void glfw_framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	std::string the_log = "window size changed to: " + std::to_string(w) + "x" + std::to_string(h);
	write_log(the_log.c_str());
	glViewport(0, 0, w, h);
}
