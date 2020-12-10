#include "field.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
#include <stdlib.h>
//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define	VALUE_MOVE		(10.0f)							// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)				// ��]��

#define	FIELD_WIDTH		(100.0f)						// �n�ʂ̕�(X����)
#define	FIELD_DEPTH		(100.0f)						// �n�ʂ̉��s(Z����)
#define FIELD_HIGHT		(100.0f)						// �n�ʂ̍���

#define BLOCK_X			(402)			//Block + 1 ��������2�{�������������ɕK�v
#define BLOCK_Y			(101)			//Block + 1 ���������c�ɕK�v

#define NUM_BOX 1
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffField = NULL;
int						g_NumIndexField = 90000;

typedef struct {
	D3DXMATRIX				g_mtxWorldField;		// ���[���h�}�g���b�N�X(�s��)
	D3DXVECTOR3				g_posField;				// �n�ʂ̈ʒu
	D3DXVECTOR3				g_rotField;				// �n�ʂ̌���(��])
	D3DXVECTOR3				g_rot2Field;			// �n�ʂ̌���(��])
	D3DXVECTOR3				g_sclField;				// �n�ʂ̑傫��(�X�P�[��)
}BOX_T;

static BOX_T g_Box[NUM_BOX];

float g_rot1_x = 0.05f;
float g_rot2_x = 0.01f;

int g_NumVertex = (BLOCK_X + 1) * (BLOCK_Y + 1);						//���_��
int g_NumIndex = ((BLOCK_X + 1) * 2) * BLOCK_Y + ((BLOCK_Y*-1) * 2);	//�C���f�b�N�X��
int g_NumPolygon = (BLOCK_X * 2)*BLOCK_Y + (BLOCK_Y - 1) * 4;			//�|���S����

//=============================================================================
// ����������
//=============================================================================
HRESULT Field_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice[2];
	pDevice[0] = GetD3DDevice();
	pDevice[1] = GetD3DDevice();

	// ���_���̍쐬
	MakeVertexField(pDevice[0]);
	MakeVertexField(pDevice[1]);

	g_rot1_x = 0.05f;
	g_rot2_x = 0.01f;

	g_NumVertex = (BLOCK_X + 1) * (BLOCK_Y + 1);						//���_��
	g_NumIndex = ((BLOCK_X + 1) * 2) * BLOCK_Y + ((BLOCK_Y*-1) * 2);	//�C���f�b�N�X��
	g_NumPolygon = (BLOCK_X * 2)*BLOCK_Y + (BLOCK_Y - 1) * 4;			//�|���S����
	g_NumIndexField = 90000;

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	for (int i = 0; i < NUM_BOX; i++)
	{
		g_Box[i].g_posField = D3DXVECTOR3(0.0f, 0.0f, 00.0f);
		g_Box[i].g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Box[i].g_rot2Field = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Box[i].g_sclField = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Field_Finalize(void)
{

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
void Field_Update(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	//���[���h�ϊ�

	//���[���h�}�g���N�X�̏�����
	for (int i = 0; i < NUM_BOX; i++)
	{
		D3DXMatrixIdentity(&g_Box[i].g_mtxWorldField);
	}

	g_Box[0].g_rotField.y += 0.01f;


	//��]�𔽉f
	/*���̊֐��͌���1�{�̎��̓�������*/
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Box[0].g_rotField.y, g_Box[0].g_rotField.x, g_Box[0].g_rotField.z);		//���[�A�s�b�`�A���[��	���[�ƃ��[�������������ɂȂ邱��=�W���o�����b�N
	D3DXMatrixMultiply(&g_Box[0].g_mtxWorldField, &g_Box[0].g_mtxWorldField, &mtxRot);				//��]*���[���h

	g_Box[0].g_posField.x = -3000.0f;
	g_Box[0].g_posField.y = 100.0f;
	g_Box[0].g_posField.z = 100.0f;

	//�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_Box[0].g_posField.x, g_Box[0].g_posField.y, g_Box[0].g_posField.z);
	D3DXMatrixMultiply(&g_Box[0].g_mtxWorldField, &g_Box[0].g_mtxWorldField, &mtxTranslate);			//�ړ�*���[���h


	g_Box[1].g_rotField.y -= 0.03f;

	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Box[1].g_rotField.y, g_Box[1].g_rotField.x, g_Box[1].g_rotField.z);		//���[�A�s�b�`�A���[��	���[�ƃ��[�������������ɂȂ邱��=�W���o�����b�N
	D3DXMatrixMultiply(&g_Box[1].g_mtxWorldField, &g_Box[1].g_mtxWorldField, &mtxRot);				//��]*���[���h

	g_Box[1].g_posField.x = -3000.0f;
	g_Box[1].g_posField.z = 100.0f;

	//�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_Box[1].g_posField.x, g_Box[1].g_posField.y, g_Box[1].g_posField.z);
	D3DXMatrixMultiply(&g_Box[1].g_mtxWorldField, &g_Box[1].g_mtxWorldField, &mtxTranslate);			//�ړ�*���[���h

	g_Box[1].g_rot2Field.y += 0.03f;
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Box[1].g_rot2Field.y, g_Box[1].g_rot2Field.x, g_Box[1].g_rot2Field.z);		//���[�A�s�b�`�A���[��	���[�ƃ��[�������������ɂȂ邱��=�W���o�����b�N
	D3DXMatrixMultiply(&g_Box[1].g_mtxWorldField, &g_Box[1].g_mtxWorldField, &mtxRot);				//��]*���[���h

	//�q�� * �e
	D3DXMatrixMultiply(&g_Box[1].g_mtxWorldField, &g_Box[1].g_mtxWorldField, &g_Box[0].g_mtxWorldField);			//�ړ�*���[���h

	/*
	//�X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, g_sclField.x, g_sclField.y, g_sclField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxScl);				//�g��E�k��*���[���h
	*/


	//g_rotField.y += g_rot1_x;

}

