#pragma once

#include "main.h"

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

	float fly;
	float viewangle;			//����p
	float ZoomTimer;			//�Y�[�����Ԃ̃^�C�}�[
	bool Hit;					//�v���C���[�������Ȃ��Ƃ�
} CAMERA;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void Camera_Initialize(void);
void Camera_Finalize(void);
void Camera_Update(void);

void Camera_SetCamera(int index);
void changecamera(int type, int index);
D3DXVECTOR3 GetPosR(int index);
void Hitcamera(bool trfl,int index);
void LoadCameraPos(int index);
void ZoomCamera(int index);
void ChangeCameraVer(int num, int index);
void ChangeCamera(int num, int index);
CAMERA* GetCamera();