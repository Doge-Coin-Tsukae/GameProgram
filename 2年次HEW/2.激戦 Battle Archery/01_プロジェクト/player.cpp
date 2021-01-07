//==============================================================================
// File name / type  :  player.cpp
//  Private number   :  [HEW2019 project] - groupNo.3 
// Writer copyright  :  (C) HEW2019 project group All rights reserved.
//==============================================================================

//****************************************************
//�v���C���[�֌W�̃v���O����
//****************************************************


#include "bullet.h"
#include "colision.h"
#include "camera.h"
#include "field.h"
#include "input.h"
#include "myDirect3D.h"
#include "object.h"
#include "particle.h"
#include "player.h"
#include "piller.h"
#include "piller_tutorial.h"
#include "point.h"
#include "sound.h"
#include "selectcharctor.h"
#include "shadow.h"
#include "score_draw.h"
#include "saku.h"
#include "saku_yoko.h"
#include "texture.h"
#include "wall.h"
#include "wall_tutorial.h"
#include "wall_tate.h"
#include "wall_tate_tutorial.h"
#include "xfile.h"
#include "x_gamepad.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_ROTATE	(1.0f)				// ��]��
#define MAX_POWER		(100.0f)			// �p���[�̏��

#define INIT_PLAYERONE_POS  D3DXVECTOR3(0.0f,0.0f,2000.0f)
#define INIT_PLAYERTWO_POS  D3DXVECTOR3(0.0f,0.0f,-2000.0f)
#define INIT_PLAYERONE_ROT  D3DXVECTOR3(0.0f, 270.0f, 0.0f)
#define INIT_PLAYERTWO_ROT  D3DXVECTOR3(0.0f, 90.0f, 0.0f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DXMATRIX				static g_mtxWorldField;		// ���[���h�}�g���b�N�X(�s��)

//*****************************************************************************
//enum
//*****************************************************************************
enum ANIMEPATAN
{	
	WAIT,
	WALK,
	ATTACK,
	ANIMATION_MAX,
};


//*****************************************************************************
//�N���X
//*****************************************************************************

class player {

private:
	D3DXVECTOR3		PosPlayer;				//�v���C���[�̃|�W�V����
	D3DXVECTOR3		RotPlayer;				// �v���C���[�̌���(��])
	D3DXVECTOR3		SclPlayer;				//�v���C���[�̑傫��
	D3DXVECTOR3		Dir;					//�v���C���[�̍s����

	int				playercolor;			//�v���C���[�̍���
	int				idxShadow;				//�V���h�EID

	float			speed;					//�v���C���[�̑��x
	float			power;					//�͂̑傫��
	float			CoolTime;				//�e�̎c�S����
	float			fly;					//�؋󎞊�
	float			jump;					//�W�����v����
	bool			CoolDown;				//�e��������΂��肩
	bool			Attacktime;				//���|�������Ă��邩

public:

	//�v���C���[�̏�������(�������W,������]��)
	void PlayerInit(D3DXVECTOR3 IniPos, D3DXVECTOR3 IniRot,int index)
	{
		PosPlayer = IniPos;		//�������W
		RotPlayer = IniRot;			//������]
		SclPlayer = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			//�����傫��
		Dir = PosPlayer;									//����̍s������v���C���[�Ɠ�����

		idxShadow = Shadow_Create(PosPlayer, D3DXVECTOR3(1.0f, 1.0f, 1.0f));		//�e��Id�Z�b�g
		speed = 12.5f;										//�v���C���[�̑f����
		power = 0.0f;										//�̓��Z�b�g
		fly = 0.0f;
		jump = 0.0f;
		playercolor = HUMAN_JPN + GetCharaData(index);	//�v���C���[�̍��W������
		CoolDown = false;		//�e��łĂ��Ԃɂ���
		Attacktime = false;		//�|�������Ă��Ȃ��󋵂ɂ���
	}

	void PlayerFinalize()
	{
		Shadow_Release(idxShadow);
	}

