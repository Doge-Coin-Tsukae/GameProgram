#include "field.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
#include <stdlib.h>
//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define	VALUE_MOVE		(10.0f)							// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)				// 回転量

#define	FIELD_WIDTH		(100.0f)						// 地面の幅(X方向)
#define	FIELD_DEPTH		(100.0f)						// 地面の奥行(Z方向)
#define FIELD_HIGHT		(100.0f)						// 地面の高さ

#define BLOCK_X			(402)			//Block + 1 した数に2倍させた数が横に必要
#define BLOCK_Y			(101)			//Block + 1 した数が縦に必要

#define NUM_BOX 1
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffField = NULL;
int						g_NumIndexField = 90000;

typedef struct {
	D3DXMATRIX				g_mtxWorldField;		// ワールドマトリックス(行列)
	D3DXVECTOR3				g_posField;				// 地面の位置
	D3DXVECTOR3				g_rotField;				// 地面の向き(回転)
	D3DXVECTOR3				g_rot2Field;			// 地面の向き(回転)
	D3DXVECTOR3				g_sclField;				// 地面の大きさ(スケール)
}BOX_T;

static BOX_T g_Box[NUM_BOX];

float g_rot1_x = 0.05f;
float g_rot2_x = 0.01f;

int g_NumVertex = (BLOCK_X + 1) * (BLOCK_Y + 1);						//頂点数
int g_NumIndex = ((BLOCK_X + 1) * 2) * BLOCK_Y + ((BLOCK_Y*-1) * 2);	//インデックス数
int g_NumPolygon = (BLOCK_X * 2)*BLOCK_Y + (BLOCK_Y - 1) * 4;			//ポリゴン数

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Field_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice[2];
	pDevice[0] = GetD3DDevice();
	pDevice[1] = GetD3DDevice();

	// 頂点情報の作成
	MakeVertexField(pDevice[0]);
	MakeVertexField(pDevice[1]);

	g_rot1_x = 0.05f;
	g_rot2_x = 0.01f;

	g_NumVertex = (BLOCK_X + 1) * (BLOCK_Y + 1);						//頂点数
	g_NumIndex = ((BLOCK_X + 1) * 2) * BLOCK_Y + ((BLOCK_Y*-1) * 2);	//インデックス数
	g_NumPolygon = (BLOCK_X * 2)*BLOCK_Y + (BLOCK_Y - 1) * 4;			//ポリゴン数
	g_NumIndexField = 90000;

	// 位置・回転・スケールの初期設定
	for (int i = 0; i < NUM_BOX; i++)
	{
		g_Box[i].g_posField = D3DXVECTOR3(0.0f, 0.0f, 00.0f);
		g_Box[i].g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Box[i].g_rot2Field = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Box[i].g_sclField = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Field_Finalize(void)
{

	if (g_pIdxBuffField != NULL)
	{//インデックスバッファの解放
		g_pIdxBuffField->Release();
		g_pIdxBuffField = NULL;
	}

	if (g_pVtxBuffField != NULL)
	{// 頂点バッファの開放
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Field_Update(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	//ワールド変換

	//ワールドマトリクスの初期化
	for (int i = 0; i < NUM_BOX; i++)
	{
		D3DXMatrixIdentity(&g_Box[i].g_mtxWorldField);
	}

	g_Box[0].g_rotField.y += 0.01f;


	//回転を反映
	/*この関数は原則1本の軸の動かせる*/
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Box[0].g_rotField.y, g_Box[0].g_rotField.x, g_Box[0].g_rotField.z);		//ヨー、ピッチ、ロール	ヨーとロールが同じ動きになること=ジンバルロック
	D3DXMatrixMultiply(&g_Box[0].g_mtxWorldField, &g_Box[0].g_mtxWorldField, &mtxRot);				//回転*ワールド

	g_Box[0].g_posField.x = -3000.0f;
	g_Box[0].g_posField.y = 100.0f;
	g_Box[0].g_posField.z = 100.0f;

	//移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_Box[0].g_posField.x, g_Box[0].g_posField.y, g_Box[0].g_posField.z);
	D3DXMatrixMultiply(&g_Box[0].g_mtxWorldField, &g_Box[0].g_mtxWorldField, &mtxTranslate);			//移動*ワールド


	g_Box[1].g_rotField.y -= 0.03f;

	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Box[1].g_rotField.y, g_Box[1].g_rotField.x, g_Box[1].g_rotField.z);		//ヨー、ピッチ、ロール	ヨーとロールが同じ動きになること=ジンバルロック
	D3DXMatrixMultiply(&g_Box[1].g_mtxWorldField, &g_Box[1].g_mtxWorldField, &mtxRot);				//回転*ワールド

	g_Box[1].g_posField.x = -3000.0f;
	g_Box[1].g_posField.z = 100.0f;

	//移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_Box[1].g_posField.x, g_Box[1].g_posField.y, g_Box[1].g_posField.z);
	D3DXMatrixMultiply(&g_Box[1].g_mtxWorldField, &g_Box[1].g_mtxWorldField, &mtxTranslate);			//移動*ワールド

	g_Box[1].g_rot2Field.y += 0.03f;
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Box[1].g_rot2Field.y, g_Box[1].g_rot2Field.x, g_Box[1].g_rot2Field.z);		//ヨー、ピッチ、ロール	ヨーとロールが同じ動きになること=ジンバルロック
	D3DXMatrixMultiply(&g_Box[1].g_mtxWorldField, &g_Box[1].g_mtxWorldField, &mtxRot);				//回転*ワールド

	//子供 * 親
	D3DXMatrixMultiply(&g_Box[1].g_mtxWorldField, &g_Box[1].g_mtxWorldField, &g_Box[0].g_mtxWorldField);			//移動*ワールド

	/*
	//スケールを反映
	D3DXMatrixScaling(&mtxScl, g_sclField.x, g_sclField.y, g_sclField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxScl);				//拡大・縮小*ワールド
	*/


	//g_rotField.y += g_rot1_x;

}

