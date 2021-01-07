#include<stdio.h>
#include<string.h>
#include"player.h"
#include"battle.h"
#include"shori.h"
#include"character.h"
#include"serif.h"
#include"conioex.h"

//タイトル表示
void title(void) {

	int i , j;
	const char *title[7] = { "      ■              ■                  ■          ■ ■ ■    ■ ■",
							 "■■■■■■■  ■■■■■■■  ■■■■■■■■■■  ■■■■  ■■■■",
							 "■  ■■■  ■  ■    ■    ■           ■■         ■=■=■     ■",
							 "      ■          ■■■■■          ■■  ■■      ■■■■      ■  ■",
							 "■■■■■■■    ■--■--■       ■■        ■■      ■          ■■",
							 "      ■          ■--■--■     ■■            ■■  ■■■      ■ ■ ■",
							 "    ■■          ■■■■■  ■■                  ■■ ■     ■■    ■",
	};

	int sound;
	sound = opensound("music/UnicronMedley.mp3");
	playsound(sound, 1);
	//カーソル削除
	setcursortype(NOCURSOR);

	for (i = 0; i <= 30; i++) {
		clrscr();

		for (j = 0; j < 8; j += 2) {
			gotoxy(i - j, 10 + j);
			printf("%s\n", title[j]);
		}

		for (j = 1; j < 6; j += 2) {
			gotoxy(60 -j -i, 10 + j);
			printf("%s\n", title[j]);
		}

		
		msleep(20);
	}

	gotoxy(54, 18);
	printf("～ s p a c e  w a r s ～");
	gotoxy(60, 20);
	printf("press enter");
	rewind(stdin);
	getchar();

	closesound(sound);

	for (i = 0; i <= 35; i++) {//宇宙大戦
		clrscr();

		for (j = 0; j < 7; j ++) {
			gotoxy(30 - j , 10 + j +i);
			printf("%s\n", title[j]);
		}
		msleep(30);
	}
	msleep(100);
}

