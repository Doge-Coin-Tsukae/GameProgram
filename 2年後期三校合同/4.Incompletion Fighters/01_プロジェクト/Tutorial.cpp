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
	// ���C�g�̏���������
	Light_Initialize();

	//�e�̏�������(�g�����̂̑O�ɓ���邱��)
	Shadow_Initialize();

	//�r���|�[�g�̏���������
	Billboard_Initialize();

	//�e�̏���������
	Bullet_Initialize();


	// �n�ʂ̏���������
	Field_Initialize();

	SetAImode(WAITTIME);

	//�v���C���[�̏�������
	Player_Initialize();

	//�ǂ̏�������
	Object_Initialize();

	//Human_Initialize();

	Coli_Initialize();

	Screendraw_Initialize();

	// �J�����̏���������
	Camera_Initialize();

	PlaySound(SOUND_LABEL_TUTORIAL_BGM);

	g_Phase = PHASE_INDEX_FADE;

	Fade_Start(false, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void Tutorial_Finalize(void)
{
	// �J�����̏I������
	Camera_Finalize();

	Screendraw_Finalize();

	// ���C�g�̏I������
	Light_Finalize();

	// �n�ʂ̏I������
	Field_Finalize();

	//�v���C���[�̏I������
	Player_Finalize();

	//�ǂ̏I������
	Object_Finalize();

	Human_Finalize();

	//�s���{�[�h�̏I������
	Billboard_Finalize();

	//�e�̏I������
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
		// �J�����̍X�V����
		Camera_Update();

		// ���C�g�̍X�V����
		Light_Update();


		// �n�ʂ̍X�V����
		Field_Update();

		//�v���C���[�̍X�V����
		Player_Update();

		//�ǂ̍X�V����
		Object_Update();

		Shadow_Update();

		Bullet_Update();

		Billboard_Update();

		Screendraw_Update();

		//�`���[�g���A�����I��������
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
{// �J�����̐ݒ�
	Camera_SetCamera(0);

	// �n�ʂ̕`�揈��
	Field_Draw();

	//�v���C���[�̕`�揈��
	Player_Draw();
	//�ǂ̕`�揈��
	Object_Draw();

	Coli_Draw();

	Bullet_Draw();

	//�r���{�[�h�̕`�揈��
	Billboard_Draw();

	/*��ʂɒ���t������̂͌�ŕ`�悷��(Z�\�[�g)*/
	// �t�F�[�h�̕`��
	Fade_Draw();

	Shadow_Draw();

	Screendraw_Draw();

	Sprite_Draw(TEXTURE_INDEX_TUTORIAL, 0.0f, 100.0f);
	/*Z�\�[�g�����܂�*/
}
