//=============================================================================
//
// ビルボード処理 [billboard.h]
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Billboard_Initialize(void);
void Billboard_Finalize(void);
void Billboard_Update(void);
void Billboard_Draw(void);
void SetBill(D3DXVECTOR3 pos, int type);