//プレイヤーや船のデータを入出力する
void player_sakusei(void) {
	//変数宣言
	int i = 0;
	int seed[2];	//ASCIIを乱数に変換する
	bool hantei = true;		//表示するときにプレイヤーと相手を識別する
	int sound;
	sound = opensound("music/MoonBase2.mp3");

	//画面クリア
	clrscr();
	playsound(sound, 1);
	//プレーヤーの名前を入力
	gotoxy(1, 35);
	player_soto();

	textcolor(14);
	input_player_voice();
	gotoxy(3 +  1, 37);
	serif_display();
	input_player_voice_2();
	gotoxy(3 +  1, 38);
	serif_display();
	textcolor(15);

	gotoxy(40, 10);
	player_name(hantei);		//提督の名を入力:
	gotoxy(39,11);
	frame();
	gotoxy(41, 12);
	input(player[0].NAME);		//入力処理
	clrscr();

	gotoxy(1, 35);
	player_soto();

	textcolor(14);
	input_ship_voice();
	gotoxy(3 + 1, 37);
	serif_display();
	input_ship_voice_2();
	gotoxy(3 + 1, 38);
	serif_display();
	textcolor(15);

	gotoxy(34, 10);
	ship_name(hantei);			//船の名を入力
	gotoxy(39, 11);
	frame();
	gotoxy(41, 12);
	input(ship[0].NAME);		//入力処理

	//ASCIIの乱数を得る(提督の方)
	seed[0] = player_atai(player[0].NAME);

	//提督の能力
	player[0].EFFICIENCY = player_efficiency(seed[0]);
	//提督のグラフィック
	player[0].GRA = player_graphic(seed[0]);

	//ASCIIの乱数を得る(船の方)
	seed[0] = ship_atai(ship[0].NAME);

	//船のデータ
	ship[0].HP = ship_hp(seed[0]);		//船の耐久値
	seed[0] = seed[0] /= 13;			//ASCIIで得た値を13で割る(他のパーツと被るのを防ぐため)
	ship[0].HEAD = ship_parts(seed[0]);		//船の先頭部分
	seed[0] = seed[0] /= 17;			//ASCIIで得た値を17で割る(他のパーツと被るのを防ぐため)
	ship[0].BOTOM = ship_parts(seed[0]);		//船の胴体部分
	seed[0] = seed[0] /= 19;			//ASCIIで得た値を19を割る(他のパーツと被るのを防ぐため)
	ship[0].LEG = ship_parts(seed[0]);			//船の後尾部分
	ship[0].WEAPON_T = ship_weapon_t(ship[0].HEAD, ship[0].WEAPON_T);		//超々大型の武器を習得
	ship[0].WEAPON_XL = ship_weapon_xl(ship[0].HEAD, ship[0].WEAPON_XL);	//超大型の武器を習得
	ship[0].WEAPON_L = ship_weapon_l(ship[0].HEAD, ship[0].BOTOM, ship[0].LEG, ship[0].WEAPON_L);		//大型の武器を習得
	ship[0].WEAPON_M = ship_weapon_m(ship[0].BOTOM, ship[0].LEG, ship[0].WEAPON_M);		//中型の武器を習得
	ship[0].WEAPON_S = ship_weapon_s(ship[0].BOTOM, ship[0].LEG, ship[0].WEAPON_S);		//小型の武器を習得
	moji1(ship[0].WEA_MOJI1, ship[0].HEAD);		//1番目の武器の名前を習得
	moji2(ship[0].WEA_MOJI2, ship[0].HEAD, ship[0].BOTOM);		//2番目の武器の名前を習得
	moji3(ship[0].WEA_MOJI3, ship[0].HEAD, ship[0].BOTOM, ship[0].LEG);		//3番目の武器の名前を習得

	//得たデータを出力
	clrscr();
	gotoxy(1, 35);
	player_soto();

	textcolor(14);
	input_result_voice();
	gotoxy(3 + 1, 37);
	serif_display();
	textcolor(15);

	gotoxy(1, 3);
	plyaer_display(player[0].NAME, player[0].EFFICIENCY, player[0].GRA);		//提督のデータを表示
	gotoxy(1, 7);
	ship_display(ship[0].NAME, ship[0].HP, ship[0].HEAD, ship[0].BOTOM, ship[0].LEG, ship[0].WEAPON_T, ship[0].WEAPON_XL, ship[0].WEAPON_L, ship[0].WEAPON_M, ship[0].WEAPON_S);	//船のデータを出力
	getchar();

	//判定を相手用にする
	hantei = false;
	clrscr();

	//相手のデータを作成する
	gotoxy(1, 35);
	player_soto();
	textcolor(14);
	input_eplayer_voice();
	gotoxy(3 + 1, 37);
	serif_display();
	input_eplayer_voice_2();
	gotoxy(3 + 1, 38);
	serif_display();
	textcolor(15);

	gotoxy(37, 10);
	player_name(hantei);		//提督の名を入力:
	gotoxy(39, 11);
	frame();
	gotoxy(41, 12);
	input(player[1].NAME);		//入力処理
	clrscr();

	gotoxy(1, 35);
	player_soto();
	textcolor(14);
	input_eship_voice();
	gotoxy(3 + 1, 37);
	serif_display();
	input_eship_voice_2();
	gotoxy(3 + 1, 38);
	serif_display();
	textcolor(15);

	gotoxy(30, 10);
	ship_name(hantei);			//船の名を入力
	gotoxy(39, 11);
	frame();
	gotoxy(41, 12);
	input(ship[1].NAME);		//入力処理
	clrscr();

	//SCIIの乱数を得る(提督の方)
	seed[1] = player_atai(player[1].NAME);

	//提督の能力
	player[1].EFFICIENCY = player_efficiency(seed[1]);
	//提督のグラフィック
	player[1].GRA = player_graphic(seed[1]);

	//ASCIIの乱数を得る(船の方)
	seed[1] = ship_atai(ship[1].NAME);

	//船のデータ
	ship[1].HP = ship_hp(seed[1]);		//船の耐久値
	seed[1] = seed[1] /= 13;				//ASCIIで得た値を13で割る(他のパーツと被るのを防ぐため)
	ship[1].HEAD = ship_parts(seed[1]);		//船の先頭部分
	seed[1] = seed[1] /= 17;			//ASCIIで得た値を17で割る(他のパーツと被るのを防ぐため)
	ship[1].BOTOM = ship_parts(seed[1]);	//船の胴体部分
	seed[1] = seed[1] /= 19;			//ASCIIで得た値を19で割る(他のパーツと被るのを防ぐため)
	ship[1].LEG = ship_parts(seed[1]);		//船の後尾部分
	ship[1].WEAPON_T = ship_weapon_t(ship[1].HEAD, ship[1].WEAPON_T);		//超々大型の武器を習得
	ship[1].WEAPON_XL = ship_weapon_xl(ship[1].HEAD, ship[1].WEAPON_XL);	//超大型の武器を習得
	ship[1].WEAPON_L = ship_weapon_l(ship[1].HEAD, ship[1].BOTOM, ship[1].LEG, ship[1].WEAPON_L);		//大型の武器を習得
	ship[1].WEAPON_M = ship_weapon_m(ship[1].BOTOM, ship[1].LEG, ship[1].WEAPON_M);		//中型の武器を習得
	ship[1].WEAPON_S = ship_weapon_s(ship[1].BOTOM, ship[1].LEG, ship[1].WEAPON_S);		//小型の武器を習得
	moji1(ship[1].WEA_MOJI1, ship[1].HEAD);			//1番目の武器の名前を習得
	moji2(ship[1].WEA_MOJI2, ship[1].HEAD, ship[1].BOTOM);		//2番目の武器の名前を習得
	moji3(ship[1].WEA_MOJI3, ship[1].HEAD, ship[1].BOTOM, ship[1].LEG);		//3番目の武器の名前を習得

	//得たデータを出力
	clrscr();

	gotoxy(1, 35);
	player_soto();
	textcolor(14);
	input_eresult_voice();
	gotoxy(3 + 1, 37);
	serif_display();
	textcolor(15);

	gotoxy(1, 15);
	plyaer_display(player[1].NAME, player[1].EFFICIENCY, player[1].GRA);		//提督のデータを表示
	gotoxy(1, 19);
	ship_display(ship[1].NAME, ship[1].HP, ship[1].HEAD, ship[1].BOTOM, ship[1].LEG, ship[1].WEAPON_T, ship[1].WEAPON_XL, ship[1].WEAPON_L, ship[1].WEAPON_M, ship[1].WEAPON_S);		//船のデータを出力
	getchar();
	closesound(sound);
}

