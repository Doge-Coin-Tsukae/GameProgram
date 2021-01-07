#define _CRT_SECURE_NO_WARNINGS
#include "myDirect3D.h"
#include "OXAllocateHierarchy.h"
#include "xfile.h"
#include <string.h>
#include <tchar.h>
#include <map>

OX::OXD3DXMESHCONTAINER *getMeshContainer(D3DXFRAME *frame) {
	if (frame->pMeshContainer)
		return (OX::OXD3DXMESHCONTAINER*)frame->pMeshContainer;
	if (frame->pFrameFirstChild)
		return getMeshContainer(frame->pFrameFirstChild);
	if (frame->pFrameSibling)
		return getMeshContainer(frame->pFrameSibling);
	return 0;
}

//�v���g�^�C�v�錾
void setFrameId(OX::OXD3DXFRAME *frame, ID3DXSkinInfo *info) {
	std::map<std::string, DWORD> nameToIdMap;
	for (DWORD i = 0; i < info->GetNumBones(); i++)
		nameToIdMap[info->GetBoneName(i)] = i;

	struct create {
		static void f(std::map<std::string, DWORD> nameToIdMap, ID3DXSkinInfo *info, OX::OXD3DXFRAME* frame) {
			if (nameToIdMap.find(frame->Name) != nameToIdMap.end()) {
				frame->id = nameToIdMap[frame->Name];
				frame->offsetMatrix = *info->GetBoneOffsetMatrix(frame->id);
			}
			if (frame->pFrameFirstChild)
				f(nameToIdMap, info, (OX::OXD3DXFRAME*)frame->pFrameFirstChild);
			if (frame->pFrameSibling)
				f(nameToIdMap, info, (OX::OXD3DXFRAME*)frame->pFrameSibling);
		}
	};
	create::f(nameToIdMap, info, frame);
}

void updateCombMatrix(std::map<DWORD, D3DXMATRIX> &combMatrixMap, OX::OXD3DXFRAME *frame) {
	struct update {
		static void f(std::map<DWORD, D3DXMATRIX> &combMatrixMap, D3DXMATRIX &parentBoneMatrix, OX::OXD3DXFRAME *frame) {
			D3DXMATRIX &localBoneMatrix = frame->TransformationMatrix;
			D3DXMATRIX boneMatrix = localBoneMatrix * parentBoneMatrix;
			if (frame->id != 0xffffffff)
				combMatrixMap[frame->id] = frame->offsetMatrix * boneMatrix;
			if (frame->pFrameFirstChild)
				f(combMatrixMap, boneMatrix, (OX::OXD3DXFRAME*)frame->pFrameFirstChild);
			if (frame->pFrameSibling)
				f(combMatrixMap, parentBoneMatrix, (OX::OXD3DXFRAME*)frame->pFrameSibling);
		}
	};
	D3DXMATRIX iden;
	D3DXMatrixIdentity(&iden);
	update::f(combMatrixMap, iden, frame);
}

//�}�N���錾
#define XFILE_MAX	6

//�\����
XFILE g_Xfile[XFILE_MAX];

ANIMATIONXFILE g_AnimationXfile[10];

LPDIRECT3DDEVICE9 static pDevice;
std::map<DWORD, D3DXMATRIX> combMatrixMap;
// �X�L�����b�V������X�t�@�C������擾
OX::AllocateHierarchy allocater;
OX::OXD3DXMESHCONTAINER *cont;


HRESULT Xfile_Initialize(void)
{
	pDevice = GetD3DDevice();

	strcpy(g_Xfile[0].filename, "asset/model/human.x");
	strcpy(g_Xfile[1].filename, "asset/model/parts/arm.x");
	strcpy(g_Xfile[2].filename, "asset/model/parts/body.x");
	strcpy(g_Xfile[3].filename, "asset/model/parts/hand.x");
	strcpy(g_Xfile[4].filename, "asset/model/parts/head.x");
	strcpy(g_Xfile[5].filename, "asset/model/parts/leg.x");

	for (int i = 0; i < XFILE_MAX; i++)
	{
		g_Xfile[i].g_pTextureModel = NULL;
		g_Xfile[i].g_pMeshModel = NULL;
		g_Xfile[i].g_pBuffMatModel = NULL;
		g_Xfile[i].hr = NULL;
	}


	for (int i = 0; i < 10; i++)
	{
		g_AnimationXfile[i].g_pMeshModel = NULL;
		g_AnimationXfile[i].g_pBuffMatModel = NULL;
		g_AnimationXfile[i].hr = NULL;
	}
	return S_OK;
}

