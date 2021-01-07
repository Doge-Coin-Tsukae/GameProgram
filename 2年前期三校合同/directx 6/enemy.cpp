
#include "enemy.h"
#include "main.h"
#include "sprite.h"
#include "sound.h"
#include "table.h"
#include "player.h"
#include "enemybullet.h"
#include "enemylaser.h"
#include "explosion.h"
#include "game.h"

#define _USE_MATH_DEFINES
#include <math.h>

//�}�N���錾
#define ENEMY_WIDTH				(32)
#define ENEMY_HEIGHT			(32)
#define ANIME_PATTERN_MAX		(3)
#define ANIME_PATTERN_SKIPFRAME (8)

#define ENEMY_SEARCH_RADIUS		(200.0f)
#define ENEMY_SEARCH_ANGLE		(0.85f)
#define ENEMY_CHASE_SPEED		(3.0f)
#define ENEMY_RETURN_SPEED		(1.0f)

#define ENEMY (true)

class ENEMY_DATA
{
public :
	int			enable;	//�����t���O

	D3DXVECTOR2 pos;	//�ʒu
	float		rot;	//��]
	int			color;	//�F
	int			muki;	//�����i�ړ������j

	int			animePattern;	//�A�j���p�^�[��
	int			animeFrame;		//�p�^�[���؂�ւ��E�G�C�g

	CIRCLE		collision;

	int			frame;
	int			frame_alpha;
	int			state;
	D3DXVECTOR2 dir_shot;
	D3DXVECTOR2 pos_return;

	bool move;		//�ړ�����̂��ǂ���
	int hp;
	int type;		//0,yuki 1,cho 2,maho

	D3DXVECTOR2 posing[3];		//�ړ��ꏊ
	int late;					//�ړ�����|�W�V����
};

ENEMY_DATA enemy[ENEMY_COUNT];


//�G�̏��
typedef enum
{
	ENEMY_STATE_INIT,		//������
	ENEMY_STATE_SEARCH,		//���͂��T�[�`
	ENEMY_STATE_FIND,		//�G�𔭌�
	ENEMY_STATE_CHASE,		//�ǐ�
	ENEMY_STATE_SHOT,		//�V���b�g����(�~)
	ENEMY_STATE_SHOT2,		//�V���b�g����(�P��)
	ENEMY_STATE_SHOT3,		//�V���b�g����(�A��)
	ENEMY_STATE_LASER,		//���[�U�[����(�P��)
	ENEMY_STATE_LASER2,		//���[�U�[����(�A��)
	ENEMY_STATE_COOLDOWN,	//�V���b�g�I��
	ENEMY_STATE_RETURN,		//��ʒu�ɖ߂�
	ENEMY_STATE_DEAD,		//���S���
	ENEMY_STATE_BOSS,		//�{�X���L�̓���

	ENEMY_STATE_MAX

}ENEMY_STATE;


int Enemy_CalcMuki(D3DXVECTOR2 dir);

void Enemy_StateInit(int index);
void Enemy_StateSearch(int index);
void Enemy_StateFind(int index);
void Enemy_StateChase(int index);
void Enemy_StateShot(int index);
void Enemy_Stateshot2(int index);
void Enemy_Stateshot3(int index, int repet);
void Enemy_StateLaser(int index);
void Enemy_StateLaser2(int index, int repet);
void Enemy_StateCooldown(int index);
void Enemy_StateReturn(int index);


void Enemy_Initialize(void)
{
	//�G�̏�����
	for (int i = 0; i < ENEMY_COUNT; i++) {
		Enemy_StateInit(i);
		enemy[i].state = ENEMY_STATE_SEARCH;
	}
}

void Enemy_Finalize(void)
{

}

