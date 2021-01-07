//****************************************************
// �Ǌ֌W�̃v���O����
//****************************************************

#include "wall.h"
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
#define NUM_WALL 14								//�\�����钌�̑���

// *****************************************************************************
// �O���[�o���ϐ�
// *****************************************************************************
LPDIRECT3DVERTEXBUFFER9 static g_pVtxBuffField = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	static g_pIdxBuffField = NULL;

// *****************************************************************************
// �N���X
// *****************************************************************************
// ���̃N���X
class WALLS {
private:
	bool live;				//�ǂ����݂��邩�ǂ���
	int  type;				//���̒l�ɂ���ĐF���ς��


public:
	D3DXMATRIX				g_mtxWorldField;		// ���[���h�}�g���b�N�X(�s��)

	D3DXVECTOR3				PosWal;					// ���̈ʒu
	D3DXVECTOR3				RotWal;					// ���̌���(��])
	D3DXVECTOR3				SclWal;					// ���̑傫��(�X�P�[��)

	//�R���X�g���N�^
	WALLS() {
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

static WALLS g_Wall[NUM_WALL];

//=============================================================================
// ����������
//=============================================================================
HRESULT Wall_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetD3DDevice();

	// 1P�v���C���[���ǂ̐ݒu
	g_Wall[0].SetObject(D3DXVECTOR3(875.0f, 125.0f, 2750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.2f, 1.25f));
	g_Wall[1].SetObject(D3DXVECTOR3(500.0f, 125.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[2].SetObject(D3DXVECTOR3(1000.0f, 125.0f, 1250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[3].SetObject(D3DXVECTOR3(875.0f, 125.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[4].SetObject(D3DXVECTOR3(-250.0f, 125.0f, 1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[5].SetObject(D3DXVECTOR3(-1000.0f, 125.0f, 2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[6].SetObject(D3DXVECTOR3(-1250.0f, 125.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));

	// 2P�v���C���[���ǂ̐ݒu
	g_Wall[7].SetObject(D3DXVECTOR3(1000.0f, 125.0f, -2000.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 1.2f, 1.25f));
	g_Wall[8].SetObject(D3DXVECTOR3(-250.0f, 125.0f, -1250.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.2f, 1.25f));
	g_Wall[9].SetObject(D3DXVECTOR3(-1000.0f, 125.0f, -2000.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.2f, 1.25f));
	g_Wall[10].SetObject(D3DXVECTOR3(-1125.0f, 125.0f, -750.0f), D3DXVECTOR3(3.1f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.2f, 1.25f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Wall_Finalize(void)
{

	for (int i = 0; i < NUM_WALL; i++)
	{
		g_Wall[i].Finalize();
	}
	
	if (g_pVtxBuffField != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void Wall_Update(void)
{
}


//=============================================================================
// �`�揈��
//=============================================================================
void Wall_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//���[���h�}�g���N�X�̐ݒ�
	for (int i = 0; i < NUM_WALL; i++)
	{
		//�ǂ����݂��Ă����Ƃ��A�`�悷��
		if (g_Wall[i].checklive() == true)
		{
			Xfile_Draw(g_Wall[i].GetScl(), g_Wall[i].GetPos(), g_Wall[i].GetRot(), WALL);
		}
	}
}


//=============================================================================
// �v���C���[�ƕǂ̓����蔻�菈��
//=============================================================================
bool CheckHitPlayer_vs_Wall(D3DXVECTOR3 Ppos)
{
	for (int i = 0; i < NUM_WALL; i++)
	{
		// �v���C���[���W���ǂ̑傫���������������������Ă���
		if (Ppos.x >= g_Wall[i].PosWal.x - (300.0f * (g_Wall[i].SclWal.x/1.2f)) && Ppos.x <= g_Wall[i].PosWal.x + (300.0f * (g_Wall[i].SclWal.x / 1.2f)) &&			//X���W
			Ppos.y >= g_Wall[i].PosWal.y - (300.0f * g_Wall[i].SclWal.y) && Ppos.y <= g_Wall[i].PosWal.y + (50.0f * g_Wall[i].SclWal.y) * 2 &&		//Y���W								//Y���W
			Ppos.z >= g_Wall[i].PosWal.z - (40.0f * (g_Wall[i].SclWal.z / 1.5f)) && Ppos.z <= g_Wall[i].PosWal.z + (40.0f * (g_Wall[i].SclWal.z / 1.5f)) &&			//Z���W
			g_Wall[i].checklive() == true)
		{
			return true;
		}

	}
	return false;
}