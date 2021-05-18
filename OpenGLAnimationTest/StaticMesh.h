#ifndef STATICMESH_H
#define STATICMESH_H

#include "Mesh.h"

class StaticMesh : public Mesh
{
public:
	StaticMesh() { }
	StaticMesh(
		VertexData* vertices, const unsigned int& nrVertices,
		unsigned int* indices, const unsigned int& nrIndices,
		Texture* textures, const unsigned int& nrTextures);

protected:
	void Initialize();
};

#endif