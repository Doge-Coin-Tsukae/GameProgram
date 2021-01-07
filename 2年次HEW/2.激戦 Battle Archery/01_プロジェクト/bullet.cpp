//****************************************************
//�e�֌W�̃v���O����
//****************************************************

#include "bullet.h"
#include "myDirect3D.h"
#include "camera.h"
#include "object.h"
#include "sound.h"
#include "xfile.h"
#include "player.h"
#include "Vector.h"
#include "field.h"
#include "point.h"
#include "particle.h"
#include "wall.h"
#include "wall_tate.h"
#include "wall_tutorial.h"
#include "wall_tate_tutorial.h"
#include "piller_tutorial.h"
#include "piller.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GRAVITY			(0.3f)						//�d��
#define TIMER_MAX		(30.0f)						//�e��������܂ł̎���

//*****************************************************************************
//�N���X
//*****************************************************************************

//�e�̃N���X
class BULLET {
private:
	D3DXVECTOR3		PosBullet;				//�e�̃|�W�V����
	D3DXVECTOR3		PosCamera;				//�J�����̒����_������
	D3DXVECTOR3		RotBullet;				// �e�̌���(��])
	D3DXVECTOR3		SclBullet;				//�e�̑傫��
	D3DXVECTOR3		LoadPos;				//�i��ł������W
	D3DXVECTOR3		OneVector;				//1�x�N�g�������

	int				PlayerNumber;			//�������e�̔ԍ�
	float			speed;					//�e�̑��x
	float			timer;					//�e�̗L������
	bool			Use;					//�e�̎g�p��
	bool			Move;					//�ړ����Ă��邩
	bool			Parti;					//�p�[�e�B�N���̐���
public:
	//�e�̏�������
	void BulletInit()
	{
		//�ϐ��̏�����
		PosBullet = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		RotBullet = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SclBullet = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		LoadPos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		OneVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		PlayerNumber = 0;
		timer = 0.0f;
		speed = 50.0f;
		Use = false;
		Move = false;
		Parti = false;
	}

	//�e��ݒu����
	void Enabled(D3DXVECTOR3 ppos,float pow,int FirePlayer)
	{
		PlayerNumber = FirePlayer;				//�e�Ƀv���C���[�ԍ�����
		PosCamera = Get_Pos(PlayerNumber);		//�Ə����K��
		PosCamera.y -= 40.0f;					//�J������Y���W��������(��ʂɍ��킹��)
		PosBullet = ppos;						//�v���C���[�̍��W������
		PosBullet.y += 100.0f;					//�v���C���[��Y���W������(�|�ɍ��킹��)
		speed += pow;							//�e�̑��x���w��
		timer = TIMER_MAX;		//�e��������܂ł̎��Ԃ�����
		Use = true;				//�e��L���ɂ���
		Move = true;			//�e�̈ړ���L���ɂ���		

		//�P�ʃx�N�g�������
		OneVector = GetVector(PosBullet, PosCamera);
		//�i�ރX�s�[�h��������
		LoadPos = OneVector * speed;

		//�p�x����
		RotBullet = GetRot(PlayerNumber) / -57;	//�v���C���[�̊p�x��e�̊p�x�ɓ����
	}

	//�e�̍��W���X�V����
	void Update()
	{
		//�e�����ł���Ƃ�
		if (Move == true)
		{
			PosBullet += LoadPos;		//�e�̍X�V
			LoadPos.y -= GRAVITY;//�e��������悤�ɂ���(�d��)
		}

		//�����蔻��
		for (float i = 0; i < speed; i += 0.1f) {
			//�e���ǂɐڐG�A���͒n�ʂɐڐG�����Ƃ�
			if (CheckHitPlayer(PosBullet - (-OneVector*i)) == true ||
				CheckHitPlayer_vs_Wall(PosBullet - (-OneVector * i)) == true ||
				CheckHitPlayer_vs_WallTate(PosBullet - (-OneVector * i)) == true ||
				CheckHitPlayer_vs_PILLER(PosBullet - (-OneVector * i)) == true ||
				CheckHitPlayer_vs_WallTutorial(PosBullet - (-OneVector * i)) == true ||
				CheckHitPlayer_vs_WallTateTutorial(PosBullet - (-OneVector * i)) == true ||
				CheckHitPlayer_vs_PillerTutorial(PosBullet - (-OneVector * i)) == true ||

				PosBullet.y <= FIELD_HIGHT)
			{
				if (Parti == false)
				{
					ParticleSetNum(10, PosBullet, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.85f), 30.0f, 30.0f, 60, 0);	//�p�[�e�B�N���̃Z�b�g
					Parti = true;
				}
				Move = false;
				break;
			}
		}

