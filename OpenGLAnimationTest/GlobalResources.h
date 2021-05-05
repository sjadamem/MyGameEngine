#ifndef GLOBAL_RESOURCES_H
#define GLOBAL_RESOURCES_H

#include <GLFW/glfw3.h>

#include <assimp/vector3.h>
#include <assimp/matrix4x4.h>
#include <assimp/quaternion.h>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>

class GlobalResources
{
public:
	const static float FRAMES;
	
	static float deltaTime;
	static float currentTime;

	static void resetTimer();
	static void updateDeltaTime();

	static glm::mat4 aiMat4_to_glmMat4(const aiMatrix4x4 mat);
	static glm::quat aiQuat_to_glmQuat(const aiQuaternion quat);
	static glm::vec3 aiVec3_to_glmVec3(const aiVector3D mat);
	
private:
	static float lastTime;

	GlobalResources() {}
};

#endif