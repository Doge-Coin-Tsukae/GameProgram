#include "input.h"
#include "scene.h"
#include "sprite.h"
#include "texture.h"
#include "sound.h"
#include "fade.h"
#include <d3d9.h>

static bool g_bEnd = false;

void Tutorial_Initialize(void)
{
	g_bEnd = false;
	Fade_Start(false, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void Tutorial_Finalize(void)
{
}

void Tutorial_Update(void)
{
	if (!g_bEnd) {
		if (Keyboard_IsTrigger(DIK_SPACE)) {
			StopSound(SOUND_LABEL_BGM000);
			PlaySound(SOUND_LABEL_SE_CLICK);
			Fade_Start(true, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_bEnd = true;
		}
	}
	else {
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_GAME);
		}
	}
}

void Tutorial_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_TUTORIAL, 0.0f, 0.0f);
}