//戦闘の処理
int battle_syori(void) {
	//変数宣言
	int sentaku = 0;	//プレイヤー選択の初期値
	int attacknum = 0;
	int damage = 0;
	int hit = 0;
	int defcol = 0;
	int sound;
	bool pdef = false;
	bool pvc = false;

	sound = opensound("music/AutobotDecepticonBattle.mp3");
	playsound(sound, 1);

	//どちらかが死ぬまで繰り返す
	while (1) {
		haikei_matome();
		//自分のターン
		while (1) {
			//プレーヤーに選択肢を選ばせる
			sentaku = battle_input();
			//選択が1だった(攻撃を選んだ)場合
			if (sentaku == 1) {
				//攻撃選択画面に入る
				attacknum = battle_attack(ship[0].WEAPON_T, ship[0].WEAPON_XL, ship[0].WEAPON_L, ship[0].WEAPON_M, ship[0].WEAPON_S, ship[0].WEA_MOJI1, ship[0].WEA_MOJI2, ship[0].WEA_MOJI3, ship[1].HP);
				if (attacknum != 7) {
					if (attacknum == 1) {
						hit = battlepart(ship[0].WEAPON_T);
					}
					if (attacknum == 2) {
						hit = battlepart(ship[0].WEAPON_XL);
					}
					if (attacknum == 3) {
						hit = battlepart(ship[0].WEAPON_L);
					}
					if (attacknum == 4) {
						hit = battlepart(ship[0].WEAPON_M);
					}
					if (attacknum == 5) {
						hit = battlepart(ship[0].WEAPON_S);
					}
					haikei_matome();
					damage = battle_attack_shori(pdef, hit, attacknum, player[0].EFFICIENCY);
					animation(attacknum,hit);
					battle_log(damage,attacknum,hit);
					rewind(stdin);
					getchar();

					ship[1].HP -= damage;
					//ターン終了時にクールダウンを1減らす
					cooldowncnt();
					defcol--;
					hit = 0;
					break;
				}
				haikei_matome();

			}

			else if (sentaku == 2) {
				if (defcol <= 0) {
					haikei_matome();
					defense_hyoji();
					gotoxy(4, 40);
					serif_display();
					rewind(stdin);
					getchar();
					pdef = true;
					defcol = 3;
					break;
				}
				else {
					haikei_matome();
					defence_error();
					gotoxy(4, 40);
					serif_display();
					printf("(%dターン)", defcol);
					rewind(stdin);
					getchar();
				}
			}
			
			else if (sentaku == 3) {
				cooldowncnt();
				defcol--;
				break;
			}

			else {
			}

		}

		//相手が死んだら勝ちフラグを入れてループを抜ける
		if (ship[1].HP <= 0) {
			pvc = true;
			break;
		}

		//相手のターン
		haikei_matome();
		//攻撃選択処理
		ship[0].HP = ai_battle(pdef,ship[0].HP,player[1].EFFICIENCY, ship[1].WEA_MOJI1, ship[1].WEA_MOJI2, ship[1].WEA_MOJI3, ship[1].WEAPON_L, ship[1].WEAPON_M, ship[1].WEAPON_S);
		pdef = false;
		hit = 0;

		//自分が死んだか判断する
		if (ship[0].HP <= 0) {
			break;
		}
	}

	closesound(sound);

	return pvc;
}

