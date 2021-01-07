#pragma once

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Piller_Initialize(void);
void Piller_Finalize(void);
void Piller_Update(void);
void Piller_Draw(void);
bool CheckHitPlayer_vs_PILLER(D3DXVECTOR3);
