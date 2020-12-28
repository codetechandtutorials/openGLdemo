#pragma once
#include <vector>
#include "../Vertex.h"

static DrawDetails UploadMesh(const std::vector<Vertex>& verts, const std::vector<uint32_t> elem)
{
	if (verts.empty() || elem.empty())
		throw("empty vector");

	uint32_t VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Pos));
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elem.size() * sizeof(uint32_t), elem.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return DrawDetails(VAO, elem.size());
}


static void UnloadMesh(std::vector<DrawDetails>& details)
{
	for (auto& d : details)
	{
		glDeleteBuffers(1, &d.vao);
	}

	details.clear();
}