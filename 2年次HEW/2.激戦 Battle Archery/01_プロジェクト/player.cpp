//==============================================================================
// File name / type  :  player.cpp
//  Private number   :  [HEW2019 project] - groupNo.3 
// Writer copyright  :  (C) HEW2019 project group All rights reserved.
//==============================================================================

//****************************************************
//プレイヤー関係のプログラム
//****************************************************


#include "bullet.h"
#include "colision.h"
#include "camera.h"
#include "field.h"
#include "input.h"
#include "myDirect3D.h"
#include "object.h"
#include "particle.h"
#include "player.h"
#include "piller.h"
#include "piller_tutorial.h"
#include "point.h"
#include "sound.h"
#include "selectcharctor.h"
#include "shadow.h"
#include "score_draw.h"
#include "saku.h"
#include "saku_yoko.h"
#include "texture.h"
#include "wall.h"
#include "wall_tutorial.h"
#include "wall_tate.h"
#include "wall_tate_tutorial.h"
#include "xfile.h"
#include "x_gamepad.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_ROTATE	(1.0f)				// 回転量
#define MAX_POWER		(100.0f)			// パワーの上限

#define INIT_PLAYERONE_POS  D3DXVECTOR3(0.0f,0.0f,2000.0f)
#define INIT_PLAYERTWO_POS  D3DXVECTOR3(0.0f,0.0f,-2000.0f)
#define INIT_PLAYERONE_ROT  D3DXVECTOR3(0.0f, 270.0f, 0.0f)
#define INIT_PLAYERTWO_ROT  D3DXVECTOR3(0.0f, 90.0f, 0.0f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXMATRIX				static g_mtxWorldField;		// ワールドマトリックス(行列)

//*****************************************************************************
//enum
//*****************************************************************************
enum ANIMEPATAN
{	
	WAIT,
	WALK,
	ATTACK,
	ANIMATION_MAX,
};


//*****************************************************************************
//クラス
//*****************************************************************************

class player {

private:
	D3DXVECTOR3		PosPlayer;				//プレイヤーのポジション
	D3DXVECTOR3		RotPlayer;				// プレイヤーの向き(回転)
	D3DXVECTOR3		SclPlayer;				//プレイヤーの大きさ
	D3DXVECTOR3		Dir;					//プレイヤーの行き先

	int				playercolor;			//プレイヤーの国籍
	int				idxShadow;				//シャドウID

	float			speed;					//プレイヤーの速度
	float			power;					//力の大きさ
	float			CoolTime;				//弾の残心時間
	float			fly;					//滞空時間
	float			jump;					//ジャンプ時間
	bool			CoolDown;				//弾を放ったばかりか
	bool			Attacktime;				//今弓を引いているか

public:

	//プレイヤーの初期処理(初期座標,初期回転数)
	void PlayerInit(D3DXVECTOR3 IniPos, D3DXVECTOR3 IniRot,int index)
	{
		PosPlayer = IniPos;		//初期座標
		RotPlayer = IniRot;			//初期回転
		SclPlayer = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			//初期大きさ
		Dir = PosPlayer;									//仮定の行き先をプレイヤーと同じに

		idxShadow = Shadow_Create(PosPlayer, D3DXVECTOR3(1.0f, 1.0f, 1.0f));		//影のIdセット
		speed = 12.5f;										//プレイヤーの素早さ
		power = 0.0f;										//力リセット
		fly = 0.0f;
		jump = 0.0f;
		playercolor = HUMAN_JPN + GetCharaData(index);	//プレイヤーの座標を入れる
		CoolDown = false;		//弾を打てる状態にする
		Attacktime = false;		//弓を引いていない状況にする
	}

	void PlayerFinalize()
	{
		Shadow_Release(idxShadow);
	}

