
#pragma once

#include "main.h"

//�}�N���錾
#define FIELD_HIGHT		(30.0f)						// �n�ʂ̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT Field_Initialize(void);
void Field_Finalize(void);
void Field_Update(void);
void Field_Draw(void);
