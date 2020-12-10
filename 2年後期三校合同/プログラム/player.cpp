//****************************************************
//�v���C���[�֌W�̃v���O����
//****************************************************

#include "player.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "colision.h"
#include "object.h"
#include "debugproc.h"
#include "sound.h"
#include "xfile.h"
#include "colision.h"
#include "Vector.h"
#include "shadow.h"
#include "game.h"
#include "human.h"
#include "billboard.h"
#include "bullet.h"
#include <math.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define	VALUE_ROTATE	(3.0f)				// ��]��
#define MAX_POWER		(200.0f)			// �p���[�̏��

#define NORMAL_Y		(100.0f)			//��

#define INIT_PLAYERONE_POS  D3DXVECTOR3(0.0f,NORMAL_Y,-1000.0f)
#define INIT_PLAYERONE_ROT  D3DXVECTOR3(0.0f,180.0f, 0.0f)

#define INIT_PLAYERTWO_POS  D3DXVECTOR3(0.0f,NORMAL_Y,1000.0f)
#define INIT_PLAYERTWO_ROT  D3DXVECTOR3(0.0f, 0.0f, 0.0f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 static g_pVtxBuffField = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
D3DXMATRIX				static g_mtxWorldField;		// ���[���h�}�g���b�N�X(�s��)

//*****************************************************************************
//enum
//*****************************************************************************
//�v���C���[�̈ړ�
enum MOVE
{
	UP,			//�O�ړ�
	DOWN,		//���ړ�
	RIGHT,		//�E�ړ�
	LEFT,		//���ړ�
	RIGHTUP,	//�E�O�ړ�
	RIGHTDOWN,	//�E���ړ�
	LEFTUP,		//���O�ړ�
	LEFTDOWN,	//�����ړ�
	FLY,		//�󒆕��V
	DAMAGE,		//�_���[�W�\��
	DAMAGEDOWN,	//�_�E���\��
	GRAVITY,	//�d�͂Ɉ���������
};

//�U���`��
enum ATTACKPATTAN
{
	NONE,
	PPUNCH,
	PPUNCHSTRONG,
	PKICK,
	PKICKSTRONG,
};
//*****************************************************************************
//�N���X
//*****************************************************************************

class player {

private:
	D3DXVECTOR3		PosPlayer;				//�v���C���[�̃|�W�V����
	D3DXVECTOR3		RotPlayer;				// �v���C���[�̌���(��])
	D3DXVECTOR3		SclPlayer;				//�v���C���[�̑傫��
	D3DXVECTOR3		InitVector;				//�x�N�g���̏������W
	D3DXVECTOR3		fly;					//�؋󎞊�
	D3DXVECTOR3		Dir;					//�v���C���[�̍s����
	D3DXVECTOR3		arm;
	D3DXVECTOR3		armstrong;
	D3DXVECTOR3		leg;
	D3DXVECTOR3		legstrong;

	float			speed;					//�v���C���[�̑��x
	float			combotime;				//�U�����̎���(�R���{�֌W)
	int				Hp;						//�̗�
	int				combo;					//�R���{
	int				idxShadow;				//�V���h�EID
	int				cooldown;				//�U�������Ƃ��A�����ŏo�Ȃ��悤�ɂ���
	int				damagecooldown;			//�U�����󂯂��Ƃ��̍d��
	int				beforattack;			//�O�A�������U�����Ă�������
	int				attackpower;			//�U����
	bool			downattack;				//���̍U�����_�E�����ʂ�����U����
	bool			onehit;
	bool			Attack;					//�U������
	bool			Damaged;				//�U�����󂯂Ă��邩
	bool			CheckDeath;
public:

