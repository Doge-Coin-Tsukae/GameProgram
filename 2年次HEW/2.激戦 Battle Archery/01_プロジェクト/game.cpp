#include "bullet.h"
#include "camera.h"
#include "debugproc.h"
#include "fade.h"
#include "field.h"
#include "input.h"
#include "light.h"
#include "myDirect3D.h"
#include "number.h"
#include "object.h"
#include "player.h"
#include "point.h"
#include "result.h"
#include "scene.h"
#include "score_draw.h"
#include "sound.h"
#include "shadow.h"
#include "sprite.h"
#include "saku.h"
#include "saku_yoko.h"
#include "target.h"
#include "texture.h"
#include <time.h>
#include "countdown_draw.h"
#include "piller.h"
#include "wall.h"
#include "wall_tate.h"
#include "particle.h"
#include "table.h"
#include "xfile.h"

#define TIMELIMIT (50000)		//制限時間 (1000=1秒)
#define COUNTDOWNTV	(240)		//ゲームがスタートするまでの時間
#define GETCOUNT (15)			//一フレームで進む秒数	

typedef enum PHASE_INDEX
{
	PHASE_INDEX_FADE,
	PHASE_INDEX_PLAYER_IN,

	PHASE_INDEX_STAGE_CLEAR,
	PHASE_INDEX_END,

	PHASE_INDEX_MAX
};

static PHASE_INDEX g_Phase;

//クラス
class GAMEMANAGEMENT
{
private:
	int g_time;			//制限時間
	int g_count;			//1フレームの時間
	int countdown;		//カウントダウン
	int animepattan;		//アニメパターン
	bool EndFlag;		//ゲームが終了したかのフラグ

public:

	//コンストラクタ
	GAMEMANAGEMENT()
	{
		//変数の初期化
		g_time = TIMELIMIT;
		g_count = GETCOUNT;
		countdown = 0;
		animepattan = 0;
		EndFlag = false;
	}

	//デストラクタ
	~GAMEMANAGEMENT()
	{
		//変数の初期化
		g_time = 0;
		g_count = 0;
		countdown = 0;
		animepattan = 0;
		EndFlag = false;
	}

	//ゲームの開始処理
	void Game_Initialize()
	{
		// ライトの初期化処理
		Light_Initialize();

		//影の初期化処理
		Shadow_Initialize();

		// 地面の初期化処理
		Field_Initialize();

		//プレイヤーの初期処理
		Player_Initialize();

		//弾の初期処理
		Bullet_Initialize();

		//壁の初期処理
		Object_Initialize();

		//照準の初期処理
		Point_Initialize();

		//的の初期処理
		Target_Initialize();

		//柱の初期処理
		Piller_Initialize();

		//柵(縦)の初期処理
		Saku_Initialize();

		//柵(横)の初期処理
		SakuYoko_Initialize();

		//壁の当たり判定(横)の初期処理
		Wall_Initialize();

		//壁の当たり判定(縦)の初期処理
		WallTate_Initialize();

		//スコアの初期処理
		Score_Init();

		// カメラの初期化処理
		Camera_Initialize();

		//パーティクルの初期化処理
		InitParticle();


		//ゲーム開始時、画面から消えているので一回描画処理を行う
		Object_Update();
		Object_Draw();
	}

	//ゲームの終了処理
	void Game_Finalize()
	{
		//パーティクルの終了処理
		UninitParticle();

		//影の終了処理
		Shadow_Finalize();

		// カメラの終了処理
		Camera_Finalize();

		// ライトの終了処理
		Light_Finalize();

		// 地面の終了処理
		Field_Finalize();

		//プレイヤーの終了処理
		Player_Finalize();

		//弾の終了処理
		Bullet_Finalize();

		//照準の終了処理
		Point_Initialize();

		//壁の終了処理
		Object_Finalize();

		Piller_Finalize();

		Saku_Finalize();

		SakuYoko_Finalize();

		//壁の当たり判定(横)の終了処理
		Wall_Finalize();

		//壁の当たり判定(縦)の終了処理
		WallTate_Finalize();

		//的の終了処理
		Target_Finalize();
	}

