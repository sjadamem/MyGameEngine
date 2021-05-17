#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

using namespace std;

const glm::vec3 EULER_ANGLES(0.0f);
const glm::vec3 ORIGIN		(0.0f);
const glm::vec3 SCALE		(1.0f);

class Transform
{
public:

	glm::vec3	mPosition;
	
	glm::quat	mRotation;
//	PITCH = x, YAW = y, ROLL = z
	glm::vec3	mEulerAngles;
	glm::vec3	mForward, mRight, mUp;
	
	glm::vec3	mScale;

	glm::mat4	mLocalMatrix;

	Transform(glm::vec3 position = ORIGIN, glm::vec3 eulers = EULER_ANGLES,	glm::vec3 scale = SCALE);

	void Translate(glm::vec3 position);
//	void Translate(float x, float y, float z);

	void Rotate(glm::vec3 eulerAngles);
	void Rotate(float pitch, float yaw, float roll);

	void Scale(glm::vec3 scale);
	void Scale(float xScale, float yScale, float zScale);
//	void Scale(float x, float y, float z);

//	void Update();

private:

	void CheckRotations(float& angle);
	void UpdateDirectionalVectors();
	void UpdateLocalMatrix();
};

#endif