	//座標の変更(方向(enum),方向(0.0f,0.2f,0.5f,0.75f,1.0f))
	void ChangePos(int xyzpm ,int i)
	{

		switch (xyzpm) {
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

			//宙に浮く
		case FLY:
			fly = 300.0f;
			break;

			//宙に浮く
		case JUMP:
			jump = 20.0f;
			break;

			//重力に引っ張られる
		case GRAVITY:
			Dir.y += fly;
			Dir.y += jump;
			//地面よりもy座標が低かったら
			if (PosPlayer.y <= FIELD_HIGHT)
			{
				PosPlayer.y = FIELD_HIGHT;	//地面と同じ位置に
				fly = 0.0f;					//飛ばなくする
				jump = 0.0f;
			}
			else
			{
				fly -= 1.0f;
				jump = 0.0f;
			}
			break;

			//それ以外
		default:
			break;
		}

		//壁・背景・柱の当たり判定
		if ((CheckHitPlayer_vs_Wall(Dir) == false) && (CheckHitPlayer_vs_WallTate(Dir) == false) && 
			(CheckHitPlayer_vs_Saku(Dir) == false) && (CheckHitPlayer_vs_SakuYoko(Dir) == false) &&
			(CheckHitPlayer(Dir) == false) && (CheckHitPlayer_vs_PILLER(Dir) == false) && 
			(CheckHitPlayer_vs_WallTutorial(Dir) == false) && (CheckHitPlayer_vs_WallTateTutorial(Dir) == false) &&
			(CheckHitPlayer_vs_PillerTutorial(Dir) == false))
		{
			Hitcamera(false, i);
			PosPlayer = Dir;
		}

		else
		{
			Hitcamera(true, i);
			Dir = PosPlayer;
		}
	}

	//力を籠める
	void PowerUp(int index)
	{
		if (power < MAX_POWER)
		{
			power += 1.5f;
		}
		else
		{
			StopAnimation(index);
		}
	}

	//弓を発射する体制にする (true=発射体制, false=発射後の体制)
	void changeAttackMode(bool index)
	{
		Attacktime = index;
	}

	//弾発射のクールタイムを有効にする (矢を発射後のプレイヤー処理)
	void CoolDownEnabled()
	{
		CoolTime = 5.0f;
		CoolDown = true;
		power = 1.0f;
	}

	//クールタイムを無効にする&減らす
	void CoolDownDisabled()
	{
		if (CoolTime <= 0.0f)
		{
			CoolTime = 0.0f;
			CoolDown = false;
		}
		CoolTime -= 0.1f;
	}

	//プレイヤーに相手の弾がヒットしたときknockbackさせる
	void knockback(int index)
	{
		//全弾の判定
		for (int i = 0; i < BULLET_NUM; i++)
		{
			//弾が使われていて、プレイヤーに命中してて、かつ敵の弾だった場合
			if (CheckHitPlayerToPlayer(GetBulletPos(i), PosPlayer, GetBulletScl(i), GetPlyNum(i), index) == true && GetUse(i) == true)
			{
				//弾が飛んでいるか
				if (GetMove(i)==true)
				{
					DeleteBullet(i);			//該当の弾を削除
					for (int j = 0; j < 10; j++)
					{
						PlaySound(SOUND_LABEL_SE_PLAYER_HIT);
						ChangePos(DOWN, 0);			//後ろに下がる
						ChangePos(FLY, 0);
						changecamera(DOWN, index, speed);		//カメラも一緒に
					}
					ParticleSetNum(10, GetBulletPos(i), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 30.0f, 30.0f, 60, 0);
				}

			}
		}
	}

	//指定した値の数だけ回転に加える
	D3DXVECTOR3 AddRot(D3DXVECTOR3 index)
	{
		if (RotPlayer.y >= 360.0f)
		{
			RotPlayer.y = 0.0f;
		}
		if (RotPlayer.y < -0.9f)
		{
			RotPlayer.y = 359.0f;
		}

		return RotPlayer += index;
	}

	/*ゲッター*/
	
	//クールダウンを調べる
	bool CheckCoolDown()
	{
		return CoolDown;
	}

	//現在攻撃姿勢かを調べる
	bool CheckAttackMode()
	{
		return Attacktime;
	}

	//プレイヤーが込めた力を返す
	float CheckPower()
	{
		return power;
	}

	float GetSpeed()
	{
		return  speed;
	}