	//�v���C���[�̏�������(�������W,������]��)
	void PlayerInit(D3DXVECTOR3 IniPos, D3DXVECTOR3 IniRot)
	{
		PosPlayer = IniPos;		//�������W
		arm = PosPlayer;
		arm.y += 600.0f;
		leg = PosPlayer;
		leg.y += 300.0f;
		RotPlayer = IniRot;			//������]
		SclPlayer = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			//�����傫��
		Dir = PosPlayer;									//����̍s������v���C���[�Ɠ�����
		Hp = MAX_HP;										//�̗�
		combo = 0;
		damagecooldown = 0;
		cooldown = 0;
		speed = 50.0f;										//�v���C���[�̑f����
		beforattack = NONE;
		attackpower = 0;
		fly = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		downattack = false;
		onehit = false;
		Attack = false;
		Damaged = false;
		CheckDeath = false;

		idxShadow = Shadow_Create(PosPlayer, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	}

	void PlayerFinalize()
	{
		Shadow_Release(idxShadow);
	}

	//���W�̕ύX(����(enum),����(0.0f,0.2f,0.5f,0.75f,1.0f))
	void ChangePos(int xyzpm, int i, float speed)
	{

		switch (xyzpm) {
			if (Attack == false)
			{
				//�O�ړ�
		case UP:
			Dir.z += sin(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x += cos(RotPlayer.y*D3DX_PI / 180)*speed;

			break;

			//���ړ�
		case DOWN:
			Dir.z -= sin(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x -= cos(RotPlayer.y*D3DX_PI / 180)*speed;

			break;

			//�E�ړ�
		case RIGHT:
			Dir.z -= cos(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x += sin(RotPlayer.y*D3DX_PI / 180)*speed;
			break;

			//���ړ�
		case LEFT:
			Dir.z += cos(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x -= sin(RotPlayer.y*D3DX_PI / 180)*speed;

			break;

			//�E�O
		case RIGHTUP:
			Dir.z -= cos(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x += sin(RotPlayer.y*D3DX_PI / 180)*speed;

			Dir.z += sin(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x += cos(RotPlayer.y*D3DX_PI / 180)*speed;
			break;

			//�E���
		case RIGHTDOWN:
			Dir.z -= cos(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x += sin(RotPlayer.y*D3DX_PI / 180)*speed;

			Dir.z -= sin(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x -= cos(RotPlayer.y*D3DX_PI / 180)*speed;
			break;

			//���O
		case LEFTUP:
			Dir.z += cos(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x -= sin(RotPlayer.y*D3DX_PI / 180)*speed;

			Dir.z += sin(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x += cos(RotPlayer.y*D3DX_PI / 180)*speed;
			break;

			//�����
		case LEFTDOWN:
			Dir.z += cos(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x -= sin(RotPlayer.y*D3DX_PI / 180)*speed;

			Dir.z -= sin(RotPlayer.y*D3DX_PI / 180)*speed;
			Dir.x -= cos(RotPlayer.y*D3DX_PI / 180)*speed;
			break;
			}

			//���ɕ���
		case FLY:
			if (fly.y == 0)
			{
				fly.y = 30.0f;
			}
			break;

		case DAMAGE:

			Damaged = true;
			damagecooldown = 10;

			//�������Ɍ�ނ�����
			for (int i = 0; i <= 1; i++)
			{
				ChangePos(LEFT, 0, 10.0f);
			}
			break;

			//�_�E���\��
		case DAMAGEDOWN:
			Damaged = true;
			damagecooldown = 60;

			//���ɕ���
			fly.y = 50.0f;
			fly.z = cos(RotPlayer.y*D3DX_PI / 180)*speed;
			fly.x = sin(RotPlayer.y*D3DX_PI / 180)*speed;

			break;

			//�d�͂Ɉ���������
		case GRAVITY:
			Dir.x -= fly.x;
			Dir.y += fly.y;
			Dir.z += fly.z;

			//�����蔻��
			if (CheckHitPlayer(Dir) == false)
			{
				Hitcamera(false, i);
				PosPlayer = Dir;
			}
			else
			{
				Hitcamera(true, i);
				PosPlayer.y += fly.y;
				Dir = PosPlayer;
			}

			if (PosPlayer.y < NORMAL_Y)
			{
				PosPlayer.y = NORMAL_Y;
				fly = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			else
			{
				fly.y -= 1.4f;
			}

			break;


			//����ȊO
		default:
			break;
		}
	}

	//�v���C���[�𑊎�v���C���[�Ɍ��������킹��(�X�V����)
	void UpdateRot(D3DXVECTOR3 AnotherPos)
	{
		D3DXVECTOR3 vector = GetVector(AnotherPos, PosPlayer);

		RotPlayer.y = (((InitVector.x * vector.x) + (InitVector.y * vector.y) + (InitVector.z * vector.z)) / (sqrt((InitVector.x*InitVector.x) + (InitVector.y * InitVector.y) + (InitVector.z * InitVector.z)) * sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z))));
		if (PosPlayer.x >= AnotherPos.x)
		{
			RotPlayer.y = (1 + (RotPlayer.y + 1))*-1;
		}

		RotPlayer.y *= 90;
		RotPlayer.y += 90;
	}

	//�X�V����
	void Update()
	{
		//����p�̍��W���X�V
		arm.z = PosPlayer.z - cos(RotPlayer.y*D3DX_PI / 180)*700.0f;
		arm.x = PosPlayer.x - sin(-RotPlayer.y*D3DX_PI / 180)*700.0f;
		arm.y = PosPlayer.y + 600.0f;
		armstrong.z = PosPlayer.z - cos(RotPlayer.y*D3DX_PI / 180)*1000.0f;
		armstrong.x = PosPlayer.x - sin(RotPlayer.y*D3DX_PI / 180)*1000.0f;
		armstrong.y = PosPlayer.y + 600.0f;

		leg.z = PosPlayer.z - cos(RotPlayer.y*D3DX_PI / 180)*700.0f;
		leg.x = PosPlayer.x - sin(RotPlayer.y*D3DX_PI / 180)*700.0f;
		leg.y = PosPlayer.y + 300.0f;
		legstrong.z = PosPlayer.z - cos(RotPlayer.y*D3DX_PI / 180)*1000.0f;
		legstrong.x = PosPlayer.x - sin(RotPlayer.y*D3DX_PI / 180)*1000.0f;
		legstrong.y = PosPlayer.y + 300.0f;

		cooldown--;
		damagecooldown--;
	}

	//�����蔻��(���W,�_���[�W��,�g�p���Ă��邩�ǂ���,�_�E������,��������,���������̃i���o�[)
	void Colision(D3DXVECTOR3 arms, int damage ,bool attacks, bool Down,bool shoot,int number,int eneattack)
	{
		D3DXVECTOR3 attackpos;		//�U���|�W�V����

		if (damagecooldown <= 0)
		{
			damagecooldown = 0;
			Damaged = false;
		}

		//�����蔻��ł��Ԃ���true��������
		if (PointtoRectangley(arms, PosPlayer, SclPlayer, attacks, 200.0f, 450.0f) == true)
		{
			//�_�E�����ʂ��L���������琁����΂�
			if (Down == true)
			{
				if (eneattack == PPUNCH || eneattack == PPUNCHSTRONG)
				{
					PlaySound(SOUND_LABEL_SE_PUNCH_FLY);
				}
				else
				{
					PlaySound(SOUND_LABEL_SE_KICK_FLY);
				}
				Hp -= damage;
				ChangePos(DAMAGEDOWN, 0, 50.0f);
			}
			//�Ȃ������炽���̃_���[�W��������
			else
			{
				if (shoot == true)
				{
					PlaySound(SOUND_LABEL_SE_PUNCH_HIT);
				}
				else
				{
					if (eneattack == PPUNCH)
					{
						PlaySound(SOUND_LABEL_SE_PUNCH_HIT);
					}
					else
					{
						PlaySound(SOUND_LABEL_SE_KICK_HIT);
					}
				}
				Hp -= damage;
				ChangePos(DAMAGE, 0, 50.0f);
			}
			if (shoot == true)
			{
				DisabledBullet(number);
			}
		}
	}

	//�U����true��
	void attack()
	{
		Attack = true;
		onehit = true;
	}

	//�U����false��
	void unleshdattack()
	{
		Attack = false;
	}

	//�R���{��1���₷
	void comboup()
	{
		combo += 1;
	}

	//�R���{�̃��Z�b�g
	void resetcombo()
	{
		combo = 0;
	}

	//
	void combotimeUpdate()
	{
		if (Attack == true)
		{
			combotime -= 0.1f;

			if (combotime <= 0.0f)
			{
				combotime = 0.0f;
				unleshdattack();
			}
		}

		onehit = false;
	}

	//���S����
	void Death(int index)
	{
		//�̗͂�0�ɂȂ����Ƃ��Ɏ��S������
		if (Hp <= 0)
		{
			RotPlayer.x -= 10.0f;
			//���S�t���O��false�̎�
			if (CheckDeath == false)
			{
				PlaySound(SOUND_LABEL_SE_DEATH);		//���SSE������
				//�v���C���[2���E������
				if (index == 0)
				{
					SetGameSet(1);		//�v���C���[2�ɃZ�b�g��t����
				}
				else
				{
					SetGameSet(0);		//�v���C���[1�ɃZ�b�g��t����
				}
				SetDeathflag();
				CheckDeath = true;		//���S�t���O��true����(2�d���[�v�h�~)
			}
		}
	}

	//
	bool cooldowncheck()
	{
		if (cooldown <= 0)
		{
			cooldown = 20;
			return true;
		}
		return false;
	}

	/*�Q�b�^�[*/

	bool Getattack()
	{
		return Attack;
	}

	bool Gethit()
	{
		return onehit;
	}

	bool GetDownAttack()
	{
		return downattack;
	}

	bool GetDamaged()
	{
		return Damaged;
	}

	int GetIdShadow()
	{
		return idxShadow;
	}

	int GetBeforAttack()
	{
		return beforattack;
	}

	int GetAttackpower()
	{
		return attackpower;
	}

	int CheckHp()
	{
		return Hp;
	}

	int CheckCombo()
	{
		return combo;
	}

	//�v���C���[�̍��W�����߂�
	D3DXVECTOR3 CheckPos()
	{
		return PosPlayer;
	}

	//�v���C���[�̃X�P�[��(�傫��)�����߂�
	D3DXVECTOR3 CheckScl()
	{
		return SclPlayer;
	}

	//�v���C���[�̊p�x�����߂�
	D3DXVECTOR3 CheckRot()
	{
		return RotPlayer;
	}

	D3DXVECTOR3 CheckArm()
	{
		return arm;
	}

	D3DXVECTOR3 CheckArmstrong()
	{
		return armstrong;
	}

	D3DXVECTOR3 CheckLeg()
	{
		return leg;
	}

	D3DXVECTOR3 CheckLegstrong()
	{
		return legstrong;
	}

	//�v���C���[�����݂̍U�����擾����
	D3DXVECTOR3 GetAttackPattan()
	{
		switch (beforattack)
		{
		case PPUNCH:
			attackpower = 10;
			return arm;
			break;

		case PPUNCHSTRONG:
			attackpower = 80;
			return armstrong;
			break;

		case PKICK:
			attackpower = 20;
			return leg;
			break;

		case PKICKSTRONG:
			attackpower = 80;
			return legstrong;
			break;
		default:
			return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		}
	}

	/*�Q�b�^�[�����܂�*/

	/*�Z�b�^�[*/
	void SetInitVector(D3DXVECTOR3 start, D3DXVECTOR3 end)
	{
		InitVector = GetVector(start, end);
	}

	//2P�ɔ��]������
	void SetRot(D3DXVECTOR3 rot)
	{
		RotPlayer.y = rot.y;
		RotPlayer.y -= 180;
	}

	void Setcombotime(float time)
	{
		combotime = time;
	}

	//�_���[�W�d�����鎞�Ԃ̃Z�b�g
	void SetDamagedtime(int time)
	{
		damagecooldown = time;
	}

	//�_�E�����ʂ�t����
	void SetDownAttack(bool Set)
	{
		downattack = Set;
	}

	//�O�ɍU�����Ă����̂��Z�b�g
	void SetBeforAttack(int Set)
	{
		beforattack = Set;
	}

	//�_���[�W��ݒ�
	void Setdamage()
	{
		switch (beforattack)
		{
		case PPUNCH:
			attackpower = 100;
			break;

		case PPUNCHSTRONG:
			attackpower = 500;
			break;

		case PKICK:
			attackpower = 200;
			break;

		case PKICKSTRONG:
			attackpower = 600;
			break;
		default:
			attackpower = 0;
			break;
		}
	}
};

//*****************************************************************************
//�N���X�̃O���[�o���錾
//*****************************************************************************
player g_player[MAX_PLAYER];

//=============================================================================
// ����������
//=============================================================================
HRESULT Player_Initialize(void)
{

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_player[0].PlayerInit(INIT_PLAYERONE_POS, INIT_PLAYERONE_ROT);		//�v���C���[1�̏�������
	g_player[1].PlayerInit(INIT_PLAYERTWO_POS, INIT_PLAYERTWO_ROT);		//�v���C���[2�̏�������
	g_player[0].SetInitVector(g_player[1].CheckPos(), g_player[0].CheckPos());		//���x�N�g�������(�v���C���[��]�ɕK�v)
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Player_Finalize(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_player[i].PlayerFinalize();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Player_Update(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_player[i].combotimeUpdate();												//�R���{�@�\
		g_player[i].ChangePos(GRAVITY, 0, 50.0f);									//�d�͂�t����
		g_player[i].Death(i);														//���S����
		Shadow_SetPosition(g_player[i].GetIdShadow(), g_player[i].CheckPos());		//�e�̍X�V����
	}

	//1P�̏���
	{
		if (g_player[0].GetDamaged() == false)
		{
			//�ړ����� (��)
			if (Keyboard_IsPress(DIK_D) || GamePad_IsPress(0, BUTTON_LEFT))
			{
				if (Keyboard_IsPress(DIK_S))
				{// �����ړ�
					g_player[0].ChangePos(RIGHTDOWN, 0, 50.0f);
				}
				else if (Keyboard_IsPress(DIK_W))
				{// ����O�ړ�
					g_player[0].ChangePos(RIGHTUP, 0, 50.0f);
				}
				else
				{// ���ړ�
					g_player[0].ChangePos(RIGHT, 0, 50.0f);
				}
			}

			//�ړ�����(�E)
			else if (Keyboard_IsPress(DIK_A) || GamePad_IsPress(0, BUTTON_RIGHT))
			{

				if (Keyboard_IsPress(DIK_S))
				{// �E���ړ�
					g_player[0].ChangePos(LEFTDOWN, 0, 50.0f);
				}

				else if (Keyboard_IsPress(DIK_W))
				{// �E��O�ړ�
					g_player[0].ChangePos(LEFTUP, 0, 50.0f);
				}

				else
				{// �E�ړ�
					g_player[0].ChangePos(LEFT, 0, 50.0f);
				}
			}

			//�O�ړ�
			else if (Keyboard_IsPress(DIK_S) || GamePad_IsPress(0, BUTTON_UP))
			{// ���ړ�
				g_player[0].ChangePos(DOWN, 0, 50.0f);
			}

			//���ړ�
			else if (Keyboard_IsPress(DIK_W) || GamePad_IsPress(0, BUTTON_DOWN))
			{// ��O�ړ�
				g_player[0].ChangePos(UP, 0, 50.0f);
			}

			//�󒆕��V
			else if (Keyboard_IsPress(DIK_SPACE) || GamePad_IsPress(0, BUTTON_DOWN))
			{// ��O�ړ�
				g_player[0].ChangePos(FLY, 0, 50.0f);
			}

			//Y�Ō��U��
			if (Keyboard_IsTrigger(DIK_Y))
			{
				//�R���{��3�𒴂����� + �O�̍U�����p���`������(���̍U�����O�Ɠ���)
				if (g_player[0].CheckCombo() > 1 && g_player[0].GetBeforAttack() == PPUNCH)
				{//���U���ɂ���
					g_player[0].SetDownAttack(true);		//�_�E�����ʂ�t����
					g_player[0].attack();
					SetPolygon(g_player[0].CheckLeg());
					g_player[0].resetcombo();
					g_player[0].Setcombotime(2.0f);
					g_player[0].SetBeforAttack(PKICK);
					PlaySound(SOUND_LABEL_SE_KICK_MISS);
				}
				else
				{
					//�O�̍U�����p���`��������
					if (g_player[0].GetBeforAttack() == PPUNCH)
					{
						g_player[0].SetDownAttack(false);		//�_�E�����ʂ��O��
						g_player[0].attack();
						SetPolygon(g_player[0].CheckArm());
						g_player[0].comboup();
						g_player[0].Setcombotime(2.0f);
						g_player[0].SetBeforAttack(PPUNCH);
						PlaySound(SOUND_LABEL_SE_PUNCH_MISS);
					}
					//�O�̍U�������̑��������Ƃ�
					else
					{
						g_player[0].SetDownAttack(false);		//�_�E�����ʂ��O��
						g_player[0].attack();
						SetPolygon(g_player[0].CheckArm());
						g_player[0].resetcombo();
						g_player[0].Setcombotime(2.0f);
						g_player[0].SetBeforAttack(PPUNCH);
						PlaySound(SOUND_LABEL_SE_PUNCH_MISS);
					}
				}
			}

			//H�ő��U��
			if (Keyboard_IsTrigger(DIK_H))
			{
				//�O�̍U�����R�肾������
				if (g_player[0].GetBeforAttack() == PKICK)
				{
					if (g_player[0].CheckCombo() > 1 && g_player[0].GetBeforAttack() == PKICK)
					{
						g_player[0].SetDownAttack(true);		//�_�E�����ʂ��O��
						g_player[0].attack();
						SetPolygon(g_player[0].CheckLeg());
						g_player[0].resetcombo();
						g_player[0].Setcombotime(2.0f);
						g_player[0].SetBeforAttack(PKICK);
						PlaySound(SOUND_LABEL_SE_KICK_MISS);
					}
					else
					{
						g_player[0].SetDownAttack(false);		//�_�E�����ʂ��O��
						g_player[0].attack();
						SetPolygon(g_player[0].CheckLeg());
						g_player[0].comboup();
						g_player[0].Setcombotime(2.0f);
						g_player[0].SetBeforAttack(PKICK);
						PlaySound(SOUND_LABEL_SE_KICK_MISS);

					}
				}
				//�O�̍U�������̑��������Ƃ�
				else
				{
					g_player[0].SetDownAttack(false);		//�_�E�����ʂ��O��
					g_player[0].attack();
					SetPolygon(g_player[0].CheckLeg());
					g_player[0].resetcombo();
					g_player[0].Setcombotime(2.0f);
					g_player[0].SetBeforAttack(PKICK);
					PlaySound(SOUND_LABEL_SE_KICK_MISS);
				}
			}

			//U�Ō����U��
			if (Keyboard_IsTrigger(DIK_U))
			{
				g_player[0].SetDownAttack(true);		//�_�E�����ʂ��O��
				g_player[0].attack();
				g_player[0].resetcombo();
				g_player[0].SetBeforAttack(PPUNCHSTRONG);
				SetPolygon(g_player[0].CheckArmstrong());
				PlaySound(SOUND_LABEL_SE_PUNCH_MISS);
			}

			//J�ő����U��
			if (Keyboard_IsTrigger(DIK_J))
			{
				g_player[0].SetDownAttack(true);		//�_�E�����ʂ��O��
				g_player[0].attack();
				g_player[0].resetcombo();
				g_player[0].SetBeforAttack(PKICKSTRONG);
				SetPolygon(g_player[0].CheckLegstrong());
				PlaySound(SOUND_LABEL_SE_KICK_MISS);
			}

			//N�œ���U��
			if (Keyboard_IsTrigger(DIK_N))
			{
				g_player[0].SetDownAttack(true);		//�_�E�����ʂ��O��
				g_player[0].attack();
				g_player[0].resetcombo();
				SetBill(g_player[0].CheckPos(),0);		//����ݒu
			}
		}
	}

	//2P�̏���������
	switch (GetAI())
	{
	case WAITTIME:
		break;

	case BACKMOVE:
		g_player[1].ChangePos(LEFT, 0, 40.0f);
		break;

	case SEKKINMOVE:
		g_player[1].ChangePos(RIGHT, 0, 40.0f);
		break;

	case PUNCH:
		//�R���{��3�𒴂�����
		if (g_player[1].cooldowncheck() == true)
		{
			if (g_player[1].CheckCombo() > 1)
			{
				g_player[1].SetDownAttack(true);		//�_�E�����ʂ�t����
				g_player[1].attack();
				SetPolygon(g_player[1].CheckLeg());
				g_player[1].resetcombo();
				g_player[1].Setcombotime(2.0f);
				g_player[1].SetBeforAttack(PPUNCH);
				PlaySound(SOUND_LABEL_SE_KICK_MISS);
			}
			else
			{
				g_player[1].SetDownAttack(false);		//�_�E�����ʂ��O��
				g_player[1].attack();
				SetPolygon(g_player[1].CheckArm());
				g_player[1].comboup();
				g_player[1].Setcombotime(2.0f);
				g_player[1].SetBeforAttack(PPUNCH);
				PlaySound(SOUND_LABEL_SE_PUNCH_MISS);
			}
		}
		break;

	case KICK:
		if (g_player[1].cooldowncheck() == true)
		{
			if (g_player[1].CheckCombo() > 1)
			{
				g_player[1].SetDownAttack(true);		//�_�E�����ʂ�t����
				g_player[1].attack();
				SetPolygon(g_player[1].CheckLeg());
				g_player[1].resetcombo();
				g_player[1].Setcombotime(2.0f);
				g_player[1].SetBeforAttack(PKICK);
				PlaySound(SOUND_LABEL_SE_KICK_MISS);
			}
			else
			{
				g_player[1].SetDownAttack(false);		//�_�E�����ʂ��O��
				g_player[1].attack();
				SetPolygon(g_player[1].CheckLeg());
				g_player[1].comboup();
				g_player[1].Setcombotime(2.0f);
				g_player[1].SetBeforAttack(PKICK);
				PlaySound(SOUND_LABEL_SE_KICK_MISS);
			}
		}
		break;

	case DAMAGED:
		break;

	default:
		break;
	}

	//���菈��
	g_player[0].Update();
	g_player[1].Update();

	//�_���[�W
	g_player[0].Setdamage();
	g_player[1].Setdamage();

	//�����蔻��
	g_player[0].Colision(g_player[1].GetAttackPattan(), g_player[1].GetAttackpower(), g_player[1].Gethit(),g_player[1].GetDownAttack(),false,0,g_player[1].GetBeforAttack());
	g_player[1].Colision(g_player[0].GetAttackPattan(), g_player[0].GetAttackpower(), g_player[0].Gethit(), g_player[0].GetDownAttack(),false,0, g_player[0].GetBeforAttack());

	//�����蔻��(�������U��)
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (GetBulletUse(i) == true)
		{
			g_player[0].Colision(GetBulletPos(i), 100, true, false,true,i, g_player[1].GetBeforAttack());
			g_player[1].Colision(GetBulletPos(i), 100, true, false,true,i, g_player[0].GetBeforAttack());
		}
	}

	//�v���C���[�ƃv���C���[���������킹��
	g_player[0].UpdateRot(g_player[1].CheckPos());		//1P�݂̂ɂ��� (2P�ɂ�����ƃo�O��)
	g_player[1].SetRot(g_player[0].CheckRot());			//1P�̕����Ɍ����������L�����ɂ���

}

//=============================================================================
// �`�揈��
//=============================================================================
void Player_Draw(void)
{
	for (int i = 0; i < MAX_PLAYER ; i++)
	{
		LPDIRECT3DDEVICE9 static pDevice = GetD3DDevice();
		D3DXMATRIX static mtxScl, mtxRot, mtxTranslate;
		D3DXVECTOR3 plscl, plpos, plrot;

		//�v���C���[�̑傫���A���W�A�p�x���󂯂Ƃ�
		plscl = g_player[i].CheckScl();
		plpos = g_player[i].CheckPos();
		plrot = g_player[i].CheckRot();

		//���[���h�}�g���N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldField);

		//�X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, plscl.x, plscl.y, plscl.z);
		D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxScl);

		//��]�𔽉f(��]������Ƃ��͂����؂�ɉ�]������Ƃ悭�Ȃ�)
		D3DXMatrixRotationYawPitchRoll(&mtxRot, plrot.y, plrot.x, plrot.z);
		D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);
		//�����؂�ɉ�]������Ƃ��̓N�H�[�^�j�I�����g��

		//�ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, plpos.x, plpos.y, plpos.z);
		D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTranslate);

		//���[���h�}�g���N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldField);

		//�q�g�̕\��
		Xfile_Draw(g_player[i].CheckScl(), g_player[i].CheckPos(), g_player[i].CheckRot()/ -55, HUMAN);

		
	}
}

//=============================================================================
// �v���C���[�̉�]���󂯎��
//=============================================================================
D3DXVECTOR3 GetRot(int index)
{
	return g_player[index].CheckRot();
}

D3DXVECTOR3 GetPos(int index)
{
	return g_player[index].CheckPos();
}

int GetHp(int index)
{
	return g_player[index].CheckHp();
}