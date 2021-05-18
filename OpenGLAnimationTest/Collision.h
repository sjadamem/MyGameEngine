#ifndef COLLISION_H
#define COLLISION_H

#include <glm/glm.hpp>

#include <vector>

#include "Transform.h"

/*
*******NOTE*******
You will probably need to make this an abstract class and have derived classes for different shape 
of collision such as BoxCollision, SphereCollision, PillCollision for 3D collision, or even
SquareCollision and CircleCollision for 2D collision.
*/

enum CollisionType
{
	BOX, SPHERE, PILL
};

class Collision
{
public:
	Transform* mTransform;

	Collision(
		float rightX, float leftX, 
		float topY, float botY, 
		float farZ, float nearZ, 
		Transform* trans = new Transform());

	void Update();

	bool CheckCollision();

//	inline void SetNewTransform(Transform* trans) { mTransform = trans; }

private:
	float mMaxX, mMaxY, mMaxZ, mMinX, mMinY, mMinZ;

	std::vector<glm::vec3>  mCollisionPoints;
	glm::vec3				mCollisionOrigin;

};

#endif