#pragma once

#include "main.h"

//********************************************************************************
//構造体宣言
//********************************************************************************



//********************************************************************************
//プロトタイプ宣言
//********************************************************************************
HRESULT Coli_Initialize(void);
bool CircleAndPoint(D3DXVECTOR3 pos, D3DXVECTOR3 epos, float radius);
bool PointtoSquare(D3DXVECTOR3 Point, D3DXVECTOR3 Square, D3DXVECTOR3 SquareScl, bool Used, float side);
bool PointtoRectangley(D3DXVECTOR3 Point, D3DXVECTOR3 Square, D3DXVECTOR3 SquareScl, bool Used, float side, float longside);
void Coli_Draw(void);
void SetPolygon(D3DXVECTOR3 Pos);