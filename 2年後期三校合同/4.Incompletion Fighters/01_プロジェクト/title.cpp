#include "input.h"
#include "scene.h"
#include "sprite.h"
#include "texture.h"
#include "fade.h"
#include "xfile.h"
#include "sound.h"
#include <d3d9.h>

static bool g_bEnd;


void Title_Initialize(void)
{
	g_bEnd = false;

	Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));

	SetXfile(0);

	for (int i = 0; i < 2; i++)
	{
		SetAnimationXfile(i);
		ChengeAnimation(i, 8, 0.3f);
	}

	PlaySound(SOUND_LABEL_TITLE_BGM);
}

void Title_Finalize(void)
{
}

void Title_Update(void)
{
	if (!g_bEnd) {
		if (Keyboard_IsTrigger(DIK_SPACE)) {
			StopSound(SOUND_LABEL_TITLE_BGM);
			Fade_Start(true, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_bEnd = true;
		}
	}
	else {
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_TUTORIAL);
		}
	}
}

void Title_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_TITLE, 0.0f, 0.0f);
}
