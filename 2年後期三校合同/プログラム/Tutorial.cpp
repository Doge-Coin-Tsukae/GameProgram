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
#include "bullet.h"
#include "billboard.h"
#include <time.h>

PHASE_INDEX static g_Phase;

void Tutorial_Initialize(void)
{
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

	SetAImode(WAITTIME);

	//プレイヤーの初期処理
	Player_Initialize();

	//壁の初期処理
	Object_Initialize();

	//Human_Initialize();

	Coli_Initialize();

	Screendraw_Initialize();

	// カメラの初期化処理
	Camera_Initialize();

	PlaySound(SOUND_LABEL_TUTORIAL_BGM);

	g_Phase = PHASE_INDEX_FADE;

	Fade_Start(false, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void Tutorial_Finalize(void)
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

	Human_Finalize();

	//ピルボードの終了処理
	Billboard_Finalize();

	//弾の終了処理
	Bullet_Finalize();

	Shadow_Finalize();

	StopSound(SOUND_LABEL_TUTORIAL_BGM);

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

		//壁の更新処理
		Object_Update();

		Shadow_Update();

		Bullet_Update();

		Billboard_Update();

		Screendraw_Update();

		//チュートリアルを終了させる
		if (Keyboard_IsPress(DIK_Q))
		{
			Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_Phase = PHASE_INDEX_STAGE_CLEAR;
		}

		break;
	case PHASE_INDEX_STAGE_CLEAR:
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_GAME);
			g_Phase = PHASE_INDEX_END;
		}
		break;
	case PHASE_INDEX_END:
		break;
	}
}

void Tutorial_Draw(void)
{// カメラの設定
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

	Shadow_Draw();

	Screendraw_Draw();

	Sprite_Draw(TEXTURE_INDEX_TUTORIAL, 0.0f, 100.0f);
	/*Zソートここまで*/
}
