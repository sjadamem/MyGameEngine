#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

#include <vector>
#include <string>

//#include "Bone.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexData.h"

#define POSITION	0
#define NORMAL		1
#define TEXCOORDS	2
#define IDS			3
#define WEIGHTS		4

class Mesh
{
public:
//	Skeleton skeleton;
	unsigned int mNumOfIndices, mBaseVertexID, mBaseIndexID;

	Mesh() { }
	Mesh(unsigned int nrIndices, unsigned int baseVertexID, unsigned int baseIndexID);
//	Mesh(Vertex* vertices, const unsigned int& nrVertices, unsigned int* indices, const unsigned int& nrIndices);
	Mesh(VertexBoneData* vertices, const unsigned int& nrVertices, unsigned int* indices, const unsigned int& nrIndices, Texture* textures = nullptr);
	Mesh(Vertex* vertices, const unsigned int& nrVertices, 
		unsigned int* indices, const unsigned int& nrIndices, 
		BoneData* bones = nullptr, const unsigned int& nrBones = 0, 
		Texture* texture = nullptr);
	~Mesh();

	void Initialize(Vertex* vertices, unsigned int* indices,
		BoneData* bones = nullptr);
	void Initialize(VertexBoneData* vertices, unsigned int* indices);

	void SetTextures(Texture* textures);
	void Render(Shader* shader);

private:
	std::vector<Texture> mTextures;

	unsigned int nrVertices;
	unsigned int nrIndices;
	unsigned int nrBones;

	unsigned int VAO, vertexBO, boneBO, EBO;

};

#endif