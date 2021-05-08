#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include <iostream>
#include <string>

#include "stb_image.h"

class Texture
{
public:
	std::string textureType;
	
	Texture() { };
	Texture(std::string texturePath, std::string textureType);

	void BindTexture() { glBindTexture(GL_TEXTURE_2D, textureID); }

	std::string GetTexturePath() { return texturePath; }
private:
	unsigned int textureID;
	std::string texturePath;

};

#endif