#include "Camera.h"

Camera::Camera() : 
	mZoom(ZOOM), mSensitivity(SENSITIVITY), mSpeed(SPEED), 
	mWorldUp(WORLDUP), mCameraConstraints(CONSTRAINT)
{
	mTransform		= Transform();
}

Camera::Camera(glm::vec3 pos, glm::vec3 eulers, glm::vec3 constraint) :
	mZoom(ZOOM), mSensitivity(SENSITIVITY), mSpeed(SPEED), mWorldUp(WORLDUP), mCameraConstraints(constraint)
{
	mTransform		= Transform(pos, eulers);
}

void Camera::Move(Direction dir, float deltaTime)
{
	float velocity = mSpeed * deltaTime;

	if (dir == FORWARD)
		mTransform.Translate( mTransform.mForward * velocity);
	if (dir == BACKWARD)
		mTransform.Translate(-mTransform.mForward * velocity);
	if (dir == LEFT)
		mTransform.Translate(-mTransform.mRight	* velocity);
	if (dir == RIGHT)
		mTransform.Translate( mTransform.mRight * velocity);
}

void Camera::Turn(float xOffset, float yOffset, float deltaTime)
{
	xOffset *= mSensitivity * deltaTime;
	yOffset *= mSensitivity * deltaTime;

//	if (pitch > 360.0f || pitch < -360.0f)
//	{
//		pitch = fmod(pitch, 360.0f);
//	}

	float pitch	= mTransform.mEulerAngles.x + yOffset;
	if (pitch > mCameraConstraints.x || pitch < -mCameraConstraints.x)
		yOffset = 0.0f;
	
	mTransform.Rotate(yOffset, xOffset, 0.0f);
}

glm::mat4 Camera::GetViewMatrix()
{
	CalculateCameraVectors();

	return glm::lookAt(mTransform.mPosition, mTransform.mPosition + mTransform.mForward, mTransform.mUp);	
}

void Camera::CalculateCameraVectors()
{
	glm::vec3* front = &mTransform.mForward;
	glm::vec3  euler = mTransform.mEulerAngles;
	front->x = cos(glm::radians(euler.y)) * cos(glm::radians(euler.x));
	front->y = sin(glm::radians(euler.x));
	front->z = sin(glm::radians(euler.y)) * cos(glm::radians(euler.x));
	*front = glm::normalize(*front);
	std::cout << "X\t" << front->x << "\nY\t" << front->y << "\nZ\t" << front->z << std::endl << std::endl;

	glm::vec3* right = &mTransform.mRight;
	*right = glm::normalize(glm::cross(mTransform.mForward, mWorldUp));

	glm::vec3* up = &mTransform.mUp;
	*up = glm::normalize(glm::cross(mTransform.mRight, mTransform.mForward));
}
