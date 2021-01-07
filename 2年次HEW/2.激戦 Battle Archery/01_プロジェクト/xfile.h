#pragma once

#include "main.h"
#include "OXAllocateHierarchy.h"

//********************************************************************************
//�\���̐錾
//********************************************************************************
typedef struct
{
	char filename[64];						//�t�@�C���̃p�X��
	D3DXMATRIX			g_mtxWorldField;	// ���[���h�}�g���b�N�X(�s��)
	LPDIRECT3DTEXTURE9	g_pTextureModel;	// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH			g_pMeshModel;		// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		g_pBuffMatModel;	// �}�e���A�����ւ̃|�C���^(�o�b�t�@)
	HRESULT hr;
	DWORD				g_nNumMatModel;		// �}�e���A�����̑���

}XFILE;

typedef struct
{
	char filename[64];						//�t�@�C���̃p�X��
	D3DXMATRIX			g_mtxWorldField;	// ���[���h�}�g���b�N�X(�s��)
	//LPDIRECT3DTEXTURE9	g_pTextureModel;	// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH			g_pMeshModel;		// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		g_pBuffMatModel;	// �}�e���A�����ւ̃|�C���^(�o�b�t�@)
	HRESULT hr;
	DWORD				g_nNumMatModel;		// �}�e���A�����̑���

	IDirect3DTexture9 *tex;
	OX::OXD3DXFRAME *pRootFrame;
	ID3DXAnimationController *controller;
	D3DXBONECOMBINATION *combs;
	LPD3DXANIMATIONSET pAnimSet[10];   // �A�j���[�V�����Z�b�g

}ANIMATIONXFILE;

//*****************************************************************************
//enum
//*****************************************************************************
enum XFAILNAME		//X�t�@�C���̖��O
{
	ARROW,
	BOW,
	TARGETRED,
	TARGETBLUE,
	TARGETWHITE,
	PILLER,
	PILLER_B,
	PILLER_R,
	WALL,
	SAKU,
	HUMAN_JPN,
	HUMAN_USA,
	HUMAN_FRA,
	HUMAN_KOR,
	HUMAN_VICJPN,
	HUMAN_VICUSA,
	HUMAN_VICFRA,
	HUMAN_VICKOR,
	HUMAN_LOSJPN,
	HUMAN_LOSUSA,
	HUMAN_LOSFRA,
	HUMAN_LOSKOR,
	HUMAN_DRAWJPN,
	HUMAN_DRAWUSA,
	HUMAN_DRAWFRA,
	HUMAN_DRAWKOR,
};

//********************************************************************************
//�v���g�^�C�v�錾
//********************************************************************************

HRESULT Xfile_Initialize(void);
void Xfile_Finalize(void);
void Xfile_Draw(D3DXVECTOR3 scl, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int number);
void AnimationXfile_Draw(D3DXVECTOR3 scl, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int number);
void SetXfile(int index);
void SetAnimationXfile(int index, int texnumber);
void ReleaseXfile(int index);
void ChengeAnimation(int index, int animID);
void StopAnimation(int index);