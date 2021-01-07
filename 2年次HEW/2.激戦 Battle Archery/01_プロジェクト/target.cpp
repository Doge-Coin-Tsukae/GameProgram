//****************************************************
//弾関係のプログラム
//****************************************************

#include "target.h"
#include "bullet.h"
#include "xfile.h"
#include "colision.h"
#include "score_draw.h"
#include "particle.h"
#include "sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_TARGET 8								//表示的の総数
#define MAX_HP	   1
//*****************************************************************************
//クラス
//*****************************************************************************
//的のクラス
class TARGET {
private:
	bool live;				//壁が存在するかどうか
	int  type;				//この値によって色が変わる
	int	 Hp;				//的のHp
	float radius;			//直径
	D3DXVECTOR3				PosTgt;					// 地面の位置
	D3DXVECTOR3				RotTgt;					// 地面の向き(回転)
	D3DXVECTOR3				SclTgt;					// 地面の大きさ(スケール)

public:
	D3DXMATRIX				g_mtxWorldField;		// ワールドマトリックス(行列)
	//コンストラクタ
	TARGET()
	{
		live = false;								//的の存在抹殺
		radius = 70.0f;							//的の半径 (150.0f)
		type = TARGETWHITE;							//的のタイプを指定(全部白色に)
		Hp = MAX_HP;								//体力を最大値に
		PosTgt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期座標
		RotTgt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期回転
		SclTgt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期大きさ
	}

	void Finalize()
	{
		live = false;				//的を全部消す
		type = TARGETWHITE;			//まとの状態を白に戻す
		Hp = MAX_HP;				//体力を最大値に
	}

	//的のの配置(設置座標,スケール(大きさ)の指定)
	void SetObject(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot,D3DXVECTOR3 Scl)
	{
		if (live == false)
		{
			PosTgt = Pos;
			RotTgt = Rot;
			SclTgt = Scl;
			type = TARGETWHITE;
			live = true;
		}
	}

	//更新処理
	void Update()
	{
		//弾の数だけ調べる
		for (int i = 0; i < BULLET_NUM; i++)
		{
			//スピードに0.1ずつ増やしていく
			for (float j = 0.0f; j < GetSpeed(i); j += 0.01f)
			 {
				//判定がTrueだったら
				if (CircleAndPoint(PosTgt,GetBulletPos(i) - (-GetOne(i) * j),radius) == true &&			//Z座標
					live == true && GetUse(i) && GetMove(i) == true)			//その的が使われている + その弾が使われている + その弾が動いている
				{

					PlaySound(SOUND_LABEL_SE_TARGET_HIT);

					Hp--;				//hpを減らす

					//体力が0になったとき
					if (Hp <= 0)
					{
						addscore(GetPlyNum(i), 1);		//スコアを加える
						PlaySound(SOUND_LABEL_SE_TARGET_HIT_CHEERS);

						//もし的がplayerが所有していたとき
						if (type != TARGETWHITE)
						{
							addscore(type - 2, -1);		//的の持ち主減点
						}

						//パーティクルのセット
						if (GetPlyNum(i) == 0)
						{
							ParticleSetNum(10, PosTgt, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.85f), 30.0f, 100.0f, 60, 0);
						}
						if (GetPlyNum(i) == 1)
						{
							ParticleSetNum(10, PosTgt, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.90f), 30.0f, 100.0f, 60, 0);
						}

						StopBullet(i);				//弾を停止させる
						type = GetPlyNum(i) + 2;	//そのプレイヤーの物にする (xファイルの都合上)+2
						Hp = MAX_HP;				//体力を回復させる
					}
					break;
				}

				if (GetMove(i) == false)
				{
					break;
				}

				if (GetUse(i) == false)
				{
					break;
				}
			}
		}
	}

	//壁が存在しているかどうか調べる
	bool Getlive()
	{
		return live;
	}

	//的の色を取得
	int Gettype()
	{
		return type;
	}

	//座標を取得
	D3DXVECTOR3 GetPos()
	{
		return PosTgt;
	}

	//角度を取得
	D3DXVECTOR3 GetRot()
	{
		return RotTgt;
	}

	//スケールを取得
	D3DXVECTOR3 GetScl()
	{
		return SclTgt;
	}
};

static TARGET g_Target[NUM_TARGET];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Target_Initialize(void)
{
	//的のの設置
	g_Target[0].SetObject(D3DXVECTOR3(-2000.0f, 175.0f, 3050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));
	g_Target[1].SetObject(D3DXVECTOR3(2000, 175.0f, 3050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));

	g_Target[2].SetObject(D3DXVECTOR3(-2000.0f, 175.0f, -3050.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));
	g_Target[3].SetObject(D3DXVECTOR3(2000.0f, 175.0f, -3050.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));

	g_Target[4].SetObject(D3DXVECTOR3(-1050, 175.0f, 700.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));
	g_Target[5].SetObject(D3DXVECTOR3(775.0f, 175.0f, 1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));

	g_Target[6].SetObject(D3DXVECTOR3(-1125.0f, 175.0f, -1750.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));
	g_Target[7].SetObject(D3DXVECTOR3(1250.0f, 175.0f, -1075.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Target_Finalize(void)
{
	for (int i = 0; i < NUM_TARGET; i++)
	{
		g_Target[i].Finalize();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Target_Update(void)
{
	//ワールド変換
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	//ワールドマトリクスの初期化
	for (int i = 0; i < NUM_TARGET; i++)
	{
		//的が存在していたとき、処理をする
		if (g_Target[i].Getlive() == true)
		{

			D3DXMatrixIdentity(&g_Target[i].g_mtxWorldField);

			//回転を反映
			/*この関数は原則1本の軸の動かせる*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Target[i].GetRot().y, g_Target[i].GetRot().x, g_Target[i].GetRot().z);		//ヨー、ピッチ、ロール	ヨーとロールが同じ動きになること=ジンバルロック
			D3DXMatrixMultiply(&g_Target[i].g_mtxWorldField, &g_Target[i].g_mtxWorldField, &mtxRot);				//回転*ワールド

			//移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_Target[i].GetPos().x, g_Target[i].GetPos().y, g_Target[i].GetPos().z);
			D3DXMatrixMultiply(&g_Target[i].g_mtxWorldField, &g_Target[i].g_mtxWorldField, &mtxTranslate);			//移動*ワールド

			//スケールを反映
			D3DXMatrixScaling(&mtxScl, g_Target[i].GetScl().x, g_Target[i].GetScl().y, g_Target[i].GetScl().z);
			D3DXMatrixMultiply(&g_Target[i].g_mtxWorldField, &g_Target[i].g_mtxWorldField, &mtxScl);				//拡大・縮小*ワールド

			g_Target[i].Update();
		}

	}

}

//=============================================================================
// 描画処理
//=============================================================================
void Target_Draw(void)
{
	//ワールドマトリクスの設定
	for (int i = 0; i < NUM_TARGET; i++)
	{
		//壁が存在していたとき、描画する
		if (g_Target[i].Getlive() == true)
		{
			Xfile_Draw(g_Target[i].GetScl(), g_Target[i].GetPos(), g_Target[i].GetRot(), g_Target[i].Gettype());
		}
	}
}

int GetColor(int index)
{
	return g_Target[index].Gettype();
}