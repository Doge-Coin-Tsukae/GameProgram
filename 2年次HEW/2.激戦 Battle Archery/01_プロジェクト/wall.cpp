//****************************************************
// 壁関係のプログラム
//****************************************************

#include "wall.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
#include "bullet.h"
#include "player.h"
#include "xfile.h"
#include "player.h"


// *****************************************************************************
// マクロ定義
// *****************************************************************************
#define NUM_WALL 14								//表示する柱の総数

// *****************************************************************************
// グローバル変数
// *****************************************************************************
LPDIRECT3DVERTEXBUFFER9 static g_pVtxBuffField = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9	static g_pIdxBuffField = NULL;

// *****************************************************************************
// クラス
// *****************************************************************************
// 柱のクラス
class WALLS {
private:
	bool live;				//壁が存在するかどうか
	int  type;				//この値によって色が変わる


public:
	D3DXMATRIX				g_mtxWorldField;		// ワールドマトリックス(行列)

	D3DXVECTOR3				PosWal;					// 柱の位置
	D3DXVECTOR3				RotWal;					// 柱の向き(回転)
	D3DXVECTOR3				SclWal;					// 柱の大きさ(スケール)

	//コンストラクタ
	WALLS() {
		live = false;								//柱の存在抹殺
		type = WALL;
		PosWal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期座標
		RotWal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期回転
		SclWal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期大きさ
	}

	// 柱が存在しているかどうか調べる
	bool checklive()
	{
		return live;
	}

	// 柱の色を取得
	int checktype()
	{
		return type;
	}

	// 柱の配置(設置座標,スケール(大きさ)の指定)
	void SetObject(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Scl)
	{
		if (live == false)
		{
			PosWal = Pos;
			RotWal = Rot;
			SclWal = Scl;
			live = true;
		}
	}

	//終了処理
	void Finalize()
	{
		live = false;
		type = WALL;
	}

	//更新処理
	void Update()
	{
		// 的が色を変えたとき、連動して色が変わる
	}

	//座標を取得
	D3DXVECTOR3 GetPos()
	{
		return PosWal;
	}

	//角度を取得
	D3DXVECTOR3 GetRot()
	{
		return RotWal;
	}

	//スケールを取得
	D3DXVECTOR3 GetScl()
	{
		return SclWal;
	}
};

static WALLS g_Wall[NUM_WALL];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Wall_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetD3DDevice();

	// 1Pプレイヤー側壁の設置
	g_Wall[0].SetObject(D3DXVECTOR3(875.0f, 125.0f, 2750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.2f, 1.25f));
	g_Wall[1].SetObject(D3DXVECTOR3(500.0f, 125.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[2].SetObject(D3DXVECTOR3(1000.0f, 125.0f, 1250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[3].SetObject(D3DXVECTOR3(875.0f, 125.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[4].SetObject(D3DXVECTOR3(-250.0f, 125.0f, 1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[5].SetObject(D3DXVECTOR3(-1000.0f, 125.0f, 2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[6].SetObject(D3DXVECTOR3(-1250.0f, 125.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));

	// 2Pプレイヤー側壁の設置
	g_Wall[7].SetObject(D3DXVECTOR3(1000.0f, 125.0f, -2000.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.2f, 1.25f));
	g_Wall[8].SetObject(D3DXVECTOR3(-250.0f, 125.0f, -1250.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[9].SetObject(D3DXVECTOR3(-1000.0f, 125.0f, -2000.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.2f, 1.25f));
	g_Wall[10].SetObject(D3DXVECTOR3(-1125.0f, 125.0f, -750.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.2f, 1.25f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Wall_Finalize(void)
{

	for (int i = 0; i < NUM_WALL; i++)
	{
		g_Wall[i].Finalize();
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
void Wall_Update(void)
{
}


//=============================================================================
// 描画処理
//=============================================================================
void Wall_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//ワールドマトリクスの設定
	for (int i = 0; i < NUM_WALL; i++)
	{
		//壁が存在していたとき、描画する
		if (g_Wall[i].checklive() == true)
		{
			Xfile_Draw(g_Wall[i].GetScl(), g_Wall[i].GetPos(), g_Wall[i].GetRot(), WALL);
		}
	}
}


//=============================================================================
// プレイヤーと壁の当たり判定処理
//=============================================================================
bool CheckHitPlayer_vs_Wall(D3DXVECTOR3 Ppos)
{
	for (int i = 0; i < NUM_WALL; i++)
	{
		// プレイヤー座標が壁の大きさよりも小さい→当たっている
		if (Ppos.x >= g_Wall[i].PosWal.x - (300.0f * (g_Wall[i].SclWal.x/1.2f)) && Ppos.x <= g_Wall[i].PosWal.x + (300.0f * (g_Wall[i].SclWal.x / 1.2f)) &&			//X座標
			Ppos.y >= g_Wall[i].PosWal.y - (300.0f * g_Wall[i].SclWal.y) && Ppos.y <= g_Wall[i].PosWal.y + (50.0f * g_Wall[i].SclWal.y) * 2 &&		//Y座標								//Y座標
			Ppos.z >= g_Wall[i].PosWal.z - (40.0f * (g_Wall[i].SclWal.z / 1.5f)) && Ppos.z <= g_Wall[i].PosWal.z + (40.0f * (g_Wall[i].SclWal.z / 1.5f)) &&			//Z座標
			g_Wall[i].checklive() == true)
		{
			return true;
		}

	}
	return false;
}