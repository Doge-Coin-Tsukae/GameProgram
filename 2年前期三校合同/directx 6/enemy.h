#pragma once


#include "collision.h"


#define ENEMY_COUNT 10

void Enemy_Initialize(void);
void Enemy_Finalize(void);
void Enemy_Update(void);
void Enemy_Draw(void);
void Enemy_Destroy(int index, bool kill);
bool Enemy_IsEnable(int index);
const CIRCLE* Enemy_GetCollision(int index);
void SetEnemy(int px, int py, int select, int round, bool mov, int col);
void EnemyDamage(int index, int dama);
void Enemy_StateBoss(int index);