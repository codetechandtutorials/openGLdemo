#include "Callbacks.h"
#include "Input.h"
#include "Utilities.h"
#include "rendering/GL/DrawDetails.h"
#include "rendering/GL/MeshLoader.h"
#include "rendering/GL/TextureLoader.h"
#include "rendering/GL/Settings.h"
#include "rendering/GL/Draw.h"
#include "rendering/GL/Version.h"
#include "rendering/GLSL/GLSLShader.h"
#include "rendering/GLSL/QueryShader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <fstream>
#include <memory>
#include <stb_image.h>
#include "2dGame/sidescroller.h"
#include "cursor/cursor.h"

// global states, access in other source files using extern
static float perspective_fov = glm::radians(45.f);
static float perspective_near = .0001f;
static float perspective_far = 3000.f;
static float ortho_near = .0001f;
static float ortho_far = 3000.f;
static const int default_window_width = 800;
static const int default_window_height = 600;
static int last_vpwidth = default_window_width;
static int last_vpheight = default_window_height;
GLFWwindow* window;
//std::vector<DrawDetails> ourDrawDetails;
std::vector<DrawStripDetails> ourDrawStripDetails;
// end globals

int main(int argc, char** argv) {
  // setup GLFW window and system
  glfwSetErrorCallback(glfw_error_callback);
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = glfwCreateWindow(default_window_width, default_window_height, extract_prog_name(argv[0]), nullptr, nullptr);
  glfwMakeContextCurrent(window);

  // set window to opengl context
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glViewport(0, 0, default_window_width, default_window_height);

  // print open info in our console
  printGLinfo();

  // setup our default callbacks (see Callbacks.h)
  glfwSetWindowCloseCallback(window, glfw_window_close_callback);
  glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
  glfwSetCursorPosCallback(window, glfw_mouse_movement_callback);


  // disable the OS mouse cursor on our applications (because we are rendering our own)
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  cursor::Setup();

  sidescroller::Setup();

  glfwMaximizeWindow(window);


  const GLfloat _plane_neg1_to_1[] = {
    -1 /*left*/,   1 /*top*/,
    -1 /*left*/,  -1 /*bottom*/,
     1 /*right*/,  1 /*top*/,
     1 /*right*/, -1 /*bottom*/
  };

  ourDrawStripDetails.push_back(
    UploadMesh(
      _plane_neg1_to_1,
      sizeof(_plane_neg1_to_1) / sizeof(_plane_neg1_to_1[0])
    )
  );

  double prev_time = glfwGetTime();
  //SetClearColor(.3f, .3f, .65f, 0.f);
  while (!glfwWindowShouldClose(window)) {
    // HANDLE KEYPRESS
    ProcessInput(window);

    sidescroller::PlayerControls(window);

    double current_time = glfwGetTime();
    double dt = current_time - prev_time;
    prev_time = current_time;
    static double accumTime = 0;
    accumTime += dt;

    sidescroller::Update(dt);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sidescroller::Render(ourDrawStripDetails);

    cursor::Render(ourDrawStripDetails);

    // show all the stuff we drew
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // unloaded all our data from the graphics card
  //UnloadMesh(ourDrawDetails);
  UnloadMesh(ourDrawStripDetails);

  glfwTerminate();
  return 0;
}
