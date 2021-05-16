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

//Test from the new branch

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

	Mesh() { };
	Mesh(VertexBoneData* vertices, const unsigned int& nrVertices,
		unsigned int* indices, const unsigned int& nrIndices,
		Texture* textures, const unsigned int& nrTextures);

	~Mesh() { };
	
	void FindMaximumPoints(
		float& posX, float& negX,
		float& posY, float& negY,
		float& posZ, float& negZ);
	void Render(Shader* shader);

//	void Initialize(Vertex* vertices, unsigned int* indices, BoneData* bones = nullptr);

protected:
	VertexBoneData* mVertices;
	unsigned int	mNrVertices;

	unsigned int*	mIndices;
	unsigned int	mNrIndices;
	
	Texture*		mTextures;
	unsigned int	mNrTextures;

//	We might need the actual vertex position data from the vertex data we pass in to read thru and
//	find the peak height, widest width and furthest depth coordinates from the mesh's origin.

//	SkeletalMesh/SkinnedMesh will have to have boneEBO
	unsigned int VAO, VBO, EBO;

	virtual void Initialize() = 0;
};

#endif