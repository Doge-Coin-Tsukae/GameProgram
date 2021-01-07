#include "field.h"
#include "myDirect3D.h"
#include "texture.h"
#include "debugproc.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BLOCK_X 40
#define BLOCK_Y 60

#define BLOCK_SIZE_X 150.0f
#define BLOCK_SIZE_Y 150.0f


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffField = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
static LPDIRECT3DINDEXBUFFER9	g_pIdxBuffField = NULL; // 
static int						g_NumIndexField;		// 
static LPDIRECT3DTEXTURE9		g_pTextureField;		// �e�N�X�`���ւ̃|�C���^


static int g_NumBlockX;
static int g_NumBlockZ;
static float g_SizeBlockX;
static float g_SizeBlockZ;
static int g_NumVertex;
static int g_NumIndex;
static int g_NumPolygon;


//=============================================================================
// ����������
//=============================================================================
HRESULT Field_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// ���_���̍쐬
	MakeVertexField(pDevice);

	SetTexture(TEXTURE_INDEX_KUSSA);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Field_Finalize(void)
{
	if (g_pVtxBuffField != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
	ReleaseTexture(TEXTURE_INDEX_KUSSA);
}

//=============================================================================
// �X�V����
//=============================================================================
void Field_Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void Field_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	//���_�̖@�����m�[�}���C�Y����
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMATRIX mtxWorld;
	D3DXMatrixIdentity(&mtxWorld);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	pDevice->SetIndices(g_pIdxBuffField);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_KUSSA));

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_NumVertex, 0, g_NumPolygon);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	g_NumVertex = (BLOCK_X + 1) * (BLOCK_Y + 1);
	g_NumIndex = (BLOCK_X + 1) * 2 * BLOCK_Y + (BLOCK_Y - 1) * 2;
	g_NumPolygon = BLOCK_X * 2 * BLOCK_Y + (BLOCK_Y - 1) * 4;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_NumVertex,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pVtxBuffField,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		//		const float fTexSizeX = 1.0f / g_NumBlockX;
		//		const float fTexSizeZ = 1.0f / g_NumBlockZ;
		const float fTexSizeX = 1.0f;
		const float fTexSizeZ = 1.0f;

		const float offset_x = BLOCK_X * BLOCK_SIZE_X / 2;
		const float offset_y = BLOCK_Y * BLOCK_SIZE_Y / 2;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		for (int z = 0; z < (BLOCK_Y + 1); z++) {
			for (int x = 0; x < (BLOCK_X + 1); x++) {
				// ���W�̐ݒ�
				pVtx[z * (BLOCK_X + 1) + x].pos = D3DXVECTOR3(x*BLOCK_SIZE_X - offset_x, 0.0f, z*-BLOCK_SIZE_Y + offset_y);
				// �@���̐ݒ�
				pVtx[z * (BLOCK_X + 1) + x].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				// ���_�J���[�̐ݒ�
				pVtx[z * (BLOCK_X + 1) + x].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				// �e�N�X�`�����W�̐ݒ�
				pVtx[z * (BLOCK_X + 1) + x].tex.x = (float)x;
				pVtx[z * (BLOCK_X + 1) + x].tex.y = (float)z;
			}
		}

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffField->Unlock();
	}

	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * g_NumIndex,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
		D3DFMT_INDEX16,						// �g�p����C���f�b�N�X�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pIdxBuffField,					// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
		WORD *pIdx;

		// �C���f�b�N�X�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pIdxBuffField->Lock(0, 0, (void**)&pIdx, 0);

		int idx_cnt = 0;

		//�C���f�b�N�X�o�b�t�@�̐ݒ�
		for (int y = 0; y < BLOCK_Y; y++)
		{
			for (int x = 0; x < (BLOCK_X + 1); x++)
			{
				pIdx[idx_cnt] = (BLOCK_X + 1) * y + (BLOCK_X + 1) + x;
				idx_cnt++;
				pIdx[idx_cnt] = (BLOCK_X + 1) * y + x;
				idx_cnt++;
			}
			if (y < (BLOCK_Y - 1))
			{
				//�k�ރ|���S���̃C���f�b�N�X
				pIdx[idx_cnt] = (BLOCK_X + 1)*y + BLOCK_X;
				idx_cnt++;
				pIdx[idx_cnt] = (BLOCK_X + 1)*(y + 2);
				idx_cnt++;
			}
		}

		// �C���f�b�N�X�f�[�^���A�����b�N����
		g_pIdxBuffField->Unlock();
	}

	return S_OK;
}