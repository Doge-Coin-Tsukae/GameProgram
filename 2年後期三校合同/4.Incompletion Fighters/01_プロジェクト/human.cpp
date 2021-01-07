//****************************************************
//AI�̃v���O����
//****************************************************

#include "human.h"
#include "player.h"
#include "myDirect3D.h"
#include "Vector.h"
//*****************************************************************************
//�N���X
//*****************************************************************************
class PEAPLE 
{
private:
	int				AImode;					//�L�����N�^�[��AI���[�h
	int				waittime;				//�ҋ@����

public:
	//�v���C���[�̏�������
	void AIInit()
	{
		AImode = SEKKINMOVE;
		waittime = 0;
	}

	//�X�V����(AI�̍X�V����)
	void AIUpdate()
	{
		switch (AImode)
		{
		case WAITTIME:
			waittime++;		//�ҋ@���Ԃ̍X�V
			//180�b�ɂȂ�����X�V����
			if (waittime >= 10)
			{
				if (GetVectorfloat(GetPos(0), GetPos(1)) <= 900.0f)
				{
					if (GetVectorfloat(GetPos(0), GetPos(1)) <= 550.0f)
					{
						AImode = BACKMOVE;
					}
					else
					{
						if (rand() % 100 < 40)
						{
							AImode = PUNCH;
						}
						if (rand() % 100 < 40)
						{
							AImode = KICK;
						}
					}
				}
				else
				{
					//�����ɑ���AI�Ɉړ�����
					AImode = SEKKINMOVE;
				}
				waittime = 0;		//�ҋ@���Ԃ̃��Z�b�g
			}
			break;

			//�O�i
		case SEKKINMOVE:
			//�v���C���[�Ƃ̋�����700�ɂȂ�����
			if (GetVectorfloat(GetPos(0),GetPos(1)) <= 700.0f)
			{
					AImode = WAITTIME;
			}
			break;

			//��i
		case BACKMOVE:
			waittime++;
			if (GetVectorfloat(GetPos(0), GetPos(1)) >= 2300.0f)
			{
				waittime = 0;
				AImode = WAITTIME;
			}
			if (GetVectorfloat(GetPos(0), GetPos(1)) <= 700.0f)
			{
				waittime = 0;

				if (GetVectorfloat(GetPos(0), GetPos(1)) >= 540.0f)
				{
					if (rand() % 100 < 70)
					{
						AImode = PUNCH;
					}
					else
					{
						AImode = WAITTIME;
					}
				}
			}
			break;


			//���ōU��
		case PUNCH:
			waittime++;		//�ҋ@���Ԃ̍X�V
			//180�b�ɂȂ�����X�V����
			if (waittime >= 60)
			{
				//�����ɑ���AI�Ɉړ�����
				AImode = BACKMOVE;
				waittime = 0;		//�ҋ@���Ԃ̃��Z�b�g
			}
			break;

			//���ōU��
		case KICK:
			waittime++;		//�ҋ@���Ԃ̍X�V
			//180�b�ɂȂ�����X�V����
			if (waittime >= 1)
			{
				//�����ɑ���AI�Ɉړ�����
				AImode = BACKMOVE;
				waittime = 0;		//�ҋ@���Ԃ̃��Z�b�g
			}
			break;

			//�_���[�W�󂯂��Ƃ�
		case DAMAGED:
			break;

		default:
			break;
		}
	}

	/*�Q�b�^�[*/
	//�g�p�󋵂���ɓ����
	int GetAI()
	{
		return AImode;
	}
	/*�Q�b�^�[�����܂�*/

	/*�Z�b�^�[*/
	//�g�p�󋵂���ɓ����
	void SetAI(int SetAI)
	{
		AImode = SetAI;
	}
	/*�Q�b�^�[�����܂�*/
};

//*****************************************************************************
//�N���X�̃O���[�o���錾
//*****************************************************************************
PEAPLE g_peepe;

//=============================================================================
// ����������
//=============================================================================
HRESULT Human_Initialize(void)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_peepe.AIInit();		//�v���C���[1�̏�������
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Human_Finalize(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void Human_Update(void)
{
	g_peepe.AIUpdate();
}

//�Q�b�^�[
int GetAI(void)
{
	return g_peepe.GetAI();
}

//�Z�b�^�[
void SetAImode(int SetAI)
{
	g_peepe.SetAI(SetAI);
}