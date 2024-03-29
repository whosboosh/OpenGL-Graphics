#pragma once

#include <GLAD\glad.h>
#include <vector>
#include "Utilities.h"
#include "Texture.h"
#include "Material.h"

class Mesh
{
public:
	Mesh();
	Mesh(Texture* texture, Material* material);
	void CreateMesh(GLfloat *vertices, unsigned int verticeCount, unsigned int numOfVertices);
	void CreateMeshIndex(std::vector<Vertex>* vertices, std::vector<uint32_t>* indices);
	void RenderMesh(unsigned int texture);
	void RenderMeshIndex(Shader* shader);
	void ClearMesh();
	~Mesh();
private:
	unsigned int VAO, VBO, IBO;
	GLsizei indiceCount;
	GLsizei verticeCount;

	Texture* texture;
	Material* material;
};

