#ifndef SHAPE_H
#define SHAPE_H

#include "StaticMesh.h"

class Shape : public StaticMesh
{
public:
	
	Shape() { }
	Shape(
		VertexData* vertices, const unsigned int& nrVertices,
		unsigned int* indices, const unsigned int& nrIndices,
		Texture* textures, const unsigned int& nrTextures) :
		StaticMesh(vertices, nrVertices, indices, nrIndices, textures, nrTextures) 
	{ }
private:


};

#endif