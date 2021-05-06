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
//The following may be defined in the SkeletalMesh/SkinnedMesh class
#define IDS			3
#define WEIGHTS		4

/*
You will have to consider the fact that not all meshes will be skinned (skeletal). The way you have
it, there are two separate Initialize functions for skinned and static meshes respectively. Both 
functions have largely the same code, with the second version having extra code relating to setting
up data for the layout variables for a mesh's given vertex's bone IDs and weights, which has 
redundant code.

My suggestion is to make a class 'Mesh' with an virtual functions called Initialize that setups the 
vertex data, their indices and its texture coordinates. This class will be used for static meshes 
(meshes that do not have any associated bones or animations) and will be the parent of another class 
called 'SkeletalMesh' or 'SkinnedMesh'. This child class will be forced to create its own Initialize 
function designed for setting up the extra data for skinned meshes such as the mesh's given vertex's
bone IDs and weights. If possible, you might be able to call the parent's Initialize function with
its child's Initialize function.
*/
class Mesh
{
public:

	Mesh() { }
	Mesh(VertexBoneData* vertices, const unsigned int& nrVertices, unsigned int* indices, const unsigned int& nrIndices, Texture* textures = nullptr);
	Mesh(Vertex* vertices, const unsigned int& nrVertices, 
		unsigned int* indices, const unsigned int& nrIndices, 
		BoneData* bones = nullptr, const unsigned int& nrBones = 0, 
		Texture* texture = nullptr);
	~Mesh();

	void Initialize(Vertex* vertices, unsigned int* indices, BoneData* bones = nullptr);
	void Initialize(VertexBoneData* vertices, unsigned int* indices);

	void SetTextures(Texture* textures);
	void Render(Shader* shader);


private:
	std::vector<Texture> mTextures;

//	We might need the actual vertex position data from the vertex data we pass in to read thru and
//	find the peak height, widest width and furthest depth coordinates from the mesh's origin.

//	std::vector<VertexBoneData> mVertices;
//	std::vector<unsigned int>	mIndices;
//	std::vector<BoneData>		mBones;

//	These counts might become obsolete since we can simply obtain the sizes by invoking the size of
//	the respective vectors.
	unsigned int nrVertices;
	unsigned int nrIndices;
	unsigned int nrBones;

//	SkeletalMesh/SkinnedMesh will have to have boneEBO
	unsigned int VAO, vertexBO, boneBO, EBO;

};

#endif