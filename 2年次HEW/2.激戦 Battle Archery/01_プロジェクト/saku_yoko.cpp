//****************************************************
// ����֌W�̃v���O����
//****************************************************

#include "saku_yoko.h"
#include "myDirect3D.h"
#include "xfile.h"


// *****************************************************************************
// �}�N����`
// *****************************************************************************
#define NUM_SAKU_YOKO 14								//�\�����钌�̑���

// *****************************************************************************
// �O���[�o���ϐ�
// *****************************************************************************
LPDIRECT3DVERTEXBUFFER9 static g_pVtxBuffField = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	static g_pIdxBuffField = NULL;

// *****************************************************************************
// �N���X
// *****************************************************************************
// ��̃N���X
class SAKUS_YOKO {
private:
	bool live;				//�򂪑��݂��邩�ǂ���
	int  type;				//���̒l�ɂ���ĐF���ς��
	D3DXVECTOR3				PosSakY;					// ��̈ʒu
	D3DXVECTOR3				RotSakY;					// ��̌���(��])
	D3DXVECTOR3				SclSakY;					// ��̑傫��(�X�P�[��)

public:
	D3DXMATRIX				g_mtxWorldField;		// ���[���h�}�g���b�N�X(�s��)

	//�R���X�g���N�^
	SAKUS_YOKO() {
		live = false;								//��̑��ݖ��E
		type = SAKU;
		PosSakY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�������W
		RotSakY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//������]
		SclSakY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����傫��
	}

	~SAKUS_YOKO() {
		live = false;								//��̑��ݖ��E
		PosSakY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�������W
		RotSakY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//������]
		SclSakY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����傫��
	}

	// �򂪑��݂��Ă��邩�ǂ������ׂ�
	bool checklive()
	{
		return live;
	}

	// ����擾
	int checktype()
	{
		return type;
	}

	// ��̔z�u(�ݒu���W,�X�P�[��(�傫��)�̎w��)
	void SetObject(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Scl)
	{
		if (live == false)
		{
			PosSakY = Pos;
			RotSakY = Rot;
			SclSakY = Scl;
			live = true;
		}
	}

	//�X�V����
	void Update()
	{
	}

	//���W���擾
	D3DXVECTOR3 GetPos()
	{
		return PosSakY;
	}

	//�p�x���擾
	D3DXVECTOR3 GetRot()
	{
		return RotSakY;
	}

	//�X�P�[�����擾
	D3DXVECTOR3 GetScl()
	{
		return SclSakY;
	}
};

static SAKUS_YOKO *g_Saku[NUM_SAKU_YOKO];

//=============================================================================
// ����������
//=============================================================================
HRESULT SakuYoko_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetD3DDevice();

	//�N���X�̃Z�b�g
	for (int i = 0; i < NUM_SAKU_YOKO; i++)
	{
		g_Saku[i] = new SAKUS_YOKO;
	}

	// ��̐ݒu
	//
	g_Saku[0]->SetObject(D3DXVECTOR3(2150.0f, -12.5f, -2750.0f), D3DXVECTOR3(0.0f, 900.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[1]->SetObject(D3DXVECTOR3(2150.0f, -12.5f, -1875.0f), D3DXVECTOR3(0.0f, 900.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[2]->SetObject(D3DXVECTOR3(2150.0f, -12.5f, -1000.0f), D3DXVECTOR3(0.0f, 900.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[3]->SetObject(D3DXVECTOR3(2150.0f, -12.5f, -0.0f),	 D3DXVECTOR3(0.0f, 900.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[4]->SetObject(D3DXVECTOR3(2150.0f, -12.5f, 1000.0f),  D3DXVECTOR3(0.0f, 900.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[5]->SetObject(D3DXVECTOR3(2150.0f, -12.5f, 1875.0f),  D3DXVECTOR3(0.0f, 900.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[6]->SetObject(D3DXVECTOR3(2150.0f, -12.5f, 2750.0f),  D3DXVECTOR3(0.0f, 900.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));

	g_Saku[7]->SetObject(D3DXVECTOR3(-2150.0f, -12.5f, -2750.0f), D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[8]->SetObject(D3DXVECTOR3(-2150.0f, -12.5f, -1875.0f), D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[9]->SetObject(D3DXVECTOR3(-2150.0f, -12.5f, -1000.0f), D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[10]->SetObject(D3DXVECTOR3(-2150.0f, -12.5f, -0.0f),	  D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[11]->SetObject(D3DXVECTOR3(-2150.0f, -12.5f, 1000.0f), D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[12]->SetObject(D3DXVECTOR3(-2150.0f, -12.5f, 1875.0f), D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[13]->SetObject(D3DXVECTOR3(-2150.0f, -12.5f, 2750.0f), D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void SakuYoko_Finalize(void)
{
	if (g_pVtxBuffField != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}

	//�N���X�̉��
	for (int i = 0; i < NUM_SAKU_YOKO; i++)
	{
		delete g_Saku[i];
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void SakuYoko_Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void SakuYoko_Draw(void)
{
	//���[���h�}�g���N�X�̐ݒ�
	for (int i = 0; i < NUM_SAKU_YOKO; i++)
	{
		//�ǂ����݂��Ă����Ƃ��A�`�悷��
		if (g_Saku[i]->checklive() == true)
		{
			Xfile_Draw(g_Saku[i]->GetScl(), g_Saku[i]->GetPos(), g_Saku[i]->GetRot(), SAKU);
		}
	}
}

//=============================================================================
// �v���C���[�ƍ�̓����蔻�菈��
//=============================================================================
bool CheckHitPlayer_vs_SakuYoko(D3DXVECTOR3 Ppos)
{
	for (int i = 0; i < NUM_SAKU_YOKO; i++)
	{
		// �v���C���[���W���ǂ̑傫���������������������Ă���
		if (Ppos.x >= g_Saku[i]->GetPos().x - (5.0f * g_Saku[i]->GetScl().x) && Ppos.x <= g_Saku[i]->GetPos().x + (5.0f * g_Saku[i]->GetScl().x) &&				//X���W
			Ppos.y >= g_Saku[i]->GetPos().y - (150.0f * g_Saku[i]->GetScl().y) && Ppos.y <= g_Saku[i]->GetPos().y + (150.0f * g_Saku[i]->GetScl().y) * 2 &&		//Y���W								//Y���W
			Ppos.z >= g_Saku[i]->GetPos().z - (400.0f * g_Saku[i]->GetScl().z) && Ppos.z <= g_Saku[i]->GetPos().z + (400.0f * g_Saku[i]->GetScl().z) &&			//Z���W
			g_Saku[i]->checklive() == true)
		{
			return true;
		}

	}
	return false;
}