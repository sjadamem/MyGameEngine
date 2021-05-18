#include "SkeletalMesh.h"

void SkeletalMesh::Initialize()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mNrVertices * sizeof(VertexData), mVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNrIndices * sizeof(unsigned int), mIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(offsetof(VertexData, Normals)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(offsetof(VertexData, TexCoords)));
	glEnableVertexAttribArray(3);
	glVertexAttribIPointer(3, 4,GL_INT,				sizeof(VertexData), (GLvoid*)(offsetof(VertexData, IDs)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(offsetof(VertexData, Weights)));


	glBindVertexArray(0);
}