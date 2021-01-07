#include "bullet.h"
#include "camera.h"
#include "debugproc.h"
#include "fade.h"
#include "field.h"
#include "input.h"
#include "light.h"
#include "myDirect3D.h"
#include "number.h"
#include "object.h"
#include "player.h"
#include "point.h"
#include "result.h"
#include "scene.h"
#include "score_draw.h"
#include "sound.h"
#include "shadow.h"
#include "sprite.h"
#include "saku.h"
#include "saku_yoko.h"
#include "target.h"
#include "texture.h"
#include <time.h>
#include "countdown_draw.h"
#include "piller.h"
#include "wall.h"
#include "wall_tate.h"
#include "particle.h"
#include "table.h"
#include "xfile.h"

#define TIMELIMIT (50000)		//�������� (1000=1�b)
#define COUNTDOWNTV	(240)		//�Q�[�����X�^�[�g����܂ł̎���
#define GETCOUNT (15)			//��t���[���Ői�ޕb��	

typedef enum PHASE_INDEX
{
	PHASE_INDEX_FADE,
	PHASE_INDEX_PLAYER_IN,

	PHASE_INDEX_STAGE_CLEAR,
	PHASE_INDEX_END,

	PHASE_INDEX_MAX
};

static PHASE_INDEX g_Phase;

//�N���X
class GAMEMANAGEMENT
{
private:
	int g_time;			//��������
	int g_count;			//1�t���[���̎���
	int countdown;		//�J�E���g�_�E��
	int animepattan;		//�A�j���p�^�[��
	bool EndFlag;		//�Q�[�����I���������̃t���O

public:

	//�R���X�g���N�^
	GAMEMANAGEMENT()
	{
		//�ϐ��̏�����
		g_time = TIMELIMIT;
		g_count = GETCOUNT;
		countdown = 0;
		animepattan = 0;
		EndFlag = false;
	}

	//�f�X�g���N�^
	~GAMEMANAGEMENT()
	{
		//�ϐ��̏�����
		g_time = 0;
		g_count = 0;
		countdown = 0;
		animepattan = 0;
		EndFlag = false;
	}

	//�Q�[���̊J�n����
	void Game_Initialize()
	{
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
		Target_Initialize();

		//���̏�������
		Piller_Initialize();

		//��(�c)�̏�������
		Saku_Initialize();

		//��(��)�̏�������
		SakuYoko_Initialize();

		//�ǂ̓����蔻��(��)�̏�������
		Wall_Initialize();

		//�ǂ̓����蔻��(�c)�̏�������
		WallTate_Initialize();

		//�X�R�A�̏�������
		Score_Init();

		// �J�����̏���������
		Camera_Initialize();

		//�p�[�e�B�N���̏���������
		InitParticle();


		//�Q�[���J�n���A��ʂ�������Ă���̂ň��`�揈�����s��
		Object_Update();
		Object_Draw();
	}

	//�Q�[���̏I������
	void Game_Finalize()
	{
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

		Piller_Finalize();

		Saku_Finalize();

		SakuYoko_Finalize();

		//�ǂ̓����蔻��(��)�̏I������
		Wall_Finalize();

		//�ǂ̓����蔻��(�c)�̏I������
		WallTate_Finalize();

		//�I�̏I������
		Target_Finalize();
	}

