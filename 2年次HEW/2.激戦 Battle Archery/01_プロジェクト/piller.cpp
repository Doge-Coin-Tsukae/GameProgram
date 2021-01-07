//****************************************************
// ���֌W�̃v���O����
//****************************************************

#include "piller.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
#include "bullet.h"
#include "xfile.h"
#include "target.h"


// *****************************************************************************
// �}�N����`
// *****************************************************************************
#define NUM_PILLER 8								//�\�����钌�̍ő吔

// *****************************************************************************
// �N���X
// *****************************************************************************
// ���̃N���X
class PILLERS {
private:
	bool live;				//�ǂ����݂��邩�ǂ���
	int  type;				//���̒l�ɂ���ĐF���ς��


public:
	D3DXMATRIX				g_mtxWorldField;		// ���[���h�}�g���b�N�X(�s��)
	
	D3DXVECTOR3				PosPil;					// ���̈ʒu
	D3DXVECTOR3				RotPil;					// ���̌���(��])
	D3DXVECTOR3				SclPil;					// ���̑傫��(�X�P�[��)
													
													//�R���X�g���N�^
	PILLERS() {
		live = false;								//���̑��ݖ��E
		type = PILLER;
		PosPil = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�������W
		RotPil = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//������]
		SclPil = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����傫��
	}

	void Finalize()
	{
		live = false;				//�I��S������
		type = TARGETWHITE;			//�܂Ƃ̏�Ԃ𔒂ɖ߂�
	}

	// �������݂��Ă��邩�ǂ������ׂ�
	bool checklive()
	{
		return live;
	}

	// ���̐F���擾
	int checktype()
	{
		return type;
	}

	// ���̔z�u(�ݒu���W,�X�P�[��(�傫��)�̎w��)
	void SetObject(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Scl)
	{
		if (live == false)
		{
			PosPil = Pos;
			RotPil = Rot;
			SclPil = Scl;
			live = true;
			type = PILLER;
		}
	}

	//���W���擾
	D3DXVECTOR3 GetPos()
	{
		return PosPil;
	}

	//�p�x���擾
	D3DXVECTOR3 GetRot()
	{
		return RotPil;
	}

	//�X�P�[�����擾
	D3DXVECTOR3 GetScl()
	{
		return SclPil;
	}

	//�Z�b�^�[
	void SetType(int Set)
	{
		type = Set;
	}
};

static PILLERS g_Piller[NUM_PILLER];

//=============================================================================
// ����������
//=============================================================================
HRESULT Piller_Initialize(void)
{
	// ���̐ݒu
	g_Piller[0].SetObject(D3DXVECTOR3(-2000, 175.0f, 3125.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_Piller[1].SetObject(D3DXVECTOR3(2000.0f, 175.0f, 3125.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_Piller[2].SetObject(D3DXVECTOR3(-2000.0f, 175.0f, -3125.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_Piller[3].SetObject(D3DXVECTOR3(2000.0f, 175.0f, -3125.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_Piller[4].SetObject(D3DXVECTOR3(-1050, 175.0f, 625.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_Piller[5].SetObject(D3DXVECTOR3(775.0f, 175.0f, 1125.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_Piller[6].SetObject(D3DXVECTOR3(-1125.0f, 175.0f, -1825.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_Piller[7].SetObject(D3DXVECTOR3(1250.0f, 175.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Piller_Finalize(void)
{
	for (int i = 0; i < NUM_PILLER; i++)
	{
		g_Piller[i].Finalize();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Piller_Update(void)
{
	for (int j = 0; j < NUM_PILLER; j++)
	{
		// �I�̐F���ς�����Ƃ��A���̐F���ς�� = �m�[�}���F
		if (GetColor(j) == TARGETWHITE)
		{
			g_Piller[j].SetType(PILLER);
		}
		// �I�̐F���ς�����Ƃ��A���̐F���ς�� = �ԐF
		else if (GetColor(j) == TARGETRED)
		{
			g_Piller[j].SetType(PILLER_R);
		}
		// �I�̐F���ς�����Ƃ��A���̐F���ς�� = �F
		else if (GetColor(j) == TARGETBLUE)
		{
			g_Piller[j].SetType(PILLER_B);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Piller_Draw(void)
{
	//���[���h�}�g���N�X�̐ݒ�
	for (int i = 0; i < NUM_PILLER; i++)
	{
		//�������݂��Ă����Ƃ��A�`�悷��
		if (g_Piller[i].checklive() == true)
		{
			Xfile_Draw(g_Piller[i].GetScl(), g_Piller[i].GetPos(), g_Piller[i].GetRot(), g_Piller[i].checktype());
		}
	}
}


//=============================================================================
// �v���C���[�ƒ��̓����蔻�菈��
//=============================================================================
bool CheckHitPlayer_vs_PILLER(D3DXVECTOR3 Ppos)
{

	for (int i = 0; i < NUM_PILLER; i++)
	{
		// �v���C���[���W�����̑傫���������������������Ă���@�����̈ʒu�ɖ߂�
		if (Ppos.x >= g_Piller[i].PosPil.x - (30.0f * g_Piller[i].SclPil.x) && Ppos.x <= g_Piller[i].PosPil.x + (30.0f * g_Piller[i].SclPil.x) &&			//X���W
			Ppos.y >= g_Piller[i].PosPil.y - (100.0f * g_Piller[i].SclPil.y) * 2 && Ppos.y <= g_Piller[i].PosPil.y + (60.0f * g_Piller[i].SclPil.y) * 2 &&		//Y���W								//Y���W
			Ppos.z >= g_Piller[i].PosPil.z - (30.0f * g_Piller[i].SclPil.z) && Ppos.z <= g_Piller[i].PosPil.z + (30.0f * g_Piller[i].SclPil.z) &&			//Z���W
			g_Piller[i].checklive() == true)
		{
			return true;
		}

	}
	return false;
}