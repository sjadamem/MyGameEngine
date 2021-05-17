#include "Collision.h"

Collision::Collision(
	float posX, float negX,
	float posY, float negY,
	float posZ, float negZ,
	Transform* trans) :
	mPositiveX(posX), mNegativeX(negX),
	mPositiveY(posY), mNegativeY(negY),
	mPositiveZ(posZ), mNegativeZ(negZ),
	mTransform(trans)
{
	InitializeCollisionBox();
}

void Collision::Update()
{

}

bool Collision::CheckCollision()
{
	//This is a test of pushing with GitHub and GitKraken
	return true;
}

void Collision::InitializeCollisionBox()
{
	mCollisionPoints.push_back(glm::vec3(mPositiveX, mPositiveY, mPositiveZ));
	mCollisionPoints.push_back(glm::vec3(mPositiveX, mPositiveY, mNegativeZ));
	mCollisionPoints.push_back(glm::vec3(mNegativeX, mPositiveY, mNegativeZ));
	mCollisionPoints.push_back(glm::vec3(mNegativeX, mPositiveY, mPositiveZ));
	mCollisionPoints.push_back(glm::vec3(mPositiveX, mNegativeY, mPositiveZ));
	mCollisionPoints.push_back(glm::vec3(mPositiveX, mNegativeY, mNegativeZ));
	mCollisionPoints.push_back(glm::vec3(mNegativeX, mNegativeY, mNegativeZ));
	mCollisionPoints.push_back(glm::vec3(mNegativeX, mNegativeY, mPositiveZ));

	mCollisionOrigin = 
		(glm::vec3(mPositiveX, mPositiveY, mPositiveZ) 
			- glm::vec3(mNegativeX, mNegativeY, mNegativeZ)) / 2.0f;
}