	//�Q�[���̍X�V����
	void Game_Update()
	{
		//�Q�[���J�n���Ă��邩
		if (countdown >= COUNTDOWNTV)
		{
			// �J�����̍X�V����
			Camera_Update();

			// ���C�g�̍X�V����
			Light_Update();

			//�������Ԃ̍X�V����
			g_time = g_time - g_count;

			// �n�ʂ̍X�V����
			Field_Update();

			//�v���C���[�̍X�V����
			Player_Update();

			//�Ə��̍X�V����
			Point_Update();

			//�I�̍X�V����
			Target_Update();

			//�e�̍X�V����
			Bullet_Update();

			//�ǂ̍X�V����
			Object_Update();

			Piller_Update();

			Saku_Update();

			SakuYoko_Update();

			Shadow_Update();

			// �p�[�e�B�N�������̍X�V
			UpdateParticle();

			//�ǂ̓����蔻��(��)�̍X�V����
			Wall_Update();

			//�ǂ̓����蔻��(�c)�̍X�V����
			WallTate_Update();

			//�Q�[���̏I���`�F�b�N
			if (Game_EndCheck())
			{
				Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
				g_Phase = PHASE_INDEX_STAGE_CLEAR;
			}
		}
		//�܂��J�n���Ă��Ȃ��Ƃ�
		else
		{
			countdown++;

			//1�b�����ɃJ�E���g�̉���炷
			switch (countdown)
			{
			case 60:
				PlaySound(SOUND_LABEL_SE_GIRL_COUNT_3);
				break;
			case 120:
				animepattan++;
				PlaySound(SOUND_LABEL_SE_GIRL_COUNT_2);
				break;
			case 180:
				animepattan++;
				PlaySound(SOUND_LABEL_SE_GIRL_COUNT_1);
				break;
			case COUNTDOWNTV:
				PlaySound(SOUND_LABEL_SE_GIRL_COUNT_GO);
				break;
			}
		}

		if (countdown >= COUNTDOWNTV && countdown <= COUNTDOWNTV + 100)
		{
			countdown++;
		}
	}

	//�Q�[���̕`�揈��
	void Game_Draw(int i)
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

		//�ǂ̕`�揈��
		Object_Draw();

		//�I�̕`�揈��
		Target_Draw();

		//���̕`�揈��
		Piller_Draw();

		//��(�c)�̕`�揈��
		Saku_Draw();

		//��(��)�̕`�揈��
		SakuYoko_Draw();

		//�ǂ̓����蔻��(��)�̓����蔻��
		Wall_Draw();

		//�ǂ̓����蔻��(�c)�̓����蔻��
		WallTate_Draw();



		/*��ʂɒ���t������̂͌�ŕ`�悷��(Z�\�[�g)*/

		// �p�[�e�B�N�������̕`��
		DrawParticle(i);

		//�Ə��̕`�揈��
		Point_Draw();

		//�������Ԃ̕`�揈��
		Timelimit_Draw(700 + (1600 * i), 10, g_time / 1000, 3, true);

		//�X�R�A�̕`�揈��(1P = 0)
		Score_Draw(0 + (1540 * i), 10, 0, 3, true, 0, 32 - (i * 32));

		//�X�R�A�̕`�揈��(2P = 1)
		Score_Draw(1430 + (1520 * i), 10, 1, 3, true, 1, 0 + (i * 32));

		//�|���������Ƃ��ɏo��Q�[�W�̕`�揈��
		PlayerScreenDraw();

		//�J�n����Ƃ��A�J�E���g�_�E�����s��
		if (countdown < COUNTDOWNTV)
		{
			Sprite_Draw(TEXTURE_INDEX_COUNTDOWN,
				640 + (1600 * i),
				200,
				GetAnimTbl(animepattan).x * 256,
				GetAnimTbl(animepattan).y * 256,
				191.66f,
				200,
				16,
				16,
				1.5f,
				1.5f,
				0.0f);
		}
		//�X�^�[�g���o��
		else if (countdown < COUNTDOWNTV + 100)
		{
			Sprite_Draw(TEXTURE_INDEX_START, 450 + (1600 * i), 300);
		}

		//�Q�[���I�����̃J�E���g�_�E��
		if (g_time < 4000 && g_time > 1000)
		{
			if (g_time < 2000)
			{
				if (animepattan != 2)
				{
					PlaySound(SOUND_LABEL_SE_GIRL_COUNT_1);
					animepattan = 2;
				}
			}
			else if (g_time < 3000)
			{
				if (animepattan != 1)
				{
					PlaySound(SOUND_LABEL_SE_GIRL_COUNT_2);
					animepattan = 1;
				}
			}
			else
			{
				if (animepattan != 0)
				{
					PlaySound(SOUND_LABEL_SE_GIRL_COUNT_3);
					animepattan = 0;
				}
			}

			//��ʂɕ\��
			Sprite_Draw(TEXTURE_INDEX_COUNTDOWN,
				640 + (1600 * i),
				200,
				GetAnimTbl(animepattan).x * 256,
				GetAnimTbl(animepattan).y * 256,
				191.66f,
				200,
				16,
				16,
				1.5f - (g_time / 5000.0f),
				1.5f - (g_time / 5000.0f),
				0.0f);

		}

