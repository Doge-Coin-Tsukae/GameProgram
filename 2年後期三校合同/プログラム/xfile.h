#pragma once

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
	LPD3DXANIMATIONCONTROLLER ppAnimController;	//アニメーション格納
	LPD3DXFRAME			ppFrameHeirarchy;
	DWORD				g_nNumMatModel;		// マテリアル情報の総数

}XFILE2;

//*****************************************************************************
//enum
//*****************************************************************************
enum XFAILNAME		//Xファイルの名前
{
	HUMAN,
};

//********************************************************************************
//プロトタイプ宣言
//********************************************************************************

HRESULT Xfile_Initialize(void);
void Xfile_Finalize(void);
void Xfile_Draw(D3DXVECTOR3 scl, D3DXVECTOR3 pos, D3DXVECTOR3 rot,int number);