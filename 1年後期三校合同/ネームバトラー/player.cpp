#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"player.h"

#define MOJIRETU (15)

void player_soto(void) {
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	printf("□                                              □   ■■■■■■   □\n");
	printf("□                                              □   ◎■■■■■   □\n");
	printf("□                                              □ ■■■■■■■   □\n");
	printf("□                                              □   □■□■□□   □\n");
	printf("□                                              □   □□□□□□   □\n");
	printf("□                                              □     ■□■■■   □\n");
	printf("□                                              □ ■■〇■■■■■ □\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

//プレイヤーに名前を入力させる
void player_name(bool hantei) {
	//プレイヤーか相手かを判断して文章を入れる
	if (hantei) {
		printf("艦長の");
	}
	else {
		printf("相手の艦長の");
	}

	printf("名前を入力してください\n");

}

//プレイヤーに船の名前を入力させる
void ship_name(bool hantei) {
	//プレイヤーか相手かを判断して文章を入れる
	if (hantei) {
		printf("艦長");
	}
	else {
		printf("相手の艦長");
	}

	printf("が乗船する船の名前を入力してください\n");
}

//入力処理
int input(char name[32]) {
	scanf("%s", name);		//入力処理
	rewind(stdin);

	return name[32];
}

void frame(void) {
	printf("■■■■■■■■■■■■■■\n");
	printf("                                      ■                        ■\n");
	printf("                                      ■■■■■■■■■■■■■■\n");
}

//名前からASCIIで乱数の種を決める
int player_atai(char name[32]) {
	//変数宣言
	int kazu, i;		//数字を数える(kazu)
	int ascii = 0;	//名前をASCIIにして種にする

	//名前の数を数える
	kazu = strlen(name);
	//moji配列の内容をASCIIへ、変換する
	for (i = 0; i < kazu; i++) {
		ascii += name[i];
	}

	//乱数生成
	ascii *= 3597;

	return ascii;
}

//プレイヤーの能力判断
int player_efficiency(int ascii) {
	//変数宣言
	int EFFICIENCY;

	EFFICIENCY = (ascii % 500 + 1);		//効率 = 1～500

	//ASCIIが0以下になってしまったときにプラスにする処理
	if (EFFICIENCY <= 0) {
		EFFICIENCY -= (EFFICIENCY * 2);
	}

	return EFFICIENCY;
}

//プレイヤーの外見を決める
int player_graphic(int ascii) {
	//変数宣言
	int GRA;

	GRA = (ascii % 5);	//0～10で顔のパターンを作る

	//ASCIIが0未満になったときにプラスにする処理
	if (GRA < 0) {
		GRA -= (GRA * 2);
	}

	return GRA;
}

//提督の作成が終わった時に結果を表示する
void plyaer_display(char name[32], int efficiency, int gra) {
	printf("%s 艦長\n", name);
	printf("プレイヤーの能力:%d\n", efficiency);
	printf("外見:");
	if (gra == 0) {
		printf("機械生命体\n");
	}
	else if (gra == 1) {
		printf("哺乳類\n");
	}
	else if (gra == 2) {
		printf("霊体\n");
	}
	else if (gra == 3) {
		printf("鳥類\n");
	}
	else if (gra == 4) {
		printf("虫類\n");
	}
}

//船の名前からASCIIで乱数の種を作る
int ship_atai(char name[32]) {
	//変数宣言
	int kazu, j;
	int ascii = 0;

	//名前の数を数える
	kazu = strlen(name);
	//moji配列の内容をASCIIへ、変換する
	for (j = 0; j < kazu; j++) {
		ascii += name[j];
	}

	//乱数生成
	ascii *= 447;

	return ascii;
}

//船の体力の設定
int ship_hp(int ascii) {
	//変数宣言
	int hp;

	hp = (ascii % 10000 + 6000);		//HP = 6000～16000

	//HPの数値が0以下になった場合
	if (hp <= 0) {
		hp -= (hp * 2);
	}

	return hp;
}

//船の頭、胴体、後尾部分の設定
int ship_parts(int ascii) {
	//変数宣言
	int parts;

	parts = ascii % 3;			//0～2の値を入れる

	//変数が0以下になった場合
	if (parts <= 0) {
		parts  -= (parts * 2);
	}

	return parts;
}

//超々大型兵器の設定
int ship_weapon_t(int head, int t) {
	//頭が0の値が入った場合
	if (head == 0) {
		t += 1;
	}
	return t;
}

//超大型兵器の設定
int ship_weapon_xl(int head, int xl) {
	//頭が1の値が入った場合
	if (head == 1) {
		xl += 2;
	}
	return xl;
}

//大型兵器の設定
int ship_weapon_l(int head, int botom, int leg, int l) {
	//頭が2の値が入った場合
	if (head == 2) {
		l += 5;
	}

	//胴体が0の値が入った場合
	if (botom == 0) {
		l += 10;
	}

	//後尾が0の値が入った場合
	if (leg == 0) {
		l += 3;
	}

	return l;
}

//中型兵器の設定
int ship_weapon_m(int botom, int leg, int m) {
	//胴体が1の値が入った場合
	if (botom == 1) {
		m+= 12;
	}

	//後尾が0の値が入った場合
	if (leg == 1) {
		m += 4;
	}

	return m;
}

//小型兵器の設定
int ship_weapon_s(int botom, int leg, int s) {
	//胴体が2の値が入った場合
	if (botom == 2) {
		s += 18;
	}

	//後尾が0の値が入った場合
	if (leg == 2) {
		s += 8;
	}

	return s;
}

//1つ目の兵器の名前を代入
int moji1(char moji[MOJIRETU], int head) {
	if (head == 0) {
		strcpy(moji, "タイタンランス");
	}
	else if (head == 1) {
		strcpy(moji, "事象崩壊砲");
	}
	else {
		strcpy(moji, "大型実弾砲");
	}

	return moji[MOJIRETU];
}

//2つ目の兵器の名前を代入
int moji2(char moji[MOJIRETU], int head, int botom) {
	if (botom == 0 && head != 2) {
		strcpy(moji, "大型実弾砲");
	}
	else if (botom == 1) {
		strcpy(moji,"マスドライバー");
	}
	else if (botom == 2) {
		strcpy(moji,"オートキャノン");
	}
	else {
		strcpy(moji, "");
	}

	return moji[MOJIRETU];
}

//3つ目の兵器の名前を代入
int moji3(char moji[MOJIRETU], int head, int botom, int leg) {
	if (leg == 0 && head != 2 && botom != 0) {
		strcpy(moji, "大型実弾砲");
	}
	else if (leg == 1 && botom != 1) {
		strcpy(moji, "マスドライバー");
	}
	else if (leg == 2 && botom != 2) {
		strcpy(moji, "オートキャノン");
	}
	else {
		strcpy(moji, "");
	}

	return moji[MOJIRETU];
}

//船の作成が終わった時に結果を表示する
void ship_display(char name[32], int HP, int HEAD, int BOTOM, int LEG, int WEAPON_T, int WEAPON_XL, int WEAPON_L, int WEAPON_M, int WEAPON_S) {
	printf("%s級\n", name);
	printf("船の耐久力:%d\n", HP);
	printf("頭:%d\n", HEAD);
	printf("腹部:%d\n", BOTOM);
	printf("脚部:%d\n", LEG);
	printf("武器の数:T:%d XL:%d L:%d M:%d S:%d\n", WEAPON_T, WEAPON_XL, WEAPON_L, WEAPON_M, WEAPON_S);
}