void Enemy_Update(void)
{
	for (int i = 0; i<ENEMY_COUNT; i++){

		//�����蔻��p���W�̍X�V
		enemy[i].collision.cx = enemy[i].pos.x;
		enemy[i].collision.cy = enemy[i].pos.y;

		//�X�L�b�v����t���[���l�𒴂�����
		if (++enemy[i].animeFrame > ANIME_PATTERN_SKIPFRAME)
		{
			//�A�j���p�^�[����i�߂�(�ő�l�𒴂����烊�Z�b�g)
			if (++enemy[i].animePattern >= ANIME_PATTERN_MAX)
				enemy[i].animePattern = 0;
			//�t���[���͌��ɖ߂�
			enemy[i].animeFrame = 0;
		}

		switch (enemy[i].state)
		{
		case ENEMY_STATE_INIT:
			Enemy_StateInit(i);
			break;
		case ENEMY_STATE_SEARCH:
			Enemy_StateSearch(i);
			break;
		case ENEMY_STATE_FIND:
			Enemy_StateFind(i);
			break;
		case ENEMY_STATE_CHASE:
			Enemy_StateChase(i);
			break;
		case ENEMY_STATE_SHOT:
			Enemy_StateShot(i);
			break;
		case ENEMY_STATE_SHOT2:
			Enemy_Stateshot2(i);
			break;
		case ENEMY_STATE_SHOT3:
			Enemy_Stateshot3(i,5);
			break;
		case ENEMY_STATE_LASER:
			Enemy_StateLaser(i);
			break;
		case ENEMY_STATE_LASER2:
			Enemy_StateLaser2(i,3);
			break;
		case ENEMY_STATE_COOLDOWN:
			Enemy_StateCooldown(i);
			break;
		case ENEMY_STATE_RETURN:
			Enemy_StateReturn(i);
			break;
		case ENEMY_STATE_BOSS:
			Enemy_StateBoss(i);
			break;
		default:
			break;
		}
	}
}

void Enemy_Draw(void)
{
	for (int i = 0; i < ENEMY_COUNT; i++) {

		//�����t���O��TRUE�̓G�̂ݏ������s��
		if (!enemy[i].enable) {
			continue;
		}

		//��ނɂ���ăe�N�X�`�����ς��
		switch (enemy[i].type) {
		case 0:
			Sprite_Draw(TEXTURE_INDEX_YUKIDARUMA,
				enemy[i].pos.x,
				enemy[i].pos.y,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).x * 256,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).y * 256,
				32,
				32,
				16,
				16,
				2.0f,
				2.0f,
				enemy[i].rot);
			break;

		case 1:
			//�G�e�N�X�`��
			Sprite_Draw(TEXTURE_INDEX_BOSS,
				enemy[i].pos.x,
				enemy[i].pos.y,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).x * 0,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).y * 0,
				256,
				256,
				128,
				128,
				0.5f,
				0.5f,
				enemy[i].rot);

			//�̗̓o�[(�{�X�̂�)
			Sprite_Draw(TEXTURE_INDEX_BAR,
				enemy[i].pos.x - 40,
				enemy[i].pos.y + 50,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).x * 0,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).y * 0,
				enemy[i].hp * 10,
				32,
				64,
				64,
				0.5f,
				0.5f,
				enemy[i].rot);
			break;

		case 2:
			Sprite_Draw(TEXTURE_INDEX_YUKIDARUMA,
				enemy[i].pos.x,
				enemy[i].pos.y,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).x * 256,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).y * 256,
				32,
				32,
				16,
				16,
				2.0f,
				2.0f,
				enemy[i].rot);
			break;

		default:
			break;
		}
	}
}

void Enemy_Destroy(int index, bool kill )
{
	if (kill == true)
	{
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		Game_AddKillCount();
	}
	enemy[index].state = ENEMY_STATE_DEAD;
	enemy[index].enable = false;
}

bool Enemy_IsEnable(int index)
{
	return enemy[index].enable;
}

const CIRCLE* Enemy_GetCollision(int index)
{
	return &enemy[index].collision;
}

