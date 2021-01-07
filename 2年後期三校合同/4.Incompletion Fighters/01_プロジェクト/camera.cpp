//****************************************************
//�J�����̃v���O����
//****************************************************

#include "camera.h"
#include "player.h"
#include "myDirect3D.h"
#include "debugproc.h"
#include "Vector.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	CAM_ONE_POS_V_X		(2000.0f)					// 1P�̃J�����̎��_�����ʒu(X���W)
#define	CAM_ONE_POS_V_Y		(2000.0f)				// 1P�̃J�����̎��_�����ʒu(Y���W)
#define	CAM_ONE_POS_V_Z		(0.0f)				// 1P�̃J�����̎��_�����ʒu(Z���W)
#define	CAM_ONE_POS_R_X		(0.0f)					// 1P�̃J�����̒����_�����ʒu(X���W)
#define	CAM_ONE_POS_R_Y		(1000.0f)				// 1P�̃J�����̒����_�����ʒu(Y���W)
#define	CAM_ONE_POS_R_Z		(0.0f)				// 1P�̃J�����̒����_�����ʒu(Z���W)

#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(25500.0f)										// �r���[���ʂ�FarZ�l

#define CAMERANANAMESPEED	(35.36f)		//�J�������i�ރX�s�[�h
#define MAX_CAMERA		(1)					//�v���C���[���̏��

//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************

void centercamera(D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos);

//*****************************************************************************
//enum
//*****************************************************************************

//�ړ���enum
enum MOVEMENT
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	RIGHTUP,
	RIGHTDOWN,
	LEFTUP,
	LEFTDOWN,
	FLY,
	GRAVITY,
};

//*****************************************************************************
//�~�̃N���X
//*****************************************************************************
class DRAWOBJECT
{
private:
	float m_Angle;		// �p�x
	float m_Angle2;		// �p�x
	float m_Length;		// ���a�̒���

public:
	//��������
	void InitCircle(int index)
	{
		m_Angle = GetRot(index).y;		//�~�̊p�x�Ƀv���C���[�̊p�x������
		m_Angle2 = 0.0f;
		m_Length = 200.0f;
	}

	//�J������](���E)
	void ChangeCameraRot(int index)
	{
		m_Angle = GetRot(index).y;		//�J�����A���O���ƃv���C���[�A���O�������킹��
	}

	//�J������](�㉺)
	void ChangeCameraRotVertical(int type)
	{
		//��̔��肪�������Ƃ�
		if (type == UP)
		{
			m_Angle2 += 4.0f;
		}
		//���̔��肪�������Ƃ�
		else if (type == DOWN)
		{
			m_Angle2 -= 4.0f;
		}
		else {
		}

		//������̈ړ�����
		if (m_Angle2 >= 40)
		{
			m_Angle2 = 40;
		}

		//�������̈ړ�����
		if (m_Angle2 <= -90)
		{
			m_Angle2 = -90;
		}
	}

	/*�Q�b�^�[*/
	//�E���̃A���O��
	float GetAngle()
	{
		return m_Angle;
	}

	//�㉺�̃A���O��
	float GetAngle2()
	{
		return m_Angle2;
	}

	//���a����ɓ����
	float GetLength()
	{
		return m_Length;
	}

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
CAMERA g_camera[MAX_CAMERA];		// �J�������
DRAWOBJECT g_en[MAX_CAMERA];		//�~���

//=============================================================================
// �J�����̏���������
//=============================================================================
void Camera_Initialize(void)
{

	g_camera[0].posV = D3DXVECTOR3(CAM_ONE_POS_V_X, CAM_ONE_POS_V_Y, CAM_ONE_POS_V_Z);
	g_camera[0].posR = D3DXVECTOR3(CAM_ONE_POS_R_X, CAM_ONE_POS_R_Y, CAM_ONE_POS_R_Z);

	for (int i = 0; i < MAX_CAMERA; i++)
	{
		g_en[i].InitCircle(i);	//�~�̏��L����

		//g_camera[i].shake = 10.0f;
		g_camera[i].viewangle = D3DXToRadian(45.0f);
		g_camera[i].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera[i].ZoomTimer = 0.0f;
		g_camera[i].Hit = false;
		g_camera[i].fly = 0.0f;
		g_en[i].ChangeCameraRot(i);
	}

	//�J��������
	//1P
	g_camera[0].g_view = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f };
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void Camera_Finalize(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void Camera_Update(void)
{
		centercamera(GetPos(0),GetPos(1));
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
}

/*�J�������W�̕ύX*/
void changecamera(int type, int index)
{
	if (g_camera[index].Hit == false) {
		switch (type) {
			//�O�ړ�
		case UP:
			g_camera[index].posV.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

			//���ړ�
		case DOWN:
			g_camera[index].posV.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

			//�E�ړ�
		case RIGHT:
			g_camera[index].posV.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

			//���ړ�
		case LEFT:
			g_camera[index].posV.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

			//�E�O
		case RIGHTUP:
			g_camera[index].posV.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;

			g_camera[index].posV.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

			//�E���
		case RIGHTDOWN:
			g_camera[index].posV.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;

			g_camera[index].posV.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

			//���O
		case LEFTUP:
			g_camera[index].posV.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;

			g_camera[index].posV.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

			//�����
		case LEFTDOWN:
			g_camera[index].posV.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;

			g_camera[index].posV.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

		case FLY:
			g_camera[index].fly = 200.0f;
			break;

			//�d�͂Ɉ���������
		case GRAVITY:
			g_camera[index].posV.y += g_camera[index].fly;
			g_camera[index].posR.y += g_camera[index].fly;

			if (g_camera[index].posV.y <= CAM_ONE_POS_V_Y)
			{
				g_camera[index].posV.y = CAM_ONE_POS_V_Y;
				g_camera[index].fly = 0.0f;
			}
			else
			{
				g_camera[index].fly -= 10.0f;
			}
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

void centercamera(D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos)
{

	g_camera[0].posR = P1Pos - (GetOnlyVector(P1Pos, P2Pos) / 2);
	g_camera[0].posV = g_camera[0].posR;
	//g_camera[0].posV = vector / 2;

	g_camera[0].posR.y = CAM_ONE_POS_R_Y;
	g_camera[0].posV.x = CAM_ONE_POS_V_X;
	g_camera[0].posV.y = CAM_ONE_POS_V_Y +200;
}

CAMERA* GetCamera()
{
	return &g_camera[0];
}