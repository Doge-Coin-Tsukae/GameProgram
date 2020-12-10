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
	SOUND_LABEL_TUTORIAL_BGM,			// 2.���U���gBGM
	SOUND_LABEL_BATTLE_BGM,				// 3.�퓬��BGM�i�K�v�Ȃ�΁j

	//�t�B�[���hSE
	SOUND_LABEL_SE_POINT_SELECT,		// 7.�Z���N�g��
	SOUND_LABEL_SE_SELECT_DECISION,		// 8.�Z���N�g���艹

	SOUND_LABEL_SE_POINT_COUNT,			// 9.�J�E���g�_�E��
	SOUND_LABEL_SE_POINT_COUNT_GO,		// 10.�J�E���g�_�E���I���Q�[���X�^�[�g��

	//�v���C���[SE
	SOUND_LABEL_SE_PUNCH_MISS,		// 15.�v���C���[�̑���
	SOUND_LABEL_SE_PUNCH_HIT,		// 16.��������`���[�W�� 
	SOUND_LABEL_SE_PUNCH_FLY,		// 17.����΂��Ƃ��̉�
	SOUND_LABEL_SE_KICK_MISS,		// 18.��󒆂ɂ��鎞�̉�
	SOUND_LABEL_SE_KICK_HIT,		// 19.��ƓI���ڐG�����Ƃ��̉�
	SOUND_LABEL_SE_KICK_FLY,		// 20.��v���C���[�ƐڐG�����Ƃ��̉�
	SOUND_LABEL_SE_DEATH,			//���S����SE


	//���U���gSE
	SOUND_LABEL_SE_TIMEUP,				// 21.�^�C���A�b�v��
	SOUND_LABEL_SE_DRAMROLL,			// 22.���U���g���\���̃h�������[��
	SOUND_LABEL_SE_CHEERS,				// 23.���U���g���\���̊���
	SOUND_LABEL_SE_MATASONDENE,			// 24.�܂�������ł�
	
	SOUND_LABEL_TEST_BGM,		// 25.�e�X�g

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
