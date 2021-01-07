//****************************************************
// 壁(縦)関係のプログラム
//****************************************************

#include "wall_tate.h"
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
#define NUM_WALL_TATE_TUTORIAL 14								//表示する柱の総数

// *****************************************************************************
// グローバル変数
// *****************************************************************************
LPDIRECT3DVERTEXBUFFER9 static g_pVtxBuffField = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9	static g_pIdxBuffField = NULL;


// *****************************************************************************
// enum
// *****************************************************************************

// *****************************************************************************
// クラス
// *****************************************************************************
// 柱のクラス
class WALLS_TATE_TUTORIAL {
private:
	bool live;				//壁が存在するかどうか
	int  type;				//この値によって色が変わる


public:
	D3DXMATRIX				g_mtxWorldField;		// ワールドマトリックス(行列)

	D3DXVECTOR3				PosWalT;					// 柱の位置
	D3DXVECTOR3				RotWalT;					// 柱の向き(回転)
	D3DXVECTOR3				SclWalT;					// 柱の大きさ(スケール)

	//コンストラクタ
	WALLS_TATE_TUTORIAL() {
		live = false;								//柱の存在抹殺
		type = WALL;
		PosWalT = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期座標
		RotWalT = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期回転
		SclWalT = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期大きさ
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
			PosWalT = Pos;
			RotWalT = Rot;
			SclWalT = Scl;
			live = true;
		}
	}

	void Finalize()
	{
		live = 0;
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
		return PosWalT;
	}

	//角度を取得
	D3DXVECTOR3 GetRot()
	{
		return RotWalT;
	}

	//スケールを取得
	D3DXVECTOR3 GetScl()
	{
		return SclWalT;
	}
};

static WALLS_TATE_TUTORIAL g_WallTateTutorial[NUM_WALL_TATE_TUTORIAL];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT WallTate_Tutorial_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetD3DDevice();

	// 縦壁
	g_WallTateTutorial[0].SetObject(D3DXVECTOR3(-450, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 4.71f, 0.0f), D3DXVECTOR3(8.0f, 0.4f, 1.25f));
	g_WallTateTutorial[1].SetObject(D3DXVECTOR3(450, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), D3DXVECTOR3(8.0f, 0.4f, 1.25f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void WallTate_Tutorial_Finalize(void)
{
	if (g_pVtxBuffField != NULL)
	{// 頂点バッファの開放
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}


	for (int i = 0; i < NUM_WALL_TATE_TUTORIAL; i++)
	{
		g_WallTateTutorial[i].Finalize();
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void WallTate_Tutorial_Update(void)
{
}


//=============================================================================
// 描画処理
//=============================================================================
void WallTate_Tutorial_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//ワールドマトリクスの設定
	for (int i = 0; i < NUM_WALL_TATE_TUTORIAL; i++)
	{
		//壁が存在していたとき、描画する
		if (g_WallTateTutorial[i].checklive() == true)
		{
			Xfile_Draw(g_WallTateTutorial[i].GetScl(), g_WallTateTutorial[i].GetPos(), g_WallTateTutorial[i].GetRot(), WALL);
		}
	}
}


//=============================================================================
// ?プレイヤーと壁の当たり判定処理
//=============================================================================
bool CheckHitPlayer_vs_WallTateTutorial(D3DXVECTOR3 Ppos)
{
	for (int i = 0; i < NUM_WALL_TATE_TUTORIAL; i++)
	{
		// プレイヤー座標が壁の大きさよりも小さい→当たっている
		if (Ppos.x >= g_WallTateTutorial[i].PosWalT.x - (40.0f * (g_WallTateTutorial[i].SclWalT.z / 1.5f)) && Ppos.x <= g_WallTateTutorial[i].PosWalT.x + (40.0f * (g_WallTateTutorial[i].SclWalT.z / 1.5f)) &&			//X座標
			Ppos.y >= g_WallTateTutorial[i].PosWalT.y - (300.0f * g_WallTateTutorial[i].SclWalT.y) && Ppos.y <= g_WallTateTutorial[i].PosWalT.y + (50.0f * g_WallTateTutorial[i].SclWalT.y) * 2 &&						//Y座標
			Ppos.z >= g_WallTateTutorial[i].PosWalT.z - (300.0f * (g_WallTateTutorial[i].SclWalT.x / 1.2f)) && Ppos.z <= g_WallTateTutorial[i].PosWalT.z + (300.0f *(g_WallTateTutorial[i].SclWalT.x / 1.2f)) &&		//Z座標
			g_WallTateTutorial[i].checklive() == true)
		{
			return true;
		}

	}
	return false;
}