#pragma once

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Target_Tutorial_Initialize(void);
void Target_Tutorial_Finalize(void);
void Target_Tutorial_Update(void);
void Target_Tutorial_Draw(void);
int GetColor_Tutorial(int index);