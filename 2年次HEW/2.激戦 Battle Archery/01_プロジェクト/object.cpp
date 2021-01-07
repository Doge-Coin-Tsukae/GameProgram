//****************************************************
//�Ǌ֌W�̃v���O����
//****************************************************

#include "object.h"
#include "player.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	FIELD_WIDTH		(100.0f)						// �n�ʂ̕�(X����)
#define	FIELD_DEPTH		(100.0f)						// �n�ʂ̉��s(Z����)
#define FIELD_HIGHT		(100.0f)						// �n�ʂ̍���

#define NUM_BOX 4										//�\���u���b�N�̑���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT static MakeVertexField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffField = NULL;
int						g_NumIndexField = 36;

//*****************************************************************************
//�N���X
//*****************************************************************************
class WALL{
private:
	bool live;				//�ǂ����݂��邩�ǂ���

public:
	D3DXMATRIX				g_mtxWorldField;		// ���[���h�}�g���b�N�X(�s��)
	D3DXVECTOR3				PosObj;					// �n�ʂ̈ʒu
	D3DXVECTOR3				RotObj;					// �n�ʂ̌���(��])
	D3DXVECTOR3				SclObj;					// �n�ʂ̑傫��(�X�P�[��)

	//�R���X�g���N�^
	WALL() {
		live = false;								//�e�̑��ݖ��E
		PosObj = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�������W
		RotObj = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//������]
		SclObj = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����傫��
	}

	//�ǂ����݂��Ă��邩�ǂ������ׂ�
	bool checklive()
	{
		return live;
	}

	//�u���b�N�̔z�u(�ݒu���W,�X�P�[��(�傫��)�̎w��)
	void SetObject(D3DXVECTOR3 Pos,D3DXVECTOR3 Scl,D3DXVECTOR3 Rot)
	{
		for (int i = 0; i < NUM_BOX;i++)
		{
			//���̕ǂ����݂��Ă��Ȃ��Ƃ�
			if (live == false)
			{
				PosObj = Pos;
				SclObj = Scl;
				RotObj = Rot;
				live = true;
				break;
			}
		}
		
	}
};

static WALL *g_Box[NUM_BOX];

