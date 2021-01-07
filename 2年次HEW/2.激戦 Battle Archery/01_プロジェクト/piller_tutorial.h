#pragma once

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Piller_Tutorial_Initialize(void);
void Piller_Tutorial_Finalize(void);
void Piller_Tutorial_Update(void);
void Piller_Tutorial_Draw(void);
bool CheckHitPlayer_vs_PillerTutorial(D3DXVECTOR3);
