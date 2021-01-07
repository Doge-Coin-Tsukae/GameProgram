#include "sprite.h"
#include "texture.h"
#include "player.h"
#include "game.h"

float Hp[MAX_PLAYER];

void Screendraw_Initialize(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		Hp[i] = GetHp(i);
		Hp[i] /= MAX_HP;
	}
}


void Screendraw_Finalize(void)
{
}

void Screendraw_Update(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		Hp[i] = GetHp(i);
		Hp[i] /= MAX_HP;
	}
}

void Screendraw_Draw(void)
{
	//HPバーの外身の表示
	Sprite_Draw(TEXTURE_INDEX_HPBARBOX, 0.0f, 0.0f);
	Sprite_Draw(TEXTURE_INDEX_HPBARBOX, 879.0f, 0.0f);

	//HPバーの中身の表示
	Sprite_Draw(TEXTURE_INDEX_HP, 4.0f, 3.0f,1,1,392.0f * Hp[0], 58);
	Sprite_Draw(TEXTURE_INDEX_HP, 883.0f, 3.0f, 1, 1, 392.0f * Hp[1], 58);

	//取ったセット数を表示
	//プレイヤー1のとき
	for (int i = 0; i < GetSetCount(0); i++)
	{
		Sprite_Draw(TEXTURE_INDEX_WINMARK, 4.0f + 80.0f*i, 90.0f);
	}
	//プレイヤー2のとき
	for (int i = 0; i < GetSetCount(1); i++)
	{
		Sprite_Draw(TEXTURE_INDEX_WINMARK, 883.0f + 80.0f*i, 90.0f);
	}
}
