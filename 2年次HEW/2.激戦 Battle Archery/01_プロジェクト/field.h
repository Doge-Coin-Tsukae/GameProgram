
#pragma once

#include "main.h"

//マクロ宣言
#define FIELD_HIGHT		(30.0f)						// 地面の高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Field_Initialize(void);
void Field_Finalize(void);
void Field_Update(void);
void Field_Draw(void);
