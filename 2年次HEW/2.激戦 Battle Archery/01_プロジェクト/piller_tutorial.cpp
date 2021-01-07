//****************************************************
// ���֌W�̃v���O����
//****************************************************

#include "piller_tutorial.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
#include "bullet.h"
#include "xfile.h"
#include "target_tutorial.h"


// *****************************************************************************
// �}�N����`
// *****************************************************************************
#define NUM_PILLER_TUTORIAL 20								//�\�����钌�̍ő吔

// *****************************************************************************
// �N���X
// *****************************************************************************
// ���̃N���X
class PILLERS_TUTORIAL {
private:
	bool live;				//�ǂ����݂��邩�ǂ���
	int  type;				//���̒l�ɂ���ĐF���ς��


public:
	D3DXMATRIX				g_mtxWorldField;		// ���[���h�}�g���b�N�X(�s��)

	D3DXVECTOR3				PosPil;					// ���̈ʒu
	D3DXVECTOR3				RotPil;					// ���̌���(��])
	D3DXVECTOR3				SclPil;					// ���̑傫��(�X�P�[��)

													//�R���X�g���N�^
	PILLERS_TUTORIAL() {
		live = false;								//���̑��ݖ��E
		type = PILLER;
		PosPil = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�������W
		RotPil = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//������]
		SclPil = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����傫��
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
		}
	}

	void Finalize()
	{
		live = false;
		type = PILLER;
	}

	//�X�V����
	void Update()
	{
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

static PILLERS_TUTORIAL g_PillerTutorial[NUM_PILLER_TUTORIAL];

//=============================================================================
// ����������
//=============================================================================
HRESULT Piller_Tutorial_Initialize(void)
{
	// ���̐ݒu

	g_PillerTutorial[0].SetObject(D3DXVECTOR3(-1825.0f, 175.0f, 1250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_PillerTutorial[1].SetObject(D3DXVECTOR3(-1825.0f, 175.0f, 1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_PillerTutorial[2].SetObject(D3DXVECTOR3(-1325.0f, 175.0f, 750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_PillerTutorial[3].SetObject(D3DXVECTOR3(-1325.0f, 175.0f, 550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_PillerTutorial[4].SetObject(D3DXVECTOR3(-825.0f, 175.0f, 250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_PillerTutorial[5].SetObject(D3DXVECTOR3(-825.0f, 175.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_PillerTutorial[6].SetObject(D3DXVECTOR3(825.0f, 175.0f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_PillerTutorial[7].SetObject(D3DXVECTOR3(825.0f, 175.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_PillerTutorial[8].SetObject(D3DXVECTOR3(1325.0f, 175.0f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_PillerTutorial[9].SetObject(D3DXVECTOR3(1325.0f, 175.0f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));

	g_PillerTutorial[10].SetObject(D3DXVECTOR3(1825.0f, 175.0f, -1250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	g_PillerTutorial[11].SetObject(D3DXVECTOR3(1825.0f, 175.0f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Piller_Tutorial_Finalize(void)
{
	for (int i = 0; i < NUM_PILLER_TUTORIAL; i++)
	{
		g_PillerTutorial[i].Finalize();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Piller_Tutorial_Update(void)
{
	for (int i = 0; i < NUM_PILLER_TUTORIAL; i++)
	{
		// �I�̐F���ς�����Ƃ��A���̐F���ς�� = �m�[�}���F
		if (GetColor_Tutorial(i) == TARGETWHITE)
		{
			g_PillerTutorial[i].SetType(PILLER);
		}
		// �I�̐F���ς�����Ƃ��A���̐F���ς�� = �ԐF
		else if (GetColor_Tutorial(i) == TARGETRED)
		{
			g_PillerTutorial[i].SetType(PILLER_R);
		}
		// �I�̐F���ς�����Ƃ��A���̐F���ς�� = �F
		else if (GetColor_Tutorial(i) == TARGETBLUE)
		{
			g_PillerTutorial[i].SetType(PILLER_B);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Piller_Tutorial_Draw(void)
{
	//���[���h�}�g���N�X�̐ݒ�
	for (int i = 0; i < NUM_PILLER_TUTORIAL; i++)
	{
		//�������݂��Ă����Ƃ��A�`�悷��
		if (g_PillerTutorial[i].checklive() == true)
		{
			Xfile_Draw(g_PillerTutorial[i].GetScl(), g_PillerTutorial[i].GetPos(), g_PillerTutorial[i].GetRot(), g_PillerTutorial[i].checktype());
		}
	}
}


//=============================================================================
// �v���C���[�ƒ��̓����蔻�菈��
//=============================================================================
bool CheckHitPlayer_vs_PillerTutorial(D3DXVECTOR3 Ppos)
{

	for (int i = 0; i < NUM_PILLER_TUTORIAL; i++)
	{
		// �v���C���[���W�����̑傫���������������������Ă���@�����̈ʒu�ɖ߂�
		if (Ppos.x >= g_PillerTutorial[i].PosPil.x - (30.0f * g_PillerTutorial[i].SclPil.x) && Ppos.x <= g_PillerTutorial[i].PosPil.x + (30.0f * g_PillerTutorial[i].SclPil.x) &&			//X���W
			Ppos.y >= g_PillerTutorial[i].PosPil.y - (100.0f * g_PillerTutorial[i].SclPil.y) * 2 && Ppos.y <= g_PillerTutorial[i].PosPil.y + (60.0f * g_PillerTutorial[i].SclPil.y) * 2 &&		//Y���W								//Y���W
			Ppos.z >= g_PillerTutorial[i].PosPil.z - (30.0f * g_PillerTutorial[i].SclPil.z) && Ppos.z <= g_PillerTutorial[i].PosPil.z + (30.0f * g_PillerTutorial[i].SclPil.z) &&			//Z���W
			g_PillerTutorial[i].checklive() == true)
		{
			return true;
		}

	}
	return false;
}