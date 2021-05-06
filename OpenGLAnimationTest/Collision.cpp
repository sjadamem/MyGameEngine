#include "Collision.h"

Collision::Collision(
	float rightX, float leftX, 
	float topY, float botY, 
	float farZ, float nearZ, 
	CollisionShape type)
{

}

bool Collision::CheckCollision()
{
	//This is a test of pushing with GitHub and GitKraken
	return true;
}

void Collision::Initialize(float rightX, float leftX, float topY, float botY, float farZ, float nearZ)
{
	glm::vec3 point1(rightX, topY, farZ);
	glm::vec3 point2(rightX, topY, nearZ);
	glm::vec3 point3(leftX,	 topY, nearZ);
	glm::vec3 point4(leftX,  topY, farZ);
	glm::vec3 point5(rightX, botY, farZ);
	glm::vec3 point6(rightX, botY, nearZ);
	glm::vec3 point7(leftX,  botY, nearZ);
	glm::vec3 point8(leftX,  botY, farZ);

	mCollisionOrigin = (point1 - point7) / 2.0f;
}
