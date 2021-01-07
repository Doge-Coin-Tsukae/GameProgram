#include "input.h"
#include "scene.h"
#include "sprite.h"
#include "texture.h"
#include "fade.h"
#include "result.h"
#include "sound.h"
#include "table.h"

#define ANIME_PATTERN_MAX		11
#define ANIME_PATTERN_SKIPFRAME 8

bool lose;			//負けフラグ
static bool g_bEnd = false;

int			animePattern;	//アニメパターン
int			animeFrame;		//パターン切り替えウエイト

void Result_Initialize(void)
{
	g_bEnd = false;

	Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
	PlaySound(SOUND_LABEL_TUTORIAL_BGM);
}

void Result_Finalize(void)
{
}

void Result_Update(void)
{

	if (!g_bEnd) {
		if (Keyboard_IsTrigger(DIK_SPACE)) {
			StopSound(SOUND_LABEL_TUTORIAL_BGM);
			Fade_Start(true, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_bEnd = true;
		}
	}
	else {
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_TITLE);
		}
	}

	//スキップするフレーム値を超えたら
	if (++animeFrame > ANIME_PATTERN_SKIPFRAME)
	{
		//アニメパターンを進める(最大値を超えたらリセット)
		if (++animePattern >= ANIME_PATTERN_MAX)
			animePattern = 0;
		//フレームは元に戻す
		animeFrame = 0;
	}


}

void Result_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_RESULT, 0, 0);

	//Sprite_Draw(TEXTURE_INDEX_WINNER, SCREEN_WIDTH / 4, 100.0f);
	Sprite_Draw(TEXTURE_INDEX_WINNER,
		SCREEN_WIDTH / 5,
		100.0f,
		GetAnimTbl(animePattern).x * 256,
		GetAnimTbl(animePattern).y * 256,
		600,
		115,
		16,
		16,
		1.5f,
		1.5f,
		0.0f);

	//負けなかったとき(勝ち)
	if (lose == false)
	{
		Sprite_Draw(TEXTURE_INDEX_1P, SCREEN_WIDTH / 2, 300.0f);
	}
	//負けたとき(負け)
	else
	{
		Sprite_Draw(TEXTURE_INDEX_2P, SCREEN_WIDTH / 2, 300.0f);
	}
}

//負けフラグを入れる
void SetResultFlag(bool flag)
{
	lose = flag;
}