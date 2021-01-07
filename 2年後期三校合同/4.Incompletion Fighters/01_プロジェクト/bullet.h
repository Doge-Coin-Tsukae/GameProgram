#pragma once

#include "main.h"

#define MAX_BULLET			20

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Bullet_Initialize(void);
void Bullet_Finalize(void);
void Bullet_Update(void);
void Bullet_Draw(void);
void SetBullet(D3DXVECTOR3 pos, int type);
bool GetBulletUse(int index);
D3DXVECTOR3 GetBulletPos(int index);
void DisabledBullet(int index);