#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

#include "VertexData.h"
#include "Texture.h"

class Shape
{
public:

	std::vector<VertexData> mVertices;
	std::vector<unsigned int> mIndices;
	std::vector<Texture> mTextures;

	Shape() { }
};

#endif