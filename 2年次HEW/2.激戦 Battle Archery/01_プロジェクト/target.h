#pragma once

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT Target_Initialize(void);
void Target_Finalize(void);
void Target_Update(void);
void Target_Draw(void);
int GetColor(int index);