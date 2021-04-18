#pragma once
#include <glad/glad.h>
#include <vector>
#include <stdio.h>
#include <iostream>
const char* getTypeString(GLenum type) {
  // There are many more types than are covered here, but
  // these are the most common in these examples.
  switch (type) {
  case GL_FLOAT:
    return "float";
  case GL_FLOAT_VEC2:
    return "vec2";
  case GL_FLOAT_VEC3:
    return "vec3";
  case GL_FLOAT_VEC4:
    return "vec4";
  case GL_DOUBLE:
    return "double";
  case GL_INT:
    return "int";
  case GL_UNSIGNED_INT:
    return "unsigned int";
  case GL_BOOL:
    return "bool";
  case GL_FLOAT_MAT2:
    return "mat2";
  case GL_FLOAT_MAT3:
    return "mat3";
  case GL_FLOAT_MAT4:
    return "mat4";
  case GL_TRUE:
    return "true";
  case GL_FALSE:
    return "false";
  default:
    return "?";
  }
}

void QueryInputAttribs(GLuint handle) {
  printf("-----ATTRIBUTES-----\n");
  // method 1
  GLint numAttribs;
  glGetProgramInterfaceiv(handle, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numAttribs);
  printf("Active Inputs: %i):\n", numAttribs);

  GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };
  for (int i = 0; i < numAttribs; ++i) {
    GLint results[3];
    glGetProgramResourceiv(handle, GL_PROGRAM_INPUT, i, 3, properties, 3, NULL, results);

    GLint nameBufSize = results[0] + 1;
    char* name = new char[nameBufSize];
    glGetProgramResourceName(handle, GL_PROGRAM_INPUT, i, nameBufSize, NULL, name);
    printf("%-5d %s (%s)\n", results[2], name, getTypeString(results[1]));
    delete[] name;
  }

  // method 2
  //GLint i;
  //GLint count;

  //GLint size; // size of the variable
  //GLenum type; // type of the variable (float, vec3 or mat4, etc)

  //const GLsizei bufSize = 16; // maximum name length
  //GLchar name[bufSize]; // variable name in GLSL
  //GLsizei length; // name length

  //glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTES, &count);
  //printf("Active Attributes: %d\n", count);

  //for (i = 0; i < count; i++)
  //{
  //	glGetActiveAttrib(handle, (GLuint)i, bufSize, &length, &size, &type, name);
  //	printf("Attribute #%d Type: %u Name: %s\n", i, type, name);
  //}

  // method 3
  //GLint numActiveAttribs = 0;
  //glGetProgramInterfaceiv(handle, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numActiveAttribs);
  //std::vector<GLchar> nameData(256);
  //std::vector<GLenum> properties;
  //properties.push_back(GL_NAME_LENGTH);
  //properties.push_back(GL_TYPE);
  //properties.push_back(GL_ARRAY_SIZE);
  //std::vector<GLint> values(properties.size());
  //for (int attrib = 0; attrib < numActiveAttribs; ++attrib)
  //{
  //	glGetProgramResourceiv(handle, GL_PROGRAM_INPUT, attrib, properties.size(),
  //		&properties[0], values.size(), NULL, &values[0]);

  //	nameData.resize(values[0]); //The length of the name.
  //	glGetProgramResourceName(handle, GL_PROGRAM_INPUT, attrib, nameData.size(), NULL, &nameData[0]);
  //	std::string name((char*)&nameData[0], nameData.size() - 1);
  //	
  //	printf("Attribute #%d Type: %u Name: %s\n", attrib, properties[attrib], name);
  //}
  //{
  //	GLint active_vertex_resource;
  //	glGetProgramInterfaceiv(handle, GL_PROGRAM_INPUT, GL_ACTIVE_VARIABLES, &active_vertex_resource);
  //	printf("Active vertex resource count: %i\n", active_vertex_resource);
  //}
  //{
  //	GLint active_output_resource_count;
  //	glGetProgramInterfaceiv(handle, GL_PROGRAM_OUTPUT, GL_ACTIVE_RESOURCES, &active_output_resource_count);
  //	printf("Active output resource count: %i\n", active_output_resource_count);
  //}

}

void QueryUniforms(GLuint handle) {
  printf("-----UNIFORMS-----\n");

  GLint numUniforms = 0;
  glGetProgramInterfaceiv(handle, GL_UNIFORM,
    GL_ACTIVE_RESOURCES, &numUniforms);
  //  2. Loop through each uniform index and query for the length of the name, the type, the
    //  location and the block index:
  GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE,
    GL_LOCATION, GL_BLOCK_INDEX };
  printf("Active uniforms:\n");
  for (int i = 0; i < numUniforms; ++i) {
    GLint results[4];
    glGetProgramResourceiv(handle, GL_UNIFORM, i, 4,
      properties, 4, NULL, results);
    if (results[3] != -1)
      continue; // Skip uniforms in blocks
    GLint nameBufSize = results[0] + 1;
    char* name = new char[nameBufSize];
    glGetProgramResourceName(handle, GL_UNIFORM, i,
      nameBufSize, NULL, name);
    printf("%-5d %s (%s)\n", results[2], name,
      getTypeString(results[1]));
    delete[] name;
  }
}