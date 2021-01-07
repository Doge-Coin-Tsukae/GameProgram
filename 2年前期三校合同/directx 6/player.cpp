#include "player.h"
#include "main.h"
#include "input.h"
#include "sprite.h"
#include "sound.h"
#include "table.h"
#include "bullet.h"
#include "collision.h"
#include "enemybullet.h"
#include "enemylaser.h"
#include "fade.h"


#define PLAYER_WIDTH	(32)
#define PLAYER_HEIGHT	(32)

#define ANIME_PATTERN_MAX		3
#define ANIME_PATTERN_SKIPFRAME 8

#define NOTENEMY (0)

typedef struct
{
	D3DXVECTOR2 pos;			//�ʒu
	int			muki;			//����
	int			color;			//�F

	int			animePattern;	//�A�j���p�^�[��
	int			animeFrame;		//�p�^�[���؂�ւ��E�G�C�g

	CIRCLE		collision;		//�~�̓����蔻��
	int			hitpoint;		//�q�b�g�|�C���g
	int			bomb;			//�e�����{��

}PLAYER;

PLAYER player;

void Player_Initialize(void)
{
	//�v���C���[�̏�����
	player.pos.x = SCREEN_WIDTH / 12;
	player.pos.y = SCREEN_HEIGHT / 1.1;

	player.color = 2;
	player.muki = 0;

	player.collision.cx = player.pos.x;
	player.collision.cy = player.pos.y;
	player.collision.r = PLAYER_WIDTH * 0.1f;

	player.hitpoint = 4000;		//�̗͒���
	player.bomb = 3;
}

void Player_Finalize(void)
{

}

