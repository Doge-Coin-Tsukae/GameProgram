#pragma once

#include "main.h"
#include "player.h"

#define POTATO (1.0f)	//�c�̃A���O���ϊ�

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
	JUMP,
	GRAVITY,
};

//*****************************************************************************
// �J�����̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posV;			// ���_
	D3DXVECTOR3 posR;			// �����_
	D3DXVECTOR3 vecU;			// ������x�N�g��
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
	D3DVIEWPORT9 g_view;

	float fly;					//�󒆂ɕ����Ă���Ƃ��ɐi�ލ��W
	float viewangle;			//����p
	float ZoomTimer;			//�Y�[�����Ԃ̃^�C�}�[
	bool Hit;					//�v���C���[�������Ȃ��Ƃ�
} CAMERA;

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
		m_Length = 150.0f;
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
			m_Angle2 += POTATO;
		}
		//���̔��肪�������Ƃ�
		else if (type == DOWN)
		{
			m_Angle2 -= POTATO;
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
void Camera_Initialize(void);
void Camera_Finalize(void);
void Camera_Update(void);

void Camera_SetCamera(int index);
void changecamera(int type, int index, float cameraspeed);
D3DXVECTOR3 GetPosR(int index);
D3DXVECTOR3 GetPosV(int index);
void Hitcamera(bool trfl,int index);
void LoadCameraPos(int index);
void ZoomCamera(int index);
void ChangeCameraVer(int num, int index);
void ChangeCamera(int num, int index);
float GetAngle2(int index);
void SetCamera(D3DXVECTOR3 posr, D3DXVECTOR3 posv);
CAMERA *GetCamera(int index);