void Xfile_Finalize(void)
{
	for (int i = 0; i < XFILE_MAX; i++)
	{
		if (g_Xfile[i].g_pTextureModel != NULL)
		{// �e�N�X�`���̊J��
			g_Xfile[i].g_pTextureModel->Release();
			g_Xfile[i].g_pTextureModel = NULL;
		}

		if (g_Xfile[i].g_pMeshModel != NULL)
		{// ���b�V���̊J��
			g_Xfile[i].g_pMeshModel->Release();
			g_Xfile[i].g_pMeshModel = NULL;
		}

		if (g_Xfile[i].g_pBuffMatModel != NULL)
		{// �}�e���A���̊J��
			g_Xfile[i].g_pBuffMatModel->Release();
			g_Xfile[i].g_pBuffMatModel = NULL;
		}
	}
}

//X�t�@�C���̕`�揈��(X�t�@�C����\�����������Ƃ���Ő錾)
void Xfile_Draw(D3DXVECTOR3 scl, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int number)
{
	LPDIRECT3DDEVICE9 static pDevice = GetD3DDevice();
	D3DXMATRIX static mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&g_Xfile[number].g_mtxWorldField);

	//�X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&g_Xfile[number].g_mtxWorldField, &g_Xfile[number].g_mtxWorldField, &mtxScl);

	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&g_Xfile[number].g_mtxWorldField, &g_Xfile[number].g_mtxWorldField, &mtxRot);

	//�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&g_Xfile[number].g_mtxWorldField, &g_Xfile[number].g_mtxWorldField, &mtxTranslate);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Xfile[number].g_mtxWorldField);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)g_Xfile[number].g_pBuffMatModel->GetBufferPointer();

	//�}�e���A���̐�����for���[�v
	for (int nCntMat = 0; nCntMat < (int)g_Xfile[number].g_nNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		g_Xfile[number].hr = GetD3DDevice()->SetTexture(0, g_Xfile[number].g_pTextureModel);

		//�`��
		g_Xfile[number].g_pMeshModel->DrawSubset(nCntMat);
	}


	//�}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//�A�j���[�V�����t����X�t�@�C���̕`�揈��(X�t�@�C����\�����������Ƃ���Ő錾)
void AnimationXfile_Draw(D3DXVECTOR3 scl, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int number)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX  static mtxScl, mtxRot, mtxTranslate;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *material = (D3DXMATERIAL*)g_Xfile[0].g_pBuffMatModel->GetBufferPointer();
	// Direct3D�̏���
	pDevice->SetTexture(0, g_AnimationXfile[number].tex);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_AnimationXfile[number].g_mtxWorldField);

	//�X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&g_AnimationXfile[number].g_mtxWorldField, &g_AnimationXfile[number].g_mtxWorldField, &mtxScl);


	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&g_AnimationXfile[number].g_mtxWorldField, &g_AnimationXfile[number].g_mtxWorldField, &mtxRot);

	//�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&g_AnimationXfile[number].g_mtxWorldField, &g_AnimationXfile[number].g_mtxWorldField, &mtxTranslate);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	g_AnimationXfile[number].controller->AdvanceTime(0.016f, 0);

	updateCombMatrix(combMatrixMap, g_AnimationXfile[number].pRootFrame);

	//�s�������?(�ړ��ɕK�v)
	for (DWORD i = 0; i < 35; i++)
	{
		D3DXMatrixMultiply(&combMatrixMap[i], &combMatrixMap[i], &g_AnimationXfile[number].g_mtxWorldField);
	}

	//�}�e���A���̐�����for���[�v
	for (DWORD i = 0; i < cont->numBoneCombinations; i++)
	{
		DWORD boneNum = 0;

		pDevice->SetMaterial(&material->MatD3D);

		for (DWORD j = 0; j < cont->maxFaceInfl; j++)
		{
			DWORD id = g_AnimationXfile[number].combs[i].BoneId[j];
			if (id != UINT_MAX)
			{
				pDevice->SetTransform(D3DTS_WORLDMATRIX(j), &combMatrixMap[id]);
				boneNum++;
			}
		}
		pDevice->SetRenderState(D3DRS_VERTEXBLEND, boneNum - 1);
		cont->MeshData.pMesh->DrawSubset(i);
		g_AnimationXfile[number].g_pMeshModel = cont->MeshData.pMesh;
	}

	//�}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//x�t�@�C���̌ʓǂݍ���
