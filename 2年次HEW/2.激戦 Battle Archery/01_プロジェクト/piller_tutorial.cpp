//****************************************************
// 柱関係のプログラム
//****************************************************

#include "piller_tutorial.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
#include "bullet.h"
#include "xfile.h"
#include "target_tutorial.h"


// *****************************************************************************
// マクロ定義
// *****************************************************************************
#define NUM_PILLER_TUTORIAL 20								//表示する柱の最大数

// *****************************************************************************
// クラス
// *****************************************************************************
// 柱のクラス
class PILLERS_TUTORIAL {
private:
	bool live;				//壁が存在するかどうか
	int  type;				//この値によって色が変わる


public:
	D3DXMATRIX				g_mtxWorldField;		// ワールドマトリックス(行列)

	D3DXVECTOR3				PosPil;					// 柱の位置
	D3DXVECTOR3				RotPil;					// 柱の向き(回転)
	D3DXVECTOR3				SclPil;					// 柱の大きさ(スケール)

													//コンストラクタ
	PILLERS_TUTORIAL() {
		live = false;								//柱の存在抹殺
		type = PILLER;
		PosPil = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期座標
		RotPil = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期回転
		SclPil = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期大きさ
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
		}
	}

	void Finalize()
	{
		live = false;
		type = PILLER;
	}

	//更新処理
	void Update()
	{
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

static PILLERS_TUTORIAL g_PillerTutorial[NUM_PILLER_TUTORIAL];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Piller_Tutorial_Initialize(void)
{
	// 柱の設置

	g_PillerTutorial[0].SetObject(D3DXVECTOR3(-1825.0f, 175.0f, 1250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_PillerTutorial[1].SetObject(D3DXVECTOR3(-1825.0f, 175.0f, 1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_PillerTutorial[2].SetObject(D3DXVECTOR3(-1325.0f, 175.0f, 750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_PillerTutorial[3].SetObject(D3DXVECTOR3(-1325.0f, 175.0f, 550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_PillerTutorial[4].SetObject(D3DXVECTOR3(-825.0f, 175.0f, 250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_PillerTutorial[5].SetObject(D3DXVECTOR3(-825.0f, 175.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_PillerTutorial[6].SetObject(D3DXVECTOR3(825.0f, 175.0f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_PillerTutorial[7].SetObject(D3DXVECTOR3(825.0f, 175.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_PillerTutorial[8].SetObject(D3DXVECTOR3(1325.0f, 175.0f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_PillerTutorial[9].SetObject(D3DXVECTOR3(1325.0f, 175.0f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_PillerTutorial[10].SetObject(D3DXVECTOR3(1825.0f, 175.0f, -1250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_PillerTutorial[11].SetObject(D3DXVECTOR3(1825.0f, 175.0f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Piller_Tutorial_Finalize(void)
{
	for (int i = 0; i < NUM_PILLER_TUTORIAL; i++)
	{
		g_PillerTutorial[i].Finalize();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Piller_Tutorial_Update(void)
{
	for (int i = 0; i < NUM_PILLER_TUTORIAL; i++)
	{
		// 的の色が変わったとき、柱の色も変わる = ノーマル色
		if (GetColor_Tutorial(i) == TARGETWHITE)
		{
			g_PillerTutorial[i].SetType(PILLER);
		}
		// 的の色が変わったとき、柱の色も変わる = 赤色
		else if (GetColor_Tutorial(i) == TARGETRED)
		{
			g_PillerTutorial[i].SetType(PILLER_R);
		}
		// 的の色が変わったとき、柱の色も変わる = 青色
		else if (GetColor_Tutorial(i) == TARGETBLUE)
		{
			g_PillerTutorial[i].SetType(PILLER_B);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Piller_Tutorial_Draw(void)
{
	//ワールドマトリクスの設定
	for (int i = 0; i < NUM_PILLER_TUTORIAL; i++)
	{
		//柱が存在していたとき、描画する
		if (g_PillerTutorial[i].checklive() == true)
		{
			Xfile_Draw(g_PillerTutorial[i].GetScl(), g_PillerTutorial[i].GetPos(), g_PillerTutorial[i].GetRot(), g_PillerTutorial[i].checktype());
		}
	}
}


//=============================================================================
// プレイヤーと柱の当たり判定処理
//=============================================================================
bool CheckHitPlayer_vs_PillerTutorial(D3DXVECTOR3 Ppos)
{

	for (int i = 0; i < NUM_PILLER_TUTORIAL; i++)
	{
		// プレイヤー座標が柱の大きさよりも小さい→当たっている　→元の位置に戻す
		if (Ppos.x >= g_PillerTutorial[i].PosPil.x - (30.0f * g_PillerTutorial[i].SclPil.x) && Ppos.x <= g_PillerTutorial[i].PosPil.x + (30.0f * g_PillerTutorial[i].SclPil.x) &&			//X座標
			Ppos.y >= g_PillerTutorial[i].PosPil.y - (100.0f * g_PillerTutorial[i].SclPil.y) * 2 && Ppos.y <= g_PillerTutorial[i].PosPil.y + (60.0f * g_PillerTutorial[i].SclPil.y) * 2 &&		//Y座標								//Y座標
			Ppos.z >= g_PillerTutorial[i].PosPil.z - (30.0f * g_PillerTutorial[i].SclPil.z) && Ppos.z <= g_PillerTutorial[i].PosPil.z + (30.0f * g_PillerTutorial[i].SclPil.z) &&			//Z座標
			g_PillerTutorial[i].checklive() == true)
		{
			return true;
		}

	}
	return false;
}