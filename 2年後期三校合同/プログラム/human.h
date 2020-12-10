
#pragma once

#include "main.h"

//*****************************************************************************
//enum
//*****************************************************************************
//プレイヤーのAIパターン
enum PATARN
{
	WAITTIME,		//待機時間
	SEKKINMOVE,		//前進
	BACKMOVE,		//後進
	PUNCH,			//拳攻撃
	KICK,			//足攻撃
	DAMAGED,		//攻撃を受けた
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Human_Initialize(void);
void Human_Finalize(void);
void Human_Update(void);
int GetAI(void);
void SetAImode(int SetAI);