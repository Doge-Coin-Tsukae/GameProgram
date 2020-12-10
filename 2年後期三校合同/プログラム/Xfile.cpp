#define _CRT_SECURE_NO_WARNINGS
#include "myDirect3D.h"
#include "xfile.h"
#include <string.h>

//�}�N���錾
#define XFILE_MAX	1

//�\����
XFILE2 g_Xfile[XFILE_MAX];

HRESULT Xfile_Initialize(void)
{
	LPDIRECT3DDEVICE9 static pDevice;
	pDevice = GetD3DDevice();

	strcpy(g_Xfile[0].filename, "asset/model/human.x");

	for (int i = 0; i < XFILE_MAX; i++)
	{
		g_Xfile[i].g_pTextureModel = NULL;
		g_Xfile[i].g_pMeshModel = NULL;
		g_Xfile[i].g_pBuffMatModel = NULL;

		/*D3DXLoadMeshHierarchyFromX(g_Xfile[i].filename,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			&AH,
			NULL,				//�אڃ|���S��(��{�I�ɂ���Ȃ�)
			&g_Xfile[i].ppFrameHeirarchy,
			&g_Xfile[i].ppAnimController);*/

		if (FAILED(D3DXLoadMeshFromX(g_Xfile[i].filename,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,				//�אڃ|���S��(��{�I�ɂ���Ȃ�)
			&g_Xfile[i].g_pBuffMatModel,
			NULL,
			&g_Xfile[i].g_nNumMatModel,
			&g_Xfile[i].g_pMeshModel)))
		{
			return E_FAIL;
		}
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
void Xfile_Draw(D3DXVECTOR3 scl, D3DXVECTOR3 pos, D3DXVECTOR3 rot,int number)
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
		pDevice->SetTexture(0, g_Xfile[number].g_pTextureModel);

		//�`��
		g_Xfile[number].g_pMeshModel->DrawSubset(nCntMat);
	}


	//�}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}