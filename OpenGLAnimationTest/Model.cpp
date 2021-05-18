#include "Model.h"

vector<Texture> Model::all_loaded_textures;

Model::Model(const std::string& modelDir)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(modelDir, 
		aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (!scene)
	{
		cout << "MODEL::CONSTRUCTOR::" << importer.GetErrorString() << endl;
		return;
	}

	mNumOfBones = 0;
	directory = modelDir.substr(0, modelDir.find_last_of('/'));
	aiNode* root = scene->mRootNode;

	glm::mat4 globalInverse = GlobalResources::aiMat4_to_glmMat4(root->mTransformation.Inverse());

	loadModel(scene);

	mSkeleton.Initialize(globalInverse, mBoneMap, root);
}

void Model::loadModel(const aiScene* scene)
{
	processNode(scene, scene->mRootNode);
}

void Model::processNode(const aiScene* scene, const aiNode* node)
{
	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[i];
		processMeshes(scene, mesh);
	}
}

#if 0
void Model::processMesh(const aiScene* scene, const aiMesh* mesh)
{
	vector<Vertex>		vertices;
	vector<unsigned int> indices;
	vector<BoneData>	boneData;
	vector<Texture>		textures;

	//VERTEX DATA (POSITION, NORMALS, TEXTURE COORDS)
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		glm::vec3 vec;
		vec.x = mesh->mVertices[i].x;
		vec.y = mesh->mVertices[i].y;
		vec.z = mesh->mVertices[i].z;
		vertex.Position = vec;

		if (mesh->HasNormals())
		{
			vec.x = mesh->mNormals[i].x;
			vec.y = mesh->mNormals[i].y;
			vec.z = mesh->mNormals[i].x;
			vertex.Normals = vec;
		}
		else
			vertex.Normals = glm::vec3();

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 tex;
			tex.x = mesh->mTextureCoords[0][i].x;
			tex.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = tex;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f);

		vertices.push_back(vertex);
	}

	//FACE INDICES
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	//MATERIALS (TEXTURES)
	if (scene->HasMaterials())
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> textureMaps = processMaterials(material, aiTextureType_DIFFUSE, "diffuse");
		textures.insert(textures.end(), textureMaps.begin(), textureMaps.end());
		std::vector<Texture> specularMaps = processMaterials(material, aiTextureType_SPECULAR, "specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	else
		textures.push_back(Texture("Textures/container_diffuse.jpg", "diffuse"));

	//BONE DATA
	if (mesh->HasBones())
	{
		boneData.resize(mesh->mNumVertices);
		auto boneMap = mSkeleton.GetBoneMap();

		for (unsigned int i = 0; i < mesh->mNumBones; i++)
		{
			aiBone* bone		= mesh->mBones[i];
			string boneName		= bone->mName.data;
			unsigned int index	= boneMap->at(boneName);

			//Add all vertex weights and ids from the bone to the vector
			aiVertexWeight* weights = bone->mWeights;
			for (unsigned int j = 0; j < bone->mNumWeights; j++)
			{
				unsigned int vertexId	= weights[j].mVertexId;
				float vertexWeight		= weights[j].mWeight;
				boneData[vertexId].addBoneData(index, vertexWeight);
			}
		}	
	}

	mMeshes.push_back(Mesh(vertices.data(), vertices.size(), indices.data(), indices.size(), boneData.data(), boneData.size(), textures.data()));
}
#endif

void Model::processMeshes(const aiScene * scene, const aiMesh * mesh)
{
	vector<VertexData>	vertices;
	vector<unsigned int> indices;
//	vector<BoneData>	boneData;
	vector<Texture>		textures;

	//VERTEX DATA (POSITION, NORMALS, TEXTURE COORDS)
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		VertexData vertex;

		glm::vec3 vec;
		vec.x = mesh->mVertices[i].x;
		vec.y = mesh->mVertices[i].y;
		vec.z = mesh->mVertices[i].z;
		vertex.Position = vec;

		if (mesh->HasNormals())
		{
			vec.x = mesh->mNormals[i].x;
			vec.y = mesh->mNormals[i].y;
			vec.z = mesh->mNormals[i].x;
			vertex.Normals = vec;
		}
		else
			vertex.Normals = glm::vec3();

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 tex;
			tex.x = mesh->mTextureCoords[0][i].x;
			tex.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = tex;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f);

		vertices.push_back(vertex);
	}

	//FACE INDICES
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	//MATERIALS (TEXTURES)
	if (scene->HasMaterials())
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> textureMaps = processMaterials(material, aiTextureType_DIFFUSE, "diffuse");
		textures.insert(textures.end(), textureMaps.begin(), textureMaps.end());
		std::vector<Texture> specularMaps = processMaterials(material, aiTextureType_SPECULAR, "specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	else
		textures.push_back(Texture("Textures/container_diffuse.jpg", "diffuse"));

	for (unsigned int i = 0; i < mesh->mNumBones; i++)
	{
		unsigned int boneID = -1;
		aiBone* bone = mesh->mBones[i];
		std::string boneName = bone->mName.data;
		
		if (mBoneMap.find(boneName) == mBoneMap.end())
		{
			unsigned int id		= mNumOfBones;
			glm::mat4 offset	= GlobalResources::aiMat4_to_glmMat4(bone->mOffsetMatrix);
			Bone b(id, offset);
			mBoneMap[boneName]	= b;
			
			boneID				= mNumOfBones;
			mNumOfBones++;

			std::cout << boneName << std::endl;
		}
		else
			boneID				= mBoneMap[boneName].mID;

		assert(boneID != -1);

		auto weights = bone->mWeights;
		for (unsigned int j = 0; j < bone->mNumWeights; j++)
		{
			unsigned int vertexId	= weights[j].mVertexId;
			float weight			= weights[j].mWeight;
//			assert(vertexId <= vertices.size());
			vertices[vertexId].addBoneData(boneID, weight);
		}
	}

	mMeshes.push_back(new SkeletalMesh(vertices.data(), vertices.size(), indices.data(), indices.size(), textures.data(), textures.size()));
}

vector<Texture> Model::processMaterials(aiMaterial* mat, aiTextureType type, string textureType)
{
	vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		bool skip = false;
		for (unsigned int j = 0; j < all_loaded_textures.size(); j++)
		{
			if (all_loaded_textures[j].GetTexturePath() == str.C_Str())
			{
				textures.push_back(all_loaded_textures[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			string modelTexturePath = directory + "/" + str.C_Str();
			Texture texture(modelTexturePath, textureType);
			textures.push_back(texture);
			all_loaded_textures.push_back(texture);
		}
	}

	return textures;
}