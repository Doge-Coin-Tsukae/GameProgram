//****************************************************
//プレイヤー関係のプログラム
//****************************************************

#include "player.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "colision.h"
#include "object.h"
#include "debugproc.h"
#include "sound.h"
#include "xfile.h"
#include "colision.h"
#include "Vector.h"
#include "shadow.h"
#include "game.h"
#include "human.h"
#include "billboard.h"
#include "bullet.h"
#include <math.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define	VALUE_ROTATE	(3.0f)				// 回転量
#define MAX_POWER		(200.0f)			// パワーの上限

#define NORMAL_Y		(100.0f)			//底

#define INIT_PLAYERONE_POS  D3DXVECTOR3(0.0f,NORMAL_Y,-1000.0f)
#define INIT_PLAYERONE_ROT  D3DXVECTOR3(0.0f,180.0f, 0.0f)

#define INIT_PLAYERTWO_POS  D3DXVECTOR3(0.0f,NORMAL_Y,1000.0f)
#define INIT_PLAYERTWO_ROT  D3DXVECTOR3(0.0f, 0.0f, 0.0f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 static g_pVtxBuffField = NULL;	// 頂点バッファへのポインタ
D3DXMATRIX				static g_mtxWorldField;		// ワールドマトリックス(行列)

//*****************************************************************************
//enum
//*****************************************************************************
//プレイヤーの移動
enum MOVE
{
	UP,			//前移動
	DOWN,		//後ろ移動
	RIGHT,		//右移動
	LEFT,		//左移動
	RIGHTUP,	//右前移動
	RIGHTDOWN,	//右後ろ移動
	LEFTUP,		//左前移動
	LEFTDOWN,	//左後ろ移動
	FLY,		//空中浮遊
	DAMAGE,		//ダメージ表現
	DAMAGEDOWN,	//ダウン表現
	GRAVITY,	//重力に引っ張られる
};

//攻撃形態
enum ATTACKPATTAN
{
	NONE,
	PPUNCH,
	PPUNCHSTRONG,
	PKICK,
	PKICKSTRONG,
};
//*****************************************************************************
//クラス
//*****************************************************************************

class player {

private:
	D3DXVECTOR3		PosPlayer;				//プレイヤーのポジション
	D3DXVECTOR3		RotPlayer;				// プレイヤーの向き(回転)
	D3DXVECTOR3		SclPlayer;				//プレイヤーの大きさ
	D3DXVECTOR3		InitVector;				//ベクトルの初期座標
	D3DXVECTOR3		fly;					//滞空時間
	D3DXVECTOR3		Dir;					//プレイヤーの行き先
	D3DXVECTOR3		arm;
	D3DXVECTOR3		armstrong;
	D3DXVECTOR3		leg;
	D3DXVECTOR3		legstrong;

	float			speed;					//プレイヤーの速度
	float			combotime;				//攻撃中の時間(コンボ関係)
	int				Hp;						//体力
	int				combo;					//コンボ
	int				idxShadow;				//シャドウID
	int				cooldown;				//攻撃したとき、高速で出ないようにする
	int				damagecooldown;			//攻撃を受けたときの硬直
	int				beforattack;			//前、自分が攻撃していたもの
	int				attackpower;			//攻撃力
	bool			downattack;				//その攻撃がダウン効果がある攻撃か
	bool			onehit;
	bool			Attack;					//攻撃中か
	bool			Damaged;				//攻撃を受けているか
	bool			CheckDeath;
public:

