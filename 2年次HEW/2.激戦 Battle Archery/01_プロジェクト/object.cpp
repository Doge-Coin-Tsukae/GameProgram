//****************************************************
//壁関係のプログラム
//****************************************************

#include "object.h"
#include "player.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	FIELD_WIDTH		(100.0f)						// 地面の幅(X方向)
#define	FIELD_DEPTH		(100.0f)						// 地面の奥行(Z方向)
#define FIELD_HIGHT		(100.0f)						// 地面の高さ

#define NUM_BOX 4										//表示ブロックの総数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT static MakeVertexField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffField = NULL;
int						g_NumIndexField = 36;

//*****************************************************************************
//クラス
//*****************************************************************************
class WALL{
private:
	bool live;				//壁が存在するかどうか

public:
	D3DXMATRIX				g_mtxWorldField;		// ワールドマトリックス(行列)
	D3DXVECTOR3				PosObj;					// 地面の位置
	D3DXVECTOR3				RotObj;					// 地面の向き(回転)
	D3DXVECTOR3				SclObj;					// 地面の大きさ(スケール)

	//コンストラクタ
	WALL() {
		live = false;								//弾の存在抹殺
		PosObj = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期座標
		RotObj = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期回転
		SclObj = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期大きさ
	}

	//壁が存在しているかどうか調べる
	bool checklive()
	{
		return live;
	}

	//ブロックの配置(設置座標,スケール(大きさ)の指定)
	void SetObject(D3DXVECTOR3 Pos,D3DXVECTOR3 Scl,D3DXVECTOR3 Rot)
	{
		for (int i = 0; i < NUM_BOX;i++)
		{
			//その壁が存在していないとき
			if (live == false)
			{
				PosObj = Pos;
				SclObj = Scl;
				RotObj = Rot;
				live = true;
				break;
			}
		}
		
	}
};

