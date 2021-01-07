//****************************************************
// �Ǌ֌W�̃v���O����
//****************************************************

#include "wall_tutorial.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
#include "bullet.h"
#include "player.h"
#include "xfile.h"
#include "player.h"


// *****************************************************************************
// �}�N����`
// *****************************************************************************
#define NUM_WALL 20								//�\�����钌�̑���

// *****************************************************************************
// �O���[�o���ϐ�
// *****************************************************************************
LPDIRECT3DVERTEXBUFFER9 static g_pVtxBuffField = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	static g_pIdxBuffField = NULL;


// *****************************************************************************
// enum
// *****************************************************************************

// *****************************************************************************
// �N���X
// *****************************************************************************
// ���̃N���X
class WALLS_TUTORIAL {
private:
	bool live;				//�ǂ����݂��邩�ǂ���
	int  type;				//���̒l�ɂ���ĐF���ς��


public:
	D3DXMATRIX				g_mtxWorldField;		// ���[���h�}�g���b�N�X(�s��)

	D3DXVECTOR3				PosWal;					// ���̈ʒu
	D3DXVECTOR3				RotWal;					// ���̌���(��])
	D3DXVECTOR3				SclWal;					// ���̑傫��(�X�P�[��)

	//�R���X�g���N�^
	WALLS_TUTORIAL() {
		live = false;								//���̑��ݖ��E
		type = WALL;
		PosWal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�������W
		RotWal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//������]
		SclWal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����傫��
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
			PosWal = Pos;
			RotWal = Rot;
			SclWal = Scl;
			live = true;
		}
	}

	//�I������
	void Finalize()
	{
		live = false;
		type = WALL;
	}

	//�X�V����
	void Update()
	{
		// �I���F��ς����Ƃ��A�A�����ĐF���ς��
	}

	//���W���擾
	D3DXVECTOR3 GetPos()
	{
		return PosWal;
	}

	//�p�x���擾
	D3DXVECTOR3 GetRot()
	{
		return RotWal;
	}

	//�X�P�[�����擾
	D3DXVECTOR3 GetScl()
	{
		return SclWal;
	}
};

static WALLS_TUTORIAL g_WallTutorial[NUM_WALL];

//=============================================================================
// ����������
//=============================================================================
HRESULT Wall_Tutorial_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetD3DDevice();

	// �I�̌��p��
	g_WallTutorial[0].SetObject(D3DXVECTOR3(-1825, 125.0f, 1150.0f), D3DXVECTOR3(0.0f, 3.15f, 0.0f), D3DXVECTOR3(1.0f, 1.25f, 0.5f));
	g_WallTutorial[1].SetObject(D3DXVECTOR3(-1825, 125.0f, 1125.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.25f, 0.5f));

	g_WallTutorial[2].SetObject(D3DXVECTOR3(-1325, 125.0f, 650.0f), D3DXVECTOR3(0.0f, 3.15f, 0.0f), D3DXVECTOR3(1.0f, 1.25f, 0.5f));
	g_WallTutorial[3].SetObject(D3DXVECTOR3(-1325, 125.0f, 625.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.25f, 0.5f));

	g_WallTutorial[4].SetObject(D3DXVECTOR3(-825, 125.0f, 150.0f), D3DXVECTOR3(0.0f, 3.15f, 0.0f), D3DXVECTOR3(1.0f, 1.25f, 0.5f));
	g_WallTutorial[5].SetObject(D3DXVECTOR3(-825, 125.0f, 125.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.25f, 0.5f));

	g_WallTutorial[6].SetObject(D3DXVECTOR3(825, 125.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.25f, 0.5f));
	g_WallTutorial[7].SetObject(D3DXVECTOR3(825, 125.0f, -125.0f), D3DXVECTOR3(0.0f, 3.15f, 0.0f), D3DXVECTOR3(1.0f, 1.25f, 0.5f));

	g_WallTutorial[8].SetObject(D3DXVECTOR3(1325, 125.0f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.25f, 0.5f));
	g_WallTutorial[9].SetObject(D3DXVECTOR3(1325, 125.0f, -625.0f), D3DXVECTOR3(0.0f, 3.15f, 0.0f), D3DXVECTOR3(1.0f, 1.25f, 0.5f));

	g_WallTutorial[10].SetObject(D3DXVECTOR3(1825, 125.0f, -1150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.25f, 0.5f));
	g_WallTutorial[11].SetObject(D3DXVECTOR3(1825, 125.0f, -1125.0f), D3DXVECTOR3(0.0f, 3.15f, 0.0f), D3DXVECTOR3(1.0f, 1.25f, 0.5f));


	// �I�܂ł̋������Ƃ邽�߂̕�
	g_WallTutorial[12].SetObject(D3DXVECTOR3(-1263.0, 50.0f, 2040.0f), D3DXVECTOR3(0.0f, 3.15f, 0.0f), D3DXVECTOR3(3.35f, 0.4f, 1.25f));
	g_WallTutorial[13].SetObject(D3DXVECTOR3(1263.0, 50.0f, -2032.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.35f, 0.4f, 1.25f));

	g_WallTutorial[14].SetObject(D3DXVECTOR3(1253, 50.0f, 2025.0f), D3DXVECTOR3(0.0f, 3.15f, 0.0f), D3DXVECTOR3(3.35f, 0.4f, 1.25f));
	g_WallTutorial[15].SetObject(D3DXVECTOR3(-1253, 50.0f, -2030.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.35f, 0.4f, 1.25f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Wall_Tutorial_Finalize(void)
{
	if (g_pVtxBuffField != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}

	for (int i = 0; i < NUM_WALL; i++)
	{
		g_WallTutorial[i].Finalize();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Wall_Tutorial_Update(void)
{
}


//=============================================================================
// �`�揈��
//=============================================================================
void Wall_Tutorial_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//���[���h�}�g���N�X�̐ݒ�
	for (int i = 0; i < NUM_WALL; i++)
	{
		//�ǂ����݂��Ă����Ƃ��A�`�悷��
		if (g_WallTutorial[i].checklive() == true)
		{
			Xfile_Draw(g_WallTutorial[i].GetScl(), g_WallTutorial[i].GetPos(), g_WallTutorial[i].GetRot(), WALL);
		}
	}
}


//=============================================================================
// �v���C���[�ƕǂ̓����蔻�菈��
//=============================================================================
bool CheckHitPlayer_vs_WallTutorial(D3DXVECTOR3 Ppos)
{
	for (int i = 0; i < NUM_WALL; i++)
	{
		// �v���C���[���W���ǂ̑傫���������������������Ă���
		if (Ppos.x >= g_WallTutorial[i].PosWal.x - (300.0f * (g_WallTutorial[i].SclWal.x / 1.2f)) && Ppos.x <= g_WallTutorial[i].PosWal.x + (300.0f * (g_WallTutorial[i].SclWal.x / 1.2f)) &&			//X���W
			Ppos.y >= g_WallTutorial[i].PosWal.y - (300.0f * g_WallTutorial[i].SclWal.y) && Ppos.y <= g_WallTutorial[i].PosWal.y + (50.0f * g_WallTutorial[i].SclWal.y) * 2 &&		//Y���W								//Y���W
			Ppos.z >= g_WallTutorial[i].PosWal.z - (40.0f * (g_WallTutorial[i].SclWal.z / 1.5f)) && Ppos.z <= g_WallTutorial[i].PosWal.z + (40.0f * (g_WallTutorial[i].SclWal.z / 1.5f)) &&			//Z���W
			g_WallTutorial[i].checklive() == true)
		{
			return true;
		}

	}
	return false;
}