//****************************************************
//�J�����̃v���O����
//****************************************************
#include "tittle_camera.h"
#include "field.h"
#include "camera.h"
#include "myDirect3D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	CAM_ONE_POS_V_X		(0.0f)					// 1P�̃J�����̎��_�����ʒu(X���W)
#define	CAM_ONE_POS_V_Y		(200.0f)				// 1P�̃J�����̎��_�����ʒu(Y���W)
#define	CAM_ONE_POS_V_Z		(2000.0f)				// 1P�̃J�����̎��_�����ʒu(Z���W)
#define	CAM_ONE_POS_R_X		(0.0f)					// 1P�̃J�����̒����_�����ʒu(X���W)
#define	CAM_ONE_POS_R_Y		(100.0f)				// 1P�̃J�����̒����_�����ʒu(Y���W)
#define	CAM_ONE_POS_R_Z		(2050.0f)				// 1P�̃J�����̒����_�����ʒu(Z���W)

#define	CAM_TWO_POS_V_X		(0.0f)					// 2P�̃J�����̎��_�����ʒu(X���W)
#define	CAM_TWO_POS_V_Y		(200.0f)				// 2P�̃J�����̎��_�����ʒu(Y���W)
#define	CAM_TWO_POS_V_Z		(-2000.0f)				// 2P�̃J�����̎��_�����ʒu(Z���W)
#define	CAM_TWO_POS_R_X		(0.0f)					// 2P�̃J�����̒����_�����ʒu(X���W)
#define	CAM_TWO_POS_R_Y		(100.0f)				// 2P�̃J�����̒����_�����ʒu(Y���W)
#define	CAM_TWO_POS_R_Z		(-2050.0f)				// 2P�̃J�����̒����_�����ʒu(Z���W)

#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(26000.0f)										// �r���[���ʂ�FarZ�l

#define MAX_CAMERA		(2)					//�v���C���[���̏��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
TCAMERA g_title_camera[2];		// �J�������
DRAWOBJECT g_en[2];		//�~���

static float hankei = 500;
static float kakudo = 90.0f;

//=============================================================================
// �J�����̏���������
//=============================================================================
HRESULT TCamera_Initialize(void)
{

	g_title_camera[0].posV = D3DXVECTOR3(CAM_ONE_POS_V_X, CAM_ONE_POS_V_Y, CAM_ONE_POS_V_Z);
	g_title_camera[1].posV = D3DXVECTOR3(CAM_TWO_POS_V_X, CAM_TWO_POS_V_Y, CAM_TWO_POS_V_Z);
	g_title_camera[0].posR = D3DXVECTOR3(CAM_ONE_POS_R_X, CAM_ONE_POS_R_Y, CAM_ONE_POS_R_Z);
	g_title_camera[1].posR = D3DXVECTOR3(CAM_TWO_POS_R_X, CAM_TWO_POS_R_Y, CAM_TWO_POS_R_Z);

	for (int i = 0; i < MAX_CAMERA; i++)
	{
		g_title_camera[i].viewangle = D3DXToRadian(45.0f);
		g_title_camera[i].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	}

	//�J��������
	//1P
	g_title_camera[0].g_view = { 0, 0, SCREEN_WIDTH / 2 , SCREEN_HEIGHT, 0.0f, 1.0f };
	//2P
	g_title_camera[1].g_view = { SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT,0.0f,1.0f };

	Field_Initialize();



	return S_OK;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void TCamera_Finalize(void)
{
	g_title_camera[0].g_view = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f };

	Field_Finalize();
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void TCamera_Update(void)
{
	for (int i = 0; i < MAX_CAMERA; i++)
	{

		Field_Update();

		kakudo -= 0.001f;

		g_title_camera[i].posV.x = g_title_camera[i].posR.x + hankei * cosf(kakudo);
		g_title_camera[i].posV.z = g_title_camera[i].posR.z + hankei * sinf(kakudo);


		/*�����܂�*/
	}
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void TCamera_SetCamera(int index)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_title_camera[index].mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬(3D����2D�ɂ���)
	D3DXMatrixPerspectiveFovLH(&g_title_camera[index].mtxProjection,
		g_title_camera[index].viewangle,		// �r���[���ʂ̎���p
		VIEW_ASPECT,			// �r���[���ʂ̃A�X�y�N�g��
		VIEW_NEAR_Z,			// �r���[���ʂ�NearZ�l
		VIEW_FAR_Z);			// �r���[���ʂ�FarZ�l

	D3DXMATRIX mtxProj;
	D3DXMatrixIdentity(&mtxProj);

	float aspect = D3DXToRadian(45);

	float w = 1 / tanf((aspect*1.78)*0.5);
	float h = 1 / tanf((aspect)*0.5f);
	float Q = 0;//= VIEW_FAR_Z / (VIEW_FAR_Z - VIEW_FAR_Z);

	mtxProj(0, 1) = w;
	mtxProj(1, 0) = h;
	mtxProj(2, 2) = Q;
	mtxProj(2, 3) = 1.0f;
	mtxProj(3, 2) = Q * VIEW_NEAR_Z*-1;


	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_title_camera[index].mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_title_camera[index].mtxView);		//�P�ʍs�������Ă����(�s�������������Ƃ��Ɏg��)

// �r���[�}�g���b�N�X�̐ݒ�

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_title_camera[index].mtxView,
		&g_title_camera[index].posV,		// �J�����̎��_
		&g_title_camera[index].posR,		// �J�����̒����_
		&g_title_camera[index].vecU);	// �J�����̏�����x�N�g��

//�J�����̍��W��ύX�i�r���[�s��j
	pDevice->SetViewport(&g_title_camera[index].g_view);
	pDevice->SetTransform(D3DTS_VIEW, &g_title_camera[index].mtxView);

	Field_Draw();
}


void SetTCamera(D3DXVECTOR3 posr, D3DXVECTOR3 posv,int index)
{
	g_title_camera[index].posR = posr;
	g_title_camera[index].posV = posv;
}
