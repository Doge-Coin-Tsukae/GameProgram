//****************************************************
//�J�����̃v���O����
//****************************************************

#include "camera.h"
#include "myDirect3D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAM_ONE_POS_V D3DXVECTOR3(0.0f,180.0f,2150.0f)		// 1P�̃J�����̎��_�����ʒu
#define CAM_ONE_POS_R D3DXVECTOR3(0.0f,180.0f,45.0f)		// 1P�̃J�����̒����_�����ʒu

#define	CAM_TWO_POS_V D3DXVECTOR3(0.0f,180.0f,-2150.0f)
#define	CAM_TWO_POS_R D3DXVECTOR3(0.0f,180.0f,-45.0f)

#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��
#define	VIEW_NEAR_Z		(100.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(8000.0f)										// �r���[���ʂ�FarZ�l

#define CAMERANANAMESPEED	(35.36f)		//�J�������i�ރX�s�[�h
#define MAX_CAMERA		(2)					//�v���C���[���̏��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
CAMERA g_camera[2];		// �J�������
DRAWOBJECT static g_en[2];		//�~���

//=============================================================================
// �J�����̏���������
//=============================================================================
void Camera_Initialize(void)
{

	g_camera[0].posV = CAM_ONE_POS_V;
	g_camera[1].posV = CAM_TWO_POS_V;
	g_camera[0].posR = CAM_ONE_POS_R;
	g_camera[1].posR = CAM_TWO_POS_R;

	for (int i = 0; i < MAX_CAMERA; i++)
	{
		g_en[i].InitCircle(i);	//�~�̏�������

		g_camera[i].viewangle = D3DXToRadian(45.0f);
		g_camera[i].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera[i].ZoomTimer = 0.0f;
		g_camera[i].Hit = false;
		g_camera[i].fly = 0.0f;
	}

	//�J��������
	//1P
	g_camera[0].g_view = { 0, 0, SCREEN_WIDTH / 2 , SCREEN_HEIGHT, 0.0f, 1.0f };
	//2P
	g_camera[1].g_view = { SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT,0.0f,1.0f };
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void Camera_Finalize(void)
{
	g_camera[0].g_view = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f };
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void Camera_Update(void)
{
	for (int i=0; i < MAX_CAMERA; i++)
	{
		/*���̉~������o��*/
		float radius = g_en[i].GetAngle() * 3.14f / 180.0f;

		// �O�p�֐����g�p���A�~�̈ʒu������o���B
		float add_x = cos(radius) * g_en[i].GetLength();
		float add_z = sin(radius) * g_en[i].GetLength();

		// ���ʂłł��ʒu�𒆐S�ʒu�ɉ��Z���A�����`��ʒu�Ƃ���
	
		g_camera[i].posV.x = GetPos(i).x - add_x;
		g_camera[i].posV.z = GetPos(i).z - add_z;
		/*�����܂�*/

		/*�c�̉~������o��*/
		float radius2 = g_en[i].GetAngle2() * 3.14f / 180.0f;

		// �O�p�֐����g�p���A�~�̈ʒu������o���B
		float add_y = sin(radius2) * g_en[i].GetLength();
		g_camera[i].posV.y = GetPos(i).y + 170.0f - add_y;

		g_camera[i].posR = GetPos(i);
		g_camera[i].posR.y = GetPos(i).y + 180.0f;

		/*�����܂�*/

	}
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void Camera_SetCamera(int index)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[index].mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬(3D����2D�ɂ���)
	D3DXMatrixPerspectiveFovLH(&g_camera[index].mtxProjection,
		g_camera[index].viewangle,		// �r���[���ʂ̎���p
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
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[index].mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[index].mtxView);		//�P�ʍs�������Ă����(�s�������������Ƃ��Ɏg��)

// �r���[�}�g���b�N�X�̐ݒ�

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera[index].mtxView,
		&g_camera[index].posV,		// �J�����̎��_
		&g_camera[index].posR,		// �J�����̒����_
		&g_camera[index].vecU);	// �J�����̏�����x�N�g��

//�J�����̍��W��ύX�i�r���[�s��j
	pDevice->SetViewport(&g_camera[index].g_view);
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[index].mtxView);

	//DebugProc_Print((char*)"�A���O�� [%f]\n", g_en[index].GetAngle());
	//DebugProc_Print((char*)"�A���O��2 [%f]\n", g_en[index].GetAngle2());
}

/*�J�������W�̕ύX*/
void changecamera(int type, int index,float cameraspeed)
{
	if (g_camera[index].Hit == false) {
		switch (type) {
			//�O�ړ�
		case UP:
			g_camera[index].posV.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//���ړ�
		case DOWN:
			g_camera[index].posV.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//�E�ړ�
		case RIGHT:
			g_camera[index].posV.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//���ړ�
		case LEFT:
			g_camera[index].posV.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//�E�O
		case RIGHTUP:
			g_camera[index].posV.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			g_camera[index].posV.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//�E���
		case RIGHTDOWN:
			g_camera[index].posV.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			g_camera[index].posV.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//���O
		case LEFTUP:
			g_camera[index].posV.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			g_camera[index].posV.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//�����
		case LEFTDOWN:
			g_camera[index].posV.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			g_camera[index].posV.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;
			//����ȊO
		default:
			break;
		}
	}

}

//�J�����̒����_���󂯎��
D3DXVECTOR3 GetPosR(int index)
{
	return g_camera[index].posR;
}

//�J�����̒����_���󂯎��
D3DXVECTOR3 GetPosV(int index)
{
	return g_camera[index].posV;
}

//�J�����̓������~�߂�	(true=�����Ȃ�,false=����)
void Hitcamera( bool trfl,int index)
{
	g_camera[index].Hit =trfl;
}

//����p�����Ƃɖ߂�
void LoadCameraPos(int index)
{
	g_camera[index].viewangle = D3DXToRadian(45.0f);
	g_camera[index].ZoomTimer = 0.0f;
}

//�J������^�������ɃY�[��������
void ZoomCamera(int index)
{
	if (g_camera[index].ZoomTimer < 4.0f)
	{

		g_camera[index].viewangle -= D3DXToRadian(0.3f);
		g_camera[index].ZoomTimer += 0.1f;
	}
}

//�w�肵���J�������p�x�Ɍ�������
void ChangeCameraVer(int num,int index)
{
	g_en[index].ChangeCameraRotVertical(num);
}

//�w�肵�����W�ɃJ�������ړ�������
void ChangeCamera(int num, int index)
{
	g_en[index].ChangeCameraRot(num);
}

float GetAngle2(int index)
{
	return g_en[index].GetAngle2();
}

void SetCamera(D3DXVECTOR3 posr, D3DXVECTOR3 posv)
{
	g_camera[0].posR = posr;
	g_camera[0].posV = posv;
}

//=============================================================================
// �J�����̎擾
//=============================================================================
CAMERA *GetCamera(int index)
{
	return &g_camera[index];
}