//勝敗画面を表示する
void win_lose(bool victory) {
	int i;
	int scream;

	scream = opensound("se/scream.mp3");

	clrscr();
	player_soto();

	//勝ちフラグは入ったかどうか
	if (victory) {
		fune();
		textcolor(14);
		won();
		gotoxy(3 + 1, 37);
		serif_display();
		textcolor(15);
		getchar();
	}
	else {
		playsound(scream, 0);
		textcolor(14);
		failed();
		gotoxy(3 + 1, 37);
		serif_display();
		textcolor(15);

		for (i = 0; i < 8; i++) {
			fune_move(i);
		}
		msleep(1500);
	}

	closesound(scream);
}

//リプレイするかどうか
int end(void) {
	//変数宣言
	bool refrain = true;	//繰り返すか終わるかを知る変数
	int key = 0;		//現在さしているキー
	int getkey = 0;		//キーボード入力の習得

	//どちらか選ぶまでループ
	clrscr();
	gotoxy(1, 35);
	player_soto();
	textcolor(14);
	retry();
	gotoxy(3 + 1, 37);
	serif_display();
	textcolor(15);
	while (1) {

		gotoxy(40, 11);
		clreol();
		//キーが0の場合
		if (key == 0) {
			printf("二ア はい いいえ");
		}
		//キーが1の場合
		else {
			printf("はい 二ア いいえ");
		}

		//キーボード入力待ち
		getkey = getch();

		//左キーを入力した場合
		if (getkey == 0x4B && key > 0) {
			key--;
		}
		//右キーを入力した場合
		if (getkey == 0x4D && key < 1) {
			key++;
		}
		//エンターキーを入力した場合
		if (getkey == 0x0d) {
			if (key == 0) {		//キーが"はい"を選んでいた場合
				connldownreflesh();
				clrscr();
				break;
			}
			else {		//キーが"いいえ"を選んでいた場合
				refrain = false;
				break;
			}
		}

	}

	return refrain;
}

//戦闘画面をまとめる
void haikei_matome(void) {
	clrscr();
	haikei(1, 1);
	haikei(1, 34);
	fune();
	enemy_fune();
	battle_display(ship[1].NAME, player[1].NAME, ship[1].HP, 4, 2, 15);		//画面表示
	battle_display(ship[0].NAME, player[0].NAME, ship[0].HP, 4, 35, 14);		//画面表示
	character_graf(player[0].GRA,  51,  35);
	character_graf(player[1].GRA,  51,  2);
}