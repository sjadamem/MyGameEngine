#include "Skeleton.h"

unsigned int Skeleton::FindPositionKey(float& frameTime, vector<PositionKey>& posKeys)
{
	for (unsigned int i = 0; i < posKeys.size() - 1; i++)
	{
		if (frameTime < posKeys[i + 1].time)
			return i;
	}

	return 0;
}

unsigned int Skeleton::FindRotationKey(float& frameTime, vector<RotationKey>& rotKeys)
{
	for (unsigned int i = 0; i < rotKeys.size() - 1; i++)
	{
		if (frameTime < rotKeys[i + 1].time)
			return i;
	}

	return 0;
}

unsigned int Skeleton::FindScalingKey(float& frameTime, vector<ScalingKey>& scaleKeys)
{
	for (unsigned int i = 0; i < scaleKeys.size() - 1; i++)
	{
		if (frameTime < scaleKeys[i + 1].time)
			return i;
	}

	return 0;
}

void Skeleton::InterpolatePosition(glm::vec3& vector, float& frameTime, AnimationData& animData)
{
	if (animData.positionData.size() == 1)
	{
		vector = animData.positionData[0].value;
		return;
	}

	unsigned int positionIndex = FindPositionKey(frameTime, animData.positionData);
	unsigned int nextPositionIndex = positionIndex + 1;

	float deltaTime =
		animData.positionData[nextPositionIndex].time - animData.positionData[positionIndex].time;
	
	float factor = (frameTime - animData.positionData[positionIndex].time) / deltaTime;

	glm::vec3 startPosition = animData.positionData[positionIndex].value;
	glm::vec3 endPosition = animData.positionData[nextPositionIndex].value;
//	glm::vec3 deltaPosition = endPosition - startPosition;

	vector = glm::mix(startPosition, endPosition, factor);
}

void Skeleton::InterpolateRotation(glm::quat& quat, float& frameTime, AnimationData& animData)
{
	if (animData.rotationData.size() == 1)
	{
		quat = animData.rotationData[0].value;
		return;
	}

	unsigned int rotationIndex = FindRotationKey(frameTime, animData.rotationData);
	unsigned int nextRotationIndex = rotationIndex + 1;

	float deltaTime =
		animData.rotationData[nextRotationIndex].time - animData.rotationData[rotationIndex].time;

	float factor = (frameTime - animData.rotationData[rotationIndex].time) / deltaTime;

	glm::quat startPosition = animData.rotationData[rotationIndex].value;
	glm::quat endPosition = animData.rotationData[nextRotationIndex].value;

	glm::quat slerp = glm::slerp(startPosition, endPosition, factor);
	quat = glm::normalize(slerp);
}

void Skeleton::InterpolateScaling(glm::vec3& vector, float& frameTime, AnimationData& animData)
{
	if (animData.scalingData.size() == 1)
	{
		vector = animData.scalingData[0].value;
		return;
	}

	unsigned int scalingIndex = FindScalingKey(frameTime, animData.scalingData);
	unsigned int nextScalingIndex = scalingIndex + 1;

	float deltaTime =
		animData.scalingData[nextScalingIndex].time - animData.scalingData[scalingIndex].time;

	float factor = (frameTime - animData.scalingData[scalingIndex].time) / deltaTime;

	glm::vec3 startPosition = animData.scalingData[scalingIndex].value;
	glm::vec3 endPosition = animData.scalingData[nextScalingIndex].value;

	vector = glm::mix(startPosition, endPosition, factor);
}

void Skeleton::Initialize(glm::mat4 globalInverse, map<string, Bone> boneMap, const aiNode* root)
{
	mGlobalInverseTransformMatrix = globalInverse;
	mBoneMap = boneMap;

	freeAssimpNodeData(root);
	linkNodes(root);
}