	//���W�̕ύX(����(enum),����(0.0f,0.2f,0.5f,0.75f,1.0f))
	void ChangePos(int xyzpm ,int i)
	{

		switch (xyzpm) {
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

			//���ɕ���
		case FLY:
			fly = 300.0f;
			break;

			//���ɕ���
		case JUMP:
			jump = 20.0f;
			break;

			//�d�͂Ɉ���������
		case GRAVITY:
			Dir.y += fly;
			Dir.y += jump;
			//�n�ʂ���y���W���Ⴉ������
			if (PosPlayer.y <= FIELD_HIGHT)
			{
				PosPlayer.y = FIELD_HIGHT;	//�n�ʂƓ����ʒu��
				fly = 0.0f;					//��΂Ȃ�����
				jump = 0.0f;
			}
			else
			{
				fly -= 1.0f;
				jump = 0.0f;
			}
			break;

			//����ȊO
		default:
			break;
		}

		//�ǁE�w�i�E���̓����蔻��
		if ((CheckHitPlayer_vs_Wall(Dir) == false) && (CheckHitPlayer_vs_WallTate(Dir) == false) && 
			(CheckHitPlayer_vs_Saku(Dir) == false) && (CheckHitPlayer_vs_SakuYoko(Dir) == false) &&
			(CheckHitPlayer(Dir) == false) && (CheckHitPlayer_vs_PILLER(Dir) == false) && 
			(CheckHitPlayer_vs_WallTutorial(Dir) == false) && (CheckHitPlayer_vs_WallTateTutorial(Dir) == false) &&
			(CheckHitPlayer_vs_PillerTutorial(Dir) == false))
		{
			Hitcamera(false, i);
			PosPlayer = Dir;
		}

		else
		{
			Hitcamera(true, i);
			Dir = PosPlayer;
		}
	}

	//�͂��Ă߂�
	void PowerUp(int index)
	{
		if (power < MAX_POWER)
		{
			power += 1.5f;
		}
		else
		{
			StopAnimation(index);
		}
	}

	//�|�𔭎˂���̐��ɂ��� (true=���ˑ̐�, false=���ˌ�̑̐�)
	void changeAttackMode(bool index)
	{
		Attacktime = index;
	}

	//�e���˂̃N�[���^�C����L���ɂ��� (��𔭎ˌ�̃v���C���[����)
	void CoolDownEnabled()
	{
		CoolTime = 5.0f;
		CoolDown = true;
		power = 1.0f;
	}

	//�N�[���^�C���𖳌��ɂ���&���炷
	void CoolDownDisabled()
	{
		if (CoolTime <= 0.0f)
		{
			CoolTime = 0.0f;
			CoolDown = false;
		}
		CoolTime -= 0.1f;
	}

	//�v���C���[�ɑ���̒e���q�b�g�����Ƃ�knockback������
	void knockback(int index)
	{
		//�S�e�̔���
		for (int i = 0; i < BULLET_NUM; i++)
		{
			//�e���g���Ă��āA�v���C���[�ɖ������ĂāA���G�̒e�������ꍇ
			if (CheckHitPlayerToPlayer(GetBulletPos(i), PosPlayer, GetBulletScl(i), GetPlyNum(i), index) == true && GetUse(i) == true)
			{
				//�e�����ł��邩
				if (GetMove(i)==true)
				{
					DeleteBullet(i);			//�Y���̒e���폜
					for (int j = 0; j < 10; j++)
					{
						PlaySound(SOUND_LABEL_SE_PLAYER_HIT);
						ChangePos(DOWN, 0);			//���ɉ�����
						ChangePos(FLY, 0);
						changecamera(DOWN, index, speed);		//�J�������ꏏ��
					}
					ParticleSetNum(10, GetBulletPos(i), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 30.0f, 30.0f, 60, 0);
				}

			}
		}
	}

	//�w�肵���l�̐�������]�ɉ�����
	D3DXVECTOR3 AddRot(D3DXVECTOR3 index)
	{
		if (RotPlayer.y >= 360.0f)
		{
			RotPlayer.y = 0.0f;
		}
		if (RotPlayer.y < -0.9f)
		{
			RotPlayer.y = 359.0f;
		}

		return RotPlayer += index;
	}

	/*�Q�b�^�[*/
	
	//�N�[���_�E���𒲂ׂ�
	bool CheckCoolDown()
	{
		return CoolDown;
	}

	//���ݍU���p�����𒲂ׂ�
	bool CheckAttackMode()
	{
		return Attacktime;
	}

	//�v���C���[�����߂��͂�Ԃ�
	float CheckPower()
	{
		return power;
	}

	float GetSpeed()
	{
		return  speed;
	}

