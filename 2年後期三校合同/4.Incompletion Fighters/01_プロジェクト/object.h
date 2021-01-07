#pragma once

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Object_Initialize(void);
void Object_Finalize(void);
void Object_Update(void);
void Object_Draw(void);
bool CheckHitPlayer(D3DXVECTOR3 Ppos);