void Skeleton::UpdateBoneMatrices(const float& deltaTime)
{
	mFinalTransformMatrices.clear();
	mFinalTransformMatrices.resize(mBoneMap.size());

	glm::mat4 mat(1.0f);

	ReadNodeHeirarchy(deltaTime, mNodes[0], mat);
}

void Skeleton::ReadNodeHeirarchy(float animTime, Node* node, glm::mat4& parentTransform)
{
	glm::mat4 nodeTransform = node->mTransformationMatrix;
	string nodeName = node->mNodeName;
	
	if (mBoneAnimationMap->find(nodeName) != mBoneAnimationMap->end())
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		auto animData = mBoneAnimationMap->at(nodeName);

		InterpolatePosition(position, animTime, animData);
		InterpolateRotation(rotation, animTime, animData);
		InterpolateScaling(scale, animTime, animData);

		glm::mat4 boneTransform(1.0f);
		boneTransform = glm::translate(boneTransform, position);
		boneTransform *= glm::mat4_cast(rotation);
		boneTransform = glm::scale(boneTransform, scale);

		nodeTransform = boneTransform;
	}
	
	glm::mat4 GlobalTransform = parentTransform * nodeTransform;
	
	if (mBoneMap.find(nodeName) != mBoneMap.end())
	{
		Bone* bone = &mBoneMap[nodeName];

		unsigned int index = bone->mID;
		mFinalTransformMatrices[index] = mGlobalInverseTransformMatrix * GlobalTransform * bone->mOffsetMatrix;
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
		ReadNodeHeirarchy(animTime, node->mChildrenNodes[i], GlobalTransform);
}

void Skeleton::freeAssimpNodeData(const aiNode* node)
{
	if (!node)
		return;

	string name = node->mName.data;
	glm::mat4 trans = GlobalResources::aiMat4_to_glmMat4(node->mTransformation);
	unsigned int children = node->mNumChildren;
	
	mNodes.push_back(new Node(name, trans, children));

	for (unsigned int i = 0; i < children; i++)
		freeAssimpNodeData(node->mChildren[i]);
}

void Skeleton::linkNodes(const aiNode* node)
{
	for (unsigned int i = 0; i < mNodes.size(); i++)
	{
		Node* currentNode = mNodes[i];
		const aiNode* assimpNode = findAssimpNode(currentNode->mNodeName, node);

		for (unsigned int j = 0; j < currentNode->mNumChildren; j++)
		{
			string nodeName = assimpNode->mChildren[j]->mName.data;
			Node* childNode = findOurNode(nodeName);
			*(currentNode->mChildrenNodes + j) = childNode;
		}

		if (assimpNode->mParent)
		{
			string nodeName = assimpNode->mParent->mName.data;
			Node* parentNode = findOurNode(nodeName);
			currentNode->mParentNode = parentNode;
		}
	}
}

const aiNode* Skeleton::findAssimpNode(std::string name, const aiNode* node)
{
	//Check if the current node's name is equal to the name passed in
	if (node->mName.data == name)
		//If TURE, return the current node
		return node;

	//Check if this node doesn't have children
	if (!node->mNumChildren)
		//If TRUE, return null pointer
		return nullptr;

	//Loop through the current node's children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		//Recurse through the current child node
		const aiNode* n = findAssimpNode(name, node->mChildren[i]);

		//Check if the returned node isn't a null pointer
		if (n)
			//Return the node
			return n;
	}

	//Only return null pointer value if and only if none of the node's return any ASSIMP node pointer
	return nullptr;
}

Node* Skeleton::findOurNode(string name)
{
	//Loop through the vector of nodes
	for (unsigned int i = 0; i < mNodes.size(); i++)
	{
		//Check if the current node's name is equal to the passed-in name
		if (mNodes[i]->mNodeName == name)
			//Return the reference to the current node
			return mNodes[i];
	}

	//Only return null pointer value if and only if none of the node's return any ASSIMP node pointer
	return nullptr;
}