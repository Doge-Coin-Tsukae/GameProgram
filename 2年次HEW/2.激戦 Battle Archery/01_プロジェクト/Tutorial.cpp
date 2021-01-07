#include "bullet.h"
#include "camera.h"
#include "fade.h"
#include "field.h"
#include "input.h"
#include "light.h"
#include "myDirect3D.h"
#include "object.h"
#include "player.h"
#include "piller_tutorial.h"
#include "point.h"
#include "particle.h"
#include "scene.h"
#include "sound.h"
#include "sprite.h"
#include "shadow.h"
#include "target_tutorial.h"
#include "saku.h"
#include "saku_yoko.h"
#include "wall_tutorial.h"
#include "wall_tate_tutorial.h"
#include "xfile.h"
#include "selectcharctor.h"
#include "x_gamepad.h"

typedef enum PHASE_INDEX
{
	PHASE_INDEX_FADE,
	PHASE_INDEX_PLAYER_IN,

	PHASE_INDEX_STAGE_CLEAR,
	PHASE_INDEX_END,

	PHASE_INDEX_MAX
};

static PHASE_INDEX g_Phase;

static bool Game_EndCheck(void);

void Tutorial_Initialize(void)
{
	//xファイルの読み込み
	for (int i = 0; i < HUMAN_KOR + 1; i++)
	{
		SetXfile(i);
	}

	//アニメーション付きXファイルの読み込み
	for (int i = 0; i < 2; i++)
	{
		SetAnimationXfile(i,10);
	}
	

	SetTexture(TEXTURE_INDEX_ARROWPOWERBOX_BAR);
	SetTexture(TEXTURE_INDEX_ARROWPOWER_BAR);
	SetTexture(TEXTURE_INDEX_EXPLAIN);

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
	Target_Tutorial_Initialize();

	Piller_Tutorial_Initialize();

	Wall_Tutorial_Initialize();

	WallTate_Tutorial_Initialize();

	Saku_Initialize();

	SakuYoko_Initialize();

	// カメラの初期化処理
	Camera_Initialize();

	//パーティクルの初期化処理
	InitParticle();

	PlaySound(SOUND_LABEL_WEATHER_1_BGM);
	PlaySound(SOUND_LABEL_WEATHER_2_BGM);

	g_Phase = PHASE_INDEX_FADE;

	Fade_Start(false, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void Tutorial_Finalize(void)
{
	//Xファイルの解放
	for (int i = 0; i < HUMAN_KOR + 1; i++)
	{
		ReleaseXfile(i);
	}

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

	Piller_Tutorial_Finalize();

	Saku_Finalize();

	SakuYoko_Finalize();

	//壁の当たり判定(横)の終了処理
	Wall_Tutorial_Finalize();

	WallTate_Tutorial_Finalize();

	//的の終了処理
	Target_Tutorial_Finalize();

	ReleaseTexture(TEXTURE_INDEX_EXPLAIN);
	ReleaseTexture(TEXTURE_INDEX_ARROWPOWERBOX_BAR);
	ReleaseTexture(TEXTURE_INDEX_ARROWPOWER_BAR);

	StopSound(SOUND_LABEL_WEATHER_1_BGM);
	StopSound(SOUND_LABEL_WEATHER_2_BGM);

}

void Tutorial_Update(void)
{
	switch (g_Phase)
	{
	case PHASE_INDEX_FADE:
		if (!Fade_IsFade()) {
			g_Phase = PHASE_INDEX_PLAYER_IN;
			// PlaySound(SOUND_LABEL_BGM000);
		}
		break;
	case PHASE_INDEX_PLAYER_IN:
		// カメラの更新処理
		Camera_Update();

		// ライトの更新処理
		Light_Update();
		// 地面の更新処理
		Field_Update();

		//プレイヤーの更新処理
		Player_Update();

		//照準の更新処理
		Point_Update();

		//的の更新処理
		Target_Tutorial_Update();

		//弾の更新処理
		Bullet_Update();

		Piller_Tutorial_Update();

		//壁の更新処理
		Object_Update();

		Shadow_Update();

		// パーティクル処理の更新
		UpdateParticle();

		Saku_Update();

		SakuYoko_Update();

		//壁の当たり判定(横)の更新処理
		Wall_Tutorial_Update();

		WallTate_Tutorial_Update();

		//ゲームの終了チェック
		if (Game_EndCheck())
		{
			Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_Phase = PHASE_INDEX_STAGE_CLEAR;
		}

		break;

	case PHASE_INDEX_STAGE_CLEAR:
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_2PGAME);
			g_Phase = PHASE_INDEX_END;
		}
		break;
	case PHASE_INDEX_END:
		break;
	}
}

void Tutorial_Draw(void)
{

	//プレイヤー分ループ
	for (int i = 0; i < MAX_PLAYER; i++)
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

		//的の描画処理
		Target_Tutorial_Draw();

		Piller_Tutorial_Draw();

		//壁の描画処理
		Object_Draw();

		Saku_Draw();

		SakuYoko_Draw();

		//壁の当たり判定(横)の当たり判定
		Wall_Tutorial_Draw();

		WallTate_Tutorial_Draw();

		/*画面に張り付けるものは後で描画する(Zソート)*/

		// パーティクル処理の描画
		DrawParticle(i);

		Sprite_Draw(TEXTURE_INDEX_EXPLAIN, 70.0f + (1530.0f *i), 0.0f);

		//弓を引いたときに出るゲージの描画処理
		PlayerScreenDraw();

		//照準の描画処理
		Point_Draw();

		// フェードの描画
		Fade_Draw();

		/*Zソートここまで*/
	}
}

bool Game_EndCheck(void)
{
	//制限時間を超えたら終了
	if (Keyboard_IsPress(DIK_Q) || gamepad_inport(0, PP_START) || gamepad_inport(1, PP_START))
		return true;

	return false;
}