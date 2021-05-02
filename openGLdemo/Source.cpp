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

GLSLShader* cursorShader;  //<-- she's global, get to her with 'extern GLSLShader *cursorShader;' delcared
GLSLShader* overlayerfragshader;  //<-- she's global, get to her with 'extern GLSLShader *cursorShader;' delcared

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

  std::string vertshader = ReadToString("..\\openGLdemo\\GLSL\\2DVertexShader.glsl");
  std::string fragshader = ReadToString("..\\openGLdemo\\GLSL\\CursorFragShader.glsl");
  cursorShader = new GLSLShader(vertshader.c_str(), fragshader.c_str());
  QueryInputAttribs(cursorShader->GetHandle());
  QueryUniforms(cursorShader->GetHandle());

  fragshader = ReadToString("..\\openGLdemo\\GLSL\\SmoothFragShader.glsl");
  overlayerfragshader = new GLSLShader(vertshader.c_str(), fragshader.c_str());
  QueryInputAttribs(overlayerfragshader->GetHandle());
  QueryUniforms(overlayerfragshader->GetHandle());
  overlayerfragshader->Use();
  overlayerfragshader->SetVec2("uResolution", glm::vec2(800,600));

  glClearColor(.3f, .3f, .65f, 0.f);
  std::vector<DrawDetails> ourDrawDetails;
  std::vector<DrawStripDetails> drawDetails;

  const GLfloat posData[] = {
    -1, 1,
    -1, -1,
    1, 1,
    1, -1
  };

  drawDetails.push_back(UploadMesh(posData, sizeof(posData) / sizeof(posData[0])));

  double prev_time = glfwGetTime();
  while (!glfwWindowShouldClose(window)) {
    double current_time = glfwGetTime();
    double dt = current_time - prev_time;
    prev_time = current_time;

    // HANDLE KEYPRESS
    ProcessInput(window);
    
    glClear(GL_COLOR_BUFFER_BIT);

    static float accumTime = 0;
    accumTime+=dt;
    //cursorShader->Use();
    //cursorShader->SetFloat("uRunTime", accumTime);

    //glm::mat4 finalModelMatrix = glm::mat4(1);
    //finalModelMatrix = glm::translate(finalModelMatrix, glm::vec3(sin((float)glfwGetTime()) / 2, cos((float)glfwGetTime()) / 2, 0));
    //finalModelMatrix = glm::rotate(finalModelMatrix, (float)glfwGetTime(), glm::vec3(0.f, 1.f, 0.f));
    //finalModelMatrix = glm::scale(finalModelMatrix, glm::vec3(.5));
    //cursorShader.SetMat4("uModelMatrix", finalModelMatrix);
    overlayerfragshader->Use();

    //overlayerfragshader->SetFloat("uRunTime", accumTime);
    DrawStrip(drawDetails);

    cursorShader->Use();
    // mouse cursor update
    DrawStrip(drawDetails);

    // RENDER OUR OBJECT
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // UNLOAD DATA FROM GRAPHICS CARD
  UnloadMesh(ourDrawDetails);

  glfwTerminate();
  return 0;
}