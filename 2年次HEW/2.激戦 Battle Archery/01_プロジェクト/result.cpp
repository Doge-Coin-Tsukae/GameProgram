#include "input.h"
#include "field.h"
#include "scene.h"
#include "score_draw.h"
#include "sprite.h"
#include "selectcharctor.h"
#include "texture.h"
#include "tittle_camera.h"
#include "fade.h"
#include "xfile.h"
#include "sound.h"
#include "x_gamepad.h"
#include "fade.h"


#define INIT_PLAYERONE_POS  D3DXVECTOR3(100.0f,0.0f,0.0f)
#define INIT_PLAYERTWO_POS  D3DXVECTOR3(-100.0f,0.0f,-90.0f)
#define INIT_PLAYERONE_POSDROW  D3DXVECTOR3(100.0f,0.0f,0.0f)
#define INIT_PLAYERTWO_POSDROW  D3DXVECTOR3(-100.0f,0.0f,0.0f)
#define INIT_CAMERA_POSR  D3DXVECTOR3(0.0f, 150.0f,0.0f)
#define INIT_CAMERA_POSV  D3DXVECTOR3(0.0f, 150.0f,300.0f)
#define INIT_PLAYERONE_ROT  D3DXVECTOR3(0.0f, -2.0f,0.0f)
#define INIT_PLAYERTWO_ROT  D3DXVECTOR3(0.0f,  4.9f,0.0f)
#define INIT_PLAYERONE_DRAWROT  D3DXVECTOR3(0.0f,3.0f,0.0f)
#define INIT_PLAYERTWO_DRAWROT  D3DXVECTOR3(0.0f, 0.0f,0.0f)
#define INIT_PLAYERONE_SCL  D3DXVECTOR3(1.0f, 1.0f, 1.0f)
#define INIT_PLAYERTWO_SCL  D3DXVECTOR3(1.0f, 1.0f, 1.0f)

int static g_score[2];			//�X�R�A�̎擾�̂������ɓ����
int static g_playercolor[2];	//�v���C���[�̍��Ђ̃f�[�^

static bool g_bEnd_r;

void Result_Initialize(void)
{

	g_bEnd_r = false;

	Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));

	//�J�����̃Z�b�g
	TCamera_Initialize();

	for (int i = 0; i < 2; i++)
	{
		g_score[i] = getscore(i);						//1P��2P�̃X�R�A����ɓ����
		g_playercolor[i] = HUMAN_JPN + GetCharaData(i);	//�e���̍\���̃f�[�^�ԍ�������
	}

	PlaySound(SOUND_LABEL_SE_CHEERS);

	//1P�����������A1P�̏����ԍ�+2P�̔s�k�ԍ�������
	if (g_score[0] > g_score[1])
	{


		g_playercolor[0] += 4;	//�����̔ԍ�
		g_playercolor[1] += 8;	//�s�k�̔ԍ�

	}
	//2P�����������A2P�̏����ԍ�+1P�̔s�k�ԍ�������
	else if (g_score[0] < g_score[1])
	{
		g_playercolor[1] += 4;	//�����̔ԍ�
		g_playercolor[0] += 8;	//�s�k�̔ԍ�
	}
	//���������̎��A�������Ȃ�
	else
	{
		g_playercolor[0] += 12;	//���������̔ԍ�
		g_playercolor[1] += 12;	//���������̔ԍ�
	}

	//X�t�@�C���̃Z�b�g
	for (int i = 0; i < 2; i++)
	{
		SetXfile(g_playercolor[i]);
		SetTCamera(INIT_CAMERA_POSR, INIT_CAMERA_POSV, i);
	}

	//�J�����̍��W�̎w��
	//SetCamera(INIT_CAMERA_POSR, INIT_CAMERA_POSV);


	//�e�N�X�`���̃Z�b�g
	SetTexture(TEXTURE_INDEX_1P);
	SetTexture(TEXTURE_INDEX_2P);
	SetTexture(TEXTURE_INDEX_RESULT_BAR);
	SetTexture(TEXTURE_INDEX_WIN);
	SetTexture(TEXTURE_INDEX_DRAW);

}

void Result_Finalize(void)
{

	TCamera_Finalize();

	for (int i = 12; i < 24; i++)
	{
		ReleaseXfile(i);
	}

	//�e�N�X�`�����
	ReleaseTexture(TEXTURE_INDEX_1P);
	ReleaseTexture(TEXTURE_INDEX_2P);
	ReleaseTexture(TEXTURE_INDEX_RESULT_BAR);
	ReleaseTexture(TEXTURE_INDEX_WIN);
	ReleaseTexture(TEXTURE_INDEX_DRAW);

	StopSound(SOUND_LABEL_SE_CHEERS);
}

void Result_Update(void)
{


	if (!g_bEnd_r) {
		if (Keyboard_IsTrigger(DIK_SPACE) || gamepad_inport(0, PP_A) || gamepad_inport(1, PP_A))
		{
			PlaySound(SOUND_LABEL_SE_MATASONDENE);
			Fade_Start(true, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_bEnd_r = true;
		}
	}

	else {
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_LOGO);
		}
	}

}

void Result_Draw(void)
{
	// 1P���
	for (int i = 0; i < 2; i++)
	{
		TCamera_SetCamera(i);

		//���U���g�o�[�̕\��
		Sprite_Draw(TEXTURE_INDEX_RESULT_BAR, 0.0f + (1500 * i), 50.0f);

		//1P�����������ɕ\��
		if (g_score[0] > g_score[1])
		{
			Sprite_Draw(TEXTURE_INDEX_1P, 770.0f + (1500 * i), 170.0f);
			Sprite_Draw(TEXTURE_INDEX_WIN, 500.0f + (1500 * i), 60.0f);

			Xfile_Draw(INIT_PLAYERONE_SCL, INIT_PLAYERONE_POS, INIT_PLAYERONE_ROT, g_playercolor[0]);

			Xfile_Draw(INIT_PLAYERTWO_SCL, INIT_PLAYERTWO_POS, INIT_PLAYERTWO_ROT, g_playercolor[1]);

		}
		//2P�����������ɕ\��
		else if (g_score[0] < g_score[1])
		{
			Xfile_Draw(INIT_PLAYERONE_SCL, INIT_PLAYERONE_POS, INIT_PLAYERONE_ROT, g_playercolor[1]);
			Xfile_Draw(INIT_PLAYERTWO_SCL, INIT_PLAYERTWO_POS, INIT_PLAYERTWO_ROT, g_playercolor[0]);
			Sprite_Draw(TEXTURE_INDEX_2P, 770.0f + (1500 * i), 170.0f);
			Sprite_Draw(TEXTURE_INDEX_WIN, 500.0f + (1500 * i), 60.0f);
		}
		//���������̎��ɕ\��
		else
		{
			Xfile_Draw(INIT_PLAYERONE_SCL, INIT_PLAYERONE_POSDROW, INIT_PLAYERONE_DRAWROT, g_playercolor[0]);
			Xfile_Draw(INIT_PLAYERTWO_SCL, INIT_PLAYERTWO_POSDROW, INIT_PLAYERTWO_DRAWROT, g_playercolor[1]);
			Sprite_Draw(TEXTURE_INDEX_DRAW, 580.0f + (1500 * i), 95.0f);
		}
		Fade_Draw();
	}

	
}
