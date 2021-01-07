#pragma once

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Saku_Initialize(void);
void Saku_Finalize(void);
void Saku_Update(void);
void Saku_Draw(void);
bool CheckHitPlayer_vs_Saku(D3DXVECTOR3 Ppos);
