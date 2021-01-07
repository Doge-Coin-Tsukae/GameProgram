//****************************************************
//�e�֌W�̃v���O����
//****************************************************

#include "target_tutorial.h"
#include "bullet.h"
#include "xfile.h"
#include "colision.h"
#include "score_draw.h"
#include "sound.h"
#include "particle.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_TARGET_TUTORIAL 20								//�\���I�̑���
#define MAX_HP	   1


//*****************************************************************************
//�N���X
//*****************************************************************************
//�I�̃N���X
class TARGETS_TUTORIAL {
private:
	bool live;				//�ǂ����݂��邩�ǂ���
	int  type;				//���̒l�ɂ���ĐF���ς��
	int	 Hp;				//�I��Hp
	float radius;			//���a
	D3DXVECTOR3				PosTgt;					// �n�ʂ̈ʒu
	D3DXVECTOR3				RotTgt;					// �n�ʂ̌���(��])
	D3DXVECTOR3				SclTgt;					// �n�ʂ̑傫��(�X�P�[��)

public:
	D3DXMATRIX				g_mtxWorldField;		// ���[���h�}�g���b�N�X(�s��)
	//�R���X�g���N�^
	TARGETS_TUTORIAL()
	{
		live = false;								//�I�̑��ݖ��E
		radius = 70.0f;							//�I�̔��a
		type = TARGETWHITE;							//�I�̃^�C�v���w��(�S�����F��)
		Hp = MAX_HP;								//�̗͂��ő�l��
		PosTgt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�������W
		RotTgt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//������]
		SclTgt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����傫��
	}

	void Finalize()
	{
		live = false;				//�I��S������
		type = TARGETWHITE;			//�܂Ƃ̏�Ԃ𔒂ɖ߂�
		Hp = MAX_HP;				//�̗͂��ő�l��
	}

	//�I�̂̔z�u(�ݒu���W,�X�P�[��(�傫��)�̎w��)
	void SetObject(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Scl)
	{
		if (live == false)
		{
			PosTgt = Pos;
			RotTgt = Rot;
			SclTgt = Scl;
			type = TARGETWHITE;
			live = true;
		}
	}

	//�X�V����
	void Update()
	{
		//�e�̐��������ׂ�
		for (int i = 0; i < BULLET_NUM; i++)
		{
			//�X�s�[�h��0.1�����₵�Ă���
			for (float j = 0.0f; j < GetSpeed(i); j += 0.01f)
			{
				//���肪True��������
				if (CircleAndPoint(PosTgt, GetBulletPos(i) - (-GetOne(i) * j), radius) &&			//Z���W
					live == true && GetUse(i) && GetMove(i) == true)			//���̓I���g���Ă��� + ���̒e���g���Ă��� + ���̒e�������Ă���
				{

					PlaySound(SOUND_LABEL_SE_TARGET_HIT);

					Hp--;				//hp�����炷
					StopBullet(i);				//�e���~������

					//�̗͂�0�ɂȂ����Ƃ�
					if (Hp <= 0)
					{
						addscore(GetPlyNum(i), 1);		//�X�R�A��������

						//�����I��player�����L���Ă����Ƃ�
						if (type != TARGETWHITE)
						{
							addscore(type - 2, -1);		//�I�̎����匸�_
						}

						//�p�[�e�B�N���̃Z�b�g
						if (GetPlyNum(i) == 0)
						{
							ParticleSetNum(5, PosTgt, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.85f), 30.0f, 30.0f, 60, 0);
						}
						if (GetPlyNum(i) == 1)
						{
							ParticleSetNum(5, PosTgt, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.90f), 30.0f, 30.0f, 60, 0);
						}

						type = GetPlyNum(i) + 2;	//���̃v���C���[�̕��ɂ��� (x�t�@�C���̓s����)+2
						Hp = MAX_HP;				//�̗͂��񕜂�����
					}
					break;
				}

				if (GetMove(i) == false)
				{
					break;
				}

				if (GetUse(i) == false)
				{
					break;
				}
			}
		}
	}

	//�ǂ����݂��Ă��邩�ǂ������ׂ�
	bool Getlive()
	{
		return live;
	}

	//�I�̐F���擾
	int Gettype()
	{
		return type;
	}

	//���W���擾
	D3DXVECTOR3 GetPos()
	{
		return PosTgt;
	}

	//�p�x���擾
	D3DXVECTOR3 GetRot()
	{
		return RotTgt;
	}

	//�X�P�[�����擾
	D3DXVECTOR3 GetScl()
	{
		return SclTgt;
	}
};

