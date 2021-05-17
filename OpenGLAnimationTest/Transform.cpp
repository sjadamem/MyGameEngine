#include "Transform.h"

Transform::Transform(glm::vec3 position, glm::vec3 eulers, glm::vec3 scale) :
	mPosition(position), mEulerAngles(eulers), mScale(scale)
{
	mRotation = glm::quat(mEulerAngles);

	UpdateDirectionalVectors();
	UpdateLocalMatrix();
}

void Transform::Translate(glm::vec3 translate)
{
	mPosition += translate;
}

void Transform::Rotate(glm::vec3 rotate)
{
	mRotation = glm::rotate(mRotation, glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
	mRotation = glm::rotate(mRotation, glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
	mRotation = glm::rotate(mRotation, glm::radians(rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
	
	mEulerAngles += rotate;

	CheckRotations(mEulerAngles.x);
	CheckRotations(mEulerAngles.y);
	CheckRotations(mEulerAngles.z);

	UpdateDirectionalVectors();
	UpdateLocalMatrix();
}

void Transform::Rotate(float pitch, float yaw, float roll)
{
	Rotate(glm::vec3(pitch, yaw, roll));
}

void Transform::Scale(glm::vec3 scale)
{
	mScale += scale;

	UpdateLocalMatrix();
}

void Transform::Scale(float xScale, float yScale, float zScale)
{
	Scale(glm::vec3(xScale, yScale, zScale));
}

void Transform::CheckRotations(float& angle)
{
	if (angle > 360.0f)
		angle -= 360.0f;
	if (angle < -360.0f)
		angle += 360.0f;
}

void Transform::UpdateDirectionalVectors()
{
	mForward	= mRotation * glm::vec3(0.0f, 0.0f, -1.0f);
	mRight		= mRotation * glm::vec3(1.0f, 0.0f, 0.0f);
	mUp			= mRotation * glm::vec3(0.0f, 1.0f, 0.0f);
}

void Transform::UpdateLocalMatrix()
{
	glm::mat4 mat(1.0f);

	mat = glm::translate(mat, mPosition);
	mat *= glm::mat4_cast(mRotation);
	mat = glm::scale(mat, mScale);

	mLocalMatrix = mat;
}
