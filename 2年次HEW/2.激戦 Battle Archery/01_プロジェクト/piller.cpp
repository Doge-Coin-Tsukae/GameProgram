//****************************************************
// 柱関係のプログラム
//****************************************************

#include "piller.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
#include "bullet.h"
#include "xfile.h"
#include "target.h"


// *****************************************************************************
// マクロ定義
// *****************************************************************************
#define NUM_PILLER 8								//表示する柱の最大数

// *****************************************************************************
// クラス
// *****************************************************************************
// 柱のクラス
class PILLERS {
private:
	bool live;				//壁が存在するかどうか
	int  type;				//この値によって色が変わる


public:
	D3DXMATRIX				g_mtxWorldField;		// ワールドマトリックス(行列)
	
	D3DXVECTOR3				PosPil;					// 柱の位置
	D3DXVECTOR3				RotPil;					// 柱の向き(回転)
	D3DXVECTOR3				SclPil;					// 柱の大きさ(スケール)
													
													//コンストラクタ
	PILLERS() {
		live = false;								//柱の存在抹殺
		type = PILLER;
		PosPil = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期座標
		RotPil = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期回転
		SclPil = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期大きさ
	}

	void Finalize()
	{
		live = false;				//的を全部消す
		type = TARGETWHITE;			//まとの状態を白に戻す
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
			PosPil = Pos;
			RotPil = Rot;
			SclPil = Scl;
			live = true;
			type = PILLER;
		}
	}

	//座標を取得
	D3DXVECTOR3 GetPos()
	{
		return PosPil;
	}

	//角度を取得
	D3DXVECTOR3 GetRot()
	{
		return RotPil;
	}

	//スケールを取得
	D3DXVECTOR3 GetScl()
	{
		return SclPil;
	}

	//セッター
	void SetType(int Set)
	{
		type = Set;
	}
};

static PILLERS g_Piller[NUM_PILLER];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Piller_Initialize(void)
{
	// 柱の設置
	g_Piller[0].SetObject(D3DXVECTOR3(-2000, 175.0f, 3125.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_Piller[1].SetObject(D3DXVECTOR3(2000.0f, 175.0f, 3125.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_Piller[2].SetObject(D3DXVECTOR3(-2000.0f, 175.0f, -3125.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_Piller[3].SetObject(D3DXVECTOR3(2000.0f, 175.0f, -3125.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_Piller[4].SetObject(D3DXVECTOR3(-1050, 175.0f, 625.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_Piller[5].SetObject(D3DXVECTOR3(775.0f, 175.0f, 1125.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_Piller[6].SetObject(D3DXVECTOR3(-1125.0f, 175.0f, -1825.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_Piller[7].SetObject(D3DXVECTOR3(1250.0f, 175.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Piller_Finalize(void)
{
	for (int i = 0; i < NUM_PILLER; i++)
	{
		g_Piller[i].Finalize();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Piller_Update(void)
{
	for (int j = 0; j < NUM_PILLER; j++)
	{
		// 的の色が変わったとき、柱の色も変わる = ノーマル色
		if (GetColor(j) == TARGETWHITE)
		{
			g_Piller[j].SetType(PILLER);
		}
		// 的の色が変わったとき、柱の色も変わる = 赤色
		else if (GetColor(j) == TARGETRED)
		{
			g_Piller[j].SetType(PILLER_R);
		}
		// 的の色が変わったとき、柱の色も変わる = 青色
		else if (GetColor(j) == TARGETBLUE)
		{
			g_Piller[j].SetType(PILLER_B);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Piller_Draw(void)
{
	//ワールドマトリクスの設定
	for (int i = 0; i < NUM_PILLER; i++)
	{
		//柱が存在していたとき、描画する
		if (g_Piller[i].checklive() == true)
		{
			Xfile_Draw(g_Piller[i].GetScl(), g_Piller[i].GetPos(), g_Piller[i].GetRot(), g_Piller[i].checktype());
		}
	}
}


//=============================================================================
// プレイヤーと柱の当たり判定処理
//=============================================================================
bool CheckHitPlayer_vs_PILLER(D3DXVECTOR3 Ppos)
{

	for (int i = 0; i < NUM_PILLER; i++)
	{
		// プレイヤー座標が柱の大きさよりも小さい→当たっている　→元の位置に戻す
		if (Ppos.x >= g_Piller[i].PosPil.x - (30.0f * g_Piller[i].SclPil.x) && Ppos.x <= g_Piller[i].PosPil.x + (30.0f * g_Piller[i].SclPil.x) &&			//X座標
			Ppos.y >= g_Piller[i].PosPil.y - (100.0f * g_Piller[i].SclPil.y) * 2 && Ppos.y <= g_Piller[i].PosPil.y + (60.0f * g_Piller[i].SclPil.y) * 2 &&		//Y座標								//Y座標
			Ppos.z >= g_Piller[i].PosPil.z - (30.0f * g_Piller[i].SclPil.z) && Ppos.z <= g_Piller[i].PosPil.z + (30.0f * g_Piller[i].SclPil.z) &&			//Z座標
			g_Piller[i].checklive() == true)
		{
			return true;
		}

	}
	return false;
}