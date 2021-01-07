#pragma once

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Wall_Initialize(void);
void Wall_Finalize(void);
void Wall_Update(void);
void Wall_Draw(void);
bool CheckHitPlayer_vs_Wall(D3DXVECTOR3 Ppos);
