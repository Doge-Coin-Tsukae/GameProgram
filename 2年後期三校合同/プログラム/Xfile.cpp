#define _CRT_SECURE_NO_WARNINGS
#include "myDirect3D.h"
#include "xfile.h"
#include <string.h>

//マクロ宣言
#define XFILE_MAX	1

//構造体
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
			NULL,				//隣接ポリゴン(基本的にいらない)
			&g_Xfile[i].ppFrameHeirarchy,
			&g_Xfile[i].ppAnimController);*/

		if (FAILED(D3DXLoadMeshFromX(g_Xfile[i].filename,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,				//隣接ポリゴン(基本的にいらない)
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
		{// テクスチャの開放
			g_Xfile[i].g_pTextureModel->Release();
			g_Xfile[i].g_pTextureModel = NULL;
		}

		if (g_Xfile[i].g_pMeshModel != NULL)
		{// メッシュの開放
			g_Xfile[i].g_pMeshModel->Release();
			g_Xfile[i].g_pMeshModel = NULL;
		}

		if (g_Xfile[i].g_pBuffMatModel != NULL)
		{// マテリアルの開放
			g_Xfile[i].g_pBuffMatModel->Release();
			g_Xfile[i].g_pBuffMatModel = NULL;
		}
	}
}

//Xファイルの描画処理(Xファイルを表示させたいところで宣言)
void Xfile_Draw(D3DXVECTOR3 scl, D3DXVECTOR3 pos, D3DXVECTOR3 rot,int number)
{
	LPDIRECT3DDEVICE9 static pDevice = GetD3DDevice();
	D3DXMATRIX static mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&g_Xfile[number].g_mtxWorldField);

	//スケールを反映
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&g_Xfile[number].g_mtxWorldField, &g_Xfile[number].g_mtxWorldField, &mtxScl);

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&g_Xfile[number].g_mtxWorldField, &g_Xfile[number].g_mtxWorldField, &mtxRot);

	//移動を反映
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&g_Xfile[number].g_mtxWorldField, &g_Xfile[number].g_mtxWorldField, &mtxTranslate);

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Xfile[number].g_mtxWorldField);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)g_Xfile[number].g_pBuffMatModel->GetBufferPointer();


	//マテリアルの数だけforループ
	for (int nCntMat = 0; nCntMat < (int)g_Xfile[number].g_nNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_Xfile[number].g_pTextureModel);

		//描画
		g_Xfile[number].g_pMeshModel->DrawSubset(nCntMat);
	}


	//マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}