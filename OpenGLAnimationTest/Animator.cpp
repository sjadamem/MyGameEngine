#include "Animator.h"

Animation::Animation(const aiAnimation* anim, bool loop)
{
	mFramesPerSecond = anim->mTicksPerSecond;
	mDuration = anim->mDuration / mFramesPerSecond;
//	mFramesPerSecond = fps;
	mLoop = loop;

	processAnimation(anim);
}

void Animation::AddTransition(Transition& trans)
{
	
}

void Animation::processAnimation(const aiAnimation* anim)
{
	for (unsigned int i = 0; i < anim->mNumChannels; i++)
	{
		const aiNodeAnim* nodeAnim = anim->mChannels[i];
		processNodeKeyframes(nodeAnim);
	}
}

void Animation::processNodeKeyframes(const aiNodeAnim * nodeAnim)
{
	vector<PositionKey> p;
	vector<RotationKey> r;
	vector<ScalingKey>	s;

	for (unsigned int i = 0; i < nodeAnim->mNumPositionKeys; i++)
	{
		float time = nodeAnim->mPositionKeys[i].mTime / mFramesPerSecond;
		auto value = GlobalResources::aiVec3_to_glmVec3(nodeAnim->mPositionKeys[i].mValue);
		p.push_back({ time, value });
	}

	for (unsigned int i = 0; i < nodeAnim->mNumRotationKeys; i++)
	{
		float time = nodeAnim->mRotationKeys[i].mTime / mFramesPerSecond;
		auto value = GlobalResources::aiQuat_to_glmQuat(nodeAnim->mRotationKeys[i].mValue);
		r.push_back({ time, value });
	}
	
	for (unsigned int i = 0; i < nodeAnim->mNumScalingKeys; i++)
	{
		float time = nodeAnim->mScalingKeys[i].mTime / mFramesPerSecond;
		auto value = GlobalResources::aiVec3_to_glmVec3(nodeAnim->mScalingKeys[i].mValue);
		s.push_back({ time, value });
	}

	mBoneKeyframeMap[nodeAnim->mNodeName.data] = { p, r, s };
}

Animator::Animator(Skeleton* skeleton)
{
	mSkeleton = skeleton;

	mPlay = false;
	mAnimationTime = 0.0f;
}

void Animator::SetCurrentAnimation(const string & animName)
{
	mCurrentAnimation = &mAnimations[animName];
	mSkeleton->SetBoneAnimationMap(mCurrentAnimation->GetBoneKeyframeMap());
}

void Animator::AddTransitionBetweenAnimations(string fromAnimation, string toAnimation, Transition& trans)
{
	if (mAnimations.find(fromAnimation) == mAnimations.end())
	{
		cout << "GAMEOBJECT::ANIMATOR::Animation to transition from doesn't exist!!" << endl;
		return;
	}


	if(mAnimations.find(toAnimation) == mAnimations.end())
	{
		cout << "GAMEOBJECT::ANIMATOR::Animation to transition to doesn't exist!!" << endl;
		return;
	}

	mAnimations[fromAnimation].AddTransition(trans);
}

void Animator::Update(float deltaTime)
{
	if (mPlay)
	{
		if (mCurrentAnimation)
		{
			mAnimationTime += deltaTime;
			
			if (mAnimationTime > mCurrentAnimation->mDuration)
				mAnimationTime = fmod(mAnimationTime, mCurrentAnimation->mDuration);
		}
		
		mSkeleton->UpdateBoneMatrices(mAnimationTime);
	}

// 	std::cout << mAnimationTime << std::endl;

}

void Animator::LoadAnimation(const string& animName, const string& animPath, bool loop)
{
	const aiScene* scene = importer.ReadFile(animPath, aiProcess_Triangulate);

	if (!scene)
	{
		std::cout << "GAMEOBJECT::ANIMATOR::" << importer.GetErrorString() << std::endl;
		return;
	}
	
	
	for (unsigned int i = 0; i < scene->mNumAnimations; i++)
	{		
		const aiAnimation* anim = scene->mAnimations[i];
		string sAnimName = scene->mAnimations[i]->mName.data;
		string parsedAnimName = sAnimName.substr(sAnimName.find_last_of('|') + 1, sAnimName.length());
		std::transform(parsedAnimName.begin(), parsedAnimName.end(), parsedAnimName.begin(),
			[](unsigned char c) { return std::tolower(c); });
		mapAnimation(parsedAnimName, Animation(anim, loop));
	}


	scene = nullptr;
}