//=============================================================================
// 描画処理
//=============================================================================
void Field_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//ワールドマトリクスの設定
	for (int i = 0; i < NUM_BOX; i++)
	{
		D3DXMATRIX mtxWorld;
		D3DXMatrixIdentity(&mtxWorld);

		//ワールドマトリクスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

		//インデックスバッファのセット
		pDevice->SetIndices(g_pIdxBuffField);

		pDevice->SetFVF(FVF_VERTEX_3D);

		pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_FIELD01));

		//ポリゴンの描写(インデックスバッファ版)
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_NumIndex, 0, g_NumPolygon);
	}

	/*ここから手動でライティング*/
	/*
	//光が差す方向(ディレクショナルライト)
	D3DXVECTOR3 light;
	light.x = 0.0f;
	light.y = -1.0f;
	light.z = 0.0f;

	{//頂点バッファを埋める
		VERTEX_3D *pVtx;

		//頂点データの範囲をロックし、頂点バッファへのポインタ
		g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		D3DXVECTOR3 calc_nor;

		//ベクトルに行列をかけて変形してくれる関数
		D3DXVec3TransformNormal(&calc_nor,&pVtx[0].nor,&g_mtxWorldField);

		float color =D3DXVec3Dot(&light, &calc_nor);

		//値が0より大きかったら0に補正する
		if (color > 0)
		{
			color = 0;
		}

		//-1～0の値を1～0に書き換える
		color = fabs(color);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(color , color, color, color);
		pVtx[1].col = D3DXCOLOR(color, color, color, color);
		pVtx[2].col = D3DXCOLOR(color, color, color, color);
		pVtx[3].col = D3DXCOLOR(color, color, color, color);
		pVtx[4].col = D3DXCOLOR(color, color, color, color);
		pVtx[5].col = D3DXCOLOR(color, color, color, color);

		g_pVtxBuffField->Unlock();
	}
	*/
	/*手動でライティングここまで*/

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	//オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_NumVertex * 100, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffField, NULL)))
	{
		return E_FAIL;
	}

	{
		//頂点バッファを埋める
		VERTEX_3D *pVtx;

		//頂点データの範囲をロックし、頂点バッファへのポインタ
		g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		for (int z = 0; z < BLOCK_Y; z++)
		{
			for (int x = 0; x < BLOCK_X; x++)
			{
				//int y = rand() % 1;
				pVtx[(z * BLOCK_X) + x].pos = D3DXVECTOR3(5000+(x * -100.0f), 0.0f, 5000+(z * (-100.0f)));
			}
		}

		//
		for (int i = 0; i < g_NumVertex * 100; i++)
		{
			pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}


		//テクスチャ座標の設定
		for (int i = 0; i < BLOCK_Y; i++)		//y座標
		{
			for (int j = 0; j < BLOCK_X; j++)		//x座標
			{
				pVtx[(i * BLOCK_X) + j].tex = D3DXVECTOR2(j, i);
			}
		}

		g_pVtxBuffField->Unlock();
	}

	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD)*g_NumVertex * 100,		//総頂点数
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffField,
		NULL)))
	{
		return E_FAIL;
	}

	{	//インデックスバッファの中身を埋める
		WORD *pIdx;

		g_pIdxBuffField->Lock(0, 0, (void**)&pIdx, 0);


		for (int i = 0; i < BLOCK_X; i++)	//x
		{
			pIdx[i * 2] = (BLOCK_X)+i;		//x + i
			pIdx[(i * 2) + 1] = i;
		}

		for (int j = 0; j < BLOCK_Y; j++)	//x
		{
			for (int i = 0; i < BLOCK_X; i++)	//x
			{
				pIdx[BLOCK_X + (j*BLOCK_X) + i * 2] = BLOCK_X * j + (BLOCK_X) * 2 + i;		//x + i
				pIdx[BLOCK_X + (j*BLOCK_X) + (i * 2) + 1] = (BLOCK_X * j) + BLOCK_X + i;
			}
		}

		//インデックスデータをアンロックする
		g_pIdxBuffField->Unlock();
	}
	return S_OK;
}

//DrawprinitiveUP・・・メモリ解放まで自動でやってくれる
//Drawprinitive・・・自分で作った頂点バッファを描画してくれる。動作が速い
//Lock・・・VRAMに書き込んでくれる(重いのでなるべく回数を減らす)まとめてロックする(描画する)といい
//Unlock・・・Lockを解除してくれる(重いのでなるべく回数を減らす)
//描画・・Lockする→描画変更→Unlockする
//縮退ポリゴン・・・indexのxの終わりを2回、yのはじめを2回繰り返す(12,5,13,,6,[6,14],14,7,15)