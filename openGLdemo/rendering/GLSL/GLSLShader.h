#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <ostream>
#include "ShaderLoader.h"
class GLSLShader {
public:

  GLSLShader() {
    loc = -1;
    p_Handle = -1;
  }
  GLSLShader(const char* vert, const char* frag) {
    loc = -1;
    p_Handle = -1;
    p_Handle = LoadShader(vert, frag);
  }
  
  void Use(){
    glUseProgram(p_Handle);
  }

  void SetInt(const char* name, const GLint& value) {
    loc = getUniformID(name);
    glUniform1iv(loc, 1, &value);
  }
  void SetUint(const char* name, const GLuint& value) {
    loc = getUniformID(name);
    glUniform1uiv(loc, 1, &value);
  }
  void SetFloat(const char* name, const GLfloat& value) {
    loc = getUniformID(name);
    glUniform1fv(loc, 1, &value);
  }
  void SetVec2(const char* name, const glm::vec2& value) {
    loc = getUniformID(name);
    glUniform2fv(loc, 1, &value[0]);
  }
  void SetVec3(const char* name, const glm::vec3& value) {
    loc = getUniformID(name);
    glUniform3fv(loc, 1, &value[0]);
  }
  void SetVec4(const char* name, const glm::vec4& value) {
    loc = getUniformID(name);
    glUniform4fv(loc, 1, &value[0]);
  }
  void SetMat3(const char* name, const glm::mat3& value) {
    loc = getUniformID(name);
    glUniformMatrix3fv(loc, 1, GL_FALSE, &value[0][0]);
  }
  void SetMat4(const char* name, const glm::mat4& value) {
    loc = getUniformID(name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
  }

  GLuint GetHandle() { return p_Handle; }
  GLuint DeleteShader() {
    glDeleteProgram(p_Handle);
    p_Handle = -1;
  }
  GLuint CreateShader(const char* vert, const char* frag) {
    if (p_Handle != -1)
      throw("delete previous shader first");
    p_Handle = LoadShader(vert, frag);
  };

private:

  GLuint p_Handle;
  GLint loc;

  GLint getUniformID(const char* name) {
    loc = glGetUniformLocation(p_Handle, name);
    if (loc >= 0)
      return loc;
    else
      throw("invalid uniform name");
    return loc;
  }
};
