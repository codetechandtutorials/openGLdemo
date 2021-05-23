#pragma once
#include <vector>
#include "DrawDetails.h"
#include <iostream>

DrawDetails UploadMesh(const std::vector<Vertex>& mesh, const std::vector<GLuint> elem) {
  if (mesh.empty() || elem.empty())
    throw("empty vector");

  GLuint VAO, VBO, EBO;

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(Vertex), &mesh[0], GL_STATIC_DRAW);

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, pos));
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elem.size() * sizeof(GLuint), elem.data(), GL_STATIC_DRAW);

  glBindVertexArray(0);

  //glDeleteBuffers(1, &VBO);
  //glDeleteBuffers(1, &EBO);

  return DrawDetails(VAO, static_cast<uint32_t>(elem.size()));
}

/// <summary>
///  upload a mesh square mesh meant for a plane drawn as a strip
/// </summary>
/// <param name="verts"></param>
/// <param name="v_count"></param>
/// <returns></returns>
DrawStripDetails UploadMesh(const GLfloat* verts, const GLuint v_count) {
  GLuint vaoHandle;
  glGenVertexArrays(1, &vaoHandle);
  glBindVertexArray(vaoHandle);
  GLuint vboHandle;
  glGenBuffers(1, &vboHandle);
  GLuint positionBufferHandle = vboHandle;
  glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
  glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat), verts, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);  // enable position
  glBindVertexBuffer(0, positionBufferHandle, 0, sizeof(GLfloat) * 2);
  glVertexAttribFormat(0, 2, GL_FLOAT, GL_FALSE, 0);
  glVertexAttribBinding(0, 0);  // map to shader

  std::cout << "draw strip:\n" << " -vao: " << vaoHandle << "\n -count: " << v_count << '\n';

  return DrawStripDetails(vaoHandle, v_count);

}
/// <summary>
///  intended for 2d meshes 
/// </summary>
/// <param name="verts"></param>
/// <param name="v_count"></param>
/// <param name="elems"></param>
/// <param name="e_count"></param>
/// <returns></returns>
DrawDetails UploadMesh(const GLfloat* verts, const int v_count, const GLuint* elems, const int e_count) {
  GLuint vboHandle;
  glGenBuffers(1, &vboHandle);
  GLuint positionBufferHandle = vboHandle;
  glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
  glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat), verts, GL_STATIC_DRAW);

  GLuint vaoHandle;
  glGenVertexArrays(1, &vaoHandle);
  glBindVertexArray(vaoHandle);

  glEnableVertexAttribArray(0);  // enable position
  glBindVertexBuffer(0, positionBufferHandle, 0, sizeof(GLfloat) * 2);
  glVertexAttribFormat(0, 2, GL_FLOAT, GL_FALSE, 0);
  glVertexAttribBinding(0, 0);  // map to shader

  GLuint elemHandle;
  glGenBuffers(1, &elemHandle);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemHandle);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, e_count * sizeof(GLuint), elems, GL_STATIC_DRAW);

  return DrawDetails(vaoHandle, static_cast<uint32_t>(e_count));
}

DrawDetails UploadMesh(const GLfloat* verts, const GLfloat* colors, const int v_count,
  const GLuint* elems, const int e_count) {
  GLuint vboHandles[2];
  glGenBuffers(2, vboHandles);
  GLuint positionBufferHandle = vboHandles[0];
  GLuint colorBufferHandle = vboHandles[1];
  // Populate the position buffer
  glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
  glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat), verts, GL_STATIC_DRAW);
  // Populate the color buffer
  glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
  glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat), colors, GL_STATIC_DRAW);

  // Create and set-up the vertex array object
  GLuint vaoHandle;
  glGenVertexArrays(1, &vaoHandle);
  glBindVertexArray(vaoHandle);
  // Enable the vertex attribute arrays
  glEnableVertexAttribArray(0); // Vertex position
  glEnableVertexAttribArray(1); // Vertex color

  glBindVertexBuffer(0, positionBufferHandle, 0, sizeof(GLfloat) * 3);
  glBindVertexBuffer(1, colorBufferHandle, 0, sizeof(GLfloat) * 3);

  glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexAttribBinding(0, 0);  //map to shader

  glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexAttribBinding(1, 1);  //map to shader

  GLuint elemHandle;
  glGenBuffers(1, &elemHandle);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemHandle);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, e_count * sizeof(GLuint), elems, GL_STATIC_DRAW);

  //glDeleteBuffers(2, vboHandles);
  //glDeleteBuffers(1, &elemHandle);

  return DrawDetails(vaoHandle, static_cast<uint32_t>(e_count));
}

void UnloadMesh(std::vector<DrawDetails>& details) {
  for (auto& d : details) {
    glDeleteBuffers(1, &d.vao);
  }
  details.clear();


}void UnloadMesh(std::vector<DrawStripDetails>& details) {
  for (auto& d : details) {
    glDeleteBuffers(1, &d.vao);
  }
  details.clear();
}