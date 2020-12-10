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
#include "billboard.h"
#include "bullet.h"
#include "result.h"
#include <time.h>

PHASE_INDEX static g_Phase;

bool Deathflag;					//�ǂ��������񂾂�
float Deathtime;				//���S���Ă���̎��Ԃ��J�E���g����
int g_gameset[MAX_PLAYER];		//������Z�b�g��������
int countdown;					//�Q�[�����n�܂�J�E���g�_�E��

//�v���g�^�C�v�錾
bool Game_EndCheck(void);

void Game_Initialize(void)
{

	Deathflag = false;
	Deathtime = 0.0f;
	countdown = 0;

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_gameset[i] = 0;
	}

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

	//�v���C���[�̏�������
	Player_Initialize();

	//�ǂ̏�������
	Object_Initialize();

	Human_Initialize();
	
	Coli_Initialize();

	Screendraw_Initialize();

	// �J�����̏���������
	Camera_Initialize();

	PlaySound(SOUND_LABEL_BATTLE_BGM);

	g_Phase = PHASE_INDEX_FADE;
	
	Fade_Start(false, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void Game_Finalize(void)
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

	//AI�̏I������
	Human_Finalize();

	//�s���{�[�h�̏I������
	Billboard_Finalize();

	//�e�̏I������
	Bullet_Finalize();

	//�e�̏I������
	Shadow_Finalize();

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_gameset[i] = 0;
	}
}

void Game_Update(void)
{
	switch (g_Phase)
	{
	case PHASE_INDEX_FADE:
		if (!Fade_IsFade()) {
			g_Phase = PHASE_INDEX_PLAYER_IN;
		}
		break;
	case PHASE_INDEX_PLAYER_IN:
		if (countdown >= 120)
		{
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

			//AI�̍X�V����
			Human_Update();

			//�e�̍X�V����
			Shadow_Update();

			Bullet_Update();

			Billboard_Update();

			//��ʂɒ���t���镨�̍X�V����
			Screendraw_Update();

			if (Deathflag == true)
			{
				Deathtime -= 0.1f;
				if (Deathtime <= 0.0f)
				{
					Deathflag = false;
					countdown = 0;
					//�Q�[���̏I���`�F�b�N
					if (Game_EndCheck())
					{
						StopSound(SOUND_LABEL_BATTLE_BGM);
						Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
						g_Phase = PHASE_INDEX_STAGE_CLEAR;
					}
					Player_Finalize();
					//�v���C���[�̏�������
					Player_Initialize();
					Camera_Initialize();

				}
			}
		}
		else
		{
			if (countdown== 0 || countdown == 40 || countdown == 80)
			{
				PlaySound(SOUND_LABEL_SE_POINT_COUNT);
			}
			else if (countdown == 119)
			{
				PlaySound(SOUND_LABEL_SE_POINT_COUNT_GO);
			}
			countdown++;
		}
		break;
	case PHASE_INDEX_STAGE_CLEAR:
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_RESULT);
			g_Phase = PHASE_INDEX_END;
		}
		break;
	case PHASE_INDEX_END:
		break;
	}
}

void Game_Draw(void)
{
		// �J�����̐ݒ�
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

		//�e�̕`�揈��
		Shadow_Draw();

		Screendraw_Draw();
		/*Z�\�[�g�����܂�*/
}

//�Q�[�����I�����邩�̊֐�
bool Game_EndCheck(void)
{
	//�ǂ��炩�̃v���C���[��2�Z�b�g�������I���
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (g_gameset[i] >= 2)
		{
			SetResultFlag(i);
			return true;
		}
	}

	return false;
}

//���_���P������
void SetGameSet(int index)
{
	g_gameset[index] += 1;
}

//���S�t���O�����ĂĎ��̃Z�b�g�ɍs���܂ł̎��Ԃ��v��
void SetDeathflag(void)
{
	Deathflag = true;	//�t���O�����Ă�
	Deathtime = 9.0f;	//���Ԃ̃Z�b�g
}

//�Z�b�g���̃Q�b�^�[
int GetSetCount(int index)
{
	return g_gameset[index];
}