static WALL *g_Box[NUM_BOX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Object_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice[2];
	pDevice[0] = GetD3DDevice();
	pDevice[1] = GetD3DDevice();

	// 頂点情報の作成
	MakeVertexField(pDevice[0]);
	MakeVertexField(pDevice[1]);

	//テクスチャの読み込み
	SetTexture(TEXTURE_INDEX_VENUE);

	//クラスのセット
	for (int i = 0; i < NUM_BOX; i++)
	{
		g_Box[i] = new WALL;
	}

	//ブロックの設置
	g_Box[0]->SetObject(D3DXVECTOR3(2500, 100, 0), D3DXVECTOR3(1.0f, 2.0f, 37.5f), D3DXVECTOR3(0.0f, 89.535f, 0.0f));
	g_Box[1]->SetObject(D3DXVECTOR3(-2500, 100, 0), D3DXVECTOR3(1.0f, 2.0f, 37.5f), D3DXVECTOR3(0.0f, -89.535f, 0.0f));
	g_Box[2]->SetObject(D3DXVECTOR3(0, 100, 3750), D3DXVECTOR3(25.0f, 2.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_Box[3]->SetObject(D3DXVECTOR3(0, 100, -3750), D3DXVECTOR3(25.0f, 2.0f, 1.0f), D3DXVECTOR3(-3.14f, 0.0f, 3.14f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Object_Finalize(void)
{

	//クラスの解放
	for (int i = 0; i < NUM_BOX; i++)
	{
		delete g_Box[i];
	}

	//画像の解放
	ReleaseTexture(TEXTURE_INDEX_VENUE);

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
void Object_Update(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	//ワールド変換

	//ワールドマトリクスの初期化
	for (int i = 0; i < NUM_BOX; i++)
	{
		//壁が存在していたとき、処理をする
		if (g_Box[i]->checklive() == true)
		{
			D3DXMatrixIdentity(&g_Box[i]->g_mtxWorldField);

			//回転を反映
			/*この関数は原則1本の軸の動かせる*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Box[i]->RotObj.y, g_Box[i]->RotObj.x, g_Box[i]->RotObj.z);		//ヨー、ピッチ、ロール	ヨーとロールが同じ動きになること=ジンバルロック
			D3DXMatrixMultiply(&g_Box[i]->g_mtxWorldField, &g_Box[i]->g_mtxWorldField, &mtxRot);				//回転*ワールド

			//移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_Box[i]->PosObj.x, g_Box[i]->PosObj.y, g_Box[i]->PosObj.z);
			D3DXMatrixMultiply(&g_Box[i]->g_mtxWorldField, &g_Box[i]->g_mtxWorldField, &mtxTranslate);			//移動*ワールド

			//スケールを反映
			D3DXMatrixScaling(&mtxScl, g_Box[i]->SclObj.x, g_Box[i]->SclObj.y, g_Box[i]->SclObj.z);
			D3DXMatrixMultiply(&g_Box[i]->g_mtxWorldField, &g_Box[i]->g_mtxWorldField, &mtxScl);				//拡大・縮小*ワールド
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Object_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//ワールドマトリクスの設定
	for (int i = 0; i < NUM_BOX; i++)
	{
		//壁が存在していたとき、描画する
		if (g_Box[i]->checklive() == true)
		{
			pDevice->SetTransform(D3DTS_WORLD, &g_Box[i]->g_mtxWorldField);

			pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

			//インデックスバッファのセット
			pDevice->SetIndices(g_pIdxBuffField);

			pDevice->SetFVF(FVF_VERTEX_3D);

			pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_VENUE));

			//ポリゴンの描写(インデックスバッファ版)
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, g_NumIndexField, 0, 12);
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	//オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffField, NULL)))
	{
		return E_FAIL;
	}

	{
		//頂点バッファを埋める
		VERTEX_3D *pVtx;

		//頂点データの範囲をロックし、頂点バッファへのポインタ
		g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_HIGHT, -FIELD_DEPTH);
		pVtx[1].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_HIGHT, -FIELD_DEPTH);
		pVtx[2].pos = D3DXVECTOR3(-FIELD_WIDTH, -FIELD_HIGHT, -FIELD_DEPTH);
		pVtx[3].pos = D3DXVECTOR3(FIELD_WIDTH, -FIELD_HIGHT, -FIELD_DEPTH);
		pVtx[4].pos = D3DXVECTOR3(FIELD_WIDTH, -FIELD_HIGHT, FIELD_DEPTH);
		pVtx[5].pos = D3DXVECTOR3(-FIELD_WIDTH, -FIELD_HIGHT, FIELD_DEPTH);
		pVtx[6].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_HIGHT, FIELD_DEPTH);
		pVtx[7].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_HIGHT, FIELD_DEPTH);

		//
		pVtx[0].nor = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
		pVtx[4].nor = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
		pVtx[5].nor = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
		pVtx[6].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[7].nor = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);


		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_pVtxBuffField->Unlock();
	}

	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD)*g_NumIndexField,
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

		//前
		pIdx[0] = 0;
		pIdx[1] = 1;
		pIdx[2] = 2;
		pIdx[3] = 1;
		pIdx[4] = 3;
		pIdx[5] = 2;

		//上
		pIdx[6] = 7;
		pIdx[7] = 6;
		pIdx[8] = 0;
		pIdx[9] = 6;
		pIdx[10] = 1;
		pIdx[11] = 0;

		//左
		pIdx[12] = 7;
		pIdx[13] = 0;
		pIdx[14] = 5;
		pIdx[15] = 0;
		pIdx[16] = 2;
		pIdx[17] = 5;

		//右
		pIdx[18] = 1;
		pIdx[19] = 6;
		pIdx[20] = 3;
		pIdx[21] = 6;
		pIdx[22] = 4;
		pIdx[23] = 3;

		//後ろ
		pIdx[24] = 6;
		pIdx[25] = 7;
		pIdx[26] = 4;
		pIdx[27] = 7;
		pIdx[28] = 5;
		pIdx[29] = 4;

		//裏
		pIdx[30] = 2;
		pIdx[31] = 3;
		pIdx[32] = 5;
		pIdx[33] = 3;
		pIdx[34] = 4;
		pIdx[35] = 5;

		g_pIdxBuffField->Unlock();
	}
	return S_OK;
}

//調べたい物の座標とブロックの座標との当たり判定
bool CheckHitPlayer(D3DXVECTOR3 Ppos)
{
	for (int i = 0; i < NUM_BOX; i++)
	{
		if (Ppos.x >= g_Box[i]->PosObj.x - (100.0f * g_Box[i]->SclObj.x) && Ppos.x <= g_Box[i]->PosObj.x + (100.0f * g_Box[i]->SclObj.x) &&			//X座標
			Ppos.y >= g_Box[i]->PosObj.y - (100.0f * g_Box[i]->SclObj.y) && Ppos.y <= g_Box[i]->PosObj.y + (100.0f * g_Box[i]->SclObj.y) * 2 &&		//Y座標								//Y座標
			Ppos.z >= g_Box[i]->PosObj.z - (100.0f * g_Box[i]->SclObj.z) && Ppos.z <= g_Box[i]->PosObj.z + (100.0f * g_Box[i]->SclObj.z) &&			//Z座標
			g_Box[i]->checklive() == true)			//そのブロックが使われている
		{
			return true;		//ブロックの判定内にいる
		}
	}

	return false;		//ブロックの判定外にいる
}