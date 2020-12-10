//=============================================================================
//
// �e���� [billboard.cpp]
//
//=============================================================================
#include "bullet.h"
#include "myDirect3D.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"
#include "player.h"
#include "Vector.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_BILLBOARD		"asset/texture/billboard/bullet.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	BILLBOARD_SIZE_X		(20.0f)							// �r���{�[�h�̕�
#define	BILLBOARD_SIZE_Y		(20.0f)							// �r���{�[�h�̍���
#define	VALUE_MOVE_BILLBOARD	(0.30f)							// �ړ����x
#define	VALUE_JUMP				(10.0f)							// �W�����v��
#define	VALUE_GRAVITY			(0.45f)							// �d��
#define	RATE_REGIST				(0.075f)						// ��R�W��
#define	RATE_REFRECT			(-0.90f)						// ���ˌW��

#define BULLET_TIME				180

#define BILLBORD_NUM_VERTEX		4
#define BILLBORD_NUM_POLYGON	2

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);
void SetVertexBullet(float fSizeX, float fSizeY);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

typedef struct
{
	D3DXMATRIX				g_mtxWorldBillboard;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3				g_posBullet;				// �ʒu
	D3DXVECTOR3				g_rotBullet;				// �ʒu
	D3DXVECTOR3				g_sclBullet;				// �X�P�[��
	D3DXVECTOR3				g_moveBullet;				// �ړ���
	bool					Use;						//�g�p���Ă��邩�ǂ���
	int						type;						//�ǂ��炩���g������
	int						timer;
}BULLET;

BULLET g_bullet[MAX_BULLET];

//=============================================================================
// ����������
//=============================================================================
HRESULT Bullet_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// ���_���̍쐬
	MakeVertexBullet(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BILLBOARD,		// �t�@�C���̖��O
		&g_pTextureBullet);	// �ǂݍ��ރ������[

	for (int i = 0; i < MAX_BULLET; i++)
	{
		g_bullet[i].g_rotBullet = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_bullet[i].g_sclBullet = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
		g_bullet[i].g_moveBullet = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_bullet[i].Use = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Bullet_Finalize(void)
{
	if (g_pTextureBullet != NULL)
	{// �e�N�X�`���̊J��
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	if (g_pVtxBuffBullet != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Bullet_Update(void)
{
	CAMERA *pCamera;

	// �J�����̎擾
	pCamera = GetCamera();

	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (g_bullet[i].Use == true)
		{
			g_bullet[i].g_posBullet += g_bullet[i].g_moveBullet;
			g_bullet[i].timer++;
			if (g_bullet[i].timer >= BULLET_TIME)
			{
				DisabledBullet(i);
			}
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void Bullet_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	//���e�X�g��L����
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (g_bullet[i].Use == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_bullet[i].g_mtxWorldBillboard);

			//�r���[�}�g���N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S���𐳖ʂɌ�����
#if 1
	//�t�s������Ƃ߂� (�O�̌v�Z���Ȃ��������Ƃɂ���)
			D3DXMatrixInverse(&g_bullet[i].g_mtxWorldBillboard, NULL, &mtxView);//�J�����̕������݂�悤�ɂȂ�

			//���s�ړ��̕����͖�������
			g_bullet[i].g_mtxWorldBillboard._41 = 0.0f;
			g_bullet[i].g_mtxWorldBillboard._42 = 0.0f;
			g_bullet[i].g_mtxWorldBillboard._43 = 0.0f;

#else
			g_bullet[i].g_mtxWorldBillboard._11 = mtxView._11;
			g_bullet[i].g_mtxWorldBillboard._12 = mtxView._21;
			g_bullet[i].g_mtxWorldBillboard._13 = mtxView._31;
			g_bullet[i].g_mtxWorldBillboard._21 = mtxView._12;
			g_bullet[i].g_mtxWorldBillboard._22 = mtxView._22;
			g_bullet[i].g_mtxWorldBillboard._23 = mtxView._32;
			g_bullet[i].g_mtxWorldBillboard._31 = mtxView._13;
			g_bullet[i].g_mtxWorldBillboard._32 = mtxView._23;
			g_bullet[i].g_mtxWorldBillboard._33 = mtxView._33;
#endif

			//�X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, g_bullet[i].g_sclBullet.x, g_bullet[i].g_sclBullet.y, g_bullet[i].g_sclBullet.z);
			D3DXMatrixMultiply(&g_bullet[i].g_mtxWorldBillboard, &g_bullet[i].g_mtxWorldBillboard, &mtxScale);

			//�ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_bullet[i].g_posBullet.x, g_bullet[i].g_posBullet.y, g_bullet[i].g_posBullet.z);
			D3DXMatrixMultiply(&g_bullet[i].g_mtxWorldBillboard, &g_bullet[i].g_mtxWorldBillboard, &mtxTranslate);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_bullet[i].g_mtxWorldBillboard);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, BILLBORD_NUM_POLYGON);
		}
	}

	//���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//���e�X�g�𖳌���
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * BILLBORD_NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pVtxBuffBullet,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f); -

			// �@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffBullet->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBullet(float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffBullet->Unlock();
	}
}

//�e���Z�b�g����
void SetBullet(D3DXVECTOR3 pos,int type)
{
	int enemytype;

	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (g_bullet[i].Use == false)
		{
			g_bullet[i].g_posBullet = pos;
			g_bullet[i].type = type;
			g_bullet[i].Use = true;
			
			//�G�̍��W�����߂�̂Ɏg��
			if (type == 0)
			{
				enemytype = 1;
			}
			else
			{
				enemytype = 0;
			}

			g_bullet[i].g_moveBullet = GetVector(g_bullet[i].g_posBullet, GetPos(enemytype));
			g_bullet[i].g_moveBullet *= 50.0f;
			break;
		}
	}
}

//�s���{�[�h������
void DisabledBullet(int index)
{
	g_bullet[index].timer = 0;
	g_bullet[index].type = 0;
	g_bullet[index].Use = false;

}

//�e�̑��݂���ɓ����
bool GetBulletUse(int index)
{
	return g_bullet[index].Use;
}

//�e�̍��W����ɓ����
D3DXVECTOR3 GetBulletPos(int index)
{
	return g_bullet[index].g_posBullet;
}