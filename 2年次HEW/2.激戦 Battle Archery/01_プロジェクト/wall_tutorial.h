#pragma once

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Wall_Tutorial_Initialize(void);
void Wall_Tutorial_Finalize(void);
void Wall_Tutorial_Update(void);
void Wall_Tutorial_Draw(void);
bool CheckHitPlayer_vs_WallTutorial(D3DXVECTOR3 Ppos);
