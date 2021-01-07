#pragma once
#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Point_Initialize(void);
void Point_Finalize(void);
void Point_Update(void);
void Point_Draw(void);
D3DXVECTOR3 Get_Pos(int index);
void ChangePointVer(int num, int index);
void ChangePoint(int num, int index, float cameraspeed);
void ChangePointAngle(int num, int index);