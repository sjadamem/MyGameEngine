#include "Mesh.h"

Mesh::Mesh(
	VertexData* vertices, const unsigned int& nrVertices,
	unsigned int* indices, const unsigned int& nrIndices,
	Texture* textures, const unsigned int& nrTextures)
{
	mVertices	= new VertexData[nrVertices];
	for (unsigned int i = 0; i < nrVertices; i++)
		mVertices[i] = *(vertices + i);

	mIndices	= new unsigned int[nrIndices];
	for (unsigned int i = 0; i < nrIndices; i++)
		mIndices[i] = *(indices + i);

	if (textures != nullptr)
	{
		mTextures = new Texture[nrTextures];
		for (unsigned int i = 0; i < nrTextures; i++)
			mTextures[i] = *(textures + i);
	}

	mNrVertices = nrVertices;
	mNrIndices	= nrIndices;
	mNrTextures = nrTextures;
}

void Mesh::FindMaximumPoints(float& posX, float& negX, float& posY, float& negY, float& posZ, float& negZ)
{
	for (unsigned int i = 0; i < mNrVertices; i++)
	{
		glm::vec3 vert = mVertices[i].Position;

		if (vert.x > posX)
			posX = vert.x;
		if (vert.x < negX)
			negX = vert.x;

		if (vert.y > posY)
			posY = vert.y;
		if (vert.y < negY)
			negY = vert.y;

		if (vert.z > posZ)
			posZ = vert.z;
		if (vert.z < negX)
			negX = vert.z;
	}
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
