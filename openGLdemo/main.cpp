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
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "2dGame/sidescroller.h"

// global states, access in other source files using extern
static std::unique_ptr<GLSLShader> cursor_shader;
static std::unique_ptr<GLSLShader> _2d_shader;
//static std::unique_ptr<GLSLShader> _3d_shader;
static float perspective_fov = glm::radians(45.f);
static float perspective_near = .0001f;
static float perspective_far = 3000.f;
static float ortho_near = .0001f;
static float ortho_far = 3000.f;
static const int default_window_width = 800;
static const int default_window_height = 600;
static int last_vpwidth = default_window_width;
static int last_vpheight = default_window_height;
// end globals

int main(int argc, char** argv) {
  // setup GLFW window and system
  glfwSetErrorCallback(glfw_error_callback);
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window = glfwCreateWindow(default_window_width, default_window_height, extract_prog_name(argv[0]), nullptr, nullptr);
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

  // setup a custom mouse cursor shader
  std::string vert_code = ReadFileToString("..\\openGLdemo\\GLSL_src\\vert_2DFlat.glsl");
  std::string frag_code = ReadFileToString("..\\openGLdemo\\GLSL_src\\frag_Cursor.glsl");
  cursor_shader = std::make_unique<GLSLShader>(vert_code.c_str(), frag_code.c_str());
  QueryInputAttribs(cursor_shader->GetHandle());
  QueryUniforms(cursor_shader->GetHandle());
  cursor_shader->Use();
  cursor_shader->SetFloat("uRadius", 16);

  // disable the OS mouse cursor on our applications (because we are rendering our own)
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  sidescroller::Setup();

  ////prep
  //float aspect = (float)default_window_width / default_window_height;
  //float half_height = default_window_height / 2.f; // also called ortho size
  //float half_width = half_height * aspect;
  //// setup a to draw a 2d world
  //vert_code = ReadFileToString("..\\openGLdemo\\GLSL_src\\vert_2DProjected.glsl");
  //frag_code = ReadFileToString("..\\openGLdemo\\GLSL_src\\frag_Colored.glsl");
  //_2d_shader = std::make_unique<GLSLShader>(vert_code.c_str(), frag_code.c_str());
  //QueryInputAttribs(_2d_shader->GetHandle());
  //QueryUniforms(_2d_shader->GetHandle());
  //_2d_shader->Use();
  //_2d_shader->SetMat4("uProjectionMatrix", glm::ortho(-half_width, half_width, -half_height, half_height, ortho_near, ortho_far));
  ////_2d_shader->SetMat4("uProjectionMatrix", glm::ortho(-1.f, 1.f, -1.f, 1.f, ortho_near, ortho_far));
  //glm::mat4 view_matrix(1);
  //_2d_shader->SetMat4("uViewMatrix", view_matrix);

  glfwMaximizeWindow(window);

  std::vector<DrawDetails> ourDrawDetails;
  std::vector<DrawStripDetails> ourDrawStripDetails;
  const GLfloat planeData[] = {
    -1,  1,
    -1, -1,
     1,  1,
     1, -1
  };

  ourDrawStripDetails.push_back(
    UploadMesh(
      planeData,
      sizeof(planeData) / sizeof(planeData[0])
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

    _2d_shader->Use();
    sidescroller::Render(ourDrawStripDetails);

    // mouse cursor draw
    cursor_shader->Use();
    DrawStrip(ourDrawStripDetails);

    // show all the stuff we drew
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // unloaded all our data from the graphics card
  UnloadMesh(ourDrawDetails);
  UnloadMesh(ourDrawStripDetails);

  glfwTerminate();
  return 0;
}
