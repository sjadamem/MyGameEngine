#include "SkeletalMesh.h"

SkeletalMesh::SkeletalMesh(
	VertexBoneData* vertices, const unsigned int& nrVertices,
	unsigned int* indices, const unsigned int& nrIndices,
	Texture* textures, const unsigned int& nrTextures) :
	Mesh(vertices, nrVertices, indices, nrIndices, textures, nrTextures)
{
	Initialize();
}

void SkeletalMesh::Initialize()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mNrVertices * sizeof(VertexBoneData), mVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNrIndices * sizeof(unsigned int), mIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (GLvoid*)(offsetof(VertexBoneData, Normals)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (GLvoid*)(offsetof(VertexBoneData, TexCoords)));
	glEnableVertexAttribArray(3);
	glVertexAttribIPointer(3, 4,GL_INT,				sizeof(VertexBoneData), (GLvoid*)(offsetof(VertexBoneData, IDs)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (GLvoid*)(offsetof(VertexBoneData, Weights)));


	glBindVertexArray(0);
}