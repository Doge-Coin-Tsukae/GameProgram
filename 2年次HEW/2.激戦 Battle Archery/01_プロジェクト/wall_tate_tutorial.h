#pragma once

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT WallTate_Tutorial_Initialize(void);
void WallTate_Tutorial_Finalize(void);
void WallTate_Tutorial_Update(void);
void WallTate_Tutorial_Draw(void);
bool CheckHitPlayer_vs_WallTateTutorial(D3DXVECTOR3 Ppos);