//���������
int Enemy_CalcMuki(D3DXVECTOR2 dir)
{
	int muki = 0;

	//�ړ��������L�����`�F�b�N
	if (D3DXVec2Length(&dir) > 0.01f)
	{
		//X������Y�����̑傫�����ׂāA�ǂ���̕����傫���̂��𒲂ׂ�
		//X�����̕����傫���ꍇ
		if (fabs(dir.x) > fabs(dir.y))
		{
			//X�������v���X�̒l�Ȃ̂��}�C�i�X�̒l�Ȃ̂��𒲂ׂ�
			//�}�C�i�X�����̏ꍇ�͍�����
			if (dir.x < 0.0f)
				muki = 1;
			//��������Ȃ��i�v���X�����j�ꍇ�͉E����
			else
				muki = 2;
		}
		//Y�����̕����傫���ꍇ
		else
		{
			//Y�������v���X�̒l�Ȃ̂��}�C�i�X�̒l�Ȃ̂��𒲂ׂ�
			//�}�C�i�X�����̏ꍇ�͏����
			if (dir.y < 0.0f)
				muki = 3;
			//��������Ȃ��i�v���X�����j�ꍇ�͏����
			else
				muki = 0;
		}
	}

	return muki;
}

//����������
void Enemy_StateInit(int index)
{

	D3DXVECTOR2 dir;

	dir.x = 0;
	dir.y = 0;
	//�o���|�C���g���ʍs�s���������蒼��
	while (1)
	{
		//�o�����W������
		enemy[index].pos.x = frand() * SCREEN_WIDTH;
		enemy[index].pos.y = frand() * SCREEN_HEIGHT;

		//�ʍs�s���ǂ���
		if (Collision_HitCheck_TileMap(ENEMY, enemy[index].pos, &dir) == false)
		{
			break;
		}
	}

	enemy[index].rot = 0;
	enemy[index].color = 1;

	enemy[index].muki = rand() % 4;
	enemy[index].enable = TRUE;

	enemy[index].collision.cx = enemy[index].pos.x;
	enemy[index].collision.cy = enemy[index].pos.y;
	enemy[index].collision.r = ENEMY_WIDTH * 0.8f;

	enemy[index].frame = 0;
	enemy[index].hp = 1;


	enemy[index].move = true;	//�ړ�������
	enemy[index].type = 0;
	//�X�e�[�g���T�[�`��Ԃֈڍs
	enemy[index].state = ENEMY_STATE_SEARCH;

}

void Enemy_StateSearch(int index)
{
	//�t���[����i�߂�
	enemy[index].frame++;

	D3DXVECTOR2 dir;

	//�����Ă�������̃x�N�g�������
	switch (enemy[index].muki)
	{
	case 0://������
		dir = D3DXVECTOR2( 0.0f,  1.0f);		//x��0,y��1
		if (enemy[index].move == true) {
			Collision_HitCheck_TileMap(ENEMY, enemy[index].pos, &dir);
			enemy[index].pos += dir;
		}
		break;
	case 1://������
		dir = D3DXVECTOR2(-1.0f,  0.0f);		//x��-1,y��0
		if (enemy[index].move == true) {
			Collision_HitCheck_TileMap(ENEMY, enemy[index].pos, &dir);
			enemy[index].pos += dir;
		}
		break;
	case 2://�E����
		dir = D3DXVECTOR2( 1.0f,  0.0f);		//x��1,y��0
		if (enemy[index].move == true) {
			Collision_HitCheck_TileMap(ENEMY, enemy[index].pos, &dir);
			enemy[index].pos += dir;
		}
		break;
	case 3://�����
		dir = D3DXVECTOR2( 0.0f, -1.0f);		//x��0,y��-1
		if (enemy[index].move == true) {
			Collision_HitCheck_TileMap(ENEMY, enemy[index].pos, &dir);
			enemy[index].pos += dir;
		}
		break;
	}

	//�v���C���[�̍��W���擾����
	D3DXVECTOR2 pl_pos = D3DXVECTOR2(Player_GetCollision()->cx, Player_GetCollision()->cy);

	//�G�ƃv���C���[�̋������v�Z����
	D3DXVECTOR2 vLen = enemy[index].pos - pl_pos;
	float length = D3DXVec2Length(&vLen);

	//�~�Ŕ�����Ƃ�
	//���肷�鋗���̒��ɓ����Ă��邩���`�F�b�N����
	if (length < ENEMY_SEARCH_RADIUS)
	{
		//�G���猩�ăv���C���[�̍��W�ւ̕����x�N�g�������
		D3DXVECTOR2 pl_dir = pl_pos - enemy[index].pos;
		D3DXVec2Normalize(&pl_dir, &pl_dir);

		//�G�̌����ƃv���C�����W�ւ̕����x�N�g���œ��ς����
		float dot = D3DXVec2Dot(&dir, &pl_dir);		//���ς����

		////��Ŕ�������
		//���肷��p�x���ɓ����Ă��邩���`�F�b�N����
		if (dot > ENEMY_SEARCH_ANGLE)		//dot�̒l���傫��(�v���C���[��������)
		{
			Explosion_Create(enemy[index].pos.x, enemy[index].pos.y);

			//����ɒʂ�΃v���C���[�����X�e�[�g�Ɉڍs����
			enemy[index].state = ENEMY_STATE_FIND;
			enemy[index].frame = 0;

			//�߂��ė�����W��ۑ�����
			enemy[index].pos_return = enemy[index].pos;
		}
	}

	//������ω�������
	if (enemy[index].frame > 90)
	{
		enemy[index].muki = (enemy[index].muki + 1) % 4;

		enemy[index].frame = 0;
	}

}

