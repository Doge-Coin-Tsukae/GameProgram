//****************************************************
// ��֌W�̃v���O����
//****************************************************

#include "saku.h"
#include "myDirect3D.h"
#include "xfile.h"


// *****************************************************************************
// �}�N����`
// *****************************************************************************
#define NUM_SAKU 10								//�\�������̑���

// *****************************************************************************
// �O���[�o���ϐ�
// *****************************************************************************
LPDIRECT3DVERTEXBUFFER9 static g_pVtxBuffField = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	static g_pIdxBuffField = NULL;

// *****************************************************************************
// �N���X
// *****************************************************************************
// ��̃N���X
class SAKUS {
private:
	bool live;				//�򂪑��݂��邩�ǂ���
	D3DXVECTOR3				PosSak;					// ��̈ʒu
	D3DXVECTOR3				RotSak;					// ��̌���(��])
	D3DXVECTOR3				SclSak;					// ��̑傫��(�X�P�[��)

public:
	D3DXMATRIX				g_mtxWorldField;		// ���[���h�}�g���b�N�X(�s��)]

	//�R���X�g���N�^
	SAKUS() {
		live = false;								//��̑��ݖ��E
		PosSak = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�������W
		RotSak = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//������]
		SclSak = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����傫��
	}
	~SAKUS() {
		live = false;								//��̑��ݖ��E
		PosSak = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�������W
		RotSak = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//������]
		SclSak = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����傫��
	}

	// �򂪑��݂��Ă��邩�ǂ������ׂ�
	bool checklive()
	{
		return live;
	}

	// ��̔z�u(�ݒu���W,�X�P�[��(�傫��)�̎w��)
	void SetObject(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Scl)
	{
		if (live == false)
		{
			PosSak = Pos;
			RotSak = Rot;
			SclSak = Scl;
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
		return PosSak;
	}

	//�p�x���擾
	D3DXVECTOR3 GetRot()
	{
		return RotSak;
	}

	//�X�P�[�����擾
	D3DXVECTOR3 GetScl()
	{
		return SclSak;
	}
};

static SAKUS *g_Saku[NUM_SAKU];

//=============================================================================
// ����������
//=============================================================================
HRESULT Saku_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetD3DDevice();

	//�N���X�̃Z�b�g
	for (int i = 0; i < NUM_SAKU; i++)
	{
		g_Saku[i] = new SAKUS;
	}

	// ��̐ݒu
	g_Saku[0]->SetObject(D3DXVECTOR3(1650.0f, -12.5f, 3250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[1]->SetObject(D3DXVECTOR3(825.0f, -12.5f, 3250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[2]->SetObject(D3DXVECTOR3(0.0f, -12.5f, 3250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[3]->SetObject(D3DXVECTOR3(-825.0f, -12.5f, 3250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[4]->SetObject(D3DXVECTOR3(-1650.0f, -12.5f, 3250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));

	g_Saku[5]->SetObject(D3DXVECTOR3(1650.0f, -12.5f, -3250.0f), D3DXVECTOR3(0.0f, 600.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[6]->SetObject(D3DXVECTOR3(825.0f, -12.5f, -3250.0f), D3DXVECTOR3(0.0f, 600.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[7]->SetObject(D3DXVECTOR3(0.0f, -12.5f, -3250.0f), D3DXVECTOR3(0.0f, 600.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[8]->SetObject(D3DXVECTOR3(-825.0f, -12.5f, -3250.0f), D3DXVECTOR3(0.0f, 600.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));
	g_Saku[9]->SetObject(D3DXVECTOR3(-1650.0f, -12.5f, -3250.0f), D3DXVECTOR3(0.0f, 600.0f, 0.0f), D3DXVECTOR3(12.5f, 5.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Saku_Finalize(void)
{
	if (g_pVtxBuffField != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}

	//�N���X�̉��
	for (int i = 0; i < NUM_SAKU; i++)
	{
		delete g_Saku[i];
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Saku_Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void Saku_Draw(void)
{
	//���[���h�}�g���N�X�̐ݒ�
	for (int i = 0; i < NUM_SAKU; i++)
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
bool CheckHitPlayer_vs_Saku(D3DXVECTOR3 Ppos)
{
	for (int i = 0; i < NUM_SAKU; i++)
	{
		// �v���C���[���W���ǂ̑傫���������������������Ă���
		if (Ppos.x >= g_Saku[i]->GetPos().x - (40.0f * g_Saku[i]->GetScl().x) && Ppos.x <= g_Saku[i]->GetPos().x + (40.0f * g_Saku[i]->GetScl().x) &&			//X���W
			Ppos.y >= g_Saku[i]->GetPos().y - (150.0f * g_Saku[i]->GetScl().y) && Ppos.y <= g_Saku[i]->GetPos().y + (150.0f * g_Saku[i]->GetScl().y) * 2 &&		//Y���W								//Y���W
			Ppos.z >= g_Saku[i]->GetPos().z - (10.0f * g_Saku[i]->GetScl().z) && Ppos.z <= g_Saku[i]->GetPos().z + (10.0f * g_Saku[i]->GetScl().z) &&			//Z���W
			g_Saku[i]->checklive() == true)
		{
			return true;
		}

	}
	return false;
}