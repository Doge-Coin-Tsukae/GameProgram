#pragma once

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT SakuYoko_Initialize(void);
void SakuYoko_Finalize(void);
void SakuYoko_Update(void);
void SakuYoko_Draw(void);
bool CheckHitPlayer_vs_SakuYoko(D3DXVECTOR3 Ppos);