void Enemy_StateFind(int index)
{
	//�t���[����i�߂�
	enemy[index].frame++;

	//��莞�Ԍo������ǐՃX�e�[�g�ֈڍs(�������ɉ�����������΂����ɓ����)
	if (enemy[index].frame > 20){

		enemy[index].frame = 0;

		//�X�e�[�g���T�[�`��Ԃֈڍs
		enemy[index].state = ENEMY_STATE_CHASE;
	}
}

void Enemy_StateChase(int index)
{
	//�t���[����i�߂�
	enemy[index].frame++;

	//�v���C���[�̍��W���擾����
	D3DXVECTOR2 pl_pos = D3DXVECTOR2(Player_GetCollision()->cx, Player_GetCollision()->cy);
	
	//�x�N�g���擾
	D3DXVECTOR2 dir = pl_pos - enemy[index].pos;
	D3DXVec2Normalize(&dir, &dir);
	dir *= ENEMY_CHASE_SPEED;

	if (enemy[index].move == true)
	{
		enemy[index].pos += dir;
	}

	//�ړ�����������������
	enemy[index].muki = Enemy_CalcMuki(dir);

	//��莞�Ԍo������e�ˏo�X�e�[�g�ֈڍs
	if (enemy[index].frame > 120){

		enemy[index].frame = 0;

		//�ړ�������ۑ�
		enemy[index].dir_shot = dir;

		//�����_���Łu�΂�T���e�v�������́u���[�U�[�v���ˏo
		if (rand() % 3)
		{
			//�X�e�[�g���T�[�`��Ԃֈڍs
			enemy[index].state = ENEMY_STATE_SHOT2;
		}
		else if (rand() % 3)
		{
			enemy[index].state = ENEMY_STATE_SHOT;
		}
		else{
			//�X�e�[�g���T�[�`��Ԃֈڍs
			enemy[index].state = ENEMY_STATE_LASER;
		}

		if (enemy[index].type == 2)
		{
			enemy[index].state = ENEMY_STATE_SHOT2;
		}
	}
}

