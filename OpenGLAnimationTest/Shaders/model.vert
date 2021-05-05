#version 330 core

layout (location = 0) in vec3	aPos;
layout (location = 1) in vec3	aNormal;
layout (location = 2) in vec2	aTexCoords;
layout (location = 3) in ivec4	aID;
layout (location = 4) in vec4	aWeight;

//out vec3 Pos;
//out vec3 Normal;
out vec2 TexCoords;
out vec4 Weights;
//out vec3 Normal;

const int MAX_BONES = 100;
uniform mat4 boneMatrices[MAX_BONES];

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	mat4 BoneTransform =
				 boneMatrices[aID[0]] * aWeight[0];
	BoneTransform += boneMatrices[aID[1]] * aWeight[1];
	BoneTransform += boneMatrices[aID[2]] * aWeight[2];
	BoneTransform += boneMatrices[aID[3]] * aWeight[3];

	vec4 bonePosition = BoneTransform * vec4(aPos, 1.0);
	gl_Position = projection * view * model * bonePosition;

	TexCoords = aTexCoords;
	Weights = aWeight;
}