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
//#include "Transform.h"

using namespace std;

class Skeleton;

class GameObject
{
public:

//	Transform		mTransform;
	Skeleton		mSkeleton;
//	string			mName;

	GameObject() {}

	GameObject(const std::string& modelPath, 
		glm::vec3 pos = glm::vec3(0.0f),
		glm::vec3 rot = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f));

	void AddAnimation(const std::string& animName, const std::string& animFilePath, bool loop = false);
	void SetCurrentAnimation(const std::string& animName);
	
	void CreateCollision();

	inline glm::vec3 getRotation() { return mTransform.mEulerAngles; }

	inline void StartAnimator() { mAnimator->StartAnimator(); }
	inline void StopAnimator() { mAnimator->StopAnimator(); }

	void Move(glm::vec3 translate) { mTransform.Translate(translate); }
	void Rotate(glm::vec3 rotate) { mTransform.Rotate(rotate); }
	void Scale(glm::vec3 scale) { mTransform.Scale(scale); }

	void Update(float deltaTime);
	void Render(Shader* shader);

private:
//	Is there any reason to separate these from the Model object?
	vector<Mesh*>	mMeshes;

	Animator*		mAnimator;
//	Collision		mCollision;
	string			mDirectory;

/*	Like Unity, we can potentially contain all these 3D vectors into a single class 'Transform'.
	This way I can simply point to this Transform object from other class objects to either move
	this GameObject or have access to the relevant vectors instead of referencing each vector
	separately.
	Should I make this Transform object PUBLIC or PRIVATE? */

	glm::vec3		mPosition;
//	Consider using a quaternion instead of a vector.
//	You will have to research the math behind quaternions (euler angles) before using it.
	glm::quat		mRotationQ;
	glm::vec3		mRotation;
	glm::vec3		mScale;

	Transform		mTransform;

//	Is there any reason to have a model matrix property for a GameObject? It would probably be
//	better to create a function to make and return the matrix in the Transform class and only call
//	it when we need to send it to the GameObject's shader.
	glm::mat4		mModelMatrix;

	void UpdateModelMatrix();
};

#endif