#pragma once

#include "OXAllocateHierarchy.h"
#include "main.h"

//********************************************************************************
//構造体宣言
//********************************************************************************
typedef struct
{
	char filename[64];						//ファイルのパス名
	D3DXMATRIX			g_mtxWorldField;	// ワールドマトリックス(行列)
	LPDIRECT3DTEXTURE9	g_pTextureModel;	// テクスチャへのポインタ
	LPD3DXMESH			g_pMeshModel;		// メッシュ情報へのポインタ
	LPD3DXBUFFER		g_pBuffMatModel;	// マテリアル情報へのポインタ(バッファ)
	HRESULT hr;
	DWORD				g_nNumMatModel;		// マテリアル情報の総数

}XFILE;

typedef struct
{
	char filename[64];						//ファイルのパス名
	D3DXMATRIX			g_mtxWorldField;	// ワールドマトリックス(行列)
	//LPDIRECT3DTEXTURE9	g_pTextureModel;	// テクスチャへのポインタ
	LPD3DXMESH			g_pMeshModel;		// メッシュ情報へのポインタ
	LPD3DXBUFFER		g_pBuffMatModel;	// マテリアル情報へのポインタ(バッファ)
	HRESULT hr;
	DWORD				g_nNumMatModel;		// マテリアル情報の総数

	IDirect3DTexture9 *tex;
	OX::OXD3DXFRAME *pRootFrame;
	ID3DXAnimationController *controller;
	D3DXBONECOMBINATION *combs;
	LPD3DXANIMATIONSET pAnimSet[10];   // アニメーションセット

}ANIMATIONXFILE;

//*****************************************************************************
//enum
//*****************************************************************************
enum XFAILNAME		//Xファイルの名前
{
	HUMAN,
	HEAD,
	BODY,
	ARM,
	HAND,
	LEG,
};

//********************************************************************************
//プロトタイプ宣言
//********************************************************************************

HRESULT Xfile_Initialize(void);
void Xfile_Finalize(void);
void Xfile_Draw(D3DXVECTOR3 scl, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int number);
void AnimationXfile_Draw(D3DXVECTOR3 scl, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int number);
void SetXfile(int index);
void SetAnimationXfile(int index);
void ReleaseXfile(int index);
void ChengeAnimation(int index, int animID, float speed);
void StopAnimation(int index);

D3DXMATRIX GetMatrix(int index);
LPD3DXMESH GetMesh(int index);