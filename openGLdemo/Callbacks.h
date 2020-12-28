#pragma once
#include <cstdio>
#include "Utilities.h"

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
	glViewport(0, 0, w, h);
}
