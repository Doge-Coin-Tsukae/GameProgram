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

bool lose;			//�����t���O
static bool g_bEnd = false;

int			animePattern;	//�A�j���p�^�[��
int			animeFrame;		//�p�^�[���؂�ւ��E�G�C�g

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

	//�X�L�b�v����t���[���l�𒴂�����
	if (++animeFrame > ANIME_PATTERN_SKIPFRAME)
	{
		//�A�j���p�^�[����i�߂�(�ő�l�𒴂����烊�Z�b�g)
		if (++animePattern >= ANIME_PATTERN_MAX)
			animePattern = 0;
		//�t���[���͌��ɖ߂�
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

	//�����Ȃ������Ƃ�(����)
	if (lose == false)
	{
		Sprite_Draw(TEXTURE_INDEX_1P, SCREEN_WIDTH / 2, 300.0f);
	}
	//�������Ƃ�(����)
	else
	{
		Sprite_Draw(TEXTURE_INDEX_2P, SCREEN_WIDTH / 2, 300.0f);
	}
}

//�����t���O������
void SetResultFlag(bool flag)
{
	lose = flag;
}