	int CheckPlayerColor()
	{
		return playercolor;
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

	int GetIdShadow()
	{
		return idxShadow;
	}
	/*ゲッターここまで*/

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
	g_player[0].PlayerInit(INIT_PLAYERONE_POS, INIT_PLAYERONE_ROT,0);		//プレイヤー1の初期処理
	g_player[1].PlayerInit(INIT_PLAYERTWO_POS, INIT_PLAYERTWO_ROT,1);		//プレイヤー2の初期処理

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
	//プレイヤー1
	{
		//プレイヤーが攻撃態勢ではないときのみ移動する
		if (g_player[0].CheckAttackMode() == false)
		{
			//移動処理(左)
			if (Keyboard_IsPress(DIK_A) || gamepad_inport(0, PP_LX) <= -5000)
			{
				if (Keyboard_IsPress(DIK_W) || gamepad_inport(0, PP_LY) >= 10000)
				{// 左奥移動
					g_player[0].ChangePos(LEFTUP, 0);
					changecamera(6, 0, g_player[0].GetSpeed());
					ChangePoint(6, 0, g_player[0].GetSpeed());
				}
				else if (Keyboard_IsPress(DIK_S) || gamepad_inport(0, PP_LY) <= -10000)
				{// 左手前移動
					g_player[0].ChangePos(LEFTDOWN, 0);
					changecamera(7, 0, g_player[0].GetSpeed());
					ChangePoint(7, 0, g_player[0].GetSpeed());
				}
				else
				{// 左移動
					g_player[0].ChangePos(LEFT, 0);
					changecamera(3, 0, g_player[0].GetSpeed());
					ChangePoint(3, 0, g_player[0].GetSpeed());
				}
				ChengeAnimation(0, WALK);
			}

			//移動処理(右)
			else if (Keyboard_IsPress(DIK_D) || gamepad_inport(0, PP_LX) >= 5000)
			{
				if (Keyboard_IsPress(DIK_W) || gamepad_inport(0, PP_LY) >= 10000)
				{// 右奥移動
					g_player[0].ChangePos(RIGHTUP, 0);
					changecamera(4, 0, g_player[0].GetSpeed());
					ChangePoint(4, 0, g_player[0].GetSpeed());
				}
				else if (Keyboard_IsPress(DIK_S) || gamepad_inport(0, PP_LY) <= -10000)
				{// 右手前移動
					g_player[0].ChangePos(RIGHTDOWN, 0);
					changecamera(5, 0, g_player[0].GetSpeed());
					ChangePoint(5, 0, g_player[0].GetSpeed());
				}
				else
				{// 右移動
					g_player[0].ChangePos(RIGHT, 0);
					changecamera(2, 0, g_player[0].GetSpeed());
					ChangePoint(2, 0, g_player[0].GetSpeed());
				}
				ChengeAnimation(0, WALK);
			}

			//前移動
			else if (Keyboard_IsPress(DIK_W) || gamepad_inport(0, PP_LY) >= 10000)
			{// 奥移動
				g_player[0].ChangePos(UP, 0);
				changecamera(0, 0, g_player[0].GetSpeed());
				ChangePoint(0, 0, g_player[0].GetSpeed());
				ChengeAnimation(0, WALK);
			}

			//後ろ移動
			else if (Keyboard_IsPress(DIK_S) || gamepad_inport(0, PP_LY) <= -10000)
			{// 手前移動
				g_player[0].ChangePos(DOWN, 0);
				changecamera(1, 0, g_player[0].GetSpeed());
				ChangePoint(1, 0, g_player[0].GetSpeed());
				ChengeAnimation(0, WALK);
			}

			else 
			{
				ChengeAnimation(0, WAIT);
			}
			// ジャンプ
			/*else if (Keyboard_IsPress(DIK_LSHIFT))
			{
				g_player[0].ChangePos(JUMP, 0);
				g_player[0].ChangePos(GRAVITY, 0);
				changecamera(JUMP, 0, g_player[0].GetSpeed());
				changecamera(GRAVITY, 0, g_player[0].GetSpeed());
			}*/

		}//左に回転
		if (Keyboard_IsPress(DIK_F) || gamepad_inport(0, PP_RX) <= -5000)
		{// Z軸右回転
			g_player[0].AddRot(D3DXVECTOR3(0.0f, VALUE_ROTATE, 0.0f));
			ChangeCamera(0, 0);
			ChangePointAngle(0, 0);
		}

		//右に回転
		if (Keyboard_IsPress(DIK_H) || gamepad_inport(0, PP_RX) >= 5000)
		{// Z軸左回転
			g_player[0].AddRot(D3DXVECTOR3(0.0f, -VALUE_ROTATE, 0.0f));
			ChangeCamera(0, 0);
			ChangePointAngle(0, 0);
		}

		//上キーでカメラを上に向ける
		if (Keyboard_IsPress(DIK_T) || gamepad_inport(0, PP_RY) >= 10000)
		{
			ChangeCameraVer(0, 0);
			ChangePointVer(0, 0);
		}

		//下キーでカメラを下に向ける
		if (Keyboard_IsPress(DIK_G) || gamepad_inport(0, PP_RY) <= -10000)
		{
			ChangeCameraVer(1, 0);
			ChangePointVer(1, 0);
		}

		//スペースを押して力を籠める
		if (Keyboard_IsPress(DIK_SPACE) && g_player[0].CheckCoolDown() == false && g_player[0].CheckAttackMode() == false)
		{
			ChengeAnimation(0, ATTACK);
			PlaySound(SOUND_LABEL_SE_CHARGE);
			g_player[0].changeAttackMode(true);								//攻撃態勢を有効にする
		}

		/*if (gamepad_inport(0, PP_LT) > 250 && g_player[0].CheckCoolDown() == false && g_player[0].CheckAttackMode() == false)
		{
			PlaySound(SOUND_LABEL_SE_CHARGE);
			g_player[0].changeAttackMode(true);
		}*/

		//スペースを離して弾を発射
		if (Keyboard_IsRelease(DIK_SPACE) && g_player[0].CheckAttackMode() == true)
		{
			StopSound(SOUND_LABEL_SE_CHARGE);
			PlaySound(SOUND_LABEL_SE_SHOT);
			//クールダウンが無効だったら
			if (g_player[0].CheckCoolDown() == false)
			{
				SetBullet(g_player[0].CheckPos(), g_player[0].CheckPower(), 0);		//弾を設置する
				g_player[0].CoolDownEnabled();										//弾のクールダウンを有効にする
				g_player[0].changeAttackMode(false);								//攻撃態勢を無効にする
				LoadCameraPos(0);													//ズームを解除する		
			}
		}

		//if (gamepad_inport(0, PP_LT) < 255 && g_player[0].CheckAttackMode() == true)
		//{
		//	StopSound(SOUND_LABEL_SE_CHARGE);
		//	PlaySound(SOUND_LABEL_SE_SHOT);
		//	//クールダウンが無効だったら
		//	if (g_player[0].CheckCoolDown() == false)
		//	{
		//		SetBullet(g_player[0].CheckPos(), g_player[0].CheckPower(), 0);		//弾を設置する
		//		g_player[0].CoolDownEnabled();										//弾のクールダウンを有効にする
		//		g_player[0].changeAttackMode(false);								//攻撃態勢を無効にする
		//		LoadCameraPos(0);													//ズームを解除する		
		//	}
		//}
	}
	//プレイヤー2
	{
		//プレイヤーが攻撃態勢ではないときのみ移動する
		if (g_player[1].CheckAttackMode() == false)
		{
			//移動処理 (左)
			if (Keyboard_IsPress(DIK_J) || gamepad_inport(1, PP_LX) <= -5000)
			{
				if (Keyboard_IsPress(DIK_I) || gamepad_inport(1, PP_LY) >= 10000)
				{// 左奥移動
					g_player[1].ChangePos(LEFTUP, 1);
					changecamera(6, 1, g_player[1].GetSpeed());
					ChangePoint(6, 1, g_player[1].GetSpeed());
				}
				else if (Keyboard_IsPress(DIK_K) || gamepad_inport(1, PP_LY) <= -10000)
				{// 左手前移動
					g_player[1].ChangePos(LEFTDOWN, 1);
					changecamera(7, 1, g_player[1].GetSpeed());
					ChangePoint(7, 1, g_player[1].GetSpeed());
				}
				else
				{// 左移動
					g_player[1].ChangePos(LEFT, 1);
					changecamera(3, 1, g_player[1].GetSpeed());
					ChangePoint(3, 1, g_player[1].GetSpeed());

				}
				ChengeAnimation(1, WALK);
			}

			//移動処理(右)
			else if (Keyboard_IsPress(DIK_L) || gamepad_inport(1, PP_LX) >= 5000)
			{
				if (Keyboard_IsPress(DIK_I) || gamepad_inport(1, PP_LY) >= 10000)
				{
					g_player[1].ChangePos(RIGHTUP, 1);
					changecamera(4, 1, g_player[1].GetSpeed());
					ChangePoint(4, 1, g_player[1].GetSpeed());
				}
				else if (Keyboard_IsPress(DIK_K) || gamepad_inport(1, PP_LY) <= -10000)
				{// 右手前移動
					g_player[1].ChangePos(RIGHTDOWN, 1);
					changecamera(5, 1, g_player[1].GetSpeed());
					ChangePoint(5, 1, g_player[1].GetSpeed());
				}
				else
				{// 右移動
					g_player[1].ChangePos(RIGHT, 1);
					changecamera(2, 1, g_player[1].GetSpeed());
					ChangePoint(2, 1, g_player[1].GetSpeed());
				}
				ChengeAnimation(1, WALK);
			}

			//前移動
			else if (Keyboard_IsPress(DIK_I) || gamepad_inport(1, PP_LY) >= 10000)
			{// 奥移動
				g_player[1].ChangePos(UP, 1);
				changecamera(0, 1, g_player[1].GetSpeed());
				ChangePoint(0, 1, g_player[1].GetSpeed());
				ChengeAnimation(1, WALK);
			}

			//後ろ移動
			else if (Keyboard_IsPress(DIK_K) || gamepad_inport(1, PP_LY) <= -10000)
			{// 手前移動
				g_player[1].ChangePos(DOWN, 1);
				changecamera(1, 1, g_player[1].GetSpeed());
				ChangePoint(1, 1, g_player[1].GetSpeed());
				ChengeAnimation(1, WALK);
			}

			else
			{
				ChengeAnimation(1, WAIT);
			}
		}

		//左に回転
		if (Keyboard_IsPress(DIK_LEFT) || gamepad_inport(1, PP_RX) <= -5000)
		{// Z軸右回転
			g_player[1].AddRot(D3DXVECTOR3(0.0f, VALUE_ROTATE, 0.0f));
			ChangeCamera(1, 1);
			ChangePointAngle(1, 1);
		}

		//右に回転
		if (Keyboard_IsPress(DIK_RIGHT) || gamepad_inport(1, PP_RX) >= 5000)
		{// Z軸左回転
			g_player[1].AddRot(D3DXVECTOR3(0.0f, -VALUE_ROTATE, 0.0f));
			ChangeCamera(1, 1);
			ChangePointAngle(1, 1);
		}

		//上キーでカメラを上に向ける
		if (Keyboard_IsPress(DIK_UP) || gamepad_inport(1, PP_RY) >= 10000)
		{
			ChangeCameraVer(0, 1);
			ChangePointVer(0, 1);
		}

		//下キーでカメラを下に向ける
		if (Keyboard_IsPress(DIK_DOWN) || gamepad_inport(1, PP_RY) <= -10000)
		{
			ChangeCameraVer(1, 1);
			ChangePointVer(1, 1);
		}

		//スペースを押して力を籠める
		if (Keyboard_IsPress(DIK_O) && g_player[1].CheckCoolDown() == false && g_player[1].CheckAttackMode() == false)
		{
			PlaySound(SOUND_LABEL_SE_CHARGE);
			g_player[1].changeAttackMode(true);								//攻撃態勢を有効にする
			ChengeAnimation(1, ATTACK);
		}

		/*if(gamepad_inport(1, PP_LT) > 250 && g_player[1].CheckCoolDown() == false && g_player[1].CheckAttackMode() == false)
		{
			PlaySound(SOUND_LABEL_SE_CHARGE);
			g_player[1].changeAttackMode(true);
		}*/

		//スペースを離して弾を発射
		if (Keyboard_IsRelease(DIK_O) && g_player[1].CheckAttackMode() == true /*|| !GamePad_IsPress(1, BUTTON_M) && g_player.CheckAttackMode() == true*/)
		{
			StopSound(SOUND_LABEL_SE_CHARGE);
			PlaySound(SOUND_LABEL_SE_SHOT);
			//クールダウンが無効だったら
			if (g_player[1].CheckCoolDown() == false)
			{
				SetBullet(g_player[1].CheckPos(), g_player[1].CheckPower(), 1);		//弾を設置する
				g_player[1].CoolDownEnabled();									//弾のクールダウンを有効にする
				g_player[1].changeAttackMode(false);							//攻撃態勢を無効にする
				LoadCameraPos(1);											//ズームを解除する		
			}
		}

		//if(gamepad_inport(1, PP_LT) < 255 && g_player[1].CheckAttackMode() == true)
	//{
	//	StopSound(SOUND_LABEL_SE_CHARGE);
	//	PlaySound(SOUND_LABEL_SE_SHOT);
	//	//クールダウンが無効だったら
	//	if(g_player[1].CheckCoolDown() == false)
	//	{
	//		SetBullet(g_player[1].CheckPos(), g_player[1].CheckPower(), 1);		//弾を設置する
	//		g_player[1].CoolDownEnabled();										//弾のクールダウンを有効にする
	//		g_player[1].changeAttackMode(false);								//攻撃態勢を無効にする
	//		LoadCameraPos(1);													//ズームを解除する		
	//	}
	//}
	}

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		//攻撃態勢の時
		if (g_player[i].CheckAttackMode() == true)
		{
			g_player[i].PowerUp(i);
 			ZoomCamera(i);
		}

		g_player[i].knockback(i);				//弾がプレイヤーにヒットしたとき、ノックバックする
		g_player[i].CoolDownDisabled();			//クールダウンを調べる
		Shadow_SetPosition(g_player[i].GetIdShadow(), g_player[i].CheckPos());		//影の更新処理
		g_player[i].ChangePos(GRAVITY, 0);
	}
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

