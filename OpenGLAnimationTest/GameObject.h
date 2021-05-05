#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
#include <map>
	
#include "Shader.h"
#include "Model.h"
#include "Animator.h"

using namespace std;

class Skeleton;

class GameObject
{
public:

//	string			mName;

	GameObject() {}

	GameObject(const std::string& modelPath, 
		glm::vec3 pos = glm::vec3(0.0f),
		glm::vec3 rot = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f));

	void AddAnimation(const std::string& animName, const std::string& animFilePath, bool loop = false);
	void SetCurrentAnimation(const std::string& animName);
	
	inline glm::vec3 getRotation() { return mRotation; }

	inline void StartAnimator() { mAnimator->StartAnimator(); }
	inline void StopAnimator() { mAnimator->StopAnimator(); }

	void Move(glm::vec3 translate) { mPosition += translate; }
	void Rotate(glm::vec3 rotate) { mRotation += rotate; }
	void Scale(glm::vec3 scale) { mScale += scale; }

	void Update(float deltaTime);
	void Render(Shader* shader);

private:
	Skeleton					mSkeleton;
	vector<Mesh>				mMeshes;

	Animator*					mAnimator;
//	Collision					mCollision;
	string						mDirectory;

	glm::vec3					mPosition;
	glm::vec3					mRotation;
	glm::vec3					mScale;

	glm::mat4					mModelMatrix;

	void UpdateModelMatrix();
};

#endif