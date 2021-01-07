#include "input.h"
#include "scene.h"
#include "sound.h"
#include "sprite.h"
#include "texture.h"
#include "fade.h"
#include "player.h"

static bool g_bEnd = false;
static int g_time;

void Logo_Initialize(void)
{
	SetTexture(TEXTURE_INDEX_LOGO);

	Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));

	g_bEnd = false;
	g_time = 100;
}

void Logo_Finalize(void)
{
	ReleaseTexture(TEXTURE_INDEX_LOGO);
}

void Logo_Update(void)
{
	if (!g_bEnd) {
		if (g_time <= 0)
		{
			Fade_Start(true, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_bEnd = true;
		}
		g_time--;
	}
	else {
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_TITLE);
		}
	}
}

void Logo_Draw(void)
{
	// 1P‰æ–Ê
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		Sprite_Draw(TEXTURE_INDEX_LOGO, 200.0f + (1500.0f *i), 210.0f);
		Fade_Draw();
	}
}