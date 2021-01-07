#pragma once

#include <map>
#include <vector>

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#pragma comment(lib, "assimp.lib")

//�ό`�㒸�_�\����
struct DEFORM_VERTEX
{
	aiVector3D Position;
	aiVector3D Normal;

	int				BoneNum;
	std::string		BoneName[4];	//�{���̓{�[���C���f�b�N�X�ŊǗ����ׂ�(�����̍��ɂ��Ă��邩)
	float			BoneWeight[4];
};

//�{�[���\����
struct BONE
{
	aiMatrix4x4 Matrix;
	aiMatrix4x4 AnimationMatrix;
	aiMatrix4x4 OffsetMatrix;
};

class CAnimationModel
{
private:
	const aiScene*	m_Scene = NULL;		//fbx�̃f�[�^
	std::map<std::string, const aiScene*> m_Animation;	//�A�j���[�V�����f�[�^

	ID3D11Buffer** m_VertexBuffer;			//�����K�v�Ȃ̂Ń_�u���|�C���^
	ID3D11Buffer** m_IndexBuffer;		//�����K�v�Ȃ̂Ń_�u���|�C���^

	std::map<std::string, ID3D11ShaderResourceView*> m_Texture;

	std::vector<DEFORM_VERTEX>* m_DeformVertex;	//�ό`�㒸�_�f�[�^
	std::map < const std::string, BONE> m_Bone;	//�{�[���f�[�^

	void CreateBone(aiNode* node);
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);
public:
	void Load(const char *FileName);
	void LoadAnimation(const char *FileName, const char *name);
	void Unload();
	void Update(const char *AnimationName1, const char *AnimationName2, int Frame, float rate);
	void Draw();
};