	//プレイヤーの初期処理(初期座標,初期回転数)
	void PlayerInit(D3DXVECTOR3 IniPos, D3DXVECTOR3 IniRot)
	{
		PosPlayer = IniPos;		//初期座標
		arm = PosPlayer;
		arm.y += 600.0f;
		leg = PosPlayer;
		leg.y += 300.0f;
		RotPlayer = IniRot;			//初期回転
		SclPlayer = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			//初期大きさ
		Dir = PosPlayer;									//仮定の行き先をプレイヤーと同じに
		Hp = MAX_HP;										//体力
		combo = 0;
		damagecooldown = 0;
		cooldown = 0;
		speed = 50.0f;										//プレイヤーの素早さ
		beforattack = NONE;
		attackpower = 0;
		fly = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		downattack = false;
		onehit = false;
		Attack = false;
		Damaged = false;
		CheckDeath = false;

		idxShadow = Shadow_Create(PosPlayer, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	}

	void PlayerFinalize()
	{
		Shadow_Release(idxShadow);
	}

	//座標の変更(方向(enum),方向(0.0f,0.2f,0.5f,0.75f,1.0f))
	void ChangePos(int xyzpm, int i, float speed)
	{

		switch (xyzpm) {
			if (Attack == false)
			{
				//前移動
		case UP:
			Dir.z += sin(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x += cos(RotPlayer.y*D3DX_PI / 180)*speed;

			break;

			//後ろ移動
		case DOWN:
			Dir.z -= sin(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x -= cos(RotPlayer.y*D3DX_PI / 180)*speed;

			break;

			//右移動
		case RIGHT:
			Dir.z -= cos(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x += sin(RotPlayer.y*D3DX_PI / 180)*speed;
			break;

			//左移動
		case LEFT:
			Dir.z += cos(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x -= sin(RotPlayer.y*D3DX_PI / 180)*speed;

			break;

			//右前
		case RIGHTUP:
			Dir.z -= cos(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x += sin(RotPlayer.y*D3DX_PI / 180)*speed;

			Dir.z += sin(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x += cos(RotPlayer.y*D3DX_PI / 180)*speed;
			break;

			//右後ろ
		case RIGHTDOWN:
			Dir.z -= cos(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x += sin(RotPlayer.y*D3DX_PI / 180)*speed;

			Dir.z -= sin(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x -= cos(RotPlayer.y*D3DX_PI / 180)*speed;
			break;

			//左前
		case LEFTUP:
			Dir.z += cos(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x -= sin(RotPlayer.y*D3DX_PI / 180)*speed;

			Dir.z += sin(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x += cos(RotPlayer.y*D3DX_PI / 180)*speed;
			break;

			//左後ろ
		case LEFTDOWN:
			Dir.z += cos(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x -= sin(RotPlayer.y*D3DX_PI / 180)*speed;

			Dir.z -= sin(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x -= cos(RotPlayer.y*D3DX_PI / 180)*speed;
			break;
			}

			//宙に浮く
		case FLY:
			if (fly.y == 0)
			{
				fly.y = 30.0f;
			}
			break;

		case DAMAGE:

			Damaged = true;
			damagecooldown = 10;

			//少し後ろに後退させる
			for (int i = 0; i <= 1; i++)
			{
				ChangePos(LEFT, 0, 10.0f);
			}
			break;

			//ダウン表現
		case DAMAGEDOWN:
			Damaged = true;
			damagecooldown = 60;

			//宙に浮く
			fly.y = 50.0f;
			fly.z = cos(RotPlayer.y*D3DX_PI / 180)*speed;
			fly.x = sin(RotPlayer.y*D3DX_PI / 180)*speed;

			break;

			//重力に引っ張られる
		case GRAVITY:
			Dir.x -= fly.x;
			Dir.y += fly.y;
			Dir.z += fly.z;

			//当たり判定
			if (CheckHitPlayer(Dir) == false)
			{
				Hitcamera(false, i);
				PosPlayer = Dir;
			}
			else
			{
				Hitcamera(true, i);
				PosPlayer.y += fly.y;
				Dir = PosPlayer;
			}

			if (PosPlayer.y < NORMAL_Y)
			{
				PosPlayer.y = NORMAL_Y;
				fly = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			else
			{
				fly.y -= 1.4f;
			}

			break;


			//それ以外
		default:
			break;
		}
	}

	//プレイヤーを相手プレイヤーに向かい合わせる(更新処理)
	void UpdateRot(D3DXVECTOR3 AnotherPos)
	{
		D3DXVECTOR3 vector = GetVector(AnotherPos, PosPlayer);

		RotPlayer.y = (((InitVector.x * vector.x) + (InitVector.y * vector.y) + (InitVector.z * vector.z)) / (sqrt((InitVector.x*InitVector.x) + (InitVector.y * InitVector.y) + (InitVector.z * InitVector.z)) * sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z))));
		if (PosPlayer.x >= AnotherPos.x)
		{
			RotPlayer.y = (1 + (RotPlayer.y + 1))*-1;
		}

		RotPlayer.y *= 90;
		RotPlayer.y += 90;
	}

	//更新処理
	void Update()
	{
		//判定用の座標を更新
		arm.z = PosPlayer.z - cos(RotPlayer.y*D3DX_PI / 180)*700.0f;
		arm.x = PosPlayer.x - sin(-RotPlayer.y*D3DX_PI / 180)*700.0f;
		arm.y = PosPlayer.y + 600.0f;
		armstrong.z = PosPlayer.z - cos(RotPlayer.y*D3DX_PI / 180)*1000.0f;
		armstrong.x = PosPlayer.x - sin(RotPlayer.y*D3DX_PI / 180)*1000.0f;
		armstrong.y = PosPlayer.y + 600.0f;

		leg.z = PosPlayer.z - cos(RotPlayer.y*D3DX_PI / 180)*700.0f;
		leg.x = PosPlayer.x - sin(RotPlayer.y*D3DX_PI / 180)*700.0f;
		leg.y = PosPlayer.y + 300.0f;
		legstrong.z = PosPlayer.z - cos(RotPlayer.y*D3DX_PI / 180)*1000.0f;
		legstrong.x = PosPlayer.x - sin(RotPlayer.y*D3DX_PI / 180)*1000.0f;
		legstrong.y = PosPlayer.y + 300.0f;

		cooldown--;
		damagecooldown--;
	}

	//当たり判定(座標,ダメージ量,使用しているかどうか,ダウン効果,遠距離か,遠距離時のナンバー)
	void Colision(D3DXVECTOR3 arms, int damage ,bool attacks, bool Down,bool shoot,int number,int eneattack)
	{
		D3DXVECTOR3 attackpos;		//攻撃ポジション

		if (damagecooldown <= 0)
		{
			damagecooldown = 0;
			Damaged = false;
		}

		//当たり判定でが返ってtrueだったら
		if (PointtoRectangley(arms, PosPlayer, SclPlayer, attacks, 200.0f, 450.0f) == true)
		{
			//ダウン効果が有効だったら吹き飛ばす
			if (Down == true)
			{
				if (eneattack == PPUNCH || eneattack == PPUNCHSTRONG)
				{
					PlaySound(SOUND_LABEL_SE_PUNCH_FLY);
				}
				else
				{
					PlaySound(SOUND_LABEL_SE_KICK_FLY);
				}
				Hp -= damage;
				ChangePos(DAMAGEDOWN, 0, 50.0f);
			}
			//なかったらただのダメージを加える
			else
			{
				if (shoot == true)
				{
					PlaySound(SOUND_LABEL_SE_PUNCH_HIT);
				}
				else
				{
					if (eneattack == PPUNCH)
					{
						PlaySound(SOUND_LABEL_SE_PUNCH_HIT);
					}
					else
					{
						PlaySound(SOUND_LABEL_SE_KICK_HIT);
					}
				}
				Hp -= damage;
				ChangePos(DAMAGE, 0, 50.0f);
			}
			if (shoot == true)
			{
				DisabledBullet(number);
			}
		}
	}

	//攻撃をtrueに
	void attack()
	{
		Attack = true;
		onehit = true;
	}

	//攻撃をfalseに
	void unleshdattack()
	{
		Attack = false;
	}

	//コンボを1増やす
	void comboup()
	{
		combo += 1;
	}

	//コンボのリセット
	void resetcombo()
	{
		combo = 0;
	}

	//
	void combotimeUpdate()
	{
		if (Attack == true)
		{
			combotime -= 0.1f;

			if (combotime <= 0.0f)
			{
				combotime = 0.0f;
				unleshdattack();
			}
		}

		onehit = false;
	}

	//死亡判定
	void Death(int index)
	{
		//体力が0になったときに死亡させる
		if (Hp <= 0)
		{
			RotPlayer.x -= 10.0f;
			//死亡フラグがfalseの時
			if (CheckDeath == false)
			{
				PlaySound(SOUND_LABEL_SE_DEATH);		//死亡SEをける
				//プレイヤー2が殺った時
				if (index == 0)
				{
					SetGameSet(1);		//プレイヤー2にセットを付ける
				}
				else
				{
					SetGameSet(0);		//プレイヤー1にセットを付ける
				}
				SetDeathflag();
				CheckDeath = true;		//死亡フラグをtrueする(2重ループ防止)
			}
		}
	}

	//
	bool cooldowncheck()
	{
		if (cooldown <= 0)
		{
			cooldown = 20;
			return true;
		}
		return false;
	}

	/*ゲッター*/

	bool Getattack()
	{
		return Attack;
	}

	bool Gethit()
	{
		return onehit;
	}

	bool GetDownAttack()
	{
		return downattack;
	}

	bool GetDamaged()
	{
		return Damaged;
	}

	int GetIdShadow()
	{
		return idxShadow;
	}

	int GetBeforAttack()
	{
		return beforattack;
	}

	int GetAttackpower()
	{
		return attackpower;
	}

	int CheckHp()
	{
		return Hp;
	}

	int CheckCombo()
	{
		return combo;
	}

	//プレイヤーの座標を求める
	D3DXVECTOR3 CheckPos()
	{
		return PosPlayer;
	}

	//プレイヤーのスケール(大きさ)を求める
	D3DXVECTOR3 CheckScl()
	{
		return SclPlayer;
	}

	//プレイヤーの角度を求める
	D3DXVECTOR3 CheckRot()
	{
		return RotPlayer;
	}

	D3DXVECTOR3 CheckArm()
	{
		return arm;
	}

	D3DXVECTOR3 CheckArmstrong()
	{
		return armstrong;
	}

	D3DXVECTOR3 CheckLeg()
	{
		return leg;
	}

	D3DXVECTOR3 CheckLegstrong()
	{
		return legstrong;
	}

	//プレイヤーが現在の攻撃を取得する
	D3DXVECTOR3 GetAttackPattan()
	{
		switch (beforattack)
		{
		case PPUNCH:
			attackpower = 10;
			return arm;
			break;

		case PPUNCHSTRONG:
			attackpower = 80;
			return armstrong;
			break;

		case PKICK:
			attackpower = 20;
			return leg;
			break;

		case PKICKSTRONG:
			attackpower = 80;
			return legstrong;
			break;
		default:
			return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		}
	}

	/*ゲッターここまで*/

	/*セッター*/
	void SetInitVector(D3DXVECTOR3 start, D3DXVECTOR3 end)
	{
		InitVector = GetVector(start, end);
	}

	//2Pに反転させる
	void SetRot(D3DXVECTOR3 rot)
	{
		RotPlayer.y = rot.y;
		RotPlayer.y -= 180;
	}

	void Setcombotime(float time)
	{
		combotime = time;
	}

	//ダメージ硬直する時間のセット
	void SetDamagedtime(int time)
	{
		damagecooldown = time;
	}

	//ダウン効果を付ける
	void SetDownAttack(bool Set)
	{
		downattack = Set;
	}

	//前に攻撃してたものをセット
	void SetBeforAttack(int Set)
	{
		beforattack = Set;
	}

	//ダメージを設定
	void Setdamage()
	{
		switch (beforattack)
		{
		case PPUNCH:
			attackpower = 100;
			break;

		case PPUNCHSTRONG:
			attackpower = 500;
			break;

		case PKICK:
			attackpower = 200;
			break;

		case PKICKSTRONG:
			attackpower = 600;
			break;
		default:
			attackpower = 0;
			break;
		}
	}
};

//*****************************************************************************
//クラスのグローバル宣言
//*****************************************************************************
player g_player[MAX_PLAYER];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Player_Initialize(void)
{

	// 位置・回転・スケールの初期設定
	g_player[0].PlayerInit(INIT_PLAYERONE_POS, INIT_PLAYERONE_ROT);		//プレイヤー1の初期処理
	g_player[1].PlayerInit(INIT_PLAYERTWO_POS, INIT_PLAYERTWO_ROT);		//プレイヤー2の初期処理
	g_player[0].SetInitVector(g_player[1].CheckPos(), g_player[0].CheckPos());		//基底ベクトルを作る(プレイヤー回転に必要)
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Player_Finalize(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_player[i].PlayerFinalize();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Player_Update(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_player[i].combotimeUpdate();												//コンボ機能
		g_player[i].ChangePos(GRAVITY, 0, 50.0f);									//重力を付ける
		g_player[i].Death(i);														//死亡判定
		Shadow_SetPosition(g_player[i].GetIdShadow(), g_player[i].CheckPos());		//影の更新処理
	}

	//1Pの処理
	{
		if (g_player[0].GetDamaged() == false)
		{
			//移動処理 (左)
			if (Keyboard_IsPress(DIK_D) || GamePad_IsPress(0, BUTTON_LEFT))
			{
				if (Keyboard_IsPress(DIK_S))
				{// 左奥移動
					g_player[0].ChangePos(RIGHTDOWN, 0, 50.0f);
				}
				else if (Keyboard_IsPress(DIK_W))
				{// 左手前移動
					g_player[0].ChangePos(RIGHTUP, 0, 50.0f);
				}
				else
				{// 左移動
					g_player[0].ChangePos(RIGHT, 0, 50.0f);
				}
			}

			//移動処理(右)
			else if (Keyboard_IsPress(DIK_A) || GamePad_IsPress(0, BUTTON_RIGHT))
			{

				if (Keyboard_IsPress(DIK_S))
				{// 右奥移動
					g_player[0].ChangePos(LEFTDOWN, 0, 50.0f);
				}

				else if (Keyboard_IsPress(DIK_W))
				{// 右手前移動
					g_player[0].ChangePos(LEFTUP, 0, 50.0f);
				}

				else
				{// 右移動
					g_player[0].ChangePos(LEFT, 0, 50.0f);
				}
			}

			//前移動
			else if (Keyboard_IsPress(DIK_S) || GamePad_IsPress(0, BUTTON_UP))
			{// 奥移動
				g_player[0].ChangePos(DOWN, 0, 50.0f);
			}

			//後ろ移動
			else if (Keyboard_IsPress(DIK_W) || GamePad_IsPress(0, BUTTON_DOWN))
			{// 手前移動
				g_player[0].ChangePos(UP, 0, 50.0f);
			}

			//空中浮遊
			else if (Keyboard_IsPress(DIK_SPACE) || GamePad_IsPress(0, BUTTON_DOWN))
			{// 手前移動
				g_player[0].ChangePos(FLY, 0, 50.0f);
			}

			//Yで拳攻撃
			if (Keyboard_IsTrigger(DIK_Y))
			{
				//コンボが3を超えたら + 前の攻撃がパンチだった(今の攻撃が前と同じ)
				if (g_player[0].CheckCombo() > 1 && g_player[0].GetBeforAttack() == PPUNCH)
				{//足攻撃にする
					g_player[0].SetDownAttack(true);		//ダウン効果を付ける
					g_player[0].attack();
					SetPolygon(g_player[0].CheckLeg());
					g_player[0].resetcombo();
					g_player[0].Setcombotime(2.0f);
					g_player[0].SetBeforAttack(PKICK);
					PlaySound(SOUND_LABEL_SE_KICK_MISS);
				}
				else
				{
					//前の攻撃がパンチだった時
					if (g_player[0].GetBeforAttack() == PPUNCH)
					{
						g_player[0].SetDownAttack(false);		//ダウン効果を外す
						g_player[0].attack();
						SetPolygon(g_player[0].CheckArm());
						g_player[0].comboup();
						g_player[0].Setcombotime(2.0f);
						g_player[0].SetBeforAttack(PPUNCH);
						PlaySound(SOUND_LABEL_SE_PUNCH_MISS);
					}
					//前の攻撃がその他だったとき
					else
					{
						g_player[0].SetDownAttack(false);		//ダウン効果を外す
						g_player[0].attack();
						SetPolygon(g_player[0].CheckArm());
						g_player[0].resetcombo();
						g_player[0].Setcombotime(2.0f);
						g_player[0].SetBeforAttack(PPUNCH);
						PlaySound(SOUND_LABEL_SE_PUNCH_MISS);
					}
				}
			}

			//Hで足攻撃
			if (Keyboard_IsTrigger(DIK_H))
			{
				//前の攻撃が蹴りだった時
				if (g_player[0].GetBeforAttack() == PKICK)
				{
					if (g_player[0].CheckCombo() > 1 && g_player[0].GetBeforAttack() == PKICK)
					{
						g_player[0].SetDownAttack(true);		//ダウン効果を外す
						g_player[0].attack();
						SetPolygon(g_player[0].CheckLeg());
						g_player[0].resetcombo();
						g_player[0].Setcombotime(2.0f);
						g_player[0].SetBeforAttack(PKICK);
						PlaySound(SOUND_LABEL_SE_KICK_MISS);
					}
					else
					{
						g_player[0].SetDownAttack(false);		//ダウン効果を外す
						g_player[0].attack();
						SetPolygon(g_player[0].CheckLeg());
						g_player[0].comboup();
						g_player[0].Setcombotime(2.0f);
						g_player[0].SetBeforAttack(PKICK);
						PlaySound(SOUND_LABEL_SE_KICK_MISS);

					}
				}
				//前の攻撃がその他だったとき
				else
				{
					g_player[0].SetDownAttack(false);		//ダウン効果を外す
					g_player[0].attack();
					SetPolygon(g_player[0].CheckLeg());
					g_player[0].resetcombo();
					g_player[0].Setcombotime(2.0f);
					g_player[0].SetBeforAttack(PKICK);
					PlaySound(SOUND_LABEL_SE_KICK_MISS);
				}
			}

			//Uで拳強攻撃
			if (Keyboard_IsTrigger(DIK_U))
			{
				g_player[0].SetDownAttack(true);		//ダウン効果を外す
				g_player[0].attack();
				g_player[0].resetcombo();
				g_player[0].SetBeforAttack(PPUNCHSTRONG);
				SetPolygon(g_player[0].CheckArmstrong());
				PlaySound(SOUND_LABEL_SE_PUNCH_MISS);
			}

			//Jで足強攻撃
			if (Keyboard_IsTrigger(DIK_J))
			{
				g_player[0].SetDownAttack(true);		//ダウン効果を外す
				g_player[0].attack();
				g_player[0].resetcombo();
				g_player[0].SetBeforAttack(PKICKSTRONG);
				SetPolygon(g_player[0].CheckLegstrong());
				PlaySound(SOUND_LABEL_SE_KICK_MISS);
			}

			//Nで特殊攻撃
			if (Keyboard_IsTrigger(DIK_N))
			{
				g_player[0].SetDownAttack(true);		//ダウン効果を外す
				g_player[0].attack();
				g_player[0].resetcombo();
				SetBill(g_player[0].CheckPos(),0);		//物を設置
			}
		}
	}

	//2Pの処理を入れる
	switch (GetAI())
	{
	case WAITTIME:
		break;

	case BACKMOVE:
		g_player[1].ChangePos(LEFT, 0, 40.0f);
		break;

	case SEKKINMOVE:
		g_player[1].ChangePos(RIGHT, 0, 40.0f);
		break;

	case PUNCH:
		//コンボが3を超えたら
		if (g_player[1].cooldowncheck() == true)
		{
			if (g_player[1].CheckCombo() > 1)
			{
				g_player[1].SetDownAttack(true);		//ダウン効果を付ける
				g_player[1].attack();
				SetPolygon(g_player[1].CheckLeg());
				g_player[1].resetcombo();
				g_player[1].Setcombotime(2.0f);
				g_player[1].SetBeforAttack(PPUNCH);
				PlaySound(SOUND_LABEL_SE_KICK_MISS);
			}
			else
			{
				g_player[1].SetDownAttack(false);		//ダウン効果を外す
				g_player[1].attack();
				SetPolygon(g_player[1].CheckArm());
				g_player[1].comboup();
				g_player[1].Setcombotime(2.0f);
				g_player[1].SetBeforAttack(PPUNCH);
				PlaySound(SOUND_LABEL_SE_PUNCH_MISS);
			}
		}
		break;

	case KICK:
		if (g_player[1].cooldowncheck() == true)
		{
			if (g_player[1].CheckCombo() > 1)
			{
				g_player[1].SetDownAttack(true);		//ダウン効果を付ける
				g_player[1].attack();
				SetPolygon(g_player[1].CheckLeg());
				g_player[1].resetcombo();
				g_player[1].Setcombotime(2.0f);
				g_player[1].SetBeforAttack(PKICK);
				PlaySound(SOUND_LABEL_SE_KICK_MISS);
			}
			else
			{
				g_player[1].SetDownAttack(false);		//ダウン効果を外す
				g_player[1].attack();
				SetPolygon(g_player[1].CheckLeg());
				g_player[1].comboup();
				g_player[1].Setcombotime(2.0f);
				g_player[1].SetBeforAttack(PKICK);
				PlaySound(SOUND_LABEL_SE_KICK_MISS);
			}
		}
		break;

	case DAMAGED:
		break;

	default:
		break;
	}

	//判定処理
	g_player[0].Update();
	g_player[1].Update();

	//ダメージ
	g_player[0].Setdamage();
	g_player[1].Setdamage();

	//当たり判定
	g_player[0].Colision(g_player[1].GetAttackPattan(), g_player[1].GetAttackpower(), g_player[1].Gethit(),g_player[1].GetDownAttack(),false,0,g_player[1].GetBeforAttack());
	g_player[1].Colision(g_player[0].GetAttackPattan(), g_player[0].GetAttackpower(), g_player[0].Gethit(), g_player[0].GetDownAttack(),false,0, g_player[0].GetBeforAttack());

	//当たり判定(遠距離攻撃)
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (GetBulletUse(i) == true)
		{
			g_player[0].Colision(GetBulletPos(i), 100, true, false,true,i, g_player[1].GetBeforAttack());
			g_player[1].Colision(GetBulletPos(i), 100, true, false,true,i, g_player[0].GetBeforAttack());
		}
	}

	//プレイヤーとプレイヤーを向き合わせる
	g_player[0].UpdateRot(g_player[1].CheckPos());		//1Pのみにつける (2Pにもつけるとバグる)
	g_player[1].SetRot(g_player[0].CheckRot());			//1Pの方向に向かせたいキャラにつける

}

//=============================================================================
// 描画処理
//=============================================================================
void Player_Draw(void)
{
	for (int i = 0; i < MAX_PLAYER ; i++)
	{
		LPDIRECT3DDEVICE9 static pDevice = GetD3DDevice();
		D3DXMATRIX static mtxScl, mtxRot, mtxTranslate;
		D3DXVECTOR3 plscl, plpos, plrot;

		//プレイヤーの大きさ、座標、角度を受けとる
		plscl = g_player[i].CheckScl();
		plpos = g_player[i].CheckPos();
		plrot = g_player[i].CheckRot();

		//ワールドマトリクスの初期化
		D3DXMatrixIdentity(&g_mtxWorldField);

		//スケールを反映
		D3DXMatrixScaling(&mtxScl, plscl.x, plscl.y, plscl.z);
		D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxScl);

		//回転を反映(回転させるときはいっぺんに回転させるとよくない)
		D3DXMatrixRotationYawPitchRoll(&mtxRot, plrot.y, plrot.x, plrot.z);
		D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);
		//いっぺんに回転させるときはクォータニオンを使う

		//移動を反映
		D3DXMatrixTranslation(&mtxTranslate, plpos.x, plpos.y, plpos.z);
		D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTranslate);

		//ワールドマトリクスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldField);

		//ヒトの表示
		Xfile_Draw(g_player[i].CheckScl(), g_player[i].CheckPos(), g_player[i].CheckRot()/ -55, HUMAN);

		
	}
}

//=============================================================================
// プレイヤーの回転を受け取る
//=============================================================================
D3DXVECTOR3 GetRot(int index)
{
	return g_player[index].CheckRot();
}

D3DXVECTOR3 GetPos(int index)
{
	return g_player[index].CheckPos();
}

int GetHp(int index)
{
	return g_player[index].CheckHp();
}