void Player_Update(void)
{
	D3DXVECTOR2 dir = D3DXVECTOR2(0.0f, 0.0f);
	
	//�ړ��L�[
	if (Keyboard_IsPress(DIK_UP) || GamePad_IsPress(0, BUTTON_UP))
	{
		//�V�t�g�L�[��������Ă����Ƃ�(�ᑬ�ړ�)
		if (Keyboard_IsPress(DIK_LSHIFT))
		{
			dir.y -= 2.0f;
		}
		//������Ȃ������Ƃ�(�ʏ�ړ�)
		else
		{
			dir.y -= 5.0f;
			player.muki = 3;
		}
	}
	if (Keyboard_IsPress(DIK_DOWN) || GamePad_IsPress(0, BUTTON_DOWN))
	{
		//�V�t�g�L�[��������Ă����Ƃ�(�ᑬ�ړ�)
		if (Keyboard_IsPress(DIK_LSHIFT))
		{
			dir.y += 2.0f;
		}
		//������Ȃ������Ƃ�(�ʏ�ړ�)
		else
		{
			dir.y += 5.0f;
			player.muki = 0;
		}

	}
	if (Keyboard_IsPress(DIK_LEFT) || GamePad_IsPress(0, BUTTON_LEFT))
	{
		//�V�t�g�L�[��������Ă����Ƃ�(�ᑬ�ړ�)
		if (Keyboard_IsPress(DIK_LSHIFT))
		{
			dir.x -= 2.0f;
		}
		//������Ȃ������Ƃ�(�ʏ�ړ�)
		else
		{
			dir.x -= 5.0f;
			player.muki = 1;
		}

	}
	if (Keyboard_IsPress(DIK_RIGHT) || GamePad_IsPress(0, BUTTON_RIGHT))
	{
		//�V�t�g�L�[��������Ă����Ƃ�(�ᑬ�ړ�)
		if (Keyboard_IsPress(DIK_LSHIFT))
		{
			dir.x += 2.0f;
		}
		//������Ȃ������Ƃ�(�ʏ�ړ�)
		else
		{
			dir.x += 5.0f;
			player.muki = 2;
		}
	}

	//�X�y�[�X�������ꂽ��e�𔭎�
	if (Keyboard_IsTrigger(DIK_SPACE) || GamePad_IsTrigger(0, BUTTON_A)) {
		//�J�[�\���L�[���͂�����Ă��Ȃ��ꍇ�A�������甭�˕������쐬����
		if (D3DXVec2Length(&dir) < 0.01f) {
			switch (player.muki)
			{
			case 0://������
				dir.y = 1.0f;
				break;
			case 1://������
				dir.x = -1.0f;
				break;
			case 2://�E����
				dir.x = 1.0f;
				break;
			case 3://�����
				dir.y = -1.0f;
				break;
			}
		}

		//�V�t�g�L�[��������Ă����Ƃ�
		if (Keyboard_IsPress(DIK_LSHIFT))
		{
			switch (player.muki)
			{
			case 0://������
				dir = D3DXVECTOR2(0.0f, 1.0f);
				break;
			case 1://������
				dir = D3DXVECTOR2(-1.0f, 0.0f);
				break;
			case 2://�E����
				dir = D3DXVECTOR2(1.0f, 0.0f);
				break;
			case 3://�����
				dir = D3DXVECTOR2(0.0f, -1.0f);
				break;
			}
		}
		//�e�̍쐬
		Bullet_Create(player.pos.x, player.pos.y, dir);
		dir = D3DXVECTOR2(0.0f, 0.0f);
	}

	//Z�L�[�Ń{��
	if (Keyboard_IsTrigger(DIK_Z) || GamePad_IsTrigger(0, BUTTON_B))
	{
		if (player.bomb > 0) {
			//�G�e��S���j��
			for (int i = 0; i < ENEMYBULLET_MAX; i++) {
				EnemyBullet_Destroy(i);
			}

			//�G�̃��[�U�[�S����
			for (int i = 0; i < ENEMYLASER_MAX; i++) {
				EnemyLaser_Destroy(i);
			}
			PlaySound(SOUND_LABEL_SE_SHUTA);
			Fade_Start(false, 10, D3DCOLOR_RGBA(255, 255, 255, 0));
		}
		player.bomb--;
	}

	//�}�b�v�Ƃ̃q�b�g�`�F�b�N
	Collision_HitCheck_TileMap(NOTENEMY,player.pos, &dir);

	// ���W�̍X�V����
	player.pos += dir;

	//�����蔻��p���W�̍X�V
	player.collision.cx = player.pos.x;
	player.collision.cy = player.pos.y;

	//�X�L�b�v����t���[���l�𒴂�����
	if (++player.animeFrame > ANIME_PATTERN_SKIPFRAME)
	{
		//�A�j���p�^�[����i�߂�(�ő�l�𒴂����烊�Z�b�g)
		if (++player.animePattern >= ANIME_PATTERN_MAX)
			player.animePattern = 0;
		//�t���[���͌��ɖ߂�
		player.animeFrame = 0;
	}
}

void Player_Draw(void)
{
	//�v���C���[�̃e�N�X�`���\��
	Sprite_Draw(TEXTURE_INDEX_YUKIDARUMA,
		player.pos.x,
		player.pos.y,
		GetAnimTbl(player.color, player.muki, player.animePattern).x * 256,
		GetAnimTbl(player.color, player.muki, player.animePattern).y * 256,
		32,
		32,
		16,
		16,
		1.5f,
		1.5f,
		0.0f);

	for (int i = 0; i < player.bomb; i++)
	{
		//�v���C���[�̃e�N�X�`���\��
		Sprite_Draw(TEXTURE_INDEX_BOMB,
			700 + 50 * i,
			550,
			GetAnimTbl(player.color, player.muki, player.animePattern).x * 0,
			GetAnimTbl(player.color, player.muki, player.animePattern).y * 0,
			32,
			32,
			16,
			16,
			1.5f,
			1.5f,
			0.0f);
	}

}

const CIRCLE* Player_GetCollision()
{
	return &player.collision;
}

void Player_AddDamage(int damage)
{
	player.hitpoint -= damage;
	if (player.hitpoint < 0)
		player.hitpoint = 0;
}

int Player_GetHitPoint()
{
	return player.hitpoint;
}
