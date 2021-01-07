#include "field.h"
#include "myDirect3D.h"
#include "texture.h"
#include "debugproc.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BLOCK_X 40
#define BLOCK_Y 60

#define BLOCK_SIZE_X 150.0f
#define BLOCK_SIZE_Y 150.0f


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffField = NULL;	// 頂点バッファへのポインタ
static LPDIRECT3DINDEXBUFFER9	g_pIdxBuffField = NULL; // 
static int						g_NumIndexField;		// 
static LPDIRECT3DTEXTURE9		g_pTextureField;		// テクスチャへのポインタ


static int g_NumBlockX;
static int g_NumBlockZ;
static float g_SizeBlockX;
static float g_SizeBlockZ;
static int g_NumVertex;
static int g_NumIndex;
static int g_NumPolygon;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Field_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// 頂点情報の作成
	MakeVertexField(pDevice);

	SetTexture(TEXTURE_INDEX_KUSSA);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Field_Finalize(void)
{
	if (g_pVtxBuffField != NULL)
	{// 頂点バッファの開放
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
	ReleaseTexture(TEXTURE_INDEX_KUSSA);
}

//=============================================================================
// 更新処理
//=============================================================================
void Field_Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void Field_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//頂点の法線をノーマライズする
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// ワールドマトリックスの初期化
	D3DXMATRIX mtxWorld;
	D3DXMatrixIdentity(&mtxWorld);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	// インデックスバッファの設定
	pDevice->SetIndices(g_pIdxBuffField);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_KUSSA));

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_NumVertex, 0, g_NumPolygon);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	g_NumVertex = (BLOCK_X + 1) * (BLOCK_Y + 1);
	g_NumIndex = (BLOCK_X + 1) * 2 * BLOCK_Y + (BLOCK_Y - 1) * 2;
	g_NumPolygon = BLOCK_X * 2 * BLOCK_Y + (BLOCK_Y - 1) * 4;

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_NumVertex,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pVtxBuffField,			// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		//		const float fTexSizeX = 1.0f / g_NumBlockX;
		//		const float fTexSizeZ = 1.0f / g_NumBlockZ;
		const float fTexSizeX = 1.0f;
		const float fTexSizeZ = 1.0f;

		const float offset_x = BLOCK_X * BLOCK_SIZE_X / 2;
		const float offset_y = BLOCK_Y * BLOCK_SIZE_Y / 2;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		for (int z = 0; z < (BLOCK_Y + 1); z++) {
			for (int x = 0; x < (BLOCK_X + 1); x++) {
				// 座標の設定
				pVtx[z * (BLOCK_X + 1) + x].pos = D3DXVECTOR3(x*BLOCK_SIZE_X - offset_x, 0.0f, z*-BLOCK_SIZE_Y + offset_y);
				// 法線の設定
				pVtx[z * (BLOCK_X + 1) + x].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				// 頂点カラーの設定
				pVtx[z * (BLOCK_X + 1) + x].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				// テクスチャ座標の設定
				pVtx[z * (BLOCK_X + 1) + x].tex.x = (float)x;
				pVtx[z * (BLOCK_X + 1) + x].tex.y = (float)z;
			}
		}

		// 頂点データをアンロックする
		g_pVtxBuffField->Unlock();
	}

	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * g_NumIndex,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
		D3DFMT_INDEX16,						// 使用するインデックスフォーマット
		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
		&g_pIdxBuffField,					// インデックスバッファインターフェースへのポインタ
		NULL)))								// NULLに設定
	{
		return E_FAIL;
	}

	{//インデックスバッファの中身を埋める
		WORD *pIdx;

		// インデックスデータの範囲をロックし、頂点バッファへのポインタを取得
		g_pIdxBuffField->Lock(0, 0, (void**)&pIdx, 0);

		int idx_cnt = 0;

		//インデックスバッファの設定
		for (int y = 0; y < BLOCK_Y; y++)
		{
			for (int x = 0; x < (BLOCK_X + 1); x++)
			{
				pIdx[idx_cnt] = (BLOCK_X + 1) * y + (BLOCK_X + 1) + x;
				idx_cnt++;
				pIdx[idx_cnt] = (BLOCK_X + 1) * y + x;
				idx_cnt++;
			}
			if (y < (BLOCK_Y - 1))
			{
				//縮退ポリゴンのインデックス
				pIdx[idx_cnt] = (BLOCK_X + 1)*y + BLOCK_X;
				idx_cnt++;
				pIdx[idx_cnt] = (BLOCK_X + 1)*(y + 2);
				idx_cnt++;
			}
		}

		// インデックスデータをアンロックする
		g_pIdxBuffField->Unlock();
	}

	return S_OK;
}