	int CheckPlayerColor()
	{
		return playercolor;
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

	int GetIdShadow()
	{
		return idxShadow;
	}
	/*�Q�b�^�[�����܂�*/

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
	g_player[0].PlayerInit(INIT_PLAYERONE_POS, INIT_PLAYERONE_ROT,0);		//�v���C���[1�̏�������
	g_player[1].PlayerInit(INIT_PLAYERTWO_POS, INIT_PLAYERTWO_ROT,1);		//�v���C���[2�̏�������

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
	//�v���C���[1
	{
		//�v���C���[���U���Ԑ��ł͂Ȃ��Ƃ��݈̂ړ�����
		if (g_player[0].CheckAttackMode() == false)
		{
			//�ړ�����(��)
			if (Keyboard_IsPress(DIK_A) || gamepad_inport(0, PP_LX) <= -5000)
			{
				if (Keyboard_IsPress(DIK_W) || gamepad_inport(0, PP_LY) >= 10000)
				{// �����ړ�
					g_player[0].ChangePos(LEFTUP, 0);
					changecamera(6, 0, g_player[0].GetSpeed());
					ChangePoint(6, 0, g_player[0].GetSpeed());
				}
				else if (Keyboard_IsPress(DIK_S) || gamepad_inport(0, PP_LY) <= -10000)
				{// ����O�ړ�
					g_player[0].ChangePos(LEFTDOWN, 0);
					changecamera(7, 0, g_player[0].GetSpeed());
					ChangePoint(7, 0, g_player[0].GetSpeed());
				}
				else
				{// ���ړ�
					g_player[0].ChangePos(LEFT, 0);
					changecamera(3, 0, g_player[0].GetSpeed());
					ChangePoint(3, 0, g_player[0].GetSpeed());
				}
				ChengeAnimation(0, WALK);
			}

			//�ړ�����(�E)
			else if (Keyboard_IsPress(DIK_D) || gamepad_inport(0, PP_LX) >= 5000)
			{
				if (Keyboard_IsPress(DIK_W) || gamepad_inport(0, PP_LY) >= 10000)
				{// �E���ړ�
					g_player[0].ChangePos(RIGHTUP, 0);
					changecamera(4, 0, g_player[0].GetSpeed());
					ChangePoint(4, 0, g_player[0].GetSpeed());
				}
				else if (Keyboard_IsPress(DIK_S) || gamepad_inport(0, PP_LY) <= -10000)
				{// �E��O�ړ�
					g_player[0].ChangePos(RIGHTDOWN, 0);
					changecamera(5, 0, g_player[0].GetSpeed());
					ChangePoint(5, 0, g_player[0].GetSpeed());
				}
				else
				{// �E�ړ�
					g_player[0].ChangePos(RIGHT, 0);
					changecamera(2, 0, g_player[0].GetSpeed());
					ChangePoint(2, 0, g_player[0].GetSpeed());
				}
				ChengeAnimation(0, WALK);
			}

			//�O�ړ�
			else if (Keyboard_IsPress(DIK_W) || gamepad_inport(0, PP_LY) >= 10000)
			{// ���ړ�
				g_player[0].ChangePos(UP, 0);
				changecamera(0, 0, g_player[0].GetSpeed());
				ChangePoint(0, 0, g_player[0].GetSpeed());
				ChengeAnimation(0, WALK);
			}

			//���ړ�
			else if (Keyboard_IsPress(DIK_S) || gamepad_inport(0, PP_LY) <= -10000)
			{// ��O�ړ�
				g_player[0].ChangePos(DOWN, 0);
				changecamera(1, 0, g_player[0].GetSpeed());
				ChangePoint(1, 0, g_player[0].GetSpeed());
				ChengeAnimation(0, WALK);
			}

			else 
			{
				ChengeAnimation(0, WAIT);
			}
			// �W�����v
			/*else if (Keyboard_IsPress(DIK_LSHIFT))
			{
				g_player[0].ChangePos(JUMP, 0);
				g_player[0].ChangePos(GRAVITY, 0);
				changecamera(JUMP, 0, g_player[0].GetSpeed());
				changecamera(GRAVITY, 0, g_player[0].GetSpeed());
			}*/

		}//���ɉ�]
		if (Keyboard_IsPress(DIK_F) || gamepad_inport(0, PP_RX) <= -5000)
		{// Z���E��]
			g_player[0].AddRot(D3DXVECTOR3(0.0f, VALUE_ROTATE, 0.0f));
			ChangeCamera(0, 0);
			ChangePointAngle(0, 0);
		}

		//�E�ɉ�]
		if (Keyboard_IsPress(DIK_H) || gamepad_inport(0, PP_RX) >= 5000)
		{// Z������]
			g_player[0].AddRot(D3DXVECTOR3(0.0f, -VALUE_ROTATE, 0.0f));
			ChangeCamera(0, 0);
			ChangePointAngle(0, 0);
		}

		//��L�[�ŃJ��������Ɍ�����
		if (Keyboard_IsPress(DIK_T) || gamepad_inport(0, PP_RY) >= 10000)
		{
			ChangeCameraVer(0, 0);
			ChangePointVer(0, 0);
		}

		//���L�[�ŃJ���������Ɍ�����
		if (Keyboard_IsPress(DIK_G) || gamepad_inport(0, PP_RY) <= -10000)
		{
			ChangeCameraVer(1, 0);
			ChangePointVer(1, 0);
		}

		//�X�y�[�X�������ė͂��Ă߂�
		if (Keyboard_IsPress(DIK_SPACE) && g_player[0].CheckCoolDown() == false && g_player[0].CheckAttackMode() == false)
		{
			ChengeAnimation(0, ATTACK);
			PlaySound(SOUND_LABEL_SE_CHARGE);
			g_player[0].changeAttackMode(true);								//�U���Ԑ���L���ɂ���
		}

		/*if (gamepad_inport(0, PP_LT) > 250 && g_player[0].CheckCoolDown() == false && g_player[0].CheckAttackMode() == false)
		{
			PlaySound(SOUND_LABEL_SE_CHARGE);
			g_player[0].changeAttackMode(true);
		}*/

		//�X�y�[�X�𗣂��Ēe�𔭎�
		if (Keyboard_IsRelease(DIK_SPACE) && g_player[0].CheckAttackMode() == true)
		{
			StopSound(SOUND_LABEL_SE_CHARGE);
			PlaySound(SOUND_LABEL_SE_SHOT);
			//�N�[���_�E����������������
			if (g_player[0].CheckCoolDown() == false)
			{
				SetBullet(g_player[0].CheckPos(), g_player[0].CheckPower(), 0);		//�e��ݒu����
				g_player[0].CoolDownEnabled();										//�e�̃N�[���_�E����L���ɂ���
				g_player[0].changeAttackMode(false);								//�U���Ԑ��𖳌��ɂ���
				LoadCameraPos(0);													//�Y�[������������		
			}
		}

		//if (gamepad_inport(0, PP_LT) < 255 && g_player[0].CheckAttackMode() == true)
		//{
		//	StopSound(SOUND_LABEL_SE_CHARGE);
		//	PlaySound(SOUND_LABEL_SE_SHOT);
		//	//�N�[���_�E����������������
		//	if (g_player[0].CheckCoolDown() == false)
		//	{
		//		SetBullet(g_player[0].CheckPos(), g_player[0].CheckPower(), 0);		//�e��ݒu����
		//		g_player[0].CoolDownEnabled();										//�e�̃N�[���_�E����L���ɂ���
		//		g_player[0].changeAttackMode(false);								//�U���Ԑ��𖳌��ɂ���
		//		LoadCameraPos(0);													//�Y�[������������		
		//	}
		//}
	}
	//�v���C���[2
	{
		//�v���C���[���U���Ԑ��ł͂Ȃ��Ƃ��݈̂ړ�����
		if (g_player[1].CheckAttackMode() == false)
		{
			//�ړ����� (��)
			if (Keyboard_IsPress(DIK_J) || gamepad_inport(1, PP_LX) <= -5000)
			{
				if (Keyboard_IsPress(DIK_I) || gamepad_inport(1, PP_LY) >= 10000)
				{// �����ړ�
					g_player[1].ChangePos(LEFTUP, 1);
					changecamera(6, 1, g_player[1].GetSpeed());
					ChangePoint(6, 1, g_player[1].GetSpeed());
				}
				else if (Keyboard_IsPress(DIK_K) || gamepad_inport(1, PP_LY) <= -10000)
				{// ����O�ړ�
					g_player[1].ChangePos(LEFTDOWN, 1);
					changecamera(7, 1, g_player[1].GetSpeed());
					ChangePoint(7, 1, g_player[1].GetSpeed());
				}
				else
				{// ���ړ�
					g_player[1].ChangePos(LEFT, 1);
					changecamera(3, 1, g_player[1].GetSpeed());
					ChangePoint(3, 1, g_player[1].GetSpeed());

				}
				ChengeAnimation(1, WALK);
			}

			//�ړ�����(�E)
			else if (Keyboard_IsPress(DIK_L) || gamepad_inport(1, PP_LX) >= 5000)
			{
				if (Keyboard_IsPress(DIK_I) || gamepad_inport(1, PP_LY) >= 10000)
				{
					g_player[1].ChangePos(RIGHTUP, 1);
					changecamera(4, 1, g_player[1].GetSpeed());
					ChangePoint(4, 1, g_player[1].GetSpeed());
				}
				else if (Keyboard_IsPress(DIK_K) || gamepad_inport(1, PP_LY) <= -10000)
				{// �E��O�ړ�
					g_player[1].ChangePos(RIGHTDOWN, 1);
					changecamera(5, 1, g_player[1].GetSpeed());
					ChangePoint(5, 1, g_player[1].GetSpeed());
				}
				else
				{// �E�ړ�
					g_player[1].ChangePos(RIGHT, 1);
					changecamera(2, 1, g_player[1].GetSpeed());
					ChangePoint(2, 1, g_player[1].GetSpeed());
				}
				ChengeAnimation(1, WALK);
			}

			//�O�ړ�
			else if (Keyboard_IsPress(DIK_I) || gamepad_inport(1, PP_LY) >= 10000)
			{// ���ړ�
				g_player[1].ChangePos(UP, 1);
				changecamera(0, 1, g_player[1].GetSpeed());
				ChangePoint(0, 1, g_player[1].GetSpeed());
				ChengeAnimation(1, WALK);
			}

			//���ړ�
			else if (Keyboard_IsPress(DIK_K) || gamepad_inport(1, PP_LY) <= -10000)
			{// ��O�ړ�
				g_player[1].ChangePos(DOWN, 1);
				changecamera(1, 1, g_player[1].GetSpeed());
				ChangePoint(1, 1, g_player[1].GetSpeed());
				ChengeAnimation(1, WALK);
			}

			else
			{
				ChengeAnimation(1, WAIT);
			}
		}

		//���ɉ�]
		if (Keyboard_IsPress(DIK_LEFT) || gamepad_inport(1, PP_RX) <= -5000)
		{// Z���E��]
			g_player[1].AddRot(D3DXVECTOR3(0.0f, VALUE_ROTATE, 0.0f));
			ChangeCamera(1, 1);
			ChangePointAngle(1, 1);
		}

		//�E�ɉ�]
		if (Keyboard_IsPress(DIK_RIGHT) || gamepad_inport(1, PP_RX) >= 5000)
		{// Z������]
			g_player[1].AddRot(D3DXVECTOR3(0.0f, -VALUE_ROTATE, 0.0f));
			ChangeCamera(1, 1);
			ChangePointAngle(1, 1);
		}

		//��L�[�ŃJ��������Ɍ�����
		if (Keyboard_IsPress(DIK_UP) || gamepad_inport(1, PP_RY) >= 10000)
		{
			ChangeCameraVer(0, 1);
			ChangePointVer(0, 1);
		}

		//���L�[�ŃJ���������Ɍ�����
		if (Keyboard_IsPress(DIK_DOWN) || gamepad_inport(1, PP_RY) <= -10000)
		{
			ChangeCameraVer(1, 1);
			ChangePointVer(1, 1);
		}

		//�X�y�[�X�������ė͂��Ă߂�
		if (Keyboard_IsPress(DIK_O) && g_player[1].CheckCoolDown() == false && g_player[1].CheckAttackMode() == false)
		{
			PlaySound(SOUND_LABEL_SE_CHARGE);
			g_player[1].changeAttackMode(true);								//�U���Ԑ���L���ɂ���
			ChengeAnimation(1, ATTACK);
		}

		/*if(gamepad_inport(1, PP_LT) > 250 && g_player[1].CheckCoolDown() == false && g_player[1].CheckAttackMode() == false)
		{
			PlaySound(SOUND_LABEL_SE_CHARGE);
			g_player[1].changeAttackMode(true);
		}*/

		//�X�y�[�X�𗣂��Ēe�𔭎�
		if (Keyboard_IsRelease(DIK_O) && g_player[1].CheckAttackMode() == true /*|| !GamePad_IsPress(1, BUTTON_M) && g_player.CheckAttackMode() == true*/)
		{
			StopSound(SOUND_LABEL_SE_CHARGE);
			PlaySound(SOUND_LABEL_SE_SHOT);
			//�N�[���_�E����������������
			if (g_player[1].CheckCoolDown() == false)
			{
				SetBullet(g_player[1].CheckPos(), g_player[1].CheckPower(), 1);		//�e��ݒu����
				g_player[1].CoolDownEnabled();									//�e�̃N�[���_�E����L���ɂ���
				g_player[1].changeAttackMode(false);							//�U���Ԑ��𖳌��ɂ���
				LoadCameraPos(1);											//�Y�[������������		
			}
		}

		//if(gamepad_inport(1, PP_LT) < 255 && g_player[1].CheckAttackMode() == true)
	//{
	//	StopSound(SOUND_LABEL_SE_CHARGE);
	//	PlaySound(SOUND_LABEL_SE_SHOT);
	//	//�N�[���_�E����������������
	//	if(g_player[1].CheckCoolDown() == false)
	//	{
	//		SetBullet(g_player[1].CheckPos(), g_player[1].CheckPower(), 1);		//�e��ݒu����
	//		g_player[1].CoolDownEnabled();										//�e�̃N�[���_�E����L���ɂ���
	//		g_player[1].changeAttackMode(false);								//�U���Ԑ��𖳌��ɂ���
	//		LoadCameraPos(1);													//�Y�[������������		
	//	}
	//}
	}

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		//�U���Ԑ��̎�
		if (g_player[i].CheckAttackMode() == true)
		{
			g_player[i].PowerUp(i);
 			ZoomCamera(i);
		}

		g_player[i].knockback(i);				//�e���v���C���[�Ƀq�b�g�����Ƃ��A�m�b�N�o�b�N����
		g_player[i].CoolDownDisabled();			//�N�[���_�E���𒲂ׂ�
		Shadow_SetPosition(g_player[i].GetIdShadow(), g_player[i].CheckPos());		//�e�̍X�V����
		g_player[i].ChangePos(GRAVITY, 0);
	}
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

