#define _CRT_SECURE_NO_WARNINGS
#include "myDirect3D.h"
#include "xfile.h"
#include "OXAllocateHierarchy.h"
#include "selectcharctor.h"
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

//プロトタイプ宣言
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

//マクロ宣言
#define XFILE_MAX	26

//構造体
XFILE g_Xfile[XFILE_MAX];

ANIMATIONXFILE g_AnimationXfile[10];

LPDIRECT3DDEVICE9 static pDevice;
std::map<DWORD, D3DXMATRIX> combMatrixMap;
// スキンメッシュ情報をXファイルから取得
OX::AllocateHierarchy allocater;
OX::OXD3DXMESHCONTAINER *cont;


HRESULT Xfile_Initialize(void)
{
	pDevice = GetD3DDevice();

	strcpy(g_Xfile[0].filename, "asset/model/Bow.x");
	strcpy(g_Xfile[1].filename, "asset/model/arrow.x");
	strcpy(g_Xfile[2].filename, "asset/model/targetred.x");
	strcpy(g_Xfile[3].filename, "asset/model/targetblue.x");
	strcpy(g_Xfile[4].filename, "asset/model/targetwhite.x");
	strcpy(g_Xfile[5].filename, "asset/model/piller.x");
	strcpy(g_Xfile[6].filename, "asset/model/piller_b.x");
	strcpy(g_Xfile[7].filename, "asset/model/piller_r.x");
	strcpy(g_Xfile[8].filename, "asset/model/wall.x");
	strcpy(g_Xfile[9].filename, "asset/model/saku.x");
	strcpy(g_Xfile[10].filename, "asset/model/human/jpndrawpose.x");
	strcpy(g_Xfile[11].filename, "asset/model/human/jpndrawpose.x");
	strcpy(g_Xfile[12].filename, "asset/model/human/usadrawpose.x");
	strcpy(g_Xfile[13].filename, "asset/model/human/jpndrawpose.x");
	strcpy(g_Xfile[14].filename, "asset/model/human/jpnvicpose.x");
	strcpy(g_Xfile[15].filename, "asset/model/human/jpnvicpose.x");
	strcpy(g_Xfile[16].filename, "asset/model/human/usavicpose.x");
	strcpy(g_Xfile[17].filename, "asset/model/human/jpnvicpose.x");
	strcpy(g_Xfile[18].filename, "asset/model/human/jpnlospose.x");
	strcpy(g_Xfile[19].filename, "asset/model/human/jpnlospose.x");
	strcpy(g_Xfile[20].filename, "asset/model/human/usalospose.x");
	strcpy(g_Xfile[21].filename, "asset/model/human/jpnlospose.x");
	strcpy(g_Xfile[22].filename, "asset/model/human/jpndrawpose.x");
	strcpy(g_Xfile[23].filename, "asset/model/human/jpndrawpose.x");
	strcpy(g_Xfile[24].filename, "asset/model/human/usadrawpose.x");
	strcpy(g_Xfile[25].filename, "asset/model/human/jpndrawpose.x");

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
void Xfile_Draw(D3DXVECTOR3 scl, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int number)
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
		g_Xfile[number].hr = GetD3DDevice()->SetTexture(0, g_Xfile[number].g_pTextureModel);

		//描画
		g_Xfile[number].g_pMeshModel->DrawSubset(nCntMat);
	}


	//マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//アニメーション付きのXファイルの描画処理(Xファイルを表示させたいところで宣言)
void AnimationXfile_Draw(D3DXVECTOR3 scl, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int number)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX  static mtxScl, mtxRot, mtxTranslate;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *material = (D3DXMATERIAL*)g_Xfile[1].g_pBuffMatModel->GetBufferPointer();
	// Direct3Dの処理
	pDevice->SetTexture(0, g_AnimationXfile[number].tex);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_AnimationXfile[number].g_mtxWorldField);

	//スケールを反映
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&g_AnimationXfile[number].g_mtxWorldField, &g_AnimationXfile[number].g_mtxWorldField, &mtxScl);


	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y + 89.8f, rot.x, rot.z);
	D3DXMatrixMultiply(&g_AnimationXfile[number].g_mtxWorldField, &g_AnimationXfile[number].g_mtxWorldField, &mtxRot);

	//移動を反映
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&g_AnimationXfile[number].g_mtxWorldField, &g_AnimationXfile[number].g_mtxWorldField, &mtxTranslate);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	g_AnimationXfile[number].controller->AdvanceTime(0.016f, 0);

	updateCombMatrix(combMatrixMap, g_AnimationXfile[number].pRootFrame);

	//行列を合成?(移動に必要)
	for (DWORD i = 0; i < 35; i++)
	{
		D3DXMatrixMultiply(&combMatrixMap[i], &combMatrixMap[i], &g_AnimationXfile[number].g_mtxWorldField);
	}

	//マテリアルの数だけforループ
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
	}

	//マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//xファイルの個別読み込み