void Enemy_StateShot(int index)
{
	//�t���[����i�߂�
	enemy[index].frame++;

	//���W�A�������
	//�~(2��)��20�������e����o����
	float shot_rad = atan2(enemy[index].dir_shot.y, enemy[index].dir_shot.x);
	shot_rad = (float)(M_PI * 2 / 10)*enemy[index].frame;	//20/1�̊����ŕ��o����

	//�ˏo�p�x�N�g�����t���[���l�ŉ�]������
	D3DXVECTOR2 shot_dir;
	shot_dir.x = enemy[index].dir_shot.x*cosf(shot_rad) - enemy[index].dir_shot.y*sinf(shot_rad);
	shot_dir.y = enemy[index].dir_shot.x*sinf(shot_rad) + enemy[index].dir_shot.y*cosf(shot_rad);

	EnemyBullet_Create(enemy[index].pos.x, enemy[index].pos.y, shot_dir);

	//��莞�Ԍo������N�[���_�E���X�e�[�g�ֈڍs
	if (enemy[index].frame > 90){

		enemy[index].frame = 0;

		//�X�e�[�g���A�ҏ�Ԃֈڍs
		enemy[index].state = ENEMY_STATE_COOLDOWN;
	}
}

void Enemy_StateLaser(int index)
{
	//1��̂ݕ���
	if (enemy[index].frame == 0){
		EnemyLaser_Create(enemy[index].pos.x, enemy[index].pos.y, enemy[index].dir_shot);
	}

	//�t���[����i�߂�
	enemy[index].frame++;


	//��莞�Ԍo������N�[���_�E���X�e�[�g�ֈڍs
	if (enemy[index].frame > 90){

		enemy[index].frame = 0;

		//�X�e�[�g���A�ҏ�Ԃֈڍs
		enemy[index].state = ENEMY_STATE_COOLDOWN;
	}
}

//���[�U�̘A������2
void Enemy_StateLaser2(int index, int repet)
{
	static int land = 0;
	//�v���C���[�̍��W���擾����
	D3DXVECTOR2 pl_pos = D3DXVECTOR2(Player_GetCollision()->cx, Player_GetCollision()->cy);

	//1��̂ݕ���
	if (enemy[index].frame == 0) {
		EnemyLaser_Create(enemy[index].pos.x, enemy[index].pos.y, enemy[index].dir_shot);
	}

	//�t���[����i�߂�
	enemy[index].frame++;


	//��莞�Ԍo������2���ڔ��ˏ���
	if (enemy[index].frame > 40) {
		//�x�N�g���擾
		D3DXVECTOR2 dir = pl_pos - enemy[index].pos;
		D3DXVec2Normalize(&dir, &dir);
		dir *= ENEMY_CHASE_SPEED;

		//�ړ�����������������
		enemy[index].muki = Enemy_CalcMuki(dir);

		//�ړ�������ۑ�
		enemy[index].dir_shot = dir;

		enemy[index].frame = 0;
		land++;
		if (repet <= land) {
			land = 0;
			//�X�e�[�g���A�ҏ�Ԃֈڍs
			enemy[index].state = ENEMY_STATE_COOLDOWN;
		}
	}

}

void Enemy_Stateshot2(int index)
{

	EnemyBullet_Create(enemy[index].pos.x, enemy[index].pos.y, enemy[index].dir_shot);

	//�t���[����i�߂�
	enemy[index].frame++;


	//��莞�Ԍo������N�[���_�E���X�e�[�g�ֈڍs
	if (enemy[index].frame > 15) {

		enemy[index].frame = 0;

		//�X�e�[�g���A�ҏ�Ԃֈڍs
		enemy[index].state = ENEMY_STATE_COOLDOWN;

		
	}
}

void Enemy_Stateshot3(int index,int repet)
{
	static int land=0;
	//�v���C���[�̍��W���擾����
	D3DXVECTOR2 pl_pos = D3DXVECTOR2(Player_GetCollision()->cx, Player_GetCollision()->cy);

	EnemyBullet_Create(enemy[index].pos.x, enemy[index].pos.y, enemy[index].dir_shot);

	//�t���[����i�߂�
	enemy[index].frame++;


	//��莞�Ԍo������N�[���_�E���X�e�[�g�ֈڍs
	if (enemy[index].frame > 30) {
		//�x�N�g���擾
		D3DXVECTOR2 dir = pl_pos - enemy[index].pos;
		D3DXVec2Normalize(&dir, &dir);
		dir *= ENEMY_CHASE_SPEED;

		//�ړ�����������������
		enemy[index].muki = Enemy_CalcMuki(dir);

		//�ړ�������ۑ�
		enemy[index].dir_shot = dir;

		enemy[index].frame = 0;
		land++;
		if (repet <= land) {
			land = 0;
			//�X�e�[�g���A�ҏ�Ԃֈڍs
			enemy[index].state = ENEMY_STATE_COOLDOWN;
		}
	}
}

