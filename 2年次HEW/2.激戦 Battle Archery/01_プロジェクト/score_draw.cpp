//********************************************************
//	画面に表示するもの関係のプログラム
//********************************************************

#include "number.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

//グローバル変数
int g_score[2];

void Score_Init()
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_score[i] = 0;
	}
}

//スコアを描画
void Score_Draw(float x, float y, int score, int fig, bool bZero,int player,int size)
{
	//身代わり
	int scores;

	scores = g_score[score];

	// カンスト用の最大数値を作る
	int count_stop_score = 1;
	for (int i = 0; i < fig; i++) {
		count_stop_score *= 10;
	}

	//最大値の補正処理
	if (scores >= count_stop_score) {
		scores = count_stop_score - 1;
	}

	//	if( bZero ) {

	for (int i = 0; i < fig; i++) {

		int n = scores % 10;
		scores /= 10;

		Number_Draw(x + NUMBER_WIDTH * (fig - (i + 1)), y, n, player, size);
	}
}

//弓を引いたときの力表示 (引いたときの強さ,プレイヤー)
void Gauge_Draw(float power ,int player)
{
	float DrawPower;
	DrawPower = power / 100;

	Sprite_Draw(TEXTURE_INDEX_ARROWPOWERBOX_BAR, SCREEN_WIDTH / 5 + SCREEN_WIDTH / 2 * player, 800, 1, 1, 350, 30);
	Sprite_Draw(TEXTURE_INDEX_ARROWPOWER_BAR, SCREEN_WIDTH / 5 + 4 + SCREEN_WIDTH / 2 * player, 800 + 2 , 1, 1, 342 * DrawPower, 26);
}

//時間を描画
void Timelimit_Draw(float x, float y, int time, int fig, bool bZero)
{
	// カンスト用の最大数値を作る
	int count_stop_score = 1;
	for (int i = 0; i < fig; i++) {
		count_stop_score *= 10;
	}

	//最大値の補正処理
	if (time >= count_stop_score) {
		time = count_stop_score - 1;
	}

	//	if( bZero ) {

	for (int i = 0; i < fig; i++) {

		int n = time % 10;
		time /= 10;

		Number_Draw(x + NUMBER_WIDTH * (fig - (i + 1)), y, n,2,0);
	}
}

//スコアを加える(プレイヤー番号,加える得点)
void addscore(int index, int num)
{
	g_score[index] += num;
}

//スコアを手に入れる(プレイヤー番号)
int getscore(int index)
{
	return g_score[index];
}