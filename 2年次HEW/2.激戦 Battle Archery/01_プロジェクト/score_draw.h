#pragma once

void Score_Init();
//x横位置　y縦位置　score表示する値  fig桁数  bZeroゼロの時に表示するかフラグ
void Score_Draw(float x, float y, int score, int fig, bool bZero, int player,int size);
void Gauge_Draw(float power, int player);
void Timelimit_Draw(float x, float y, int time, int fig, bool bZero);
void addscore(int index, int num);
int getscore(int index);