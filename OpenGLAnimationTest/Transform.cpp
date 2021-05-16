#include "Transform.h"

glm::mat4 Transform::GetLocalMatrix()
{
	glm::mat4 mat(1.0f);
	
	mat = glm::translate(mat, mPosition);
	mat *= glm::mat4_cast(mRotation);	
	mat = glm::scale(mat, mScale);

	return mat;
}