		//��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, plrot.y, plrot.x, plrot.z);
		D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);

		//�ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, plpos.x, plpos.y, plpos.z);
		D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTranslate);

		//���[���h�}�g���N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldField);

		//�|�̕\��
		//Xfile_Draw(g_player[i].CheckScl(), g_player[i].CheckPos(), g_player[i].CheckRot() / -55, g_player[i].CheckPlayerColor());
		AnimationXfile_Draw(g_player[i].CheckScl(), g_player[i].CheckPos(), g_player[i].CheckRot() / -55, i);

	}
}

//=============================================================================
// �v���C���[�̉�]���󂯎��
//=============================================================================
D3DXVECTOR3 GetRot(int index)
{
	return g_player[index].CheckRot();
}

//=============================================================================
// �v���C���[�̍��W���󂯎��
//=============================================================================
D3DXVECTOR3 GetPos(int index)
{
	return g_player[index].CheckPos();
}

//���ׂ������̍��W�ƃu���b�N�̍��W�Ƃ̓����蔻��(bullet,�v���C���[1)
bool CheckHitPlayerToPlayer(D3DXVECTOR3 Ppos,D3DXVECTOR3 Bullet,D3DXVECTOR3 BulScl,int bulnum,int pnum)
{
	if (Ppos.x >= Bullet.x - (50.0f * BulScl.x) && Ppos.x <= Bullet.x + (50.0f * BulScl.x) &&			//X���W
		Ppos.y >= Bullet.y - (20.0f * BulScl.y) && Ppos.y <= Bullet.y + (150.0f * BulScl.y) &&		//Y���W
		Ppos.z >= Bullet.z - (50.0f * BulScl.z) && Ppos.z <= Bullet.z + (50.0f * BulScl.z) &&			//Z���W
		bulnum!=pnum)
	{
		return true;		//�u���b�N�̔�����ɂ���
	}

	return false;		//�u���b�N�̔���O�ɂ���
}

//�Q�[�W�̕\��
void PlayerScreenDraw(void)
{
	for (int i = 0; i<MAX_PLAYER; i++)
	{
		//��ʂɋ|���������Ƃ��ɏo��Q�[�W
		if (g_player[i].CheckAttackMode() == true)
		{
			Gauge_Draw(g_player[i].CheckPower(), i);
		}
	}
}