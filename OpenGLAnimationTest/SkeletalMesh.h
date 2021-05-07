#ifndef SKELETALMESH_H
#define SKELETALMESH_H

#include "Mesh.h"

class SkeletalMesh : public Mesh
{
public:
	SkeletalMesh(
		VertexBoneData* vertices, const unsigned int& nrVertices, 
		unsigned int* indices, const unsigned int& nrIndices, 
		Texture* textures, const unsigned int& nrTextures);

protected:
	void Initialize();

};

#endif