		//回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, plrot.y, plrot.x, plrot.z);
		D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);

		//移動を反映
		D3DXMatrixTranslation(&mtxTranslate, plpos.x, plpos.y, plpos.z);
		D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTranslate);

		//ワールドマトリクスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldField);

		//弓の表示
		//Xfile_Draw(g_player[i].CheckScl(), g_player[i].CheckPos(), g_player[i].CheckRot() / -55, g_player[i].CheckPlayerColor());
		AnimationXfile_Draw(g_player[i].CheckScl(), g_player[i].CheckPos(), g_player[i].CheckRot() / -55, i);

	}
}

//=============================================================================
// プレイヤーの回転を受け取る
//=============================================================================
D3DXVECTOR3 GetRot(int index)
{
	return g_player[index].CheckRot();
}

//=============================================================================
// プレイヤーの座標を受け取る
//=============================================================================
D3DXVECTOR3 GetPos(int index)
{
	return g_player[index].CheckPos();
}

//調べたい物の座標とブロックの座標との当たり判定(bullet,プレイヤー1)
bool CheckHitPlayerToPlayer(D3DXVECTOR3 Ppos,D3DXVECTOR3 Bullet,D3DXVECTOR3 BulScl,int bulnum,int pnum)
{
	if (Ppos.x >= Bullet.x - (50.0f * BulScl.x) && Ppos.x <= Bullet.x + (50.0f * BulScl.x) &&			//X座標
		Ppos.y >= Bullet.y - (20.0f * BulScl.y) && Ppos.y <= Bullet.y + (150.0f * BulScl.y) &&		//Y座標
		Ppos.z >= Bullet.z - (50.0f * BulScl.z) && Ppos.z <= Bullet.z + (50.0f * BulScl.z) &&			//Z座標
		bulnum!=pnum)
	{
		return true;		//ブロックの判定内にいる
	}

	return false;		//ブロックの判定外にいる
}

//ゲージの表示
void PlayerScreenDraw(void)
{
	for (int i = 0; i<MAX_PLAYER; i++)
	{
		//画面に弓を引いたときに出るゲージ
		if (g_player[i].CheckAttackMode() == true)
		{
			Gauge_Draw(g_player[i].CheckPower(), i);
		}
	}
}