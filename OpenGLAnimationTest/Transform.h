#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

class Transform
{
public:
	glm::vec3 mPosition;
	glm::quat mRotation;
	glm::vec3 mScale;

	Transform(
		glm::vec3 pos = glm::vec3(0.0f),
		glm::vec3 rot = glm::vec3(0.0f),
		glm::vec3 sca = glm::vec3(1.0f)) :
		mPosition(pos), mRotation(rot), mScale(sca) 
	{ };

	glm::mat4 GetLocalMatrix();

	void UpdateRotation();
	void UpdatePosition();
	void UpdateScale();

private:
};

#endif