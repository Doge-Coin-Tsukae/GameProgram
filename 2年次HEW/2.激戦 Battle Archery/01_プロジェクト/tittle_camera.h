#pragma once
#include "main.h"

//*****************************************************************************
// �J�����̍\����
//*****************************************************************************
struct TCAMERA
{
	D3DXVECTOR3 posV;			// �J�����̎��_
	D3DXVECTOR3 posR;			// �J�����̒����_
	D3DXVECTOR3 vecU;			// �J�����̏����
	D3DXVECTOR3 posVDest;		// �J�����̎��_�̖ړI�ʒu
	D3DXVECTOR3 posRDest;		// �J�����̒����_�̖ړI�ʒu
	D3DXVECTOR3 rot;			// �J�����̉�]
	float fLengthInterval;		// �J�����̎��_�ƒ����_�̋���
	float fHeightV;				// �J�����̎��_�̍���
	float fHeightR;				// �J�����̒����_�̍���
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	float fRateRotAuto;			// ������荞�݌W��
	bool bMoveAuto;				// ������荞��ON/OFF

	//D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
	D3DVIEWPORT9 g_view;
	float viewangle;			//����p

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT TCamera_Initialize(void);
void TCamera_Finalize(void);
void TCamera_Update(void);
void TCamera_SetCamera(int index);
void SetTCamera(D3DXVECTOR3 posr, D3DXVECTOR3 posv, int index);