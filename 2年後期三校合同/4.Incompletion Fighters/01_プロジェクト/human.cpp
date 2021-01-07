//****************************************************
//AIのプログラム
//****************************************************

#include "human.h"
#include "player.h"
#include "myDirect3D.h"
#include "Vector.h"
//*****************************************************************************
//クラス
//*****************************************************************************
class PEAPLE 
{
private:
	int				AImode;					//キャラクターのAIモード
	int				waittime;				//待機時間

public:
	//プレイヤーの初期処理
	void AIInit()
	{
		AImode = SEKKINMOVE;
		waittime = 0;
	}

	//更新処理(AIの更新条件)
	void AIUpdate()
	{
		switch (AImode)
		{
		case WAITTIME:
			waittime++;		//待機時間の更新
			//180秒になったら更新処理
			if (waittime >= 10)
			{
				if (GetVectorfloat(GetPos(0), GetPos(1)) <= 900.0f)
				{
					if (GetVectorfloat(GetPos(0), GetPos(1)) <= 550.0f)
					{
						AImode = BACKMOVE;
					}
					else
					{
						if (rand() % 100 < 40)
						{
							AImode = PUNCH;
						}
						if (rand() % 100 < 40)
						{
							AImode = KICK;
						}
					}
				}
				else
				{
					//ここに他のAIに移動する
					AImode = SEKKINMOVE;
				}
				waittime = 0;		//待機時間のリセット
			}
			break;

			//前進
		case SEKKINMOVE:
			//プレイヤーとの距離が700になったら
			if (GetVectorfloat(GetPos(0),GetPos(1)) <= 700.0f)
			{
					AImode = WAITTIME;
			}
			break;

			//後進
		case BACKMOVE:
			waittime++;
			if (GetVectorfloat(GetPos(0), GetPos(1)) >= 2300.0f)
			{
				waittime = 0;
				AImode = WAITTIME;
			}
			if (GetVectorfloat(GetPos(0), GetPos(1)) <= 700.0f)
			{
				waittime = 0;

				if (GetVectorfloat(GetPos(0), GetPos(1)) >= 540.0f)
				{
					if (rand() % 100 < 70)
					{
						AImode = PUNCH;
					}
					else
					{
						AImode = WAITTIME;
					}
				}
			}
			break;


			//拳で攻撃
		case PUNCH:
			waittime++;		//待機時間の更新
			//180秒になったら更新処理
			if (waittime >= 60)
			{
				//ここに他のAIに移動する
				AImode = BACKMOVE;
				waittime = 0;		//待機時間のリセット
			}
			break;

			//足で攻撃
		case KICK:
			waittime++;		//待機時間の更新
			//180秒になったら更新処理
			if (waittime >= 1)
			{
				//ここに他のAIに移動する
				AImode = BACKMOVE;
				waittime = 0;		//待機時間のリセット
			}
			break;

			//ダメージ受けたとき
		case DAMAGED:
			break;

		default:
			break;
		}
	}

	/*ゲッター*/
	//使用状況を手に入れる
	int GetAI()
	{
		return AImode;
	}
	/*ゲッターここまで*/

	/*セッター*/
	//使用状況を手に入れる
	void SetAI(int SetAI)
	{
		AImode = SetAI;
	}
	/*ゲッターここまで*/
};

//*****************************************************************************
//クラスのグローバル宣言
//*****************************************************************************
PEAPLE g_peepe;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Human_Initialize(void)
{
	// 位置・回転・スケールの初期設定
	g_peepe.AIInit();		//プレイヤー1の初期処理
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Human_Finalize(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void Human_Update(void)
{
	g_peepe.AIUpdate();
}

//ゲッター
int GetAI(void)
{
	return g_peepe.GetAI();
}

//セッター
void SetAImode(int SetAI)
{
	g_peepe.SetAI(SetAI);
}