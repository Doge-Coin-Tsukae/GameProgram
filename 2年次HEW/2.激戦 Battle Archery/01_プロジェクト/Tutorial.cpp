#include "bullet.h"
#include "camera.h"
#include "fade.h"
#include "field.h"
#include "input.h"
#include "light.h"
#include "myDirect3D.h"
#include "object.h"
#include "player.h"
#include "piller_tutorial.h"
#include "point.h"
#include "particle.h"
#include "scene.h"
#include "sound.h"
#include "sprite.h"
#include "shadow.h"
#include "target_tutorial.h"
#include "saku.h"
#include "saku_yoko.h"
#include "wall_tutorial.h"
#include "wall_tate_tutorial.h"
#include "xfile.h"
#include "selectcharctor.h"
#include "x_gamepad.h"

typedef enum PHASE_INDEX
{
	PHASE_INDEX_FADE,
	PHASE_INDEX_PLAYER_IN,

	PHASE_INDEX_STAGE_CLEAR,
	PHASE_INDEX_END,

	PHASE_INDEX_MAX
};

static PHASE_INDEX g_Phase;

static bool Game_EndCheck(void);

void Tutorial_Initialize(void)
{
	//x�t�@�C���̓ǂݍ���
	for (int i = 0; i < HUMAN_KOR + 1; i++)
	{
		SetXfile(i);
	}

	//�A�j���[�V�����t��X�t�@�C���̓ǂݍ���
	for (int i = 0; i < 2; i++)
	{
		SetAnimationXfile(i,10);
	}
	

	SetTexture(TEXTURE_INDEX_ARROWPOWERBOX_BAR);
	SetTexture(TEXTURE_INDEX_ARROWPOWER_BAR);
	SetTexture(TEXTURE_INDEX_EXPLAIN);

	// ���C�g�̏���������
	Light_Initialize();

	//�e�̏���������
	Shadow_Initialize();

	// �n�ʂ̏���������
	Field_Initialize();

	//�v���C���[�̏�������
	Player_Initialize();

	//�e�̏�������
	Bullet_Initialize();

	//�ǂ̏�������
	Object_Initialize();

	//�Ə��̏�������
	Point_Initialize();

	//�I�̏�������
	Target_Tutorial_Initialize();

	Piller_Tutorial_Initialize();

	Wall_Tutorial_Initialize();

	WallTate_Tutorial_Initialize();

	Saku_Initialize();

	SakuYoko_Initialize();

	// �J�����̏���������
	Camera_Initialize();

	//�p�[�e�B�N���̏���������
	InitParticle();

	PlaySound(SOUND_LABEL_WEATHER_1_BGM);
	PlaySound(SOUND_LABEL_WEATHER_2_BGM);

	g_Phase = PHASE_INDEX_FADE;

	Fade_Start(false, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void Tutorial_Finalize(void)
{
	//X�t�@�C���̉��
	for (int i = 0; i < HUMAN_KOR + 1; i++)
	{
		ReleaseXfile(i);
	}

	//�p�[�e�B�N���̏I������
	UninitParticle();

	//�e�̏I������
	Shadow_Finalize();

	// �J�����̏I������
	Camera_Finalize();

	// ���C�g�̏I������
	Light_Finalize();

	// �n�ʂ̏I������
	Field_Finalize();

	//�v���C���[�̏I������
	Player_Finalize();

	//�e�̏I������
	Bullet_Finalize();

	//�Ə��̏I������
	Point_Initialize();

	//�ǂ̏I������
	Object_Finalize();

	Piller_Tutorial_Finalize();

	Saku_Finalize();

	SakuYoko_Finalize();

	//�ǂ̓����蔻��(��)�̏I������
	Wall_Tutorial_Finalize();

	WallTate_Tutorial_Finalize();

	//�I�̏I������
	Target_Tutorial_Finalize();

	ReleaseTexture(TEXTURE_INDEX_EXPLAIN);
	ReleaseTexture(TEXTURE_INDEX_ARROWPOWERBOX_BAR);
	ReleaseTexture(TEXTURE_INDEX_ARROWPOWER_BAR);

	StopSound(SOUND_LABEL_WEATHER_1_BGM);
	StopSound(SOUND_LABEL_WEATHER_2_BGM);

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

		//�Ə��̍X�V����
		Point_Update();

		//�I�̍X�V����
		Target_Tutorial_Update();

		//�e�̍X�V����
		Bullet_Update();

		Piller_Tutorial_Update();

		//�ǂ̍X�V����
		Object_Update();

		Shadow_Update();

		// �p�[�e�B�N�������̍X�V
		UpdateParticle();

		Saku_Update();

		SakuYoko_Update();

		//�ǂ̓����蔻��(��)�̍X�V����
		Wall_Tutorial_Update();

		WallTate_Tutorial_Update();

		//�Q�[���̏I���`�F�b�N
		if (Game_EndCheck())
		{
			Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_Phase = PHASE_INDEX_STAGE_CLEAR;
		}

		break;

	case PHASE_INDEX_STAGE_CLEAR:
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_2PGAME);
			g_Phase = PHASE_INDEX_END;
		}
		break;
	case PHASE_INDEX_END:
		break;
	}
}

void Tutorial_Draw(void)
{

	//�v���C���[�����[�v
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		// �J�����̐ݒ�
		Camera_SetCamera(i);

		// �n�ʂ̕`�揈��
		Field_Draw();

		//�e�̕`�揈��
		Shadow_Draw();

		//�v���C���[�̕`�揈��
		Player_Draw();

		//�e�̕`�揈��
		Bullet_Draw();

		//�I�̕`�揈��
		Target_Tutorial_Draw();

		Piller_Tutorial_Draw();

		//�ǂ̕`�揈��
		Object_Draw();

		Saku_Draw();

		SakuYoko_Draw();

		//�ǂ̓����蔻��(��)�̓����蔻��
		Wall_Tutorial_Draw();

		WallTate_Tutorial_Draw();

		/*��ʂɒ���t������̂͌�ŕ`�悷��(Z�\�[�g)*/

		// �p�[�e�B�N�������̕`��
		DrawParticle(i);

		Sprite_Draw(TEXTURE_INDEX_EXPLAIN, 70.0f + (1530.0f *i), 0.0f);

		//�|���������Ƃ��ɏo��Q�[�W�̕`�揈��
		PlayerScreenDraw();

		//�Ə��̕`�揈��
		Point_Draw();

		// �t�F�[�h�̕`��
		Fade_Draw();

		/*Z�\�[�g�����܂�*/
	}
}

bool Game_EndCheck(void)
{
	//�������Ԃ𒴂�����I��
	if (Keyboard_IsPress(DIK_Q) || gamepad_inport(0, PP_START) || gamepad_inport(1, PP_START))
		return true;

	return false;
}