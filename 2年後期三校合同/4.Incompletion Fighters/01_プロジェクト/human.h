
#pragma once

#include "main.h"

//*****************************************************************************
//enum
//*****************************************************************************
//�v���C���[��AI�p�^�[��
enum PATARN
{
	WAITTIME,		//�ҋ@����
	SEKKINMOVE,		//�O�i
	BACKMOVE,		//��i
	PUNCH,			//���U��
	KICK,			//���U��
	DAMAGED,		//�U�����󂯂�
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT Human_Initialize(void);
void Human_Finalize(void);
void Human_Update(void);
int GetAI(void);
void SetAImode(int SetAI);