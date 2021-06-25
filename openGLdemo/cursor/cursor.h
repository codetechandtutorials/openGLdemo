#pragma once
#include <memory>
#include "../rendering/GLSL/GLSLShader.h"
#include "../rendering/GL/DrawDetails.h"
#include "../rendering/GL/Draw.h"
#include "../rendering/GLSL/QueryShader.h"

extern GLFWwindow* window;

namespace cursor {

static std::unique_ptr<GLSLShader> cursor_shader;

void Setup() {
  // setup a custom mouse cursor shader
  std::string vert_code = ReadFileToString("..\\openGLdemo\\GLSL_src\\vert_2DFlat.glsl");
  std::string frag_code = ReadFileToString("..\\openGLdemo\\GLSL_src\\frag_Cursor.glsl");
  cursor_shader = std::make_unique<GLSLShader>(vert_code.c_str(), frag_code.c_str());
  QueryInputAttribs(cursor_shader->GetHandle());
  QueryUniforms(cursor_shader->GetHandle());
  cursor_shader->Use();
  cursor_shader->SetFloat("uRadius", 16);
}
void Update(double x, double y){
  int width, height;
  glfwGetWindowSize(window, &width, &height);
  cursor_shader->Use();
#if _DEBUG
  printf("mouse pos: %f, %f\n", x, y);
  printf("to ogl screen space mouse pos: %f, %f\n", x, height - y);
#endif
  cursor_shader->SetVec2("uMousePos", glm::vec2(x, height - y));
}

void Render(const std::vector<DrawStripDetails>& drawdetails){
  cursor_shader->Use();
  DrawStrip(drawdetails);
}

}