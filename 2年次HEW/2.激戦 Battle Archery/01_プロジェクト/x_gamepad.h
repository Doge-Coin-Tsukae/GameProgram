//==============================================================================
// File name / type  :  x_gamepad.h
//  Private number   :  [AT-12C-342] No.19 
// Writer copyright  :  (C) Aoi Shibuichi All rights reserved.
//==============================================================================
#ifndef _X_GAMEPAD_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`
#define _X_GAMEPAD_H_

#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")

//==============================================================================
// �|�[�g�ԍ�
//==============================================================================
enum port
{
	PP_LX, // ���X�e�B�b�NX�� 32768 �` 32767
	PP_LY, // ���X�e�B�b�NY�� 32768 �` 32767
	PP_RX, // �E�X�e�B�b�NX�� 32768 �` 32767
	PP_RY, // �E�X�e�B�b�NY�� 32768 �` 32767
	PP_LT, // LT�{�^�� 0 �` 255
	PP_RT, // RT�{�^�� 0 �` 255
	PP_Tr,
	PP_UP,
	PP_DOWN,
	PP_LEFT,
	PP_RIGHT,
	PP_START,
	PP_BACK,
	PP_L1,
	PP_L3,
	PP_R1,
	PP_R3,
	PP_A,
	PP_B, 
	PP_X,
	PP_Y
};

//==============================================================================
//�C���v�b�g�֐�
//==============================================================================
int gamepad_inport(DWORD index, enum port port);

#endif