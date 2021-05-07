#include "Mesh.h"

Mesh::Mesh(
	VertexBoneData* vertices, const unsigned int& nrVertices,
	unsigned int* indices, const unsigned int& nrIndices,
	Texture* textures, const unsigned int& nrTextures)
{
	mVertices	= vertices;
	mIndices	= indices;

	if (textures != nullptr)
		mTextures = textures;

	mNrVertices = nrVertices;
	mNrIndices	= nrIndices;
	mNrTextures = nrTextures;
}

void Mesh::Render(Shader* shader)
{
	unsigned int nrDiffuse = 1;
	unsigned int nrSpecular = 1;

	for (unsigned int i = 0; i < mNrTextures; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string name;
		std::string number;

		name = mTextures[i].textureType;
		if (name == "texture_diffuse")
			number = std::to_string(nrDiffuse++);
		else if (name == "texture_specular")
			number = std::to_string(nrSpecular++);

		std::string uniform = name + number;
		shader->SetInt(uniform, i);
		mTextures[i].BindTexture();
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)mNrIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

#if 0
void Mesh::Initialize(Vertex* vertices, unsigned int* indices, BoneData* bones)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &vertexBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBO);
	glBufferData(GL_ARRAY_BUFFER, this->nrVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, Normals)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, TexCoords)));

	glGenBuffers(1, &boneBO);
	glBindBuffer(GL_ARRAY_BUFFER, boneBO);
	glBufferData(GL_ARRAY_BUFFER, this->nrBones * sizeof(BoneData), bones, GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribIPointer(3, 4, GL_INT, sizeof(BoneData), (GLvoid*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(BoneData), (GLvoid*)(offsetof(BoneData, Weight)));
	
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}
#endif