void Enemy_StateCooldown(int index)
{
	//�t���[����i�߂�
	enemy[index].frame++;

	//��莞�Ԍo������A�҃X�e�[�g�ֈڍs
	if (enemy[index].frame > 30) {

		enemy[index].frame = 0;

		switch (enemy[index].type)
		{
		case 0:
			//�X�e�[�g���A�ҏ�Ԃֈڍs
			enemy[index].state = ENEMY_STATE_RETURN;
			break;
		case 1:
			enemy[index].state = ENEMY_STATE_BOSS;
			break;
		case 2:
			Enemy_Destroy(index,false);
		default:
			break;

		}
	
	}
}

void Enemy_StateReturn(int index)
{
	//�t���[����i�߂�
	enemy[index].frame++;

	//�v���C���[�̍��W���擾����
	D3DXVECTOR2 pl_pos = D3DXVECTOR2(Player_GetCollision()->cx, Player_GetCollision()->cy);

	//�A�҂�����W�ւ̌����x�N�g�����v�Z����
	D3DXVECTOR2 dir = enemy[index].pos_return - enemy[index].pos;

	//�x�N�g���̒������v�Z����
	float length = D3DXVec2Length(&dir);

	D3DXVec2Normalize(&dir, &dir);
	dir *= ENEMY_CHASE_SPEED;

	enemy[index].pos += dir;

	//�ړ�����������������
	enemy[index].muki = Enemy_CalcMuki(dir);

	//�A�҂�����W�ɓ���������
	if (length <= ENEMY_CHASE_SPEED){

		enemy[index].frame = 0;

		//�X�e�[�g���T�[�`��Ԃֈڍs
		enemy[index].state = ENEMY_STATE_SEARCH;
	}
}

//�G�̌ʏo��(X���W,Y���W,�G�̎��(0:�Ⴞ���,1:���X),����,�ړ����邩���Ȃ���,�F�I��)
void SetEnemy(int px, int py,int select,int round,bool mov,int col)
{
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		if (enemy[i].enable == false) {
			enemy[i].pos.x = px;
			enemy[i].pos.y = py;

			enemy[i].type = select;

			enemy[i].rot = 0;
			enemy[i].color = col;

			enemy[i].muki = round;		//�w�肵�ĕ���������
			enemy[i].enable = TRUE;

			enemy[i].collision.cx = enemy[i].pos.x;
			enemy[i].collision.cy = enemy[i].pos.y;
			enemy[i].collision.r = ENEMY_WIDTH * 0.8f;

			enemy[i].frame = 0;

			enemy[i].move = mov;	//�ړ��������邩���Ȃ���

			//�^�C�v�ɂ���ē�����ς���
			switch (enemy[i].type) {
			case 0:
				//�X�e�[�g���T�[�`��Ԃֈڍs
				enemy[i].state = ENEMY_STATE_CHASE;
				enemy[i].pos_return = D3DXVECTOR2(px, py);
				enemy[i].hp = 1;
				break;
			case 1:
				enemy[i].state = ENEMY_STATE_BOSS;
				enemy[i].posing[0]= D3DXVECTOR2(400, 200);
				enemy[i].posing[1] = D3DXVECTOR2(600, 400);
				enemy[i].posing[2] = D3DXVECTOR2(200, 400);
				enemy[i].late = 0;
				enemy[i].hp = 30;
				break;
			case 2:
				enemy[i].state = ENEMY_STATE_CHASE;
				enemy[i].hp = 5;
				break;
			default:
				break;
			}

			break;
		}
	}
}

