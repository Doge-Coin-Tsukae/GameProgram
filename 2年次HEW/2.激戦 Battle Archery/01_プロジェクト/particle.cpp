//=============================================================================
//
// パーティクル処理 [particle.cpp]
// Author : 
//
//=============================================================================
#include "debugproc.h"
#include "myDirect3D.h"
#include "input.h"
#include "camera.h"
#include "particle.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_PARTICLE	"asset/texture/billboard/effect000.jpg"	// 読み込むテクスチャファイル名
#define	PARTICLE_SIZE_X		(10.0f)							// ビルボードの幅
#define	PARTICLE_SIZE_Y		(10.0f)							// ビルボードの高さ
#define	VALUE_MOVE_PARTICLE	(2.5f)							// 移動速度

#define	MAX_PARTICLE			(80)						// ビルボード最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice);
void SetVertexParticle(int nIdxParticle, float fSizeX, float fSizeY);
void SetColorParticle(int nIdxParticle, D3DXCOLOR col);

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class PARTICLE
{
private:
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	D3DXVECTOR3 scale;		// スケール
	D3DXVECTOR3 move;		// 移動量
	D3DXCOLOR col;			// 色
	float fSizeX;			// 幅
	float fSizeY;			// 高さ
	int nLife;				// 寿命
	bool bUse;				// 使用しているかどうか
	
public:

	D3DXVECTOR3				g_posBase;				// ビルボード発生位置
	float					g_fWidthBase;			// 基準の幅
	float					g_fHeightBase;			// 基準の高さ
	float					g_roty;					// 移動方向
	float					g_spd;					// 移動スピード
	bool					g_player_touch;			// プレイヤーにくっつく

	//コンストラクタ
	PARTICLE()
	{
		pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		fSizeX = PARTICLE_SIZE_X;
		fSizeY = PARTICLE_SIZE_Y;
		g_posBase = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_roty = 0.0f;
		g_spd = 0.0f;
		g_fWidthBase = 10.0f;			// 基準の幅
		g_fHeightBase = 10.0f;			// 基準の高さ
		g_roty = 0.0f;					// 移動方向
		g_spd = 0.0f;
		nLife = 0;
		bUse = false;
		g_player_touch = true;
	}

	//デストラクタ
	~PARTICLE()
	{
	}

	//パーティクルの更新処理
	void ParticleUpdate(int index)
	{
		if (bUse == true)
		{// 使用中
			//パーティクルを移動させる
			pos.x += move.x;
			pos.z += move.z;
			pos.y += move.y;

			if (pos.y <= fSizeY / 2)
			{// 着地した
				pos.y = fSizeY / 2;				//y座標を地面に
				move.y = -move.y * 0.75f;		//反転させる(バウンドするようにする)
			}

			move.x += (0.0f - move.x) * 0.015f;
			move.y -= 0.25f;
			move.z += (0.0f - move.z) * 0.015f;

			nLife--;		//パーティクルの寿命を減らす

			//寿命が尽きたとき
			if (nLife <= 0)
			{
				bUse = false;		//弾を消す
				col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
			}
			//まだ生き延びているとき
			else
			{
				//寿命が10切ったとき
				if (nLife <= 10)
				{//弾を徐々に消えるようにする
					// α値設定
					col.a -= 0.05f;		//α値を徐々に減らす
					//α値が0未満になったとき
					if (col.a < 0.0f)
					{
						col.a = 0.0f;	//α値を0に固定
					}
				}

				// 色の設定
				SetColorParticle(index, col);
			}
		}
	}

	//パーティクルのセット
	bool SetParticle(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXCOLOR Col, float FSizeX, float FSizeY, int NLife,int index)
	{
		int nIdxParticle = -1;

			//そのパーティクルが現在使われていないとき設置処理
			if (!GetUse())
			{
				pos = Pos;
				rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
				move = Move;
				col = Col;
				fSizeX = FSizeX;
				fSizeY = FSizeY;
				nLife = NLife;
				bUse = true;

				// 頂点座標の設定
				SetVertexParticle(index, fSizeX, fSizeY);

				nIdxParticle = index;
				return true;
			}
			return false;
	}


	//bUseの値を取得する
	bool  GetUse()
	{
		return bUse;
	}

	//Posの値を取得する
	D3DXVECTOR3 GetPos()
	{
		return pos;
	}

	//Scaleの値を取得する
	D3DXVECTOR3 GetScale()
	{
		return scale;
	}

	//moveの値を取得する
	D3DXVECTOR3 GetMove()
	{
		return move;
	}
};


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureParticle = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffParticle = NULL;	// 頂点バッファインターフェースへのポインタ

D3DXMATRIX				g_mtxWorldParticle;				// ワールドマトリックス

