//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#pragma once
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#include <dsound.h>
#include <windows.h>
#include "xaudio2.h"						// �T�E���h�����ŕK�v


//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	//BGM
	SOUND_LABEL_TITLE_BGM,				// 1.�^�C�g��BGM
	SOUND_LABEL_RESULT_BGM,				// 2.���U���gBGM
	//SOUND_LABEL_BATTLE_BGM,			// 3.�퓬��BGM�i�K�v�Ȃ�΁j
	SOUND_LABEL_STAFFROLL_BGM,			// 4.�X�^�b�t���[���i�K�v�Ȃ�΁j
	SOUND_LABEL_WEATHER_RAIN_BGM,		// 5.�V�󉹁A�J
	SOUND_LABEL_WEATHER_THUNDER_BGM,	// 6.�V�󉹁A��
	SOUND_LABEL_WEATHER_1_BGM,	// 6.�V�󉹁A��
	SOUND_LABEL_WEATHER_2_BGM,	// 6.�V�󉹁A��

	//�t�B�[���hSE
	SOUND_LABEL_SE_POINT_SELECT,		// 7.�Z���N�g��
	SOUND_LABEL_SE_SELECT_DECISION,		// 8.�Z���N�g���艹

	SOUND_LABEL_SE_POINT_COUNT,			// 9.�J�E���g�_�E��
	SOUND_LABEL_SE_POINT_COUNT_GO,		// 10.�J�E���g�_�E���I���Q�[���X�^�[�g��

	SOUND_LABEL_SE_GIRL_COUNT_1,		// 11.���̎q�J�E���g�_�E���P
	SOUND_LABEL_SE_GIRL_COUNT_2,		// 12.���̎q�J�E���g�_�E���Q
	SOUND_LABEL_SE_GIRL_COUNT_3,		// 13.���̎q�J�E���g�_�E���R
	SOUND_LABEL_SE_GIRL_COUNT_GO,		// 14.���̎q�J�E���g�_�E��GO
	SOUND_LABEL_SE_GIRL_TIME_UP,		// 14.���̎qTIMEUP


	//�v���C���[SE
	SOUND_LABEL_SE_FOOTSTEPS,			// 15.�v���C���[�̑���
	SOUND_LABEL_SE_CHARGE,				// 16.��������`���[�W�� 
	SOUND_LABEL_SE_SHOT,				// 17.����΂��Ƃ��̉�
	SOUND_LABEL_SE_ARROW_FLYING,		// 18.��󒆂ɂ��鎞�̉�
	SOUND_LABEL_SE_TARGET_HIT,			// 19.��ƓI���ڐG�����Ƃ��̉�
	SOUND_LABEL_SE_TARGET_HIT_CHEERS,	// 20.����
	SOUND_LABEL_SE_PLAYER_HIT,			// 21.��v���C���[�ƐڐG�����Ƃ��̉�


	//���U���gSE
	SOUND_LABEL_SE_TIMEUP,				// 22.�^�C���A�b�v��
	SOUND_LABEL_SE_DRAMROLL,			// 23.���U���g���\���̃h�������[��
	SOUND_LABEL_SE_CHEERS,				// 24.���U���g���\���̊���
	SOUND_LABEL_SE_MATASONDENE,			// 25.�܂�������ł�
	
	SOUND_LABEL_TEST_BGM,		// 26.�e�X�g

	SOUND_LABEL_MAX,

} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
