//****************************************************
//�����蔻��̃v���O����
//****************************************************

#include "colision.h"
#include "myDirect3D.h"
#include "texture.h"

#define	COL_WIDTH		(50.0f)						// �n�ʂ̕�(X����)
#define	COL_DEPTH		(50.0f)						// �n�ʂ̉��s(Z����)
#define COL_HIGHT		(50.0f)						// �n�ʂ̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT static MakeVertexField(LPDIRECT3DDEVICE9 pDevice);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9  static g_pVtxBuffField = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

D3DXMATRIX	static			g_mtxWorldField;		// ���[���h�}�g���b�N�X(�s��)
D3DXVECTOR3	static			g_posField;				// �n�ʂ̈ʒu
D3DXVECTOR3	static			g_rotField;				// �n�ʂ̌���(��])
D3DXVECTOR3	static			g_sclField;				// �n�ʂ̑傫��(�X�P�[��)


//*****************************************************************************
//�v���O����
//*****************************************************************************
/* ����������*/
HRESULT Coli_Initialize(void)
{
	LPDIRECT3DDEVICE9 static pDevice[2];
	pDevice[0] = GetD3DDevice();
	pDevice[1] = GetD3DDevice();

	// ���_���̍쐬
	MakeVertexField(pDevice[0]);
	MakeVertexField(pDevice[1]);

	g_posField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sclField = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	return S_OK;
}

bool CircleAndPoint(D3DXVECTOR3 pos, D3DXVECTOR3 epos,float radius)
{
	//�x�N�g��
	D3DXVECTOR3 xyz;
	//�P�ʃx�N�g��
	float vector;

	//�~�̒��S - �_
	xyz = pos - epos;
	vector = sqrt((xyz.x * xyz.x) + (xyz.y * xyz.y) + (xyz.z * xyz.z));

	if (sqrt(vector*vector)<=radius)
	{
		return true;
	}

	return false;
}

//�_�Ɛ����`�̓����蔻��(�_,�����`,�����`�̑傫��,���̐����`���g���Ă��邩�ǂ���,1�ӂ̑傫��)
bool PointtoSquare(D3DXVECTOR3 Point, D3DXVECTOR3 Square, D3DXVECTOR3 SquareScl, bool Used,float side)
{
	if (Point.x >= Square.x - (side * SquareScl.x) && Point.x <= Square.x + (side * SquareScl.x) &&			//X���W
		Point.y >= Square.y - (side * SquareScl.y) && Point.y <= Square.y + (side * SquareScl.y) * 2 &&		//Y���W								//Y���W
		Point.z >= Square.z - (side * SquareScl.z) && Point.z <= Square.z + (side * SquareScl.z) &&			//Z���W
		Used == true)			//���̃u���b�N���g���Ă���
	{
		return true;		//�u���b�N�̔�����ɂ���
	}

	return false;		//�u���b�N�̔���O�ɂ���
}

//�_�ƒ����`�̓����蔻��(�_,�����`,�����`�̑傫��,���̐����`���g���Ă��邩�ǂ���,1�ӂ̑傫��,1�ӂ̒������̑傫��)
bool PointtoRectangley(D3DXVECTOR3 Point, D3DXVECTOR3 Square, D3DXVECTOR3 SquareScl, bool Used, float side,float longside)
{
	if (Point.x >= Square.x - (side * SquareScl.x) && Point.x <= Square.x + (side * SquareScl.x) &&			//X���W
		Point.y >= Square.y - (longside * SquareScl.y) && Point.y <= Square.y + (longside * SquareScl.y) * 2 &&		//Y���W								//Y���W
		Point.z >= Square.z - (side * SquareScl.z) && Point.z <= Square.z + (side * SquareScl.z) &&			//Z���W
		Used == true)			//���̃u���b�N���g���Ă���
	{
		return true;		//�u���b�N�̔�����ɂ���
	}

	return false;		//�u���b�N�̔���O�ɂ���
}

bool AABB(D3DXVECTOR3 Square1, D3DXVECTOR3 SquareScl1, D3DXVECTOR3 Square2, D3DXVECTOR3 SquareScl2, bool Used, float side, float longside)
{

}

//�����蔻��̉���
void SetPolygon(D3DXVECTOR3 Pos)
{
	g_posField = Pos;
}

