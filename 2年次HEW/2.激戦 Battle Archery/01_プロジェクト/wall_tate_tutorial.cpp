//****************************************************
// ��(�c)�֌W�̃v���O����
//****************************************************

#include "wall_tate.h"
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
#define NUM_WALL_TATE_TUTORIAL 14								//�\�����钌�̑���

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
class WALLS_TATE_TUTORIAL {
private:
	bool live;				//�ǂ����݂��邩�ǂ���
	int  type;				//���̒l�ɂ���ĐF���ς��


public:
	D3DXMATRIX				g_mtxWorldField;		// ���[���h�}�g���b�N�X(�s��)

	D3DXVECTOR3				PosWalT;					// ���̈ʒu
	D3DXVECTOR3				RotWalT;					// ���̌���(��])
	D3DXVECTOR3				SclWalT;					// ���̑傫��(�X�P�[��)

	//�R���X�g���N�^
	WALLS_TATE_TUTORIAL() {
		live = false;								//���̑��ݖ��E
		type = WALL;
		PosWalT = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�������W
		RotWalT = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//������]
		SclWalT = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����傫��
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
			PosWalT = Pos;
			RotWalT = Rot;
			SclWalT = Scl;
			live = true;
		}
	}

	void Finalize()
	{
		live = 0;
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
		return PosWalT;
	}

	//�p�x���擾
	D3DXVECTOR3 GetRot()
	{
		return RotWalT;
	}

	//�X�P�[�����擾
	D3DXVECTOR3 GetScl()
	{
		return SclWalT;
	}
};

static WALLS_TATE_TUTORIAL g_WallTateTutorial[NUM_WALL_TATE_TUTORIAL];

//=============================================================================
// ����������
//=============================================================================
HRESULT WallTate_Tutorial_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetD3DDevice();

	// �c��
	g_WallTateTutorial[0].SetObject(D3DXVECTOR3(-450, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 4.71f, 0.0f), D3DXVECTOR3(8.0f, 0.4f, 1.25f));
	g_WallTateTutorial[1].SetObject(D3DXVECTOR3(450, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), D3DXVECTOR3(8.0f, 0.4f, 1.25f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void WallTate_Tutorial_Finalize(void)
{
	if (g_pVtxBuffField != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}


	for (int i = 0; i < NUM_WALL_TATE_TUTORIAL; i++)
	{
		g_WallTateTutorial[i].Finalize();
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void WallTate_Tutorial_Update(void)
{
}


//=============================================================================
// �`�揈��
//=============================================================================
void WallTate_Tutorial_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//���[���h�}�g���N�X�̐ݒ�
	for (int i = 0; i < NUM_WALL_TATE_TUTORIAL; i++)
	{
		//�ǂ����݂��Ă����Ƃ��A�`�悷��
		if (g_WallTateTutorial[i].checklive() == true)
		{
			Xfile_Draw(g_WallTateTutorial[i].GetScl(), g_WallTateTutorial[i].GetPos(), g_WallTateTutorial[i].GetRot(), WALL);
		}
	}
}


//=============================================================================
// ?�v���C���[�ƕǂ̓����蔻�菈��
//=============================================================================
bool CheckHitPlayer_vs_WallTateTutorial(D3DXVECTOR3 Ppos)
{
	for (int i = 0; i < NUM_WALL_TATE_TUTORIAL; i++)
	{
		// �v���C���[���W���ǂ̑傫���������������������Ă���
		if (Ppos.x >= g_WallTateTutorial[i].PosWalT.x - (40.0f * (g_WallTateTutorial[i].SclWalT.z / 1.5f)) && Ppos.x <= g_WallTateTutorial[i].PosWalT.x + (40.0f * (g_WallTateTutorial[i].SclWalT.z / 1.5f)) &&			//X���W
			Ppos.y >= g_WallTateTutorial[i].PosWalT.y - (300.0f * g_WallTateTutorial[i].SclWalT.y) && Ppos.y <= g_WallTateTutorial[i].PosWalT.y + (50.0f * g_WallTateTutorial[i].SclWalT.y) * 2 &&						//Y���W
			Ppos.z >= g_WallTateTutorial[i].PosWalT.z - (300.0f * (g_WallTateTutorial[i].SclWalT.x / 1.2f)) && Ppos.z <= g_WallTateTutorial[i].PosWalT.z + (300.0f *(g_WallTateTutorial[i].SclWalT.x / 1.2f)) &&		//Z���W
			g_WallTateTutorial[i].checklive() == true)
		{
			return true;
		}

	}
	return false;
}