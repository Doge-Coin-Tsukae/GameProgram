#pragma once

void Score_Init();
//x���ʒu�@y�c�ʒu�@score�\������l  fig����  bZero�[���̎��ɕ\�����邩�t���O
void Score_Draw(float x, float y, int score, int fig, bool bZero, int player,int size);
void Gauge_Draw(float power, int player);
void Timelimit_Draw(float x, float y, int time, int fig, bool bZero);
void addscore(int index, int num);
int getscore(int index);