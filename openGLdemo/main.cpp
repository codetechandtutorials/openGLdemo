#include "Callbacks.h"
#include "Input.h"
#include "Utilities.h"
#include "rendering/GL/Vertex.h"
#include "rendering/GL/DrawDetails.h"
#include "rendering/GL/MeshLoader.h"
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

std::unique_ptr<GLSLShader> cursor_shader;  //<-- she's global, get to her with 'extern std::unique_ptr<GLSLShader> cursor_shader;' delcared
std::unique_ptr<GLSLShader> demo_shader;
float FOV = glm::radians(45.f);
float NEAR = .1f;
float FAR = 3000.f;

int main(int argc, char** argv) {
  glfwSetErrorCallback(glfw_error_callback);
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, extract_prog_name(argv[0]), nullptr, nullptr);
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  printGLinfo();

  glfwSetWindowCloseCallback(window, glfw_window_close_callback);
  glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
  glfwSetCursorPosCallback(window, glfw_mouse_movement_callback);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  std::string vert_code = ReadToString("..\\openGLdemo\\GLSL_src\\vert_2DFlat.glsl");
  std::string frag_code = ReadToString("..\\openGLdemo\\GLSL_src\\frag_Cursor.glsl");
  cursor_shader = std::make_unique<GLSLShader>(vert_code.c_str(), frag_code.c_str());
  QueryInputAttribs(cursor_shader->GetHandle());
  QueryUniforms(cursor_shader->GetHandle());
  cursor_shader->Use();
  cursor_shader->SetFloat("uRadius", 16);

  vert_code = ReadToString("..\\openGLdemo\\GLSL_src\\vert_3DProjected.glsl");
  frag_code = ReadToString("..\\openGLdemo\\GLSL_src\\frag_Demo.glsl");
  demo_shader = std::make_unique<GLSLShader>(vert_code.c_str(), frag_code.c_str());
  QueryInputAttribs(demo_shader->GetHandle());
  QueryUniforms(demo_shader->GetHandle());
  demo_shader->Use();
  demo_shader->SetVec2("uResolution", glm::vec2(800, 600));
  float ASPECT_RATIO = 800.f/600.f;
  demo_shader->SetMat4("uProjectionMatrix", glm::perspective(FOV, ASPECT_RATIO, NEAR, FAR));
  glm::mat4 model_matrix(1.f);
  model_matrix = glm::translate(model_matrix, glm::vec3(0,0,-10));
  demo_shader->SetMat4("uModelMatrix", model_matrix);
  glm::mat4 view_matrix(1);
  demo_shader->SetMat4("uViewMatrix", view_matrix);

  glClearColor(.3f, .3f, .65f, 0.f);
  std::vector<DrawDetails> ourDrawDetails;
  std::vector<DrawStripDetails> ourDrawStripDetails;

  const GLfloat posData[] = {
    -1,  1,
    -1, -1,
     1,  1,
     1, -1
  };

  ourDrawStripDetails.push_back(UploadMesh(posData, sizeof(posData) / sizeof(posData[0])));

  double prev_time = glfwGetTime();
  while (!glfwWindowShouldClose(window)) {
    double current_time = glfwGetTime();
    double dt = current_time - prev_time;
    prev_time = current_time;

    // HANDLE KEYPRESS
    ProcessInput(window);

    glClear(GL_COLOR_BUFFER_BIT);

    static double accumTime = 0;
    accumTime += dt;

    demo_shader->Use();
    demo_shader->SetFloat("uRunTime", accumTime);
    model_matrix = glm::rotate(model_matrix, glm::radians((float)(dt*100)), glm::vec3(0,1,0));
    demo_shader->SetMat4("uModelMatrix", model_matrix);
    DrawStrip(ourDrawStripDetails);

    // mouse cursor draw
    cursor_shader->Use();
    DrawStrip(ourDrawStripDetails);

    // RENDER OUR OBJECT
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // UNLOAD DATA FROM GRAPHICS CARD
  UnloadMesh(ourDrawDetails);

  UnloadMesh(ourDrawStripDetails);

  glfwTerminate();
  return 0;
}