#include "texture.h"
#include "player.h"
#include "enemy.h"
#include "fade.h"
#include "scene.h"
#include "collision.h"
#include "bullet.h"
#include "enemybullet.h"
#include "enemylaser.h"
#include "explosion.h"
#include "score_draw.h"
#include "tileMap.h"
#include "result.h"
#include "sound.h"

//�Q�[���̏�Ԃ�����
typedef enum PHASE_INDEX
{
	PHASE_INDEX_FADE,
	PHASE_INDEX_PLAYER_NORMAL,
	PHASE_INDEX_STAGE_CLEAR,
	PHASE_INDEX_END,

	PHASE_INDEX_MAX
};

static PHASE_INDEX g_Phase;			//�Q�[���̏�Ԃ�����

static int g_KillCount = 0;			//�E�Q���̕\��

//����cpp�t�@�C�����Ŏg���֐��̃v���g�^�C�v�錾
static bool Game_EndCheck(void);


//�Q�[����ʂ̏�������
void Game_Initialize(void)
{
	Player_Initialize();
	Enemy_Initialize();
	Bullet_Initialize();
	EnemyBullet_Initialize();
	EnemyLaser_Initialize();
	Explosion_Initialize();
	TileMap_Initialize();

	g_Phase = PHASE_INDEX_FADE;			//�t�F�[�h���̏�Ԃɂ���
	g_KillCount = 0;					//�E�Q���̃��Z�b�g

	//BGM�Đ�
	PlaySound(SOUND_LABEL_BGM001);

	//�t�F�[�h���J�n������
	Fade_Start(false, 30, D3DCOLOR_RGBA(0,0,0,0));
}

//�Q�[����ʂ̏I������
void Game_Finalize(void)
{
	Player_Finalize();
	Enemy_Finalize();
}

//�Q�[����ʂ̍X�V
void Game_Update(void)
{
	//�Q�[���̏�Ԃŏ�����ς���
	switch(g_Phase)
	{
		//�t�F�[�h���̂Ƃ�
	case PHASE_INDEX_FADE:
		if( !Fade_IsFade() ) {
			g_Phase = PHASE_INDEX_PLAYER_NORMAL;
		}
		break;
		//�ʏ�̂Ƃ�
	case PHASE_INDEX_PLAYER_NORMAL:
		Player_Update();
		Enemy_Update();
		Bullet_Update();
		EnemyBullet_Update();
		EnemyLaser_Update();
		Explosion_Update();

		//�����蔻��͕K�����ׂẴA�b�v�f�[�g�������I�������ɍs��
		Collision_Update();

		//�Q�[���̏I���`�F�b�N
		if (Game_EndCheck())
		{
			Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_Phase = PHASE_INDEX_STAGE_CLEAR;
		}
		break;

		//�X�e�[�W�N���A�����Ƃ�
	case PHASE_INDEX_STAGE_CLEAR:
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_RESULT);		//���U���g��ʂɃ`�F���W
			g_Phase = PHASE_INDEX_END;				//�I���̒l������
		}
		break;
		//�Q�[�����I������Ƃ�
	case PHASE_INDEX_END:
		break;
	}

}

//�Q�[����ʂ̕`�揈��
void Game_Draw(void)
{
	TileMap_Draw();
	Player_Draw();
	Enemy_Draw();
	Bullet_Draw();
	EnemyBullet_Draw();
	EnemyLaser_Draw();
	Explosion_Draw();

	//���C�t�\��
	Score_Draw(0, 0, Player_GetHitPoint(), 7, true);
	//�E�Q���\��
	Score_Draw(950, 530, g_KillCount, 2, true);
}

//�Q�[���̏I�������𖞂����Ă��邩
bool Game_EndCheck(void)
{
	//�v���C���[�����S������I��
	if (Player_GetHitPoint() <= 0)
	{
		StopSound();			//�S�Ẳ����~
		Welose();				//�����t���O�����Ă�
		return true;			//�I���t���O�����Ă�
	}

	//6�K�ɓ��B������I��(����)
	if (Mapwon())
	{
		StopSound();			//�S�Ẳ����~
		Wewon();				//�����t���O�����Ă�
		return true;			//�I���t���O�����Ă�
	}

	//�����ł��Ȃ������Ƃ�
	return false;
}


//�E�Q����ǉ�
void Game_AddKillCount()
{
	g_KillCount += 1;
}

//�Q�[�����Ƀt�F�[�h�������Q�[�����~�߂����Ƃ�
void FadeOn()
{
	g_Phase = PHASE_INDEX_FADE;
}