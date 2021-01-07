//****************************************************
// 横柵関係のプログラム
//****************************************************

#include "saku_yoko.h"
#include "myDirect3D.h"
#include "xfile.h"


// *****************************************************************************
// マクロ定義
// *****************************************************************************
#define NUM_SAKU_YOKO 14								//表示する柱の総数

// *****************************************************************************
// グローバル変数
// *****************************************************************************
LPDIRECT3DVERTEXBUFFER9 static g_pVtxBuffField = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9	static g_pIdxBuffField = NULL;

// *****************************************************************************
// クラス
// *****************************************************************************
// 柵のクラス
class SAKUS_YOKO {
private:
	bool live;				//柵が存在するかどうか
	int  type;				//この値によって色が変わる
	D3DXVECTOR3				PosSakY;					// 柵の位置
	D3DXVECTOR3				RotSakY;					// 柵の向き(回転)
	D3DXVECTOR3				SclSakY;					// 柵の大きさ(スケール)

public:
	D3DXMATRIX				g_mtxWorldField;		// ワールドマトリックス(行列)

	//コンストラクタ
	SAKUS_YOKO() {
		live = false;								//柵の存在抹殺
		type = SAKU;
		PosSakY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期座標
		RotSakY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期回転
		SclSakY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期大きさ
	}

	~SAKUS_YOKO() {
		live = false;								//柵の存在抹殺
		PosSakY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期座標
		RotSakY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期回転
		SclSakY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期大きさ
	}

	// 柵が存在しているかどうか調べる
	bool checklive()
	{
		return live;
	}

	// 柵を取得
	int checktype()
	{
		return type;
	}

	// 柵の配置(設置座標,スケール(大きさ)の指定)
	void SetObject(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Scl)
	{
		if (live == false)
		{
			PosSakY = Pos;
			RotSakY = Rot;
			SclSakY = Scl;
			live = true;
		}
	}

	//更新処理
	void Update()
	{
	}

	//座標を取得
	D3DXVECTOR3 GetPos()
	{
		return PosSakY;
	}

	//角度を取得
	D3DXVECTOR3 GetRot()
	{
		return RotSakY;
	}

	//スケールを取得
	D3DXVECTOR3 GetScl()
	{
		return SclSakY;
	}
};

static SAKUS_YOKO *g_Saku[NUM_SAKU_YOKO];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT SakuYoko_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetD3DDevice();

	//クラスのセット
	for (int i = 0; i < NUM_SAKU_YOKO; i++)
	{
		g_Saku[i] = new SAKUS_YOKO;
	}

	// 柵の設置
	//
	g_Saku[0]->SetObject(D3DXVECTOR3(2150.0f, -12.5f, -2750.0f), D3DXVECTOR3(0.0f, 900.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[1]->SetObject(D3DXVECTOR3(2150.0f, -12.5f, -1875.0f), D3DXVECTOR3(0.0f, 900.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[2]->SetObject(D3DXVECTOR3(2150.0f, -12.5f, -1000.0f), D3DXVECTOR3(0.0f, 900.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[3]->SetObject(D3DXVECTOR3(2150.0f, -12.5f, -0.0f),	 D3DXVECTOR3(0.0f, 900.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[4]->SetObject(D3DXVECTOR3(2150.0f, -12.5f, 1000.0f),  D3DXVECTOR3(0.0f, 900.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[5]->SetObject(D3DXVECTOR3(2150.0f, -12.5f, 1875.0f),  D3DXVECTOR3(0.0f, 900.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[6]->SetObject(D3DXVECTOR3(2150.0f, -12.5f, 2750.0f),  D3DXVECTOR3(0.0f, 900.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));

	g_Saku[7]->SetObject(D3DXVECTOR3(-2150.0f, -12.5f, -2750.0f), D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[8]->SetObject(D3DXVECTOR3(-2150.0f, -12.5f, -1875.0f), D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[9]->SetObject(D3DXVECTOR3(-2150.0f, -12.5f, -1000.0f), D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[10]->SetObject(D3DXVECTOR3(-2150.0f, -12.5f, -0.0f),	  D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[11]->SetObject(D3DXVECTOR3(-2150.0f, -12.5f, 1000.0f), D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[12]->SetObject(D3DXVECTOR3(-2150.0f, -12.5f, 1875.0f), D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[13]->SetObject(D3DXVECTOR3(-2150.0f, -12.5f, 2750.0f), D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void SakuYoko_Finalize(void)
{
	if (g_pVtxBuffField != NULL)
	{// 頂点バッファの開放
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}

	//クラスの解放
	for (int i = 0; i < NUM_SAKU_YOKO; i++)
	{
		delete g_Saku[i];
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void SakuYoko_Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void SakuYoko_Draw(void)
{
	//ワールドマトリクスの設定
	for (int i = 0; i < NUM_SAKU_YOKO; i++)
	{
		//壁が存在していたとき、描画する
		if (g_Saku[i]->checklive() == true)
		{
			Xfile_Draw(g_Saku[i]->GetScl(), g_Saku[i]->GetPos(), g_Saku[i]->GetRot(), SAKU);
		}
	}
}

//=============================================================================
// プレイヤーと柵の当たり判定処理
//=============================================================================
bool CheckHitPlayer_vs_SakuYoko(D3DXVECTOR3 Ppos)
{
	for (int i = 0; i < NUM_SAKU_YOKO; i++)
	{
		// プレイヤー座標が壁の大きさよりも小さい→当たっている
		if (Ppos.x >= g_Saku[i]->GetPos().x - (5.0f * g_Saku[i]->GetScl().x) && Ppos.x <= g_Saku[i]->GetPos().x + (5.0f * g_Saku[i]->GetScl().x) &&				//X座標
			Ppos.y >= g_Saku[i]->GetPos().y - (150.0f * g_Saku[i]->GetScl().y) && Ppos.y <= g_Saku[i]->GetPos().y + (150.0f * g_Saku[i]->GetScl().y) * 2 &&		//Y座標								//Y座標
			Ppos.z >= g_Saku[i]->GetPos().z - (400.0f * g_Saku[i]->GetScl().z) && Ppos.z <= g_Saku[i]->GetPos().z + (400.0f * g_Saku[i]->GetScl().z) &&			//Z座標
			g_Saku[i]->checklive() == true)
		{
			return true;
		}

	}
	return false;
}