		//�^�C���A�b�v�̕`�揈��
		if (g_time <= 1000)
		{
			Sprite_Draw(TEXTURE_INDEX_TIMEUP, 450 + (1600 * i), 300);

		}

		//�^�C���A�b�v������炷
		if (g_time <= 900 && EndFlag == false)
		{
			PlaySound(SOUND_LABEL_SE_GIRL_TIME_UP);
			EndFlag = true;
		}

		// �t�F�[�h�̕`��
		Fade_Draw();

		/*Z�\�[�g�����܂�*/



	}

	//�Q�[���̏I���̊m�F
	bool Game_EndCheck(void)
	{
		//�������Ԃ𒴂�����I��
		if (g_time <= 0)
		{
			return true;
		}

		return false;
	}
};

GAMEMANAGEMENT *m_game; //�N���X�̒�`


//�Q�[���̏�������
void Game_Initialize(void)
{
	//�N���X�̏�����
	m_game = new GAMEMANAGEMENT;

	//x�t�@�C���̓ǂݍ���
	for (int i = 0; i < HUMAN_KOR + 1; i++)
	{
		SetXfile(i);
	}

	//�摜�̃Z�b�g
	SetTexture(TEXTURE_INDEX_COUNTDOWN);
	SetTexture(TEXTURE_INDEX_START);
	SetTexture(TEXTURE_INDEX_TIMEUP);
	SetTexture(TEXTURE_INDEX_NUMBER);
	SetTexture(TEXTURE_INDEX_NUMBER_RED);
	SetTexture(TEXTURE_INDEX_NUMBER_BLUE);
	SetTexture(TEXTURE_INDEX_ARROWPOWERBOX_BAR);
	SetTexture(TEXTURE_INDEX_ARROWPOWER_BAR);

	//���y��t����
	PlaySound(SOUND_LABEL_WEATHER_1_BGM);
	PlaySound(SOUND_LABEL_WEATHER_2_BGM);

	g_Phase = PHASE_INDEX_FADE;
	
	//�Q�[���Ŏg���֐��̏�������
	m_game->Game_Initialize();

	Fade_Start(false, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
}

//�Q�[���̏I������
void Game_Finalize(void)
{
	//BGM���~�߂�
	StopSound(SOUND_LABEL_WEATHER_1_BGM);
	StopSound(SOUND_LABEL_WEATHER_2_BGM);

	//�摜�̉��
	ReleaseTexture(TEXTURE_INDEX_COUNTDOWN);
	ReleaseTexture(TEXTURE_INDEX_START);
	ReleaseTexture(TEXTURE_INDEX_TIMEUP);
	ReleaseTexture(TEXTURE_INDEX_NUMBER);
	ReleaseTexture(TEXTURE_INDEX_NUMBER_RED);
	ReleaseTexture(TEXTURE_INDEX_NUMBER_BLUE);
	ReleaseTexture(TEXTURE_INDEX_ARROWPOWERBOX_BAR);
	ReleaseTexture(TEXTURE_INDEX_ARROWPOWER_BAR);

	//X�t�@�C���̉��
	for (int i = 0; i < HUMAN_KOR + 1; i++)
	{
		ReleaseXfile(i);
	}

	//�Q�[���Ŏg���֐��̏I������
	m_game->Game_Finalize();

	//�N���X�̉��
	delete m_game;
}

//�Q�[���̍X�V����
void Game_Update(void)
{
	//�t�F�[�h�̌`�Ԃŕς��
	switch (g_Phase)
	{
	case PHASE_INDEX_FADE:
		if (!Fade_IsFade()) {
			g_Phase = PHASE_INDEX_PLAYER_IN;
			// PlaySound(SOUND_LABEL_BGM000);
		}
		break;
	case PHASE_INDEX_PLAYER_IN:
		m_game->Game_Update();
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

//�Q�[���̕`�揈��
void Game_Draw(void)
{
	//�v���C���[�����[�v
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		m_game->Game_Draw(i);
	}
}