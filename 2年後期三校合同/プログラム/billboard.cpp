//=============================================================================
//
// ビルボード処理 [billboard.cpp]
//
//=============================================================================
#include "billboard.h"
#include "bullet.h"
#include "myDirect3D.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_BILLBOARD		"asset/texture/billboard/bullet000.png"	// 読み込むテクスチャファイル名
#define	BILLBOARD_SIZE_X		(30.0f)							// ビルボードの幅
#define	BILLBOARD_SIZE_Y		(30.0f)							// ビルボードの高さ
#define	VALUE_MOVE_BILLBOARD	(0.30f)							// 移動速度
#define	VALUE_JUMP				(10.0f)							// ジャンプ力
#define	VALUE_GRAVITY			(0.45f)							// 重力
#define	RATE_REGIST				(0.075f)						// 抵抗係数
#define	RATE_REFRECT			(-0.90f)						// 反射係数

#define MAX_BILLBORD			3

#define BILLBORD_NUM_VERTEX		4
#define BILLBORD_NUM_POLYGON	2

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);
void SetVertexBillboard(float fSizeX, float fSizeY);
void DisabledBill(int index);

//*****************************************************************************
// グローバル変数
//*****************************************************************************

LPDIRECT3DTEXTURE9		g_pTextureBillboard = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffBillboard = NULL;	// 頂点バッファへのポインタ

typedef struct
{
	D3DXMATRIX				g_mtxWorldBillboard;		// ワールドマトリックス
	D3DXVECTOR3				g_posBillboard;				// 位置
	D3DXVECTOR3				g_rotBillboard;				// 位置
	D3DXVECTOR3				g_sclBillboard;				// スケール
	D3DXVECTOR3				g_moveBillboard;			// 移動量
	bool					g_bEnableGravity = false;	// 重力を有効にするかどうか
	bool					Use;						//使用しているかどうか
	int						timer;						//1発撃つまでの時間
	int						counter;					//何発まで打つか
	int						type;						//どちらかが使ったか
}BILLBORD;

BILLBORD g_billbord[MAX_BILLBORD];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Billboard_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// 頂点情報の作成
	MakeVertexBillboard(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,				// デバイスへのポインタ
								TEXTURE_BILLBOARD,		// ファイルの名前
								&g_pTextureBillboard);	// 読み込むメモリー

	for (int i = 0; i < MAX_BILLBORD; i++)
	{
		g_billbord[i].g_posBillboard = D3DXVECTOR3(0.0f, 600.0f, 0.0f);
		g_billbord[i].g_rotBillboard = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_billbord[i].g_sclBillboard = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
		g_billbord[i].g_moveBillboard = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_billbord[i].g_bEnableGravity = false;
		g_billbord[i].Use = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Billboard_Finalize(void)
{
	if(g_pTextureBillboard != NULL)
	{// テクスチャの開放
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	if(g_pVtxBuffBillboard != NULL)
	{// 頂点バッファの開放
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Billboard_Update(void)
{
	CAMERA *pCamera;

	// カメラの取得
	pCamera = GetCamera();

	for (int i = 0; i < MAX_BILLBORD; i++)
	{
		if (g_billbord[i].Use == true)
		{
			g_billbord[i].timer++;		//タイマーを1増やす
			//タイマーが30になったら
			if (g_billbord[i].timer >= 30)
			{
				SetBullet(g_billbord[i].g_posBillboard, g_billbord[i].type);
				g_billbord[i].counter++;		//カウンターを1増やす
				g_billbord[i].timer = 0;		//タイマーリセット

				//三発撃ったら消す
				if (g_billbord[i].counter >= 3)
				{
					DisabledBill(i);
				}
			}
		}
	}
	
}

//=============================================================================
// 描画処理
//=============================================================================
void Billboard_Draw(void)
{
		LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
		D3DXMATRIX mtxView, mtxScale, mtxTranslate;

		//αテストを有効に
		//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		//pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		//ライティングを無効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		for (int i = 0; i < MAX_BILLBORD; i++)
		{
			if (g_billbord[i].Use == true)
			{
				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_billbord[i].g_mtxWorldBillboard);

				//ビューマトリクスの取得
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);

				//ポリゴンを正面に向ける
#if 1
	//逆行列をもとめる (前の計算をなかったことにする)
				D3DXMatrixInverse(&g_billbord[i].g_mtxWorldBillboard, NULL, &mtxView);//カメラの方向をみるようになる

				//平行移動の部分は無視する
				g_billbord[i].g_mtxWorldBillboard._41 = 0.0f;
				g_billbord[i].g_mtxWorldBillboard._42 = 0.0f;
				g_billbord[i].g_mtxWorldBillboard._43 = 0.0f;

#else
				g_billbord[i].g_mtxWorldBillboard._11 = mtxView._11;
				g_billbord[i].g_mtxWorldBillboard._12 = mtxView._21;
				g_billbord[i].g_mtxWorldBillboard._13 = mtxView._31;
				g_billbord[i].g_mtxWorldBillboard._21 = mtxView._12;
				g_billbord[i].g_mtxWorldBillboard._22 = mtxView._22;
				g_billbord[i].g_mtxWorldBillboard._23 = mtxView._32;
				g_billbord[i].g_mtxWorldBillboard._31 = mtxView._13;
				g_billbord[i].g_mtxWorldBillboard._32 = mtxView._23;
				g_billbord[i].g_mtxWorldBillboard._33 = mtxView._33;
#endif

				//スケールを反映
				D3DXMatrixScaling(&mtxScale, g_billbord[i].g_sclBillboard.x, g_billbord[i].g_sclBillboard.y, g_billbord[i].g_sclBillboard.z);
				D3DXMatrixMultiply(&g_billbord[i].g_mtxWorldBillboard, &g_billbord[i].g_mtxWorldBillboard, &mtxScale);

				//移動を反映
				D3DXMatrixTranslation(&mtxTranslate, g_billbord[i].g_posBillboard.x, g_billbord[i].g_posBillboard.y, g_billbord[i].g_posBillboard.z);
				D3DXMatrixMultiply(&g_billbord[i].g_mtxWorldBillboard, &g_billbord[i].g_mtxWorldBillboard, &mtxTranslate);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_billbord[i].g_mtxWorldBillboard);

				//頂点バッファをデバイスのデータストリームにバインド
				pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

				//頂点フォーマットの設定
				pDevice->SetFVF(FVF_VERTEX_3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBillboard);

				//ポリゴン描写
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, BILLBORD_NUM_POLYGON);
			}
		}

		//ライティングを有効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		//αテストを無効に
		//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * BILLBORD_NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_3D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&g_pVtxBuffBillboard,		// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);-

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 頂点データをアンロックする
		g_pVtxBuffBillboard->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBillboard(float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		g_pVtxBuffBillboard->Unlock();
	}
}

//セッター
void SetBill(D3DXVECTOR3 pos,int type)
{
	for (int i = 0; i < MAX_BILLBORD; i++)
	{
		if (g_billbord[i].Use == false)
		{
			g_billbord[i].g_posBillboard = pos;
			g_billbord[i].Use = true;
			g_billbord[i].type = type;
			break;
		}
	}
}

//ピルボードを消す
void DisabledBill(int index)
{
	g_billbord[index].counter = 0;
	g_billbord[index].g_moveBillboard = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_billbord[index].g_posBillboard = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_billbord[index].timer = 0;
	g_billbord[index].type = 0;
	g_billbord[index].Use = false;
	
}