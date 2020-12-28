#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Callbacks.h"
#include "Utilities.h"
#include "Vertex.h"
#include <vector>
#include "rendering/OpenGLLoader.h"
#include "rendering/OpenGLDraw.h"
#include "Input.h"

int main(int argc, char** argv)
{
	glfwSetErrorCallback(glfw_error_callback);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	GLFWwindow* window = glfwCreateWindow(800, 600, extract_version(argv[0]), nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSetWindowCloseCallback(window, glfw_window_close_callback);
	glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
	glClearColor(.2f, .2f, .6f, 0.f);
	std::vector<DrawDetails> ourDrawDetails;
	{
		// CREATE OBJECT TO DISPLAY (POINTS) C++
		std::vector<Vertex> obj_pts;
		obj_pts.emplace_back(.5f, -.5f, 0.f);
		obj_pts.emplace_back(-.5f, -.5f, 0.f);
		obj_pts.emplace_back(0.f, .5f, 0.f);

		std::vector<uint32_t> elem = { 0, 1, 2 };

		// UPLOAD DATA TO GRAPHICS CARD
		ourDrawDetails.push_back(UploadMesh(obj_pts, elem));
	}

	while (!glfwWindowShouldClose(window))
	{
		// HANDLE KEYPRESS
		ProcessInput(window);
		glClear(GL_COLOR_BUFFER_BIT);
		// RENDER OUR OBJECT
		Draw(ourDrawDetails);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// UNLOAD DATA FROM GRAPHICS CARD
	UnloadMesh(ourDrawDetails);

	glfwTerminate();
	return 0;
}