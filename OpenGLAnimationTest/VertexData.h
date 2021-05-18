#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

const int MAX_BONE_PER_VERTEX = 4;

struct Vertex
{
	glm::vec3	Position;
	glm::vec3	Normals;
	glm::vec2	TexCoords;
};

struct VertexData
{
	glm::vec3		Position;
	glm::vec3		Normals;
	glm::vec2		TexCoords;

	float			Weights[MAX_BONE_PER_VERTEX];
	unsigned int	IDs[MAX_BONE_PER_VERTEX];

	VertexData()
	{
		memset(IDs, -1, MAX_BONE_PER_VERTEX * sizeof(IDs[0]));
		memset(Weights, 0, MAX_BONE_PER_VERTEX * sizeof(Weights[0]));
	}

	VertexData(float pX, float pY, float pZ, float nX, float nY, float nZ, float tX, float tY) :
		Position(glm::vec3(pX, pY, pZ)), 
		Normals(glm::vec3(nX, nY, nZ)), 
		TexCoords(glm::vec2(tX, tY))
	{
		memset(IDs, -1, MAX_BONE_PER_VERTEX * sizeof(IDs[0]));
		memset(Weights, 0, MAX_BONE_PER_VERTEX * sizeof(Weights[0]));
	}

	VertexData(glm::vec3 pos, glm::vec3 nor, glm::vec2 tex) : 
		Position(pos), Normals(nor), TexCoords(tex)
	{
		memset(IDs, -1, MAX_BONE_PER_VERTEX * sizeof(IDs[0]));
		memset(Weights, 0, MAX_BONE_PER_VERTEX * sizeof(Weights[0]));
	}

	void addBoneData(unsigned int id, float weight)
	{
		for (unsigned int i = 0; i < MAX_BONE_PER_VERTEX; i++)
		{
			if (Weights[i] == 0.0)
			{
				IDs[i] = id;
				Weights[i] = weight;
				return;
			}
		}
		//		assert(0);
	}
};

struct BoneData
{
	unsigned int	ID[MAX_BONE_PER_VERTEX];
	float			Weight[MAX_BONE_PER_VERTEX];

	BoneData()
	{
		memset(ID, -1, MAX_BONE_PER_VERTEX * sizeof(ID[0]));
		memset(Weight, 0, MAX_BONE_PER_VERTEX * sizeof(Weight[0]));
	}

	void addBoneData(unsigned int id, float weight)
	{
		for (unsigned int i = 0; i < MAX_BONE_PER_VERTEX; i++)
		{
			if (Weight[i] == 0.0)
			{
				ID[i] = id;
				Weight[i] = weight;
				return;
			}
		}
//		assert(0);
	}
};

struct BoneMatrix
{
	glm::mat4 offsetMatrix;
	glm::mat4 finalWorldTransform;
};

struct PositionKey
{
	float		time;
	glm::vec3	value;
};

struct RotationKey
{
	float		time;
	glm::quat	value;
};

struct ScalingKey
{
	float		time;
	glm::vec3	value;
};

struct AnimationData
{
	std::vector<PositionKey>	positionData;
	std::vector<RotationKey>	rotationData;
	std::vector<ScalingKey>		scalingData;
};

#endif