	//ゲームの更新処理
	void Game_Update()
	{
		//ゲーム開始しているか
		if (countdown >= COUNTDOWNTV)
		{
			// カメラの更新処理
			Camera_Update();

			// ライトの更新処理
			Light_Update();

			//制限時間の更新処理
			g_time = g_time - g_count;

			// 地面の更新処理
			Field_Update();

			//プレイヤーの更新処理
			Player_Update();

			//照準の更新処理
			Point_Update();

			//的の更新処理
			Target_Update();

			//弾の更新処理
			Bullet_Update();

			//壁の更新処理
			Object_Update();

			Piller_Update();

			Saku_Update();

			SakuYoko_Update();

			Shadow_Update();

			// パーティクル処理の更新
			UpdateParticle();

			//壁の当たり判定(横)の更新処理
			Wall_Update();

			//壁の当たり判定(縦)の更新処理
			WallTate_Update();

			//ゲームの終了チェック
			if (Game_EndCheck())
			{
				Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
				g_Phase = PHASE_INDEX_STAGE_CLEAR;
			}
		}
		//まだ開始していないとき
		else
		{
			countdown++;

			//1秒おきにカウントの音を鳴らす
			switch (countdown)
			{
			case 60:
				PlaySound(SOUND_LABEL_SE_GIRL_COUNT_3);
				break;
			case 120:
				animepattan++;
				PlaySound(SOUND_LABEL_SE_GIRL_COUNT_2);
				break;
			case 180:
				animepattan++;
				PlaySound(SOUND_LABEL_SE_GIRL_COUNT_1);
				break;
			case COUNTDOWNTV:
				PlaySound(SOUND_LABEL_SE_GIRL_COUNT_GO);
				break;
			}
		}

		if (countdown >= COUNTDOWNTV && countdown <= COUNTDOWNTV + 100)
		{
			countdown++;
		}
	}

	//ゲームの描画処理
	void Game_Draw(int i)
	{
		// カメラの設定
		Camera_SetCamera(i);

		// 地面の描画処理
		Field_Draw();

		//影の描画処理
		Shadow_Draw();

		//プレイヤーの描画処理
		Player_Draw();

		//弾の描画処理
		Bullet_Draw();

		//壁の描画処理
		Object_Draw();

		//的の描画処理
		Target_Draw();

		//柱の描画処理
		Piller_Draw();

		//柵(縦)の描画処理
		Saku_Draw();

		//柵(横)の描画処理
		SakuYoko_Draw();

		//壁の当たり判定(横)の当たり判定
		Wall_Draw();

		//壁の当たり判定(縦)の当たり判定
		WallTate_Draw();



		/*画面に張り付けるものは後で描画する(Zソート)*/

		// パーティクル処理の描画
		DrawParticle(i);

		//照準の描画処理
		Point_Draw();

		//制限時間の描画処理
		Timelimit_Draw(700 + (1600 * i), 10, g_time / 1000, 3, true);

		//スコアの描画処理(1P = 0)
		Score_Draw(0 + (1540 * i), 10, 0, 3, true, 0, 32 - (i * 32));

		//スコアの描画処理(2P = 1)
		Score_Draw(1430 + (1520 * i), 10, 1, 3, true, 1, 0 + (i * 32));

		//弓を引いたときに出るゲージの描画処理
		PlayerScreenDraw();

		//開始するとき、カウントダウンを行う
		if (countdown < COUNTDOWNTV)
		{
			Sprite_Draw(TEXTURE_INDEX_COUNTDOWN,
				640 + (1600 * i),
				200,
				GetAnimTbl(animepattan).x * 256,
				GetAnimTbl(animepattan).y * 256,
				191.66f,
				200,
				16,
				16,
				1.5f,
				1.5f,
				0.0f);
		}
		//スタートを出す
		else if (countdown < COUNTDOWNTV + 100)
		{
			Sprite_Draw(TEXTURE_INDEX_START, 450 + (1600 * i), 300);
		}

		//ゲーム終了時のカウントダウン
		if (g_time < 4000 && g_time > 1000)
		{
			if (g_time < 2000)
			{
				if (animepattan != 2)
				{
					PlaySound(SOUND_LABEL_SE_GIRL_COUNT_1);
					animepattan = 2;
				}
			}
			else if (g_time < 3000)
			{
				if (animepattan != 1)
				{
					PlaySound(SOUND_LABEL_SE_GIRL_COUNT_2);
					animepattan = 1;
				}
			}
			else
			{
				if (animepattan != 0)
				{
					PlaySound(SOUND_LABEL_SE_GIRL_COUNT_3);
					animepattan = 0;
				}
			}

			//画面に表示
			Sprite_Draw(TEXTURE_INDEX_COUNTDOWN,
				640 + (1600 * i),
				200,
				GetAnimTbl(animepattan).x * 256,
				GetAnimTbl(animepattan).y * 256,
				191.66f,
				200,
				16,
				16,
				1.5f - (g_time / 5000.0f),
				1.5f - (g_time / 5000.0f),
				0.0f);

		}

		//タイムアップの描画処理
		if (g_time <= 1000)
		{
			Sprite_Draw(TEXTURE_INDEX_TIMEUP, 450 + (1600 * i), 300);

		}

		//タイムアップ音声を鳴らす
		if (g_time <= 900 && EndFlag == false)
		{
			PlaySound(SOUND_LABEL_SE_GIRL_TIME_UP);
			EndFlag = true;
		}

		// フェードの描画
		Fade_Draw();

		/*Zソートここまで*/



	}