//=============================================================================
// �`�揈��
//=============================================================================
void Field_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//���[���h�}�g���N�X�̐ݒ�
	for (int i = 0; i < NUM_BOX; i++)
	{
		D3DXMATRIX mtxWorld;
		D3DXMatrixIdentity(&mtxWorld);

		//���[���h�}�g���N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

		//�C���f�b�N�X�o�b�t�@�̃Z�b�g
		pDevice->SetIndices(g_pIdxBuffField);

		pDevice->SetFVF(FVF_VERTEX_3D);

		pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_FIELD01));

		//�|���S���̕`��(�C���f�b�N�X�o�b�t�@��)
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_NumIndex, 0, g_NumPolygon);
	}

	/*��������蓮�Ń��C�e�B���O*/
	/*
	//������������(�f�B���N�V���i�����C�g)
	D3DXVECTOR3 light;
	light.x = 0.0f;
	light.y = -1.0f;
	light.z = 0.0f;

	{//���_�o�b�t�@�𖄂߂�
		VERTEX_3D *pVtx;

		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
		g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		D3DXVECTOR3 calc_nor;

		//�x�N�g���ɍs��������ĕό`���Ă����֐�
		D3DXVec3TransformNormal(&calc_nor,&pVtx[0].nor,&g_mtxWorldField);

		float color =D3DXVec3Dot(&light, &calc_nor);

		//�l��0���傫��������0�ɕ␳����
		if (color > 0)
		{
			color = 0;
		}

		//-1�`0�̒l��1�`0�ɏ���������
		color = fabs(color);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(color , color, color, color);
		pVtx[1].col = D3DXCOLOR(color, color, color, color);
		pVtx[2].col = D3DXCOLOR(color, color, color, color);
		pVtx[3].col = D3DXCOLOR(color, color, color, color);
		pVtx[4].col = D3DXCOLOR(color, color, color, color);
		pVtx[5].col = D3DXCOLOR(color, color, color, color);

		g_pVtxBuffField->Unlock();
	}
	*/
	/*�蓮�Ń��C�e�B���O�����܂�*/

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	//�I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_NumVertex * 100, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffField, NULL)))
	{
		return E_FAIL;
	}

	{
		//���_�o�b�t�@�𖄂߂�
		VERTEX_3D *pVtx;

		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
		g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		for (int z = 0; z < BLOCK_Y; z++)
		{
			for (int x = 0; x < BLOCK_X; x++)
			{
				//int y = rand() % 1;
				pVtx[(z * BLOCK_X) + x].pos = D3DXVECTOR3(5000+(x * -100.0f), 0.0f, 5000+(z * (-100.0f)));
			}
		}

		//
		for (int i = 0; i < g_NumVertex * 100; i++)
		{
			pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}


		//�e�N�X�`�����W�̐ݒ�
		for (int i = 0; i < BLOCK_Y; i++)		//y���W
		{
			for (int j = 0; j < BLOCK_X; j++)		//x���W
			{
				pVtx[(i * BLOCK_X) + j].tex = D3DXVECTOR2(j, i);
			}
		}

		g_pVtxBuffField->Unlock();
	}

	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD)*g_NumVertex * 100,		//�����_��
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


		for (int i = 0; i < BLOCK_X; i++)	//x
		{
			pIdx[i * 2] = (BLOCK_X)+i;		//x + i
			pIdx[(i * 2) + 1] = i;
		}

		for (int j = 0; j < BLOCK_Y; j++)	//x
		{
			for (int i = 0; i < BLOCK_X; i++)	//x
			{
				pIdx[BLOCK_X + (j*BLOCK_X) + i * 2] = BLOCK_X * j + (BLOCK_X) * 2 + i;		//x + i
				pIdx[BLOCK_X + (j*BLOCK_X) + (i * 2) + 1] = (BLOCK_X * j) + BLOCK_X + i;
			}
		}

		//�C���f�b�N�X�f�[�^���A�����b�N����
		g_pIdxBuffField->Unlock();
	}
	return S_OK;
}

//DrawprinitiveUP�E�E�E����������܂Ŏ����ł���Ă����
//Drawprinitive�E�E�E�����ō�������_�o�b�t�@��`�悵�Ă����B���삪����
//Lock�E�E�EVRAM�ɏ�������ł����(�d���̂łȂ�ׂ��񐔂����炷)�܂Ƃ߂ă��b�N����(�`�悷��)�Ƃ���
//Unlock�E�E�ELock���������Ă����(�d���̂łȂ�ׂ��񐔂����炷)
//�`��E�ELock���遨�`��ύX��Unlock����
//�k�ރ|���S���E�E�Eindex��x�̏I����2��Ay�̂͂��߂�2��J��Ԃ�(12,5,13,,6,[6,14],14,7,15)