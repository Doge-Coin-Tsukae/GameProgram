#include "input.h"
#include "scene.h"
#include "sound.h"
#include "sprite.h"
#include "texture.h"
#include "fade.h"
#include "player.h"
#include <d3d9.h>
#include "tittle_camera.h"
#include "x_gamepad.h"

static bool g_bEnd = false;


void Title_Initialize(void)
{
	Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));

	TCamera_Initialize();
	PlaySound(SOUND_LABEL_TITLE_BGM);

	g_bEnd = false;
	SetTexture(TEXTURE_INDEX_TITLE_2);
	SetTexture(TEXTURE_INDEX_1P);
	SetTexture(TEXTURE_INDEX_2P);
	SetTexture(TEXTURE_INDEX_4P);
	SetTexture(TEXTURE_INDEX_PLAY2);
}

void Title_Finalize(void)
{
	TCamera_Finalize();

	ReleaseTexture(TEXTURE_INDEX_TITLE_2);
	ReleaseTexture(TEXTURE_INDEX_1P);
	ReleaseTexture(TEXTURE_INDEX_2P);
	ReleaseTexture(TEXTURE_INDEX_4P);
	ReleaseTexture(TEXTURE_INDEX_PLAY2);
}

void Title_Update(void)
{
	TCamera_Update();

	if (!g_bEnd) {
		if (Keyboard_IsTrigger(DIK_SPACE) || gamepad_inport(0, PP_START) || gamepad_inport(1, PP_START)) {
			PlaySound(SOUND_LABEL_SE_SELECT_DECISION);
			Fade_Start(true, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_bEnd = true;
		}
	}
	else {
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_SELECTCHAR);
		}
	}
}

void Title_Draw(void)
{
	// 1P‰æ–Ê
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		// ƒJƒƒ‰‚ÌÝ’è
		TCamera_SetCamera(i);

		Sprite_Draw(TEXTURE_INDEX_TITLE_2, 400.0f + (1500.0f *i), 100.0f);

		if (i == 0)
		{
			Sprite_Draw(TEXTURE_INDEX_1P, 710.0f + (1500.0f *i), 600.0f);
		}
		else
		{
			Sprite_Draw(TEXTURE_INDEX_2P, 710.0f + (1500.0f *i), 600.0f);
		}

		Sprite_Draw(TEXTURE_INDEX_PLAY2, 710.0f + (1500.0f *i), 650.0f);

		Fade_Draw();
	}
}
