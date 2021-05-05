#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "Texture.h"
#include "VertexData.h"
#include "Mesh.h"
#include "Skeleton.h"

#include "Shader.h"

using namespace std;

class Model
{
public:
	Model(const std::string& modelDir);

	inline Skeleton GetSkeleton() { return mSkeleton; }
	inline vector<Mesh> GetMeshes() { return mMeshes; }

private:
	static vector<Texture> all_loaded_textures;

	unsigned int			mNumOfBones;
	map<string, Bone>		mBoneMap;				//string = name, Bone has id

	vector<Mesh>	mMeshes;
	Skeleton		mSkeleton;

	string directory;
	void			loadModel(const aiScene* scene);

	void			processNode(const aiScene* scene, const aiNode* node);
	void			processMesh(const aiScene* scene, const aiMesh* mesh);
	void			processMeshes(const aiScene* scene, const aiMesh* mesh);

	vector<Texture> processMaterials(aiMaterial* mat, aiTextureType type, string textureType);
};

#endif