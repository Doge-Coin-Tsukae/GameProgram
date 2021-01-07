//****************************************************
//弾関係のプログラム
//****************************************************

#include "bullet.h"
#include "myDirect3D.h"
#include "camera.h"
#include "object.h"
#include "sound.h"
#include "xfile.h"
#include "player.h"
#include "Vector.h"
#include "field.h"
#include "point.h"
#include "particle.h"
#include "wall.h"
#include "wall_tate.h"
#include "wall_tutorial.h"
#include "wall_tate_tutorial.h"
#include "piller_tutorial.h"
#include "piller.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GRAVITY			(0.3f)						//重力
#define TIMER_MAX		(30.0f)						//弾が消えるまでの時間

//*****************************************************************************
//クラス
//*****************************************************************************

//弾のクラス
class BULLET {
private:
	D3DXVECTOR3		PosBullet;				//弾のポジション
	D3DXVECTOR3		PosCamera;				//カメラの注視点を入れる
	D3DXVECTOR3		RotBullet;				// 弾の向き(回転)
	D3DXVECTOR3		SclBullet;				//弾の大きさ
	D3DXVECTOR3		LoadPos;				//進んでいく座標
	D3DXVECTOR3		OneVector;				//1ベクトルを取る

	int				PlayerNumber;			//撃った弾の番号
	float			speed;					//弾の速度
	float			timer;					//弾の有効時間
	bool			Use;					//弾の使用状況
	bool			Move;					//移動しているか
	bool			Parti;					//パーティクルの制限
public:
	//弾の初期処理
	void BulletInit()
	{
		//変数の初期化
		PosBullet = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		RotBullet = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SclBullet = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		LoadPos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		OneVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		PlayerNumber = 0;
		timer = 0.0f;
		speed = 50.0f;
		Use = false;
		Move = false;
		Parti = false;
	}

	//弾を設置する
	void Enabled(D3DXVECTOR3 ppos,float pow,int FirePlayer)
	{
		PlayerNumber = FirePlayer;				//弾にプレイヤー番号を代入
		PosCamera = Get_Pos(PlayerNumber);		//照準を習得
		PosCamera.y -= 40.0f;					//カメラのY座標を下げる(画面に合わせる)
		PosBullet = ppos;						//プレイヤーの座標を入れる
		PosBullet.y += 100.0f;					//プレイヤーのY座標を入れる(弓に合わせる)
		speed += pow;							//弾の速度を指定
		timer = TIMER_MAX;		//弾が消えるまでの時間を入れる
		Use = true;				//弾を有効にする
		Move = true;			//弾の移動を有効にする		

		//単位ベクトルを取る
		OneVector = GetVector(PosBullet, PosCamera);
		//進むスピードをかける
		LoadPos = OneVector * speed;

		//角度調整
		RotBullet = GetRot(PlayerNumber) / -57;	//プレイヤーの角度を弾の角度に入れる
	}

	//弾の座標を更新する
	void Update()
	{
		//弾が飛んでいるとき
		if (Move == true)
		{
			PosBullet += LoadPos;		//弾の更新
			LoadPos.y -= GRAVITY;//弾が落ちるようにする(重力)
		}

		//当たり判定
		for (float i = 0; i < speed; i += 0.1f) {
			//弾が壁に接触、又は地面に接触したとき
			if (CheckHitPlayer(PosBullet - (-OneVector*i)) == true ||
				CheckHitPlayer_vs_Wall(PosBullet - (-OneVector * i)) == true ||
				CheckHitPlayer_vs_WallTate(PosBullet - (-OneVector * i)) == true ||
				CheckHitPlayer_vs_PILLER(PosBullet - (-OneVector * i)) == true ||
				CheckHitPlayer_vs_WallTutorial(PosBullet - (-OneVector * i)) == true ||
				CheckHitPlayer_vs_WallTateTutorial(PosBullet - (-OneVector * i)) == true ||
				CheckHitPlayer_vs_PillerTutorial(PosBullet - (-OneVector * i)) == true ||

				PosBullet.y <= FIELD_HIGHT)
			{
				if (Parti == false)
				{
					ParticleSetNum(10, PosBullet, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.85f), 30.0f, 30.0f, 60, 0);	//パーティクルのセット
					Parti = true;
				}
				Move = false;
				break;
			}
		}