		timer -= 0.1f;		//1�t���[����0.1�����炷

	}

	//�e�̎g�p�󋵂𒲂ׂ�
	bool CheckMove()
	{
		return Move;
	}

	//�e�̓������~�߂�
	void StopMove()
	{
		Move = false;
	}

	//�e������
	void disabled()
	{
		Move = false;		//�ړ��𖳌��ɂ���
		Use = false;		//�e�𖳌��ɂ���
		Parti = false;
		timer = 0.0f;		//���Ԃ�0�ɂ���
		speed = 1.0f;		//�e�̑��x���Z�b�g
	}

	//�L�����Ԃ̊m�F
	float CheckTimer()
	{
		return timer;
	}

	//�g�p�󋵂̊m�F
	bool CheckUse()
	{
		return Use;
	}

	//�e���������l�̔ԍ�
	int CheckNum()
	{
		return PlayerNumber;
	}

	//���W�̊m�F
	D3DXVECTOR3 CheckPos()
	{
		return PosBullet;
	}

	//�傫���̊m�F
	D3DXVECTOR3 CheckScl()
	{
		return SclBullet;
	}

	//��]�̊m�F
	D3DXVECTOR3 CheckRot()
	{
		return RotBullet;
	}

	D3DXVECTOR3 CheckOne()
	{
		return OneVector;
	}

	float CheckSpeed()
	{
		return speed;
	}
};

BULLET  bullet[BULLET_NUM];

//*****************************************************************************
//�֐�
//*****************************************************************************

/*��������*/
HRESULT Bullet_Initialize(void)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		bullet[i].BulletInit();
	}
	return S_OK;
}

/*�I������*/
void Bullet_Finalize(void)
{

}

/*�X�V����*/
void Bullet_Update(void)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		//�e���g�p����Ă���ꍇ�A����������
		if (bullet[i].CheckUse() == true)
		{
			bullet[i].Update();		//�e�̍X�V����

			//�L�����Ԃ��؂�Ă��邩
			if (bullet[i].CheckTimer() <= 0.0f)
			{
				bullet[i].disabled();		//�e������
			}

		}
	}
}

/*�`�揈��*/
void Bullet_Draw(void)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		//�e���g�p����Ă���ꍇ�A����������
		if (bullet[i].CheckUse() == true)
		{
			Xfile_Draw(bullet[i].CheckScl(), bullet[i].CheckPos(), bullet[i].CheckRot(),BOW);
		}
	}
}

void DeleteBullet(int index)
{
	bullet[index].disabled();
}

/*�O������e���g�p����Ƃ�*/
void SetBullet(D3DXVECTOR3 index,float pow, int Player)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		//�e���g�p����Ă��Ȃ��ꍇ�A����������
		if (bullet[i].CheckUse() == false)
		{
			bullet[i].Enabled(index,pow ,Player);		//�e��L���ɂ���
			break;
		}
	}
}

//�e���~������
void StopBullet(int index)
{
	bullet[index].StopMove();
}

//�e�̍��W���󂯎��
D3DXVECTOR3 GetBulletPos(int index)
{
	return bullet[index].CheckPos();
}

D3DXVECTOR3 GetBulletScl(int index)
{
	return bullet[index].CheckScl();
}

//�e���g���Ă��邩���󂯎��
bool GetUse(int index)
{
	return bullet[index].CheckUse();
}

//�e�̏��L�҂𒲂ׂ�
int GetPlyNum(int index)
{
	return bullet[index].CheckNum();
}

//�P�ʃx�N�g�����擾
D3DXVECTOR3  GetOne(int index)
{
	return bullet[index].CheckOne();
}

//�e�������Ă邩
bool GetMove(int index)
{
	return bullet[index].CheckMove();
}

//�e�̃X�s�[�h���擾
float GetSpeed(int index)
{
	return bullet[index].CheckSpeed();
}