#ifndef SKELETON_H
#define SKELETON_H

#include <assimp/scene.h>

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "GlobalResources.h"
#include "VertexData.h"

#define MAX_NUM_OF_BONES	100

using namespace std;

struct Node
{
	string mNodeName;

	glm::mat4 mTransformationMatrix;

	unsigned int mNumChildren;
	Node*  mParentNode;
	Node** mChildrenNodes;

	Node(string name, glm::mat4 offset, unsigned int children) :
		mNodeName(name), mTransformationMatrix(offset), mNumChildren(children), mParentNode(NULL)
	{
		mChildrenNodes = new Node*[mNumChildren];
	}
};

struct Bone
{
	unsigned int			mID;
	glm::mat4				mOffsetMatrix;

	Bone() {}
	Bone(unsigned int id, glm::mat4 offset) : mID(id), mOffsetMatrix(offset) { }
};

class Skeleton
{
public:

	Skeleton() { }
	~Skeleton() { };

	void Initialize(glm::mat4 globalInverse, map<string, Bone> boneMap, const aiNode* root);

	vector<glm::mat4>& GetBoneMatrices() { return mFinalTransformMatrices; }
	
	void UpdateBoneMatrices(const float& deltaTime);

	void SetBoneAnimationMap(map<string, AnimationData>* animMap) 
		{ mBoneAnimationMap = animMap; }
private:
	vector<glm::mat4>					mFinalTransformMatrices;
	
	glm::mat4							mGlobalInverseTransformMatrix;
	
	map<string, Bone>					mBoneMap;
	vector<Node*>						mNodes;

	map<string, AnimationData>*	mBoneAnimationMap;

	void InterpolatePosition(glm::vec3& position, float& animTime, AnimationData& animData);
	void InterpolateRotation(glm::quat& rotation, float& animTime, AnimationData& animData);
	void InterpolateScaling(glm::vec3& scaling, float& animTime, AnimationData& animData);

	unsigned int FindPositionKey(float& animTime, vector<PositionKey>& posKeys);
	unsigned int FindRotationKey(float& animTime, vector<RotationKey>& rotKeys);
	unsigned int FindScalingKey(float& animTime, vector<ScalingKey>& scaleKeys);

	void ReadNodeHeirarchy(float animTime, Node* node, glm::mat4& parentTransform);

	void			freeAssimpNodeData(const aiNode* node);
	void			linkNodes(const aiNode* node);

	const aiNode*	findAssimpNode(std::string name, const aiNode* node);
	Node*			findOurNode(string name);
};

#endif