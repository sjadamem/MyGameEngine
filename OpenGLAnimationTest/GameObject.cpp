#include "GameObject.h"

GameObject::GameObject(const std::string& modelPath, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) :
	mPosition(pos), mRotation(rot), mScale(scale)
{
	Model m(modelPath);
	mSkeleton = m.GetSkeleton();
	mMeshes = m.GetMeshes();

	mAnimator = new Animator(&mSkeleton);

	UpdateModelMatrix();
}

void GameObject::AddAnimation(const std::string & animName, const std::string & animFilePath, bool loop)
{
	mAnimator->LoadAnimation(animName, animFilePath, loop);
}

void GameObject::SetCurrentAnimation(const std::string & animName)
{
	mAnimator->SetCurrentAnimation(animName);
}

void GameObject::Update(float deltaTime)
{
	UpdateModelMatrix();
	mAnimator->Update(deltaTime);
}

void GameObject::Render(Shader* shader)
{
	auto matrices = mSkeleton.GetBoneMatrices();
	for (unsigned int i = 0; i < matrices.size(); i++)
		shader->SetMat4("boneMatrices[" + std::to_string(i) + "]", matrices[i]);

	shader->SetMat4("model", mModelMatrix);
	
	for (unsigned int i = 0; i < mMeshes.size(); i++)
		mMeshes[i].Render(shader);
}

void GameObject::UpdateModelMatrix()
{
	mModelMatrix = glm::mat4(1.0f);

	mModelMatrix = glm::translate(mModelMatrix, mPosition);

	mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	mModelMatrix = glm::scale(mModelMatrix, mScale);
}