static TARGETS_TUTORIAL g_TargetTutorial[NUM_TARGET_TUTORIAL];

//=============================================================================
// ����������
//=============================================================================
HRESULT Target_Tutorial_Initialize(void)
{
	//�I�̐ݒu
	g_TargetTutorial[0].SetObject(D3DXVECTOR3(-1825.0f, 250.0f, 1325.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));
	g_TargetTutorial[1].SetObject(D3DXVECTOR3(-1825.0f, 175.0f, 975.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));

	g_TargetTutorial[2].SetObject(D3DXVECTOR3(-1325.0f, 75.0f, 825.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));
	g_TargetTutorial[3].SetObject(D3DXVECTOR3(-1325.0f, 175.0f, 475.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));

	g_TargetTutorial[4].SetObject(D3DXVECTOR3(-825.0f, 125.0f, 325.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));
	g_TargetTutorial[5].SetObject(D3DXVECTOR3(-825.0f, 175.0f, -25.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));

	g_TargetTutorial[6].SetObject(D3DXVECTOR3(825.0f, 125.0f, -325.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));
	g_TargetTutorial[7].SetObject(D3DXVECTOR3(825.0f, 175.0f, 25.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));

	g_TargetTutorial[8].SetObject(D3DXVECTOR3(1325.0f, 75.0f, -825.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));
	g_TargetTutorial[9].SetObject(D3DXVECTOR3(1325.0f, 175.0f, -475.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));

	g_TargetTutorial[10].SetObject(D3DXVECTOR3(1825.0f, 250.0f, -1325.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));
	g_TargetTutorial[11].SetObject(D3DXVECTOR3(1825.0f, 175.0f, -975.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 2.5f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Target_Tutorial_Finalize(void)
{
	for (int i = 0; i < NUM_TARGET_TUTORIAL; i++)
	{
		g_TargetTutorial[i].Finalize();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Target_Tutorial_Update(void)
{
	//���[���h�ϊ�
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	//���[���h�}�g���N�X�̏�����
	for (int i = 0; i < NUM_TARGET_TUTORIAL; i++)
	{
		//�I�����݂��Ă����Ƃ��A����������
		if (g_TargetTutorial[i].Getlive() == true)
		{

			D3DXMatrixIdentity(&g_TargetTutorial[i].g_mtxWorldField);

			//��]�𔽉f
			/*���̊֐��͌���1�{�̎��̓�������*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_TargetTutorial[i].GetRot().y, g_TargetTutorial[i].GetRot().x, g_TargetTutorial[i].GetRot().z);		//���[�A�s�b�`�A���[��	���[�ƃ��[�������������ɂȂ邱��=�W���o�����b�N
			D3DXMatrixMultiply(&g_TargetTutorial[i].g_mtxWorldField, &g_TargetTutorial[i].g_mtxWorldField, &mtxRot);				//��]*���[���h

			//�ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_TargetTutorial[i].GetPos().x, g_TargetTutorial[i].GetPos().y, g_TargetTutorial[i].GetPos().z);
			D3DXMatrixMultiply(&g_TargetTutorial[i].g_mtxWorldField, &g_TargetTutorial[i].g_mtxWorldField, &mtxTranslate);			//�ړ�*���[���h

			//�X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, g_TargetTutorial[i].GetScl().x, g_TargetTutorial[i].GetScl().y, g_TargetTutorial[i].GetScl().z);
			D3DXMatrixMultiply(&g_TargetTutorial[i].g_mtxWorldField, &g_TargetTutorial[i].g_mtxWorldField, &mtxScl);				//�g��E�k��*���[���h

			g_TargetTutorial[i].Update();
		}

	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void Target_Tutorial_Draw(void)
{
	//���[���h�}�g���N�X�̐ݒ�
	for (int i = 0; i < NUM_TARGET_TUTORIAL; i++)
	{
		//�ǂ����݂��Ă����Ƃ��A�`�悷��
		if (g_TargetTutorial[i].Getlive() == true)
		{
			Xfile_Draw(g_TargetTutorial[i].GetScl(), g_TargetTutorial[i].GetPos(), g_TargetTutorial[i].GetRot(), g_TargetTutorial[i].Gettype());
		}
	}
}

int GetColor_Tutorial(int index)
{
	return g_TargetTutorial[index].Gettype();
}