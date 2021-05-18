#ifndef STATICMESH_H
#define STATICMESH_H

#include "Shape.h"
#include "Mesh.h"

class StaticMesh : public Mesh
{
public:
	StaticMesh(
		VertexData* vertices, const unsigned int& nrVertices,
		unsigned int* indices, const unsigned int& nrIndices,
		Texture* textures, const unsigned int& nrTextures) : 
		Mesh(vertices, nrVertices, indices, nrIndices, textures, nrTextures)
	{ 
		Initialize(); 
	}

	StaticMesh(Shape shape) :
		Mesh(
			shape.mVertices.data(), shape.mVertices.size(),
			shape.mIndices.data(), shape.mIndices.size(),
			shape.mTextures.data(), shape.mTextures.size()) 
	{
		Initialize();
	}

protected:
	void Initialize();
};

#endif