//=============================================================================
// ����������
//=============================================================================
HRESULT Object_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice[2];
	pDevice[0] = GetD3DDevice();
	pDevice[1] = GetD3DDevice();

	// ���_���̍쐬
	MakeVertexField(pDevice[0]);
	MakeVertexField(pDevice[1]);

	//�e�N�X�`���̓ǂݍ���
	SetTexture(TEXTURE_INDEX_VENUE);

	//�N���X�̃Z�b�g
	for (int i = 0; i < NUM_BOX; i++)
	{
		g_Box[i] = new WALL;
	}

	//�u���b�N�̐ݒu
	g_Box[0]->SetObject(D3DXVECTOR3(2500, 100, 0), D3DXVECTOR3(1.0f, 2.0f, 37.5f), D3DXVECTOR3(0.0f, 89.535f, 0.0f));
	g_Box[1]->SetObject(D3DXVECTOR3(-2500, 100, 0), D3DXVECTOR3(1.0f, 2.0f, 37.5f), D3DXVECTOR3(0.0f, -89.535f, 0.0f));
	g_Box[2]->SetObject(D3DXVECTOR3(0, 100, 3750), D3DXVECTOR3(25.0f, 2.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_Box[3]->SetObject(D3DXVECTOR3(0, 100, -3750), D3DXVECTOR3(25.0f, 2.0f, 1.0f), D3DXVECTOR3(-3.14f, 0.0f, 3.14f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Object_Finalize(void)
{

	//�N���X�̉��
	for (int i = 0; i < NUM_BOX; i++)
	{
		delete g_Box[i];
	}

	//�摜�̉��
	ReleaseTexture(TEXTURE_INDEX_VENUE);

	if (g_pIdxBuffField != NULL)
	{//�C���f�b�N�X�o�b�t�@�̉��
		g_pIdxBuffField->Release();
		g_pIdxBuffField = NULL;
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
void Object_Update(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	//���[���h�ϊ�

	//���[���h�}�g���N�X�̏�����
	for (int i = 0; i < NUM_BOX; i++)
	{
		//�ǂ����݂��Ă����Ƃ��A����������
		if (g_Box[i]->checklive() == true)
		{
			D3DXMatrixIdentity(&g_Box[i]->g_mtxWorldField);

			//��]�𔽉f
			/*���̊֐��͌���1�{�̎��̓�������*/
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Box[i]->RotObj.y, g_Box[i]->RotObj.x, g_Box[i]->RotObj.z);		//���[�A�s�b�`�A���[��	���[�ƃ��[�������������ɂȂ邱��=�W���o�����b�N
			D3DXMatrixMultiply(&g_Box[i]->g_mtxWorldField, &g_Box[i]->g_mtxWorldField, &mtxRot);				//��]*���[���h

			//�ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_Box[i]->PosObj.x, g_Box[i]->PosObj.y, g_Box[i]->PosObj.z);
			D3DXMatrixMultiply(&g_Box[i]->g_mtxWorldField, &g_Box[i]->g_mtxWorldField, &mtxTranslate);			//�ړ�*���[���h

			//�X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, g_Box[i]->SclObj.x, g_Box[i]->SclObj.y, g_Box[i]->SclObj.z);
			D3DXMatrixMultiply(&g_Box[i]->g_mtxWorldField, &g_Box[i]->g_mtxWorldField, &mtxScl);				//�g��E�k��*���[���h
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Object_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//���[���h�}�g���N�X�̐ݒ�
	for (int i = 0; i < NUM_BOX; i++)
	{
		//�ǂ����݂��Ă����Ƃ��A�`�悷��
		if (g_Box[i]->checklive() == true)
		{
			pDevice->SetTransform(D3DTS_WORLD, &g_Box[i]->g_mtxWorldField);

			pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@�̃Z�b�g
			pDevice->SetIndices(g_pIdxBuffField);

			pDevice->SetFVF(FVF_VERTEX_3D);

			pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_VENUE));

			//�|���S���̕`��(�C���f�b�N�X�o�b�t�@��)
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, g_NumIndexField, 0, 12);
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	//�I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffField, NULL)))
	{
		return E_FAIL;
	}

	{
		//���_�o�b�t�@�𖄂߂�
		VERTEX_3D *pVtx;

		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
		g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_HIGHT, -FIELD_DEPTH);
		pVtx[1].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_HIGHT, -FIELD_DEPTH);
		pVtx[2].pos = D3DXVECTOR3(-FIELD_WIDTH, -FIELD_HIGHT, -FIELD_DEPTH);
		pVtx[3].pos = D3DXVECTOR3(FIELD_WIDTH, -FIELD_HIGHT, -FIELD_DEPTH);
		pVtx[4].pos = D3DXVECTOR3(FIELD_WIDTH, -FIELD_HIGHT, FIELD_DEPTH);
		pVtx[5].pos = D3DXVECTOR3(-FIELD_WIDTH, -FIELD_HIGHT, FIELD_DEPTH);
		pVtx[6].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_HIGHT, FIELD_DEPTH);
		pVtx[7].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_HIGHT, FIELD_DEPTH);

		//
		pVtx[0].nor = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
		pVtx[4].nor = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
		pVtx[5].nor = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
		pVtx[6].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[7].nor = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);


		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_pVtxBuffField->Unlock();
	}

	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD)*g_NumIndexField,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffField,
		NULL)))
	{
		return E_FAIL;
	}

	{	//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
		WORD *pIdx;

		g_pIdxBuffField->Lock(0, 0, (void**)&pIdx, 0);

		//�O
		pIdx[0] = 0;
		pIdx[1] = 1;
		pIdx[2] = 2;
		pIdx[3] = 1;
		pIdx[4] = 3;
		pIdx[5] = 2;

		//��
		pIdx[6] = 7;
		pIdx[7] = 6;
		pIdx[8] = 0;
		pIdx[9] = 6;
		pIdx[10] = 1;
		pIdx[11] = 0;

		//��
		pIdx[12] = 7;
		pIdx[13] = 0;
		pIdx[14] = 5;
		pIdx[15] = 0;
		pIdx[16] = 2;
		pIdx[17] = 5;

		//�E
		pIdx[18] = 1;
		pIdx[19] = 6;
		pIdx[20] = 3;
		pIdx[21] = 6;
		pIdx[22] = 4;
		pIdx[23] = 3;

		//���
		pIdx[24] = 6;
		pIdx[25] = 7;
		pIdx[26] = 4;
		pIdx[27] = 7;
		pIdx[28] = 5;
		pIdx[29] = 4;

		//��
		pIdx[30] = 2;
		pIdx[31] = 3;
		pIdx[32] = 5;
		pIdx[33] = 3;
		pIdx[34] = 4;
		pIdx[35] = 5;

		g_pIdxBuffField->Unlock();
	}
	return S_OK;
}

//���ׂ������̍��W�ƃu���b�N�̍��W�Ƃ̓����蔻��
bool CheckHitPlayer(D3DXVECTOR3 Ppos)
{
	for (int i = 0; i < NUM_BOX; i++)
	{
		if (Ppos.x >= g_Box[i]->PosObj.x - (100.0f * g_Box[i]->SclObj.x) && Ppos.x <= g_Box[i]->PosObj.x + (100.0f * g_Box[i]->SclObj.x) &&			//X���W
			Ppos.y >= g_Box[i]->PosObj.y - (100.0f * g_Box[i]->SclObj.y) && Ppos.y <= g_Box[i]->PosObj.y + (100.0f * g_Box[i]->SclObj.y) * 2 &&		//Y���W								//Y���W
			Ppos.z >= g_Box[i]->PosObj.z - (100.0f * g_Box[i]->SclObj.z) && Ppos.z <= g_Box[i]->PosObj.z + (100.0f * g_Box[i]->SclObj.z) &&			//Z���W
			g_Box[i]->checklive() == true)			//���̃u���b�N���g���Ă���
		{
			return true;		//�u���b�N�̔�����ɂ���
		}
	}

	return false;		//�u���b�N�̔���O�ɂ���
}