void SetXfile(int index)
{
	D3DXLoadMeshFromX(g_Xfile[index].filename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,				//�אڃ|���S��(��{�I�ɂ���Ȃ�)
		&g_Xfile[index].g_pBuffMatModel,
		NULL,
		&g_Xfile[index].g_nNumMatModel,
		&g_Xfile[index].g_pMeshModel);

	//�e�N�X�`��
	g_Xfile[index].hr = D3DXCreateTextureFromFile(pDevice, "asset/model/modess.png", &g_Xfile[index].g_pTextureModel);
}

//�A�j���[�V�����t����X�t�@�C���̌ʓǂݍ���
void SetAnimationXfile(int index)
{

	g_AnimationXfile[index].pRootFrame = 0;
	g_AnimationXfile[index].controller = 0;

	D3DXLoadMeshHierarchyFromX(_T("asset/model/foxy3.x"), D3DXMESH_MANAGED, pDevice, &allocater, 0, (D3DXFRAME**)&g_AnimationXfile[index].pRootFrame, &g_AnimationXfile[index].controller);

	cont = getMeshContainer(g_AnimationXfile[index].pRootFrame);
	g_AnimationXfile[index].combs = (D3DXBONECOMBINATION*)cont->boneCombinationTable->GetBufferPointer();

	// �t���[�����Ƀ{�[��ID�ƃI�t�Z�b�g�s��𖄂ߍ���
	setFrameId(g_AnimationXfile[index].pRootFrame, cont->pSkinInfo);
	// �e�N�X�`���쐬
	g_AnimationXfile[index].tex = 0;
	//�e�N�X�`���̌ʓǂݍ���

	if (index == 0)
	{
		D3DXCreateTextureFromFile(pDevice, "asset/model/modess.png", &g_AnimationXfile[index].tex);

	}
	else
	{
		D3DXCreateTextureFromFile(pDevice, "asset/model/modess2p.png", &g_AnimationXfile[index].tex);
	}

	unsigned int imax = g_AnimationXfile[index].controller->GetNumAnimationSets();

	for (int i = 0; i < imax; i++)
	{
		g_AnimationXfile[index].controller->GetAnimationSet(i, &g_AnimationXfile[index].pAnimSet[i]);
	}

}

//x�t�@�C���̌ʉ��
void ReleaseXfile(int index)
{
	if (g_Xfile[index].g_pTextureModel != NULL)
	{// �e�N�X�`���̊J��
		g_Xfile[index].g_pTextureModel->Release();
		g_Xfile[index].g_pTextureModel = NULL;
	}

	if (g_Xfile[index].g_pMeshModel != NULL)
	{// ���b�V���̊J��
		g_Xfile[index].g_pMeshModel->Release();
		g_Xfile[index].g_pMeshModel = NULL;
	}

	if (g_Xfile[index].g_pBuffMatModel != NULL)
	{// �}�e���A���̊J��
		g_Xfile[index].g_pBuffMatModel->Release();
		g_Xfile[index].g_pBuffMatModel = NULL;
	}
}

//�A�j���[�V�����؂�ւ�
void ChengeAnimation(int index, int animID, float speed)
{
	g_AnimationXfile[index].controller->SetTrackAnimationSet(0, g_AnimationXfile[index].pAnimSet[animID]);		//�A�j���[�V������؂�ւ���
	g_AnimationXfile[index].controller->SetTrackPosition(animID, 0);				//�A�j���[�V�����̃g���b�N�ʒu�̃��Z�b�g
	g_AnimationXfile[index].controller->SetTrackSpeed(0, speed);					//�A�j���[�V�����̑��x�ݒ�
}

//���݂̃A�j���[�V�������~����
void StopAnimation(int index)
{
	g_AnimationXfile[index].controller->SetTrackSpeed(0, 0.0f);
}

D3DXMATRIX GetMatrix(int index)
{
	return g_AnimationXfile[index].g_mtxWorldField;
}
LPD3DXMESH GetMesh(int index)
{
	return g_AnimationXfile[index].g_pMeshModel;
}