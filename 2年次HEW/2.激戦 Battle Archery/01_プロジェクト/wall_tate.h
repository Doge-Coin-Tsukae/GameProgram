#pragma once

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT WallTate_Initialize(void);
void WallTate_Finalize(void);
void WallTate_Update(void);
void WallTate_Draw(void);
bool CheckHitPlayer_vs_WallTate(D3DXVECTOR3 Ppos);