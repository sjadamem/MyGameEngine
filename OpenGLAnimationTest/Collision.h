#ifndef COLLISION_H
#define COLLISION_H

#include <glm/glm.hpp>

#include <vector>

enum CollisionShape
{
	BOX, SPHERE, PILL
};

class Collision
{
public:

	CollisionShape mCollisionType;

	Collision(
		float rightX, float leftX, 
		float topY, float botY, 
		float farZ, float nearZ, 
		CollisionShape type = BOX);

	void Update();

	bool CheckCollision();

private:
	std::vector<glm::vec3>  mCollisionPoints;
	glm::vec3				mCollisionOrigin;

	void Initialize(float rightX, float leftX, float topY, float botY, float farZ, float nearZ);
};

#endif