void SetXfile(int index)
{
	D3DXLoadMeshFromX(g_Xfile[index].filename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,				//隣接ポリゴン(基本的にいらない)
		&g_Xfile[index].g_pBuffMatModel,
		NULL,
		&g_Xfile[index].g_nNumMatModel,
		&g_Xfile[index].g_pMeshModel);

	//テクスチャの個別読み込み
	if (index == HUMAN_JPN || index == HUMAN_VICJPN || index == HUMAN_LOSJPN || index == HUMAN_DRAWJPN)
	{
		g_Xfile[index].hr = D3DXCreateTextureFromFile(pDevice, "asset/model/human/UV_JPN.png", &g_Xfile[index].g_pTextureModel);
	}
	if (index == HUMAN_USA || index == HUMAN_VICUSA || index == HUMAN_LOSUSA || index == HUMAN_DRAWUSA)
	{
		g_Xfile[index].hr = D3DXCreateTextureFromFile(pDevice, "asset/model/human/UV_FRA.png", &g_Xfile[index].g_pTextureModel);
	}
	if (index == HUMAN_FRA || index == HUMAN_VICFRA || index == HUMAN_LOSFRA || index == HUMAN_DRAWFRA)
	{
		g_Xfile[index].hr = D3DXCreateTextureFromFile(pDevice, "asset/model/human/UV_USA.png", &g_Xfile[index].g_pTextureModel);
	}
	if (index == HUMAN_KOR || index == HUMAN_VICKOR || index == HUMAN_LOSKOR || index == HUMAN_DRAWKOR)
	{
		g_Xfile[index].hr = D3DXCreateTextureFromFile(pDevice, "asset/model/human/UV_KOR.png", &g_Xfile[index].g_pTextureModel);
	}


}

//アニメーション付きのXファイルの個別読み込み
void SetAnimationXfile(int index,int texnumber)
{
	g_AnimationXfile[index].pRootFrame = 0;
	g_AnimationXfile[index].controller = 0;

	D3DXLoadMeshHierarchyFromX(_T("asset/model/human/jpnani.x"), D3DXMESH_MANAGED, pDevice, &allocater, 0, (D3DXFRAME**)&g_AnimationXfile[index].pRootFrame, &g_AnimationXfile[index].controller);

	cont = getMeshContainer(g_AnimationXfile[index].pRootFrame);
	g_AnimationXfile[index].combs = (D3DXBONECOMBINATION*)cont->boneCombinationTable->GetBufferPointer();

	// フレーム内にボーンIDとオフセット行列を埋め込む
	setFrameId(g_AnimationXfile[index].pRootFrame, cont->pSkinInfo);
	// テクスチャ作成
	g_AnimationXfile[index].tex = 0;
	//テクスチャの個別読み込み
	if (texnumber == HUMAN_JPN || texnumber == HUMAN_VICJPN || texnumber == HUMAN_LOSJPN || texnumber == HUMAN_DRAWJPN)
	{
		D3DXCreateTextureFromFile(pDevice, "asset/model/human/UV_JPN.png", &g_AnimationXfile[index].tex);
	}
	if (texnumber == HUMAN_USA || texnumber == HUMAN_VICUSA || texnumber == HUMAN_LOSUSA || texnumber == HUMAN_DRAWUSA)
	{
		D3DXCreateTextureFromFile(pDevice, "asset/model/human/UV_FRA.png", &g_AnimationXfile[index].tex);
	}
	if (texnumber == HUMAN_FRA || texnumber == HUMAN_VICFRA || texnumber == HUMAN_LOSFRA || texnumber == HUMAN_DRAWFRA)
	{
		D3DXCreateTextureFromFile(pDevice, "asset/model/human/UV_USA.png", &g_AnimationXfile[index].tex);
	}
	if (texnumber == HUMAN_KOR || texnumber == HUMAN_VICKOR || texnumber == HUMAN_LOSKOR || texnumber == HUMAN_DRAWKOR)
	{
		D3DXCreateTextureFromFile(pDevice, "asset/model/human/UV_KOR.png", &g_AnimationXfile[index].tex);
	}

	unsigned int imax = g_AnimationXfile[index].controller->GetNumAnimationSets();

	for (int i = 0; i < imax; i++)
	{
		g_AnimationXfile[index].controller->GetAnimationSet(i, &g_AnimationXfile[index].pAnimSet[i]);
	}

}

//xファイルの個別解放
void ReleaseXfile(int index)
{
	if (g_Xfile[index].g_pTextureModel != NULL)
	{// テクスチャの開放
		g_Xfile[index].g_pTextureModel->Release();
		g_Xfile[index].g_pTextureModel = NULL;
	}

	if (g_Xfile[index].g_pMeshModel != NULL)
	{// メッシュの開放
		g_Xfile[index].g_pMeshModel->Release();
		g_Xfile[index].g_pMeshModel = NULL;
	}

	if (g_Xfile[index].g_pBuffMatModel != NULL)
	{// マテリアルの開放
		g_Xfile[index].g_pBuffMatModel->Release();
		g_Xfile[index].g_pBuffMatModel = NULL;
	}
}

//アニメーション切り替え
void ChengeAnimation(int index,int animID)
{
	g_AnimationXfile[index].controller->SetTrackAnimationSet(0, g_AnimationXfile[index].pAnimSet[animID]);		//アニメーションを切り替える
	g_AnimationXfile[index].controller->SetTrackPosition(animID,0);				//アニメーションのトラック位置のリセット
	g_AnimationXfile[index].controller->SetTrackSpeed(0, 0.3f);					//アニメーションの速度設定
}

//現在のアニメーションを停止する
void StopAnimation(int index)
{
	g_AnimationXfile[index].controller->SetTrackSpeed(0, 0.0f);
}