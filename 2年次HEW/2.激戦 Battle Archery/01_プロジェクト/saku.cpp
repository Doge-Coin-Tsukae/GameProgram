//****************************************************
// 柵関係のプログラム
//****************************************************

#include "saku.h"
#include "myDirect3D.h"
#include "xfile.h"


// *****************************************************************************
// マクロ定義
// *****************************************************************************
#define NUM_SAKU 10								//表示する柵の総数

// *****************************************************************************
// グローバル変数
// *****************************************************************************
LPDIRECT3DVERTEXBUFFER9 static g_pVtxBuffField = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9	static g_pIdxBuffField = NULL;

// *****************************************************************************
// クラス
// *****************************************************************************
// 柵のクラス
class SAKUS {
private:
	bool live;				//柵が存在するかどうか
	D3DXVECTOR3				PosSak;					// 柵の位置
	D3DXVECTOR3				RotSak;					// 柵の向き(回転)
	D3DXVECTOR3				SclSak;					// 柵の大きさ(スケール)

public:
	D3DXMATRIX				g_mtxWorldField;		// ワールドマトリックス(行列)]

	//コンストラクタ
	SAKUS() {
		live = false;								//柵の存在抹殺
		PosSak = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期座標
		RotSak = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期回転
		SclSak = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期大きさ
	}
	~SAKUS() {
		live = false;								//柵の存在抹殺
		PosSak = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期座標
		RotSak = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期回転
		SclSak = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期大きさ
	}

	// 柵が存在しているかどうか調べる
	bool checklive()
	{
		return live;
	}

	// 柵の配置(設置座標,スケール(大きさ)の指定)
	void SetObject(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Scl)
	{
		if (live == false)
		{
			PosSak = Pos;
			RotSak = Rot;
			SclSak = Scl;
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
		return PosSak;
	}

	//角度を取得
	D3DXVECTOR3 GetRot()
	{
		return RotSak;
	}

	//スケールを取得
	D3DXVECTOR3 GetScl()
	{
		return SclSak;
	}
};

static SAKUS *g_Saku[NUM_SAKU];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Saku_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetD3DDevice();

	//クラスのセット
	for (int i = 0; i < NUM_SAKU; i++)
	{
		g_Saku[i] = new SAKUS;
	}

	// 柵の設置
	g_Saku[0]->SetObject(D3DXVECTOR3(1650.0f, -12.5f, 3250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[1]->SetObject(D3DXVECTOR3(825.0f, -12.5f, 3250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[2]->SetObject(D3DXVECTOR3(0.0f, -12.5f, 3250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[3]->SetObject(D3DXVECTOR3(-825.0f, -12.5f, 3250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[4]->SetObject(D3DXVECTOR3(-1650.0f, -12.5f, 3250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));

	g_Saku[5]->SetObject(D3DXVECTOR3(1650.0f, -12.5f, -3250.0f), D3DXVECTOR3(0.0f, 600.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[6]->SetObject(D3DXVECTOR3(825.0f, -12.5f, -3250.0f), D3DXVECTOR3(0.0f, 600.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[7]->SetObject(D3DXVECTOR3(0.0f, -12.5f, -3250.0f), D3DXVECTOR3(0.0f, 600.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[8]->SetObject(D3DXVECTOR3(-825.0f, -12.5f, -3250.0f), D3DXVECTOR3(0.0f, 600.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[9]->SetObject(D3DXVECTOR3(-1650.0f, -12.5f, -3250.0f), D3DXVECTOR3(0.0f, 600.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Saku_Finalize(void)
{
	if (g_pVtxBuffField != NULL)
	{// 頂点バッファの開放
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}

	//クラスの解放
	for (int i = 0; i < NUM_SAKU; i++)
	{
		delete g_Saku[i];
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Saku_Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void Saku_Draw(void)
{
	//ワールドマトリクスの設定
	for (int i = 0; i < NUM_SAKU; i++)
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
bool CheckHitPlayer_vs_Saku(D3DXVECTOR3 Ppos)
{
	for (int i = 0; i < NUM_SAKU; i++)
	{
		// プレイヤー座標が壁の大きさよりも小さい→当たっている
		if (Ppos.x >= g_Saku[i]->GetPos().x - (40.0f * g_Saku[i]->GetScl().x) && Ppos.x <= g_Saku[i]->GetPos().x + (40.0f * g_Saku[i]->GetScl().x) &&			//X座標
			Ppos.y >= g_Saku[i]->GetPos().y - (150.0f * g_Saku[i]->GetScl().y) && Ppos.y <= g_Saku[i]->GetPos().y + (150.0f * g_Saku[i]->GetScl().y) * 2 &&		//Y座標								//Y座標
			Ppos.z >= g_Saku[i]->GetPos().z - (10.0f * g_Saku[i]->GetScl().z) && Ppos.z <= g_Saku[i]->GetPos().z + (10.0f * g_Saku[i]->GetScl().z) &&			//Z座標
			g_Saku[i]->checklive() == true)
		{
			return true;
		}

	}
	return false;
}