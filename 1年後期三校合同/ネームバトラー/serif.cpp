#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <string.h>
#include"serif.h"

//変数宣言
char serif[40];

//変数に入れたセリフを表示
void serif_display(void) {
	printf("%s", serif);
}

//プレイヤー作成画面のセリフ
void input_player_voice(void) {
	strcpy(serif,"艦長就任おめでとうございます。");
}

//プレイヤー作成画面のセリフ
void input_player_voice_2(void) {
	strcpy(serif, "艦長の登録するので名前を教えてください。");
}

//船作成画面のセリフ
void input_ship_voice(void) {
	strcpy(serif, "建造された船の命名権が与えられました。");
}

//船作成画面のセリフ
void input_ship_voice_2(void) {
	strcpy(serif, "乗船する船の名前を決めてください。");
}

//生成した後のセリフ
void input_result_voice(void) {
	strcpy(serif, "貴方のデータと船のデータを表示します。");
}

//敵プレイヤー作成画面のセリフ
void input_eplayer_voice(void) {
	strcpy(serif, "次に今回、敵として登場させる");
}

//敵プレイヤー作成画面のセリフ
void input_eplayer_voice_2(void) {
	strcpy(serif, "艦長の名前を教えてください。");
}

//敵船作成画面のセリフ
void input_eship_voice(void) {
	strcpy(serif,"敵として登場させる");
}

//敵船作成画面のセリフ
void input_eship_voice_2(void) {
	strcpy(serif, "船の名前を入力してください。");
}

//敵生成後のセリフ
void input_eresult_voice(void) {
	strcpy(serif, "敵の艦長のデータと船のデータを表示します。");
}

//防御ができないときのセリフ
void defence_error(void) {
	strcpy(serif, "まだ使えません。");
}

//防御するときのセリフ
void defense_hyoji(void) {
	strcpy(serif, "防御システムを展開します。");
}

//勝利したときのセリフ
void won(void) {
	strcpy(serif, "勝ちです");
}

//敗北したときのセリフ
void failed(void) {
	strcpy(serif, "負けです");
}

//再戦選択のセリフ
void retry(void) {
	strcpy(serif, "再戦しますか？");
}