PARTICLE				*g_aParticle[MAX_PARTICLE];		// パーティクルワーク


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// 頂点情報の作成
	MakeVertexParticle(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_PARTICLE,			// ファイルの名前
								&g_pD3DTextureParticle);	// 読み込むメモリー

	//クラスをセットする
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		g_aParticle[i] = new PARTICLE;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitParticle(void)
{
	if(g_pD3DTextureParticle != NULL)
	{// テクスチャの開放
		g_pD3DTextureParticle->Release();
		g_pD3DTextureParticle = NULL;
	}

	if(g_pD3DVtxBuffParticle != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffParticle->Release();
		g_pD3DVtxBuffParticle = NULL;
	}

	//クラスの解放
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		delete g_aParticle[i];
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateParticle(void)
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		g_aParticle[i]->g_posBase.x = 0;
		g_aParticle[i]->g_posBase.z = 0;

		g_aParticle[i]->ParticleUpdate(i);
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawParticle(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX mtxView,mtxScale,mtxTranslate;
	CAMERA *cam;

	cam = GetCamera(i);

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// 結果 = 転送元(SRC) + 転送先(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// αデスティネーションカラーの指定
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);				// Zバッファーの書き込みをしない

		for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
		{
			if (g_aParticle[nCntParticle]->GetUse() == true)
			{
				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_mtxWorldParticle);

				// ビューマトリックスを取得
				mtxView = cam->mtxView;

				g_mtxWorldParticle._11 = mtxView._11;
				g_mtxWorldParticle._12 = mtxView._21;
				g_mtxWorldParticle._13 = mtxView._31;
				g_mtxWorldParticle._21 = mtxView._12;
				g_mtxWorldParticle._22 = mtxView._22;
				g_mtxWorldParticle._23 = mtxView._32;
				g_mtxWorldParticle._31 = mtxView._13;
				g_mtxWorldParticle._32 = mtxView._23;
				g_mtxWorldParticle._33 = mtxView._33;

				// スケールを反映
				D3DXMatrixScaling(&mtxScale, g_aParticle[nCntParticle]->GetScale().x, g_aParticle[nCntParticle]->GetScale().y, g_aParticle[nCntParticle]->GetScale().z);
				D3DXMatrixMultiply(&g_mtxWorldParticle, &g_mtxWorldParticle, &mtxScale);

				// 移動を反映
				D3DXMatrixTranslation(&mtxTranslate, g_aParticle[nCntParticle]->GetPos().x, g_aParticle[nCntParticle]->GetPos().y, g_aParticle[nCntParticle]->GetPos().z);
				D3DXMatrixMultiply(&g_mtxWorldParticle, &g_mtxWorldParticle, &mtxTranslate);

				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldParticle);

				// 頂点バッファをデバイスのデータストリームにバインド
				pDevice->SetStreamSource(0, g_pD3DVtxBuffParticle, 0, sizeof(VERTEX_3D));

				// 頂点フォーマットの設定
				pDevice->SetFVF(FVF_VERTEX_3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTextureParticle);

				// ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntParticle * 4), NUM_POLYGON);
			}
		}

	// ライティングを有効に
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// 通常ブレンドに戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// 結果 = 転送元(SRC) + 転送先(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);				// Zバッファーの書き込みをする
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_PARTICLE,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffParticle,					// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-PARTICLE_SIZE_X / 2, -PARTICLE_SIZE_Y / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(PARTICLE_SIZE_X / 2, -PARTICLE_SIZE_Y / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-PARTICLE_SIZE_X / 2, PARTICLE_SIZE_Y / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(PARTICLE_SIZE_X / 2, PARTICLE_SIZE_Y / 2, 0.0f);

			// 法線の設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// 反射光の設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffParticle->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexParticle(int nIdxParticle, float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxParticle * 4);

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffParticle->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorParticle(int nIdxParticle, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxParticle * 4);

		// 頂点座標の設定
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = col;

		// 頂点データをアンロックする
		g_pD3DVtxBuffParticle->Unlock();
	}
}

//パーティクルのセット
void ParticleSetNum(int Num, D3DXVECTOR3 Pos, D3DXCOLOR Col, float FSizeX, float FSizeY, int NLife, int index)
{
	//必要な個数分だけ
	for (int i = 0; i < Num; i++)
	{
		//使われているかチェック
		for (int j = 0; j < MAX_PARTICLE; j++)
		{
			if (g_aParticle[j]->GetUse() == false)
			{

				// パーティクル発生
				{
					D3DXVECTOR3 move;
					float fAngle, fLength;

					fAngle = (float)(rand() % 628 - 314);
					fLength = rand() % (int)(g_aParticle[i]->g_fWidthBase * 200) / 100.0f - g_aParticle[i]->g_fWidthBase;
					move.x = sinf(fAngle) * fLength;
					move.y = -cosf(fAngle) * fLength;
					move.z = sinf(fAngle) * fLength;

					g_aParticle[j]->SetParticle(Pos, move, Col, FSizeX, FSizeY, NLife, j);
						break;
				}
			}
		}
	}
}