#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"shori.h"
#include"main.h"

//メイン関数
int main(void) {
		title();		//タイトルの表示
		srand((unsigned int)time(0));		//乱数の種を決める

		//ゲームをループさせる
	while (game) {
		player_sakusei();		//プレイヤーを作成させる
		victory = battle_syori();		//戦闘処理
		win_lose(victory);		//勝ち負け表示
		game = end();		//リプレイ選択
	}
	return 0;
}