		timer -= 0.1f;		//1フレームに0.1ずつ減らす

	}

	//弾の使用状況を調べる
	bool CheckMove()
	{
		return Move;
	}

	//弾の動きを止める
	void StopMove()
	{
		Move = false;
	}

	//弾を消す
	void disabled()
	{
		Move = false;		//移動を無効にする
		Use = false;		//弾を無効にする
		Parti = false;
		timer = 0.0f;		//時間を0にする
		speed = 1.0f;		//弾の速度リセット
	}

	//有効時間の確認
	float CheckTimer()
	{
		return timer;
	}

	//使用状況の確認
	bool CheckUse()
	{
		return Use;
	}

	//弾を撃った人の番号
	int CheckNum()
	{
		return PlayerNumber;
	}

	//座標の確認
	D3DXVECTOR3 CheckPos()
	{
		return PosBullet;
	}

	//大きさの確認
	D3DXVECTOR3 CheckScl()
	{
		return SclBullet;
	}

	//回転の確認
	D3DXVECTOR3 CheckRot()
	{
		return RotBullet;
	}

	D3DXVECTOR3 CheckOne()
	{
		return OneVector;
	}

	float CheckSpeed()
	{
		return speed;
	}
};

BULLET  bullet[BULLET_NUM];

//*****************************************************************************
//関数
//*****************************************************************************

/*初期処理*/
HRESULT Bullet_Initialize(void)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		bullet[i].BulletInit();
	}
	return S_OK;
}

/*終了処理*/
void Bullet_Finalize(void)
{

}

/*更新処理*/
void Bullet_Update(void)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		//弾が使用されている場合、処理をする
		if (bullet[i].CheckUse() == true)
		{
			bullet[i].Update();		//弾の更新処理

			//有効時間が切れているか
			if (bullet[i].CheckTimer() <= 0.0f)
			{
				bullet[i].disabled();		//弾を消す
			}

		}
	}
}

/*描画処理*/
void Bullet_Draw(void)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		//弾が使用されている場合、処理をする
		if (bullet[i].CheckUse() == true)
		{
			Xfile_Draw(bullet[i].CheckScl(), bullet[i].CheckPos(), bullet[i].CheckRot(),BOW);
		}
	}
}

void DeleteBullet(int index)
{
	bullet[index].disabled();
}

/*外部から弾を使用するとき*/
void SetBullet(D3DXVECTOR3 index,float pow, int Player)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		//弾が使用されていない場合、処理をする
		if (bullet[i].CheckUse() == false)
		{
			bullet[i].Enabled(index,pow ,Player);		//弾を有効にする
			break;
		}
	}
}

//弾を停止させる
void StopBullet(int index)
{
	bullet[index].StopMove();
}

//弾の座標を受け取る
D3DXVECTOR3 GetBulletPos(int index)
{
	return bullet[index].CheckPos();
}

D3DXVECTOR3 GetBulletScl(int index)
{
	return bullet[index].CheckScl();
}

//弾が使われているかを受け取る
bool GetUse(int index)
{
	return bullet[index].CheckUse();
}

//弾の所有者を調べる
int GetPlyNum(int index)
{
	return bullet[index].CheckNum();
}

//単位ベクトルを取得
D3DXVECTOR3  GetOne(int index)
{
	return bullet[index].CheckOne();
}

//弾が動いてるか
bool GetMove(int index)
{
	return bullet[index].CheckMove();
}

//弾のスピードを取得
float GetSpeed(int index)
{
	return bullet[index].CheckSpeed();
}