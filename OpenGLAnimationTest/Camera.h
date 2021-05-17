#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include <iostream>

#include "Transform.h"

enum Direction
{
	FORWARD, BACKWARD, LEFT, RIGHT
};

const float		ZOOM		= 45.0f;
const float		SENSITIVITY	= 1.5f;
const float		SPEED		= 3.0f;

const glm::vec3	EULERS		= glm::vec3(0.0f, -90.0f, 0.0f);
const glm::vec3 CONSTRAINT	= glm::vec3(89.0f, 0.0f, 0.0f);
const glm::vec3	WORLDUP		= glm::vec3(0.0f, 1.0f, 0.0f);

class Camera
{
public:

	Camera();
//	Camera(glm::vec3 pos, glm::quat rot);
	Camera(glm::vec3 pos, glm::vec3 eulers = EULERS, glm::vec3 constraint = CONSTRAINT);

	void Move(Direction dir, float deltaTime);
	void Turn(float xOffset, float yOffset, float deltaTime);
	
	inline void SetTransform(Transform trans);
	inline void SetTransform(glm::vec3 pos, glm::vec3 eul, glm::vec3 sca);

	inline void SetCameraConstraints(float maxPitch, float maxYaw, float maxRoll) 
	{ mCameraConstraints = glm::vec3(maxPitch, maxYaw, maxRoll); }

	glm::mat4	GetViewMatrix();

private:
	Transform	mTransform;
	Direction	mCameraDirection;

	glm::vec3	mWorldUp;

	float		mSensitivity;
	float		mSpeed;
	float		mZoom;

	glm::vec3	mCameraConstraints;

//	void UpdateWorldUp();
	void CalculateCameraVectors();
};

#endif