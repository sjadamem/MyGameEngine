#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <map>
#include <cctype>

#include <iostream>

#include "Skeleton.h"
#include "VertexData.h"

using namespace std;

struct Transition 
{
	float	mVelocity;

	string	mNextAnimationName;
};

class Animation
{
public:
	float	mDuration;

	bool	mLoop;

//	std::map<unsigned int, Transition> mTransistions;
	std::map<string, AnimationData> mBoneKeyframeMap;

	Animation() { };
	Animation(const aiAnimation* anim, bool loop);

	void AddTransition(Transition& trans);

	auto GetBoneKeyframeMap() { return &mBoneKeyframeMap; }
private:
	float	mFramesPerSecond;

	void processAnimation(const aiAnimation* anim);
	void processNodeKeyframes(const aiNodeAnim* nodeAnim);

};

enum AnimationState
{
	PLAY, PAUSE, REWIND, FASTFORWARD, SLOW
};

class Animator
{
public:
	Animation*				mCurrentAnimation;
	
	Animator() { mPlay = false; mAnimationTime = 0.0f; };
	Animator(Skeleton* skeleton);

	void SetSkeleton(Skeleton& skel) { mSkeleton = &skel; }
	void LoadAnimation(const std::string& animName, const std::string& animPath, bool loop);

	inline void StartAnimator() { mPlay = true; }
	inline void StopAnimator() { mPlay = false; }

	void SetCurrentAnimation(const string& animName);
	inline void SetSkeleton(Skeleton* skeleton) { mSkeleton = skeleton; }

	void AddTransitionBetweenAnimations(string fromAnimation, string toAnimation, Transition& trans);

	void Update(float deltaTime);

private:
	Assimp::Importer importer;
	map<string, Animation>	mAnimations;


//	const Skeleton*			mBlendingSkeleton;		//This is for when the model is supposed to transition between animations
	Skeleton*				mSkeleton;

	AnimationState			mAnimationState;
	float					mAnimationTime;
	float					mFramesPerSeconds;
	bool					mPlay;

	void mapAnimation(const string& animName, Animation animSpec) 
	{ 
		mAnimations[animName] = animSpec; 
	}
};

#endif