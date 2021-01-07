#include "input.h"
#include "scene.h"
#include "sprite.h"
#include "sound.h"
#include "texture.h"
#include "fade.h"

//グローバル変数宣言
static bool won;

//リザルト画面の初期処理
void Result_Initialize(void)
{
	Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
}

//リザルト画面の終了処理
void Result_Finalize(void)
{
}

//リザルト画面の更新処理
void Result_Update(void)
{
	//スペースキーを押したときにタイトル画面に戻る & クリック音を鳴らす
	if( Keyboard_IsTrigger(DIK_SPACE) ) {
		PlaySound(SOUND_LABEL_SE_CLICK);
		Scene_Change(SCENE_INDEX_TITLE);
	}
}

//リザルト画面の描画処理
void Result_Draw(void)
{
	//このゲームに勝利していたとき勝ったときの画像を読む
	if (won == true) {
		Sprite_Draw(TEXTURE_INDEX_WIN, 0.0f, 0.0f);
	}
	//敗北したときの画像を読む
	else
	{
		Sprite_Draw(TEXTURE_INDEX_RESULT, 0.0f, 0.0f);
	}
}

//勝ちフラグを建てる
void Wewon()
{
	won = true;
}

//勝ちフラグを消す(負けさせる)
void Welose()
{
	won = false;
}