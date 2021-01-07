#pragma once

#include "main.h"

#define BULLET_NUM		(10)							//弾の総数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Bullet_Initialize(void);
void Bullet_Finalize(void);
void Bullet_Update(void);
void Bullet_Draw(void);
void StopBullet(int index);
void DeleteBullet(int index);
void SetBullet(D3DXVECTOR3 index, float pow, int Player);
int GetPlyNum(int index);
float GetSpeed(int index);
bool GetUse(int index);
bool GetMove(int index);
D3DXVECTOR3 GetOne(int index);
D3DXVECTOR3 GetBulletPos(int index);
D3DXVECTOR3 GetBulletScl(int index);