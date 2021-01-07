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
#define NUM_WALL_TATE 14								//�\�����钌�̑���

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
class WALLS_TATE {
private:
	bool live;				//�ǂ����݂��邩�ǂ���
	int  type;				//���̒l�ɂ���ĐF���ς��


public:
	D3DXMATRIX				g_mtxWorldField;		// ���[���h�}�g���b�N�X(�s��)

	D3DXVECTOR3				PosWalT;					// ���̈ʒu
	D3DXVECTOR3				RotWalT;					// ���̌���(��])
	D3DXVECTOR3				SclWalT;					// ���̑傫��(�X�P�[��)

	//�R���X�g���N�^
	WALLS_TATE() {
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

static WALLS_TATE g_Wall[NUM_WALL_TATE];

//=============================================================================
// ����������
//=============================================================================
HRESULT WallTate_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetD3DDevice();

	//// 1P�v���C���[���ǂ̐ݒu
	g_Wall[1].SetObject(D3DXVECTOR3(1500.0f, 125.0f, 2000.0f), D3DXVECTOR3(0.0f, 4.71f, 0.0f), D3DXVECTOR3(2.0f, 1.2f, 1.25f));
	g_Wall[2].SetObject(D3DXVECTOR3(675.0f, 125.0f, 825.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[3].SetObject(D3DXVECTOR3(1500.0f, 125.0f, 250.0f), D3DXVECTOR3(0.0f, 4.71f, 0.0f), D3DXVECTOR3(2.0f, 1.2f, 1.25f));
	g_Wall[4].SetObject(D3DXVECTOR3(-1500.0f, 125.0f, 1500.0f), D3DXVECTOR3(0.0f, 4.71f, 0.0f), D3DXVECTOR3(2.0f, 1.2f, 1.25f));
	g_Wall[5].SetObject(D3DXVECTOR3(-875.0f, 125.0f, 875.0f), D3DXVECTOR3(0.0f, 4.71f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));

	// 2P�v���C���[���ǂ̐ݒu
	g_Wall[6].SetObject(D3DXVECTOR3(1250.0f, 125.0f, -2750.0f), D3DXVECTOR3(0.0f, 4.71f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[7].SetObject(D3DXVECTOR3(750.0f, 125.0f, -1500.0f), D3DXVECTOR3(0.0f, 4.71f, 0.0f), D3DXVECTOR3(1.0f, 1.2f, 1.25f));
	g_Wall[8].SetObject(D3DXVECTOR3(750.0f, 125.0f, -750.0f), D3DXVECTOR3(0.0f, 4.71f, 0.0f), D3DXVECTOR3(1.0f, 1.2f, 1.25f));
	g_Wall[9].SetObject(D3DXVECTOR3(1750.0f, 125.0f, -1500.0f), D3DXVECTOR3(0.0f, 4.71f, 0.0f), D3DXVECTOR3(2.0f, 1.2f, 1.25f));
	g_Wall[10].SetObject(D3DXVECTOR3(250.0f, 125.0f, -1750.0f), D3DXVECTOR3(0.0f, 4.71f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[11].SetObject(D3DXVECTOR3(-500.0f, 125.0f, -2250.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), D3DXVECTOR3(2.0f, 1.2f, 1.25f));
	g_Wall[12].SetObject(D3DXVECTOR3(-1287.5f, 125.0f, -1650.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[13].SetObject(D3DXVECTOR3(-375.0f, 125.0f, -500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), D3DXVECTOR3(1.0f, 1.2f, 1.25f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void WallTate_Finalize(void)
{
	if (g_pVtxBuffField != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}


	for (int i = 0; i < NUM_WALL_TATE; i++)
	{
		g_Wall[i].Finalize();
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void WallTate_Update(void)
{
}


//=============================================================================
// �`�揈��
//=============================================================================
void WallTate_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//���[���h�}�g���N�X�̐ݒ�
	for (int i = 0; i < NUM_WALL_TATE; i++)
	{
		//�ǂ����݂��Ă����Ƃ��A�`�悷��
		if (g_Wall[i].checklive() == true)
		{
			Xfile_Draw(g_Wall[i].GetScl(), g_Wall[i].GetPos(), g_Wall[i].GetRot(), WALL);
		}
	}
}


//=============================================================================
// ?�v���C���[�ƕǂ̓����蔻�菈��
//=============================================================================
bool CheckHitPlayer_vs_WallTate(D3DXVECTOR3 Ppos)
{
	for (int i = 0; i < NUM_WALL_TATE; i++)
	{
		// �v���C���[���W���ǂ̑傫���������������������Ă���
		if (Ppos.x >= g_Wall[i].PosWalT.x - (40.0f * (g_Wall[i].SclWalT.z/ 1.5f)) && Ppos.x <= g_Wall[i].PosWalT.x + (40.0f * (g_Wall[i].SclWalT.z / 1.5f)) &&			//X���W
			Ppos.y >= g_Wall[i].PosWalT.y - (300.0f * g_Wall[i].SclWalT.y) && Ppos.y <= g_Wall[i].PosWalT.y + (50.0f * g_Wall[i].SclWalT.y) * 2 &&						//Y���W
			Ppos.z >= g_Wall[i].PosWalT.z - (300.0f * (g_Wall[i].SclWalT.x / 1.2f)) && Ppos.z <= g_Wall[i].PosWalT.z + (300.0f *( g_Wall[i].SclWalT.x / 1.2f)) &&		//Z���W
			g_Wall[i].checklive() == true)
		{
			return true;
		}

	}
	return false;
}