//�_���[�W��������
void EnemyDamage(int index,int dama)
{
	enemy[index].hp -= dama;
	if (enemy[index].hp <= 0)
	{
		Enemy_Destroy(index,true);
	}
}

void Enemy_StateBoss(int index)
{

	//�v���C���[�̍��W���擾����
	D3DXVECTOR2 pl_pos = D3DXVECTOR2(Player_GetCollision()->cx, Player_GetCollision()->cy);

	//�x�N�g���擾
	D3DXVECTOR2 dir = pl_pos - enemy[index].pos;

	D3DXVec2Normalize(&dir, &dir);
	dir *= ENEMY_CHASE_SPEED;

	//�ړ�����������������
	enemy[index].muki = Enemy_CalcMuki(dir);

	//�Ίp�ɓ��B������U��
	enemy[index].dir_shot = dir;

	//�t���[����i�߂�
	enemy[index].frame++;

	if (enemy[index].frame >= 10) {
		for (int i = 0; i < 10; i++) {
			//���W�A�������
			//�~(2��)��20�������e����o����
			float shot_rad = atan2(enemy[index].dir_shot.y, enemy[index].dir_shot.x);
			shot_rad = (float)(M_PI * 2 / 10)*i;	//20/1�̊����ŕ��o����

			//�ˏo�p�x�N�g�����t���[���l�ŉ�]������
			D3DXVECTOR2 shot_dir;
			shot_dir.x = enemy[index].dir_shot.x*cosf(shot_rad) - enemy[index].dir_shot.y*sinf(shot_rad);
			shot_dir.y = enemy[index].dir_shot.x*sinf(shot_rad) + enemy[index].dir_shot.y*cosf(shot_rad);

			EnemyBullet_Create(enemy[index].pos.x, enemy[index].pos.y, shot_dir);
		}
		enemy[index].frame = 0;
	}

	//�ړ�
	D3DXVECTOR2 dir2 = enemy[index].posing[enemy[index].late] - enemy[index].pos;

	//�x�N�g���̒������v�Z����
	float length = D3DXVec2Length(&dir2);
	D3DXVec2Normalize(&dir2, &dir2);
	dir2 *= (ENEMY_CHASE_SPEED*2.5f);

	enemy[index].pos += dir2;

	//�w�肵�����W�Ƃقڈ�v���Ă�����
	if (length <= ENEMY_CHASE_SPEED)
	{
		enemy[index].late++;
		if (enemy[index].late > 2)
		{
			enemy[index].late = 0;
		}

		//�ړ�������ۑ�
		enemy[index].frame = 0;			//�t���[���̃��Z�b�g

		//�����_���Łu�΂�T���e�v�������́u���[�U�[�v���ˏo
		if (rand() % 2)
		{
			enemy[index].state = ENEMY_STATE_SHOT2;
		}
		else if (rand() % 2)
		{
			enemy[index].state = ENEMY_STATE_SHOT;
		}
		else if (rand() % 2)
		{
			enemy[index].state = ENEMY_STATE_SHOT3;
		}
		else if (rand() % 2)
		{
			enemy[index].state = ENEMY_STATE_LASER;
		}
		else
		{
			enemy[index].state = ENEMY_STATE_LASER2;
		}

		//���m���œG�𐶂�
		if (rand() % 2)
		{
			SetEnemy(400, 300, 0, 0, true, 1);

		}

		//���̊m���œ����Ȃ��G�𐶂�
		if (rand() % 5)
		{
			SetEnemy(200, 100, 2, 0, false, 0);
			SetEnemy(400, 100, 2, 0, false, 0);
			SetEnemy(600, 100, 2, 0, false, 0);
			SetEnemy(200, 500, 2, 0, false, 0);
			SetEnemy(400, 500, 2, 0, false, 0);
			SetEnemy(600, 500, 2, 0, false, 0);
		}

	}
}