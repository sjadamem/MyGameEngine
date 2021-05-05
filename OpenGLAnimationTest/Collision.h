#ifndef COLLISION_H
#define COLLISION_H

#include <glm/glm.hpp>

#include <vector>

class Collision
{
public:
	glm::vec3	mCollisionOrigin;
	float		mHeight;
	float		mWidth;
	float		mDepth;

	Collision(glm::vec3 origin, float height, float width, float depth) :
		mCollisionOrigin(origin), mHeight(height), mWidth(width), mDepth(depth)
	{ };

	bool CheckCollision();

private:
	
};

#endif