	//ゲームの終了の確認
	bool Game_EndCheck(void)
	{
		//制限時間を超えたら終了
		if (g_time <= 0)
		{
			return true;
		}

		return false;
	}
};

GAMEMANAGEMENT *m_game; //クラスの定義


//ゲームの初期処理
void Game_Initialize(void)
{
	//クラスの初期化
	m_game = new GAMEMANAGEMENT;

	//xファイルの読み込み
	for (int i = 0; i < HUMAN_KOR + 1; i++)
	{
		SetXfile(i);
	}

	//画像のセット
	SetTexture(TEXTURE_INDEX_COUNTDOWN);
	SetTexture(TEXTURE_INDEX_START);
	SetTexture(TEXTURE_INDEX_TIMEUP);
	SetTexture(TEXTURE_INDEX_NUMBER);
	SetTexture(TEXTURE_INDEX_NUMBER_RED);
	SetTexture(TEXTURE_INDEX_NUMBER_BLUE);
	SetTexture(TEXTURE_INDEX_ARROWPOWERBOX_BAR);
	SetTexture(TEXTURE_INDEX_ARROWPOWER_BAR);

	//音楽を付ける
	PlaySound(SOUND_LABEL_WEATHER_1_BGM);
	PlaySound(SOUND_LABEL_WEATHER_2_BGM);

	g_Phase = PHASE_INDEX_FADE;
	
	//ゲームで使う関数の初期処理
	m_game->Game_Initialize();

	Fade_Start(false, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
}

//ゲームの終了処理
void Game_Finalize(void)
{
	//BGMを止める
	StopSound(SOUND_LABEL_WEATHER_1_BGM);
	StopSound(SOUND_LABEL_WEATHER_2_BGM);

	//画像の解放
	ReleaseTexture(TEXTURE_INDEX_COUNTDOWN);
	ReleaseTexture(TEXTURE_INDEX_START);
	ReleaseTexture(TEXTURE_INDEX_TIMEUP);
	ReleaseTexture(TEXTURE_INDEX_NUMBER);
	ReleaseTexture(TEXTURE_INDEX_NUMBER_RED);
	ReleaseTexture(TEXTURE_INDEX_NUMBER_BLUE);
	ReleaseTexture(TEXTURE_INDEX_ARROWPOWERBOX_BAR);
	ReleaseTexture(TEXTURE_INDEX_ARROWPOWER_BAR);

	//Xファイルの解放
	for (int i = 0; i < HUMAN_KOR + 1; i++)
	{
		ReleaseXfile(i);
	}

	//ゲームで使う関数の終了処理
	m_game->Game_Finalize();

	//クラスの解放
	delete m_game;
}

//ゲームの更新処理
void Game_Update(void)
{
	//フェードの形態で変わる
	switch (g_Phase)
	{
	case PHASE_INDEX_FADE:
		if (!Fade_IsFade()) {
			g_Phase = PHASE_INDEX_PLAYER_IN;
			// PlaySound(SOUND_LABEL_BGM000);
		}
		break;
	case PHASE_INDEX_PLAYER_IN:
		m_game->Game_Update();
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

//ゲームの描画処理
void Game_Draw(void)
{
	//プレイヤー分ループ
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		m_game->Game_Draw(i);
	}
}