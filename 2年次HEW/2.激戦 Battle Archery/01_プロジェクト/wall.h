#pragma once

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT Wall_Initialize(void);
void Wall_Finalize(void);
void Wall_Update(void);
void Wall_Draw(void);
bool CheckHitPlayer_vs_Wall(D3DXVECTOR3 Ppos);
