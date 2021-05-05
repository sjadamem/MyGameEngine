#include "GlobalResources.h"

const float GlobalResources::FRAMES = 1.0f / 24.0f;

float GlobalResources::deltaTime = 0.0f;
float GlobalResources::lastTime = 0.0f;
float GlobalResources::currentTime = 0.0f;

void GlobalResources::resetTimer()
{
	glfwSetTime(0.0);
}

void GlobalResources::updateDeltaTime()
{
	currentTime = (float)glfwGetTime();
	deltaTime = currentTime - lastTime;
//	std::cout << "Delta Time: " << deltaTime << "\nCurrent Time: " << currentTime << "\nLast Time: " << lastTime << std::endl;
	lastTime = currentTime;
}

glm::mat4 GlobalResources::aiMat4_to_glmMat4(const aiMatrix4x4 mat)
{
	return glm::mat4(
		mat.a1, mat.b1, mat.c1, mat.d1,
		mat.a2, mat.b2, mat.c2, mat.d2,
		mat.a3, mat.b3, mat.c3, mat.d3,
		mat.a4, mat.b4, mat.c4, mat.d4);
}

glm::quat GlobalResources::aiQuat_to_glmQuat(const aiQuaternion quat)
{
	return glm::quat(quat.w, quat.x, quat.y, quat.z);
}

glm::vec3 GlobalResources::aiVec3_to_glmVec3(const aiVector3D vec)
{
	return glm::vec3(vec.x, vec.y, vec.z);
}
