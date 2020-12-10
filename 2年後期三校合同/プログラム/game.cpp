#include "camera.h"
#include "debugproc.h"
#include "fade.h"
#include "field.h"
#include "input.h"
#include "light.h"
#include "myDirect3D.h"
#include "number.h"
#include "game.h"
#include "object.h"
#include "player.h"
#include "result.h"
#include "sound.h"
#include "scene.h"
#include "sprite.h"
#include "texture.h"
#include "human.h"
#include "colision.h"
#include "screendraw.h"
#include "shadow.h"
#include "billboard.h"
#include "bullet.h"
#include "result.h"
#include <time.h>

PHASE_INDEX static g_Phase;

bool Deathflag;					//どっちか死んだか
float Deathtime;				//死亡してからの時間をカウントする
int g_gameset[MAX_PLAYER];		//取ったセット数を入れる
int countdown;					//ゲームが始まるカウントダウン

//プロトタイプ宣言
bool Game_EndCheck(void);

void Game_Initialize(void)
{

	Deathflag = false;
	Deathtime = 0.0f;
	countdown = 0;

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_gameset[i] = 0;
	}

	// ライトの初期化処理
	Light_Initialize();

	//影の初期処理(使うものの前に入れること)
	Shadow_Initialize();

	//ビルポートの初期化処理
	Billboard_Initialize();

	//弾の初期化処理
	Bullet_Initialize();

	// 地面の初期化処理
	Field_Initialize();

	//プレイヤーの初期処理
	Player_Initialize();

	//壁の初期処理
	Object_Initialize();

	Human_Initialize();
	
	Coli_Initialize();

	Screendraw_Initialize();

	// カメラの初期化処理
	Camera_Initialize();

	PlaySound(SOUND_LABEL_BATTLE_BGM);

	g_Phase = PHASE_INDEX_FADE;
	
	Fade_Start(false, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void Game_Finalize(void)
{
	// カメラの終了処理
	Camera_Finalize();

	Screendraw_Finalize();

	// ライトの終了処理
	Light_Finalize();

	// 地面の終了処理
	Field_Finalize();

	//プレイヤーの終了処理
	Player_Finalize();

	//壁の終了処理
	Object_Finalize();

	//AIの終了処理
	Human_Finalize();

	//ピルボードの終了処理
	Billboard_Finalize();

	//弾の終了処理
	Bullet_Finalize();

	//影の終了処理
	Shadow_Finalize();

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_gameset[i] = 0;
	}
}

void Game_Update(void)
{
	switch (g_Phase)
	{
	case PHASE_INDEX_FADE:
		if (!Fade_IsFade()) {
			g_Phase = PHASE_INDEX_PLAYER_IN;
		}
		break;
	case PHASE_INDEX_PLAYER_IN:
		if (countdown >= 120)
		{
			// カメラの更新処理
			Camera_Update();

			// ライトの更新処理
			Light_Update();

			// 地面の更新処理
			Field_Update();

			//プレイヤーの更新処理
			Player_Update();

			//壁の更新処理
			Object_Update();

			//AIの更新処理
			Human_Update();

			//影の更新処理
			Shadow_Update();

			Bullet_Update();

			Billboard_Update();

			//画面に張り付ける物の更新処理
			Screendraw_Update();

			if (Deathflag == true)
			{
				Deathtime -= 0.1f;
				if (Deathtime <= 0.0f)
				{
					Deathflag = false;
					countdown = 0;
					//ゲームの終了チェック
					if (Game_EndCheck())
					{
						StopSound(SOUND_LABEL_BATTLE_BGM);
						Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
						g_Phase = PHASE_INDEX_STAGE_CLEAR;
					}
					Player_Finalize();
					//プレイヤーの初期処理
					Player_Initialize();
					Camera_Initialize();

				}
			}
		}
		else
		{
			if (countdown== 0 || countdown == 40 || countdown == 80)
			{
				PlaySound(SOUND_LABEL_SE_POINT_COUNT);
			}
			else if (countdown == 119)
			{
				PlaySound(SOUND_LABEL_SE_POINT_COUNT_GO);
			}
			countdown++;
		}
		break;
	case PHASE_INDEX_STAGE_CLEAR:
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_RESULT);
			g_Phase = PHASE_INDEX_END;
		}
		break;
	case PHASE_INDEX_END:
		break;
	}
}

void Game_Draw(void)
{
		// カメラの設定
		Camera_SetCamera(0);

		// 地面の描画処理
		Field_Draw();

		//プレイヤーの描画処理
		Player_Draw();
		//壁の描画処理
		Object_Draw();

		Coli_Draw();

		Bullet_Draw();

		//ビルボードの描画処理
		Billboard_Draw();

		/*画面に張り付けるものは後で描画する(Zソート)*/
		// フェードの描画
		Fade_Draw();

		//影の描画処理
		Shadow_Draw();

		Screendraw_Draw();
		/*Zソートここまで*/
}

//ゲームを終了するかの関数
bool Game_EndCheck(void)
{
	//どちらかのプレイヤーが2セット取ったら終わる
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (g_gameset[i] >= 2)
		{
			SetResultFlag(i);
			return true;
		}
	}

	return false;
}

//得点を１加える
void SetGameSet(int index)
{
	g_gameset[index] += 1;
}

//死亡フラグを建てて次のセットに行くまでの時間を計測
void SetDeathflag(void)
{
	Deathflag = true;	//フラグをたてる
	Deathtime = 9.0f;	//時間のセット
}

//セット数のゲッター
int GetSetCount(int index)
{
	return g_gameset[index];
}