/* �`�揈��*/
void Coli_Draw(void)
{

	LPDIRECT3DDEVICE9 static pDevice = GetD3DDevice();
	D3DXMATRIX static mtxScl, mtxRot, mtxTranslate;

	//���[���h�ϊ�

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldField);

	//�X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, g_sclField.x, g_sclField.y, g_sclField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxScl);

	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotField.y, g_rotField.x, g_rotField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);

	//�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_posField.x, g_posField.y, g_posField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTranslate);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldField);

	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_FIELD02));

	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, NUM_POLYGON);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT static MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{

	//�I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffField, NULL)))
	{
		return E_FAIL;
	}

	{
		//���_�o�b�t�@�𖄂߂�
		VERTEX_3D static *pVtx;

		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
		g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].pos = D3DXVECTOR3(-COL_WIDTH, COL_HIGHT, COL_DEPTH);
		pVtx[1].pos = D3DXVECTOR3(COL_WIDTH, COL_HIGHT, COL_DEPTH);
		pVtx[2].pos = D3DXVECTOR3(-COL_WIDTH, COL_HIGHT, -COL_DEPTH);
		pVtx[3].pos = D3DXVECTOR3(COL_WIDTH, COL_HIGHT, COL_DEPTH);
		pVtx[4].pos = D3DXVECTOR3(COL_WIDTH, COL_HIGHT, -COL_DEPTH);
		pVtx[5].pos = D3DXVECTOR3(-COL_WIDTH, COL_HIGHT, -COL_DEPTH);

		//��
		pVtx[6].pos = D3DXVECTOR3(-COL_WIDTH, -COL_HIGHT, -COL_DEPTH);
		pVtx[7].pos = D3DXVECTOR3(COL_WIDTH, -COL_HIGHT, COL_DEPTH);
		pVtx[8].pos = D3DXVECTOR3(-COL_WIDTH, -COL_HIGHT, COL_DEPTH);
		pVtx[9].pos = D3DXVECTOR3(-COL_WIDTH, -COL_HIGHT, -COL_DEPTH);
		pVtx[10].pos = D3DXVECTOR3(COL_WIDTH, -COL_HIGHT, -COL_DEPTH);
		pVtx[11].pos = D3DXVECTOR3(COL_WIDTH, -COL_HIGHT, COL_DEPTH);


		//��
		pVtx[12].pos = D3DXVECTOR3(-COL_WIDTH, COL_HIGHT, COL_DEPTH);
		pVtx[13].pos = D3DXVECTOR3(-COL_WIDTH, COL_HIGHT, -COL_DEPTH);
		pVtx[14].pos = D3DXVECTOR3(-COL_WIDTH, -COL_HIGHT, COL_DEPTH);
		pVtx[15].pos = D3DXVECTOR3(-COL_WIDTH, COL_HIGHT, -COL_DEPTH);
		pVtx[16].pos = D3DXVECTOR3(-COL_WIDTH, -COL_HIGHT, -COL_DEPTH);
		pVtx[17].pos = D3DXVECTOR3(-COL_WIDTH, -COL_HIGHT, COL_DEPTH);

		//�E
		pVtx[18].pos = D3DXVECTOR3(COL_WIDTH, -COL_HIGHT, COL_DEPTH);
		pVtx[19].pos = D3DXVECTOR3(COL_WIDTH, COL_HIGHT, -COL_DEPTH);
		pVtx[20].pos = D3DXVECTOR3(COL_WIDTH, COL_HIGHT, COL_DEPTH);
		pVtx[21].pos = D3DXVECTOR3(COL_WIDTH, -COL_HIGHT, COL_DEPTH);
		pVtx[22].pos = D3DXVECTOR3(COL_WIDTH, -COL_HIGHT, -COL_DEPTH);
		pVtx[23].pos = D3DXVECTOR3(COL_WIDTH, COL_HIGHT, -COL_DEPTH);

		//�O
		pVtx[24].pos = D3DXVECTOR3(-COL_WIDTH, COL_HIGHT, -COL_DEPTH);
		pVtx[25].pos = D3DXVECTOR3(COL_WIDTH, COL_HIGHT, -COL_DEPTH);
		pVtx[26].pos = D3DXVECTOR3(-COL_WIDTH, -COL_HIGHT, -COL_DEPTH);
		pVtx[27].pos = D3DXVECTOR3(COL_WIDTH, COL_HIGHT, -COL_DEPTH);
		pVtx[28].pos = D3DXVECTOR3(COL_WIDTH, -COL_HIGHT, -COL_DEPTH);
		pVtx[29].pos = D3DXVECTOR3(-COL_WIDTH, -COL_HIGHT, -COL_DEPTH);

		//��
		pVtx[30].pos = D3DXVECTOR3(-COL_WIDTH, -COL_HIGHT, COL_DEPTH);
		pVtx[31].pos = D3DXVECTOR3(COL_WIDTH, COL_HIGHT, COL_DEPTH);
		pVtx[32].pos = D3DXVECTOR3(-COL_WIDTH, COL_HIGHT, COL_DEPTH);
		pVtx[33].pos = D3DXVECTOR3(-COL_WIDTH, -COL_HIGHT, COL_DEPTH);
		pVtx[34].pos = D3DXVECTOR3(COL_WIDTH, -COL_HIGHT, COL_DEPTH);
		pVtx[35].pos = D3DXVECTOR3(COL_WIDTH, COL_HIGHT, COL_DEPTH);

		//
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[6].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[9].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[10].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[11].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		pVtx[12].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[13].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[14].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[15].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[16].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[17].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

		pVtx[18].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		pVtx[19].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		pVtx[20].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		pVtx[21].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		pVtx[22].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		pVtx[23].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);

		pVtx[24].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[25].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[26].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[27].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[28].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[29].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		pVtx[30].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[31].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[32].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[33].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[34].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[35].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);


		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[20].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[21].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[22].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[23].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[24].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[25].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[26].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[27].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[28].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[29].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[30].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[31].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[32].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[33].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[34].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[35].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[4].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(0.0f, 0.0f);


		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[16].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[17].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[19].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[20].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[21].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[22].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[23].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx[24].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[25].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[26].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[27].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[28].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[29].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx[30].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[31].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[32].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[33].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[34].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[35].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_pVtxBuffField->Unlock();

	}

}
