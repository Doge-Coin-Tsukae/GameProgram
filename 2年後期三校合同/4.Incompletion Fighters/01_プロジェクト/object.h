#pragma once

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT Object_Initialize(void);
void Object_Finalize(void);
void Object_Update(void);
void Object_Draw(void);
bool CheckHitPlayer(D3DXVECTOR3 Ppos);