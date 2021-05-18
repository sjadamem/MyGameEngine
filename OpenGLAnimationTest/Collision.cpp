#include "Collision.h"

Collision::Collision(
	float maxX, float minX,
	float maxY, float minY,
	float maxZ, float minZ,
	Transform* trans) :
	mMaxX(minX), mMinX(minX),
	mMaxY(minY), mMinY(minY),
	mMaxZ(minZ), mMinZ(minZ),
	mTransform(trans)
{
	
}

void Collision::Update()
{

}

bool Collision::CheckCollision()
{
	//This is a test of pushing with GitHub and GitKraken
	return true;
}
