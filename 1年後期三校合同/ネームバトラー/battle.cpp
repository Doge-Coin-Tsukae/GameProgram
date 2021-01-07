#include<stdio.h>
#include<string.h>
#include"battle.h"

#define CONIOEX
#include"conioex.h"

#define MOJIRETU (15)

//変数宣言
int key = 0;
int getkey;
int cooldown[3] = { 0,0,0 };
int ai_cooldown[3] = { 0,0,0 };

//戦闘画面の枠
void haikei(int x,int y) {
	gotoxy(x, y);
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	printf("□                                              □                  □\n");
	printf("□                                              □                  □\n");
	printf("□                                              □                  □\n");
	printf("□                                              □                  □\n");
	printf("□                                              □                  □\n");
	printf("□                                              □                  □\n");
	printf("□                                              □                  □\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

//キャラクターのグラフィック
void character_graf(int grafnum,int x,int y) {
	if (grafnum == 0) {			//ロボット
		gotoxy(x, y);
		printf("     ________     ");
		gotoxy(x, y + 1);
		printf("||  | ______ |  ||");
		gotoxy(x, y + 2);
		printf("||  | |◎●| |  ||");
		gotoxy(x, y + 3);
		printf("■■| |  ○| |■■");
		gotoxy(x, y + 4);
		printf("■■|  ----  |■■");
		gotoxy(x, y + 5);
		printf("■■|--------|■■");
		gotoxy(x, y + 6);
		printf("■■■■■■■■■");
	}
	else if(grafnum == 1){			//哺乳類
		gotoxy(x, y);
		printf("|＼  _______  ／| ");
		gotoxy(x, y + 1);
		printf("|  ／＼ ▽ ／＼ | ");
		gotoxy(x, y + 2);
		printf("|／  ＊＼／＊ ＼| ");
		gotoxy(x, y + 3);
		printf("|       △      | ");
		gotoxy(x, y + 4);
		printf("----------------- ");
		gotoxy(x, y + 5);
		printf("  ■■■〇■■■  ");
		gotoxy(x, y + 6);
		printf("■■■□□□■■■");
	}
	else if (grafnum == 2) {			//霊体
		gotoxy(x, y);
		printf("    |  | | |  |   ");
		gotoxy(x, y + 1);
		printf("  |  |--==--|  |  ");
		gotoxy(x, y + 2);
		printf("|  | ---  --- |  |");
		gotoxy(x, y + 3);
		printf("  |  |  == |  |   ");
		gotoxy(x, y + 4);
		printf(" || |  |  |  | || ");
		gotoxy(x, y + 5);
		printf("||□□■☆■□□||");
		gotoxy(x, y + 6);
		printf("□□■■■■■□□");
	}
	else if (grafnum == 3) {			//鳥類
		gotoxy(x, y);
		printf("  ______________  ");
		gotoxy(x, y + 1);
		printf("／  ●      ●  ＼");
		gotoxy(x, y + 2);
		printf("|       △       |");
		gotoxy(x, y + 3);
		printf("|       ▽       |");
		gotoxy(x, y + 4);
		printf("□■■□□□■■□");
		gotoxy(x, y + 5);
		printf("□□■■□■■□□");
		gotoxy(x, y + 6);
		printf("□□□■■■□□□");
	}
	else {			//虫類
		gotoxy(x, y);
		printf("|                |");
		gotoxy(x, y + 1);
		printf("-|-|／^^^^^^＼|-|-");
		gotoxy(x, y + 2);
		printf("／(◎========◎)＼");
		gotoxy(x, y + 3);
		printf("|   |＼ () ／|   |");
		gotoxy(x, y + 4);
		printf("■■□ ＼／ □■■");
		gotoxy(x, y + 5);
		printf("■■■□□□■■■");
		gotoxy(x, y + 6);
		printf("■■■■□■■■■");
	}
}

//自身の船の表示
void fune(void) {
	int i;
	const char *head[6] = { "====------=*",
							 "|■□□",
							 "|==-*＼",
							 "|==-*／",
							 "|■□□",
							 "====------=*",
	};

	const char *botom[8] = { "{==========}",
							 "|□■□■□□□□",
							 "|■□■□■□□□",
							 "|■■■■■■■■",
							 "|■■■■■■■■",
							 "|□■□■□□□□",
							 "|■□■□■□□□",
							 "{==========}",
	};
	const char *leg[6] = {	"=====|----------",
							"=====|■■■■■",
							"     |■□□□□",
							"     |■□□□□",
							"=====|■■■■■",
							"=====|----------",
	};
	for (i = 0; i < 6; i++) {
		gotoxy(4, 21 + i);
		printf("%s\n", leg[i]);
	}
	for (i = 0; i < 8; i++) {
		gotoxy(20, 20 + i);
		printf("%s\n", botom[i]);
	}
	
	for (i = 0; i < 6; i++) {
		gotoxy(37, 21 + i);
		printf("%s\n", head[i]);
	}
}

//敗北時の船分解シーン
void fune_move(int j) {
	int i;
	const char *head[6] = { "====------=*",
							 "|■□□",
							 "|==-*＼",
							 "|==-*／",
							 "|■□□",
							 "====------=*",
	};

	const char *botom[8] = { "{==========}",
							 "|□■□■□□□□",
							 "|■□■□■□□□",
							 "|■■■■■■■■",
							 "|■■■■■■■■",
							 "|□■□■□□□□",
							 "|■□■□■□□□",
							 "{==========}",
	};
	const char *leg[6] = {  "=====|----------",
							"=====|■■■■■",
							"     |■□□□□",
							"     |■□□□□",
							"=====|■■■■■",
							"=====|----------",
	};

	gotoxy(3, 20 + j);
	clreol();
	gotoxy(3, 28 - j);
	clreol();

	for (i = 0; i < 6; i++) {
		gotoxy(4, 21 + i + j);
		printf("%s\n", leg[i]);
	}
	for (i = 0; i < 8; i++) {
		gotoxy(20, 20 + i - j);
		printf("%s\n", botom[i]);
	}

	for (i = 0; i < 6; i++) {
		gotoxy(37, 21 + i + j);
		printf("%s\n", head[i]);
	}
	msleep(250);
}

//相手の船の表示
void enemy_fune(void) {
	int i;
	const char *head[6] = {  "*=------====",
							 "     □□■|",
							 "       *-==|",
							 "       *-==|",
							 "     □□■|",
							 "*=------====",
	};

	const char *botom[8] = { "     {==========}",
							 "□□□■□■□■|",
							 "□□■□■□□□|",
							 "■■■■■■■■|",
							 "■■■■■■■■|",
							 "□■□■□□□□|",
							 "□□□■□■□■|",
							 "     {==========}",
	};
	const char *leg[6] = {  "----------|=====",
							"■■■■■|=====",
							"□□□□■|",
							"□□□□■|",
							"■■■■■|=====",
							"----------|=====",
	};
	for (i = 0; i < 6; i++) {
		gotoxy(70, 21 + i);
		printf("%s\n", head[i]);
	}

	for (i = 0; i < 8; i++) {
		gotoxy(82, 20 + i);
		printf("%s\n", botom[i]);
	}

	for (i = 0; i < 6; i++) {
		gotoxy(99, 21 + i);
		printf("%s\n", leg[i]);
	}
}

//ダメージ表示
void battle_log(int damage, int attacknum, int hit) {
	gotoxy(3, 39);
	weapon(attacknum);
	printf("  %d発命中した", hit);
	gotoxy(3, 40);
	printf("%d", damage);
	printf("ダメージを与えた");
}

//戦闘画面を表示する
void battle_display(char ship_name[32],char player_name[32],int you_hp,int x,int y,int text) {
	textcolor(text);
	gotoxy(x, y);
	printf("%s級宇宙戦艦",ship_name);
	gotoxy(x, y + 1);
	printf("耐久力:%d",you_hp);
	gotoxy(x, y + 2);
	printf("提督:%s",player_name);
	textcolor(15);
}

//攻撃のアニメーション
void animation(int attacknum, int hit) {
	int i, j;
	int boom;
	int add = 0;
	int k;
	bool tama[2] = { false, false };

	boom = opensound("se/boom.mp3");
	k = 0;

	clrscr();
	fune();
	enemy_fune();

	if (attacknum == 1) {
		textcolor(1);
		gotoxy(42, 23);
		printf("(--)");
		gotoxy(42, 24);
		printf("(--)");
		msleep(500);
		gotoxy(44, 22);
		printf("(--)");
		gotoxy(42, 23);
		printf("(----)");
		gotoxy(42, 24);
		printf("(----)");
		gotoxy(44, 25);
		printf("(--)");
		msleep(1000);
		for (i = 0; i < 74; i++) {
			gotoxy(47 + i, 23);
			printf("=");
			gotoxy(47 + i, 24);
			printf("=");
		}
		if (hit >= 1) {
			playsound(boom, 0);
			textcolor(4);
			gotoxy(86, 21);
			printf("⌒⌒⌒⌒⌒⌒");
			gotoxy(82, 22);
			printf("⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒");
			gotoxy(80, 23);
			printf("[[[]][]][][][[]]][]]][][][]");
			gotoxy(80, 24);
			printf("[[][][[[]][][[]][][[[]]]][]");
			gotoxy(82, 25);
			printf("⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒");
			gotoxy(86, 26);
			printf("⌒⌒⌒⌒⌒⌒");
		}
		msleep(1000);
		textcolor(15);
	}

	if (attacknum == 2) {
		gotoxy(22, 19);
		printf("(--)");
		gotoxy(26, 19);
		printf("(--)");
		msleep(2000);

		tama[0] = true;

		for (i = 0; i < 5; i++) {
			for (j = 0; j < 20; j++) {
				fune();
				enemy_fune();


				if (tama[1] == true) {
					gotoxy(13 + (add - 15), 18 + (i - 1));
					printf("       ");
					gotoxy(13 + (add - 15), 19 + (i - 1));
					printf("       ");
					gotoxy(14 + (add - 15), 18 + (i - 1));
					printf("[=+@+=]");
					gotoxy(14 + (add - 15), 19 + (i - 1));
					printf("[=+@+=]");
				}

				if (tama[0] == true) {
					gotoxy(17 + add, 18 + i);
					printf("       ");
					gotoxy(17 + add, 19 + i);
					printf("       ");
					gotoxy(18 + add, 18 + i);
					printf("[=+@+=]");
					gotoxy(18 + add, 19 + i);
					printf("[=+@+=]");
				}

				if (add == 65 && hit > 0 || add == 80 && hit > 0) {
					enemy_fune();
					playsound(boom, 0);
					textcolor(4);
					gotoxy(86, 21);
					printf("⌒⌒⌒⌒⌒⌒");
					gotoxy(82, 22);
					printf("⌒⌒⌒⌒⌒⌒⌒⌒");
					gotoxy(80, 23);
					printf("[[[]][]][][][]][][]");
					gotoxy(80, 24);
					printf("[[][][[[]][][]][][]");
					gotoxy(82, 25);
					printf("⌒⌒⌒⌒⌒⌒⌒⌒");
					gotoxy(86, 26);
					printf("⌒⌒⌒⌒⌒⌒");
					textcolor(15);
					msleep(500);
					tama[k] = false;
					k++;
					hit--;
				}
				add++;

				msleep(2);
			}
			gotoxy(13 + (add - 15), 18 + (i - 1));
			printf("       ");

			gotoxy(17 + add, 18 + i);
			printf("       ");

			if (tama[0] == true) {
				tama[1] = true;
			}

		}
		clrscr();
		fune();
		enemy_fune();
		msleep(1000);

	}

	if (attacknum == 3) {

		tama[0] = true;

		for (i = 0; i < 5; i++) {
			for (j = 0; j < 20; j++) {
				fune();
				enemy_fune();

				if (tama[1] == true) {
					gotoxy(17 + (add - 15), 20 + (i - 1));
					printf("     ");
					gotoxy(17 + (add - 15), 21 + (i - 1));
					printf("     ");
					gotoxy(18 + (add - 15), 20 + (i - 1));
					printf("---＼");
					gotoxy(18 + (add - 15), 21 + (i - 1));
					printf("---／");
				}

				if (tama[0] == true) {
					gotoxy(17 + add, 20 + i);
					printf("       ");
					gotoxy(17 + add, 21 + i);
					printf("       ");
					gotoxy(18 + add, 20 + i);
					printf("---＼");
					gotoxy(18 + add, 21 + i);
					printf("---／");
				}

				if (add == 65 && hit > 0 || add == 80 && hit > 0) {
					enemy_fune();
					playsound(boom, 0);
					textcolor(4);
					gotoxy(86, 21);
					printf("⌒⌒⌒⌒⌒⌒");
					gotoxy(82, 22);
					printf("⌒⌒⌒⌒⌒⌒⌒⌒");
					gotoxy(80, 23);
					printf("[[[]][]][][][]][][]");
					gotoxy(80, 24);
					printf("[[][][[[]][][]][][]");
					gotoxy(82, 25);
					printf("⌒⌒⌒⌒⌒⌒⌒⌒");
					gotoxy(86, 26);
					printf("⌒⌒⌒⌒⌒⌒");
					textcolor(15);
					msleep(500);
					tama[k] = false;
					k++;
					hit--;
				}

				add++;

				msleep(5);
			}

			gotoxy(17 + (add - 15), 20 + (i - 1));
			printf("      ");

			if (tama[0] == true) {
				tama[1] = true;
			}
		}
		clrscr();
		fune();
		enemy_fune();
		msleep(1000);
	}

	if (attacknum == 4) {

		tama[0] = true;

		for (i = 0; i < 5; i++) {
			for (j = 0; j < 20; j++) {
				fune();
				enemy_fune();

				if (tama[1] == true) {
					gotoxy(17 + (add - 15), 19 + (i - 1));
					printf("      ");
					gotoxy(18 + (add - 15), 19 + (i - 1));
					printf("==●＞");
				}

				if (tama[0] == true) {
					gotoxy(17 + add, 18 + i);
					printf("      ");
					gotoxy(17 + add, 19 + i);
					printf("      ");
					gotoxy(18 + add, 19 + i);
					printf("==●＞");
				}

				if (add == 65 && hit > 0 || add == 80 && hit > 0) {
					enemy_fune();
					playsound(boom, 0);
					textcolor(4);
					gotoxy(86, 21);
					printf("⌒⌒⌒⌒⌒⌒");
					gotoxy(82, 22);
					printf("⌒⌒⌒⌒⌒⌒⌒⌒");
					gotoxy(80, 23);
					printf("[[[]][]][][][]][][]");
					gotoxy(80, 24);
					printf("[[][][[[]][][]][][]");
					gotoxy(82, 25);
					printf("⌒⌒⌒⌒⌒⌒⌒⌒");
					gotoxy(86, 26);
					printf("⌒⌒⌒⌒⌒⌒");
					textcolor(15);
					msleep(500);
					tama[k] = false;
					k++;
					hit--;
				}

				add++;

				msleep(5);
			}

			gotoxy(17 + (add - 15), 19 + (i - 1));
			printf("      ");

			if (tama[0] == true) {
				tama[1] = true;
			}
		}
		clrscr();
		fune();
		enemy_fune();
		msleep(1000);
	}

	if (attacknum == 5) {

		tama[0] = true;

		for (i = 0; i < 5; i++) {
			for (j = 0; j < 20; j++) {
				fune();
				enemy_fune();

				if (tama[1] == true) {
					gotoxy(17 + (add - 15), 19 + (i - 1));
					printf("  ");
					gotoxy(18 + (add - 15), 19 + (i - 1));
					printf("◎");
				}

				if (tama[0] == true) {
					gotoxy(17 + add, 18 + i);
					printf("  ");
					gotoxy(17 + add, 19 + i);
					printf("  ");
					gotoxy(18 + add, 19 + i);
					printf("◎");
				}


				if (add == 65 && hit > 0 || add == 80 && hit > 0) {
					enemy_fune();
					playsound(boom, 0);
					textcolor(4);
					gotoxy(86, 21);
					printf("⌒⌒⌒⌒⌒⌒");
					gotoxy(82, 22);
					printf("⌒⌒⌒⌒⌒⌒⌒⌒");
					gotoxy(80, 23);
					printf("[[[]][]][][][]][][]");
					gotoxy(80, 24);
					printf("[[][][[[]][][]][][]");
					gotoxy(82, 25);
					printf("⌒⌒⌒⌒⌒⌒⌒⌒");
					gotoxy(86, 26);
					printf("⌒⌒⌒⌒⌒⌒");
					textcolor(15);
					msleep(500);
					tama[k] = false;
					k++;
					hit--;
				}

				add++;

				msleep(3);
			}

			gotoxy(17 + (add - 15), 19 + (i - 1));
			printf("    ");

			if (tama[0] == true) {
				tama[1] = true;
			}

		}
		clrscr();
		fune();
		enemy_fune();
		msleep(1000);
	}

	closesound(boom);

}

//ターン終了時のクールダウンの計算
void cooldowncnt(void) {
	int i;

	for (i = 0; i <= 2; i++) {
		cooldown[i]--;
	}
}

//リトライしたときの初期化処理
void connldownreflesh(void) {
	int i;

	for (i = 0; i < 3; i++) {
		cooldown[i] = 0;
		ai_cooldown[i] = 0;
	}
}

//使用した武器の表示
void weapon(int weapon) {
	if (weapon == 1) {
		printf("タイタンランスを使用した。");
	}
	else if (weapon == 2) {
		printf("事象崩壊砲を使用した。");
	}
	else if (weapon == 3) {
		printf("大型実弾砲を使用した。");
	}
	else if (weapon == 4) {
		printf("マスドライバーを使用した。");
	}
	else if (weapon == 5) {
		printf("オートキャノンを使用した。");
	}
	else {
		printf("体当たりをした。");
	}
}

//入力画面
int battle_input(void) {
	gotoxy(4,39);
	printf("何をしますか？\n");
	gotoxy(4, 40);
	//key変数によってカーソルの位置を変える
	if (key==0) {
		printf("二ア 攻撃 シールド展開 スキップ");
	}
	else if (key == 1) {
		printf("攻撃 二アシールド展開 スキップ");
	}
	else {
		printf("攻撃 シールド展開 二アスキップ");
	}

	//キー入力待ち
	getkey = getch();

	//左矢印キーを押されたとき
	if (getkey == 0x4B && key > 0) {
		key--;
	}

	//左矢印キーを押されたとき
	if (getkey == 0x4D && key < 2) {
		key++;
	}

	//エンターキーを押されたとき
	if (getkey == 0x0d) {
		//キーの位置によって変える
		if (key == 0) {
			return 1;
		}
		else if (key == 1) {
			return 2;
		}
		else if (key == 2) {
			return 3;
		}
		else {

		}
	}
	return 0;
}

//選択で攻撃を選択したとき
int battle_attack(int T, int XL, int L, int M, int S, char moji1[MOJIRETU], char moji2[MOJIRETU], char moji3[MOJIRETU], int eshiphp) {
	//変数の初期化(カーソルを初期位置にする)
	key = 0;
	getkey = 0;

	//攻撃完了するまでループ
	while (1) {
		gotoxy(4, 40);
		
		//攻撃できる手段がない場合
		if ((strcmp(moji2, "マスドライバー") != 0 && strcmp(moji3, "マスドライバー") != 0 && strcmp(moji2, "オートキャノン") != 0 && strcmp(moji3, "オートキャノン") != 0) && (strcmp(moji1, "タイタンランス") != 0 || cooldown[0] > 0) && (strcmp(moji1, "事象崩壊砲") != 0 || cooldown[1] > 0) && (strcmp(moji1, "大型実弾砲") != 0 || strcmp(moji2, "大型実弾砲") != 0 || strcmp(moji3, "大型実弾砲") != 0) && cooldown[2] > 0) {
			return 6;
		}

		//key変数によってカーソルの位置を変える
		if (key == 0) {
			printf("ニア");
			printf("%s  ", moji1);
			printf("%s  ", moji2);
			printf("%s", moji3);
		}
		if (key == 1) {
			printf("%s  ", moji1);
			printf("ニア");
			printf("%s  ", moji2);
			printf("%s", moji3);
		}
		if (key == 2) {
			printf("%s  ", moji1);
			printf("%s  ", moji2);
			printf("ニア");
			printf("%s", moji3);
		}

		//キー入力待ち
		getkey = getch();

		//左矢印キーを入力された場合
		if (getkey == 0x4B && key > 0) {
			key--;
		}
		//右矢印キーを入力された場合
		if (getkey == 0x4D && key < 2) {
			key++;
		}
		//エンターキーを入力された場合
		if (getkey == 0x0d) {
			gotoxy(4, 36);

			//key変数の位置で変動
			if (key == 0) {

				//超々大型兵器が選択されていた場合
				if (strcmp(moji1, "タイタンランス") == 0) {

					//クールダウンが完了している場合攻撃する
					if (cooldown[0] <= 0) {
						cooldown[0] = 6;		//クールダウンを設定

						return 1;
					}

					else {
						printf("まだ攻撃できません(あと%dターン)",cooldown[0]);
					}
				}
				//超大型兵器が選択されていた場合
				else if (strcmp(moji1, "事象崩壊砲") == 0) {
					//クールダウンが完了している場合攻撃する
					if (cooldown[1] <= 0) {
						cooldown[1] = 4;		//クールダウンを設定

						return 2;
					}
					else {
						printf("まだ攻撃できません(あと%dターン)",cooldown[1]);
					}
				}
				//大型兵器が選択されていた場合
				else {
					//クールダウンが完了している場合攻撃する
					if (cooldown[2] <= 0) {
						cooldown[2] = 3;		//クールダウンを設定

						return 3;
					}
					else {
						printf("まだ攻撃できません(あと%dターン)", cooldown[2]);
					}
				}
			}

			else if (key == 1) {
				//大型兵器が選択されていた場合
				if (strcmp(moji2, "大型実弾砲") == 0) {
					//クールダウンが完了している場合攻撃する
					if (cooldown[2] <= 0) {
						cooldown[2] = 3;		//クールダウンを設定

						return 3;
					}
					else {
						printf("まだ攻撃できません(あと%dターン)", cooldown[2]);
					}
				}
				//中型兵器が選択されていた場合(クールダウンはない)
				else if (strcmp(moji2, "マスドライバー") == 0) {

					return 4;
				}
				//小型兵器が選択されていた場合(クールダウンはない)
				else if (strcmp(moji2, "オートキャノン") == 0) {

					return 5;
				}
				//大型兵器がかぶっていて、なにも設定されていない場合
				else {
					clrscr();
					return 7;
				}
			}

			else {
				//大型兵器があって頭と胴体に大型兵器が装備されていない場合
				if (strcmp(moji3, "大型実弾砲") == 0 && strcmp(moji2, "大型実弾砲") != 0 && strcmp(moji1, "大型実弾砲") != 0) {
					//クールダウンが完了している場合攻撃する
					if (cooldown[2] <= 0) {
						cooldown[2] = 3;		//クールダウンを設定

						return 3;
					}
					else {
						printf("まだ攻撃できません(あと%dターン)", cooldown[2]);
					}
				}
				//中型兵器があって胴体に中型兵器が装備されていない場合(クールダウンはない)
				else if (strcmp(moji3, "マスドライバー") == 0 && strcmp(moji2, "マスドライバー") != 0) {

					return 4;
				}
				//小型兵器があって胴体に小型兵器が装備されていない場合(クールダウンはない)
				else if (strcmp(moji3, "オートキャノン") == 0 && strcmp(moji2, "オートキャノン") != 0) {

					return 5;
				}
				//大型兵器がかぶっていて、なにも設定されていない場合
				else{
					clrscr();
					return 7;
				}
			}

			//キー入力待ち
			getch();
		}
		if (getkey == 0x1b) {
			clrscr();
			return 7;
		}
	}

}

//ダメージ計算を行う
int battle_attack_shori(bool youdef,int atari,int flag,int pe) {
	//変数宣言
	int damage = 0;

	//戦闘画面で命中するとダメージ計算する
	if (atari >= 1 || flag == 6) {
		//超々大型兵器の場合
		if (flag == 1) {
			damage = 4000 + (rand() & 4001) + (rand() & pe) - ((youdef * 2) * 2000);			//ダメージを3000～7000にする
		}
		//超大型兵器の場合
		else if (flag == 2) {
			damage = (((2000 + (rand() & 2001)) + (rand() & pe)) * atari) - ((youdef * 2) * 1750);		//ダメージを1000～3000 * 2にする
		}
		//大型兵器の場合
		else if (flag == 3) {
			damage = (((200 + (rand() & 201)) + (rand() & pe)) * atari) - ((youdef * 2) * 1250);		//ダメージを200～400 * 兵器数にする
		}
		//中型兵器の場合
		else if (flag == 4) {
			damage = (((40 + (rand() & 41)) + (rand() & pe)) * atari) - ((youdef * 2) * 750);		//ダメージを40～80 * 兵器数にする
		}
		//小型大型兵器の場合
		else if (flag == 5) {
			damage = (((10 + (rand() & 11)) + (rand() & pe)) * atari) - ((youdef * 2) * 250);		//ダメージを10～40 * 兵器数にする
		}
		//全ての兵器が使用不可の場合、何らかの手段でダメージを与える(その代わりダメージ1のみ)
		else {
			damage = 1;		//ダメージを1にする
		}

		//攻撃が0以下になった場合0にする
		if (damage < 0) {
			damage = 0;
		}
	}
	//全弾外した場合、ダメージ0を与える
	else {
		damage = 0;		//ダメージを0にする
	}

	return damage;
}

//相手の攻撃処理
int ai_battle(bool youdef, int youhp,int ee, char moji1[32], char moji2[32], char moji3[32], int L, int M, int S) {
	//変数宣言
	int kakuritu, attack_kakuritu, flag, i;	//乱数で攻撃を決める(kakuritu),攻撃手段を決める(flag),for文の中に入れる
	int damage = 0;
	int hit = 0;
	int sound;
	sound = opensound("se/boom.mp3");
	//攻撃完了までループ
	while (1) {
		//乱数を決める
		kakuritu = rand() % 100;

		//0～30の値が出たとき
		if (kakuritu <= 30) {
			//超々大型兵器が装備されていたとき
			if (strcmp(moji1, "タイタンランス") == 0) {
				//クールダウンが完了しているとき
				if (ai_cooldown[0] <= 0) {
					ai_cooldown[0] = 6;
					flag = 1;

					attack_kakuritu = rand() % 100;
					if (attack_kakuritu <= 60) {
						hit++;
					}

					damage = battle_attack_shori(youdef, hit, flag, ee);
					break;
				}
			}
			//超大型兵器が装備されていたとき
			else if (strcmp(moji1, "事象崩壊砲") == 0) {
				//クールダウンが完了しているとき
				if (ai_cooldown[1] <= 0) {
					ai_cooldown[1] = 4;
					flag = 2;

					for (i = 0; i < 2; i++) {
						attack_kakuritu = rand() % 100;
						if (attack_kakuritu <= 60) {
							hit++;
						}
					}

					damage = battle_attack_shori(youdef, hit, flag, ee);		//攻撃処理
					break;
				}
			}
			//大型兵器が装備されていたとき
			else {
				//クールダウンが完了しているとき
				if (ai_cooldown[2] <= 0) {
					ai_cooldown[2] = 3;
					flag = 3;

					for (i = 0; i < L; i++) {
						attack_kakuritu = rand() % 100;
						if (attack_kakuritu <= 60) {
							hit++;
						}
					}
					damage = battle_attack_shori(youdef, hit, flag, ee);		//攻撃処理
					break;
				}
			}
		}

		//31～60の値が出たとき
		else if (kakuritu >= 31 && kakuritu <= 60) {
			//大型兵器が装備されていたとき
			if (strcmp(moji2, "大型実弾砲") == 0) {
				//クールダウンが完了しているとき
				if (ai_cooldown[2] <= 0) {
					ai_cooldown[2] = 3;
					flag = 3;

					for (i = 0; i < L; i++) {
						attack_kakuritu = rand() % 100;
						if (attack_kakuritu <= 60) {
							hit++;
						}
					}

					damage = battle_attack_shori(youdef, hit, flag, ee);		//攻撃処理
					break;
				}
			}
			//中型兵器が装備されていたとき(クールダウンは必要ない)
			else if (strcmp(moji2, "マスドライバー") == 0) {
				flag = 4;

				for (i = 0; i < M; i++) {
					attack_kakuritu = rand() % 100;
					if (attack_kakuritu <= 60) {
						hit++;
					}
				}
				damage = battle_attack_shori(youdef, hit, flag, ee);		//攻撃処理
				break;
			}
			//小型兵器が装備されていたとき(クールダウンは必要ない)
			else if (strcmp(moji2, "オートキャノン") == 0) {
				flag = 5;

				for (i = 0; i < S; i++) {
					attack_kakuritu = rand() % 100;
					if (attack_kakuritu <= 60) {
						hit++;
					}
				}

				damage = battle_attack_shori(youdef, hit, flag, ee);		//攻撃処理
				break;
			}
			else {

			}
		}

		//61～90の値が出たとき
		else if (kakuritu >= 61 && kakuritu <= 90) {
			//大型兵器が装備されていたとき
			if (strcmp(moji3, "大型実弾砲") == 0 ) {
				//クールダウンが完了していたとき
				if (ai_cooldown[2] <= 0) {
					flag = 3;
					ai_cooldown[2] = 3;

					for (i = 0; i < L; i++) {
						attack_kakuritu = rand() % 100;
						if (attack_kakuritu <= 60) {
							hit++;
						}
					}

					damage = battle_attack_shori(youdef, hit, flag, ee);		//攻撃処理
					break;
				}
			}
			//中型兵器が装備されていたとき(クールダウンは必要ない)
			else if (strcmp(moji3, "マスドライバー") == 0 ) {
				flag = 4;
				for (i = 0; i < M; i++) {
					attack_kakuritu = rand() % 100;
					if (attack_kakuritu <= 60) {
						hit++;
					}
				}

				damage = battle_attack_shori(youdef, hit, flag, ee);		//攻撃処理
				break;
			}
			//小型兵器が装備されていたとき(クールダウンは必要ない)
			else if (strcmp(moji3, "オートキャノン") == 0) {
				flag = 5;

				for (i = 0; i < S; i++) {
					attack_kakuritu = rand() % 100;
					if (attack_kakuritu <= 60) {
						hit++;
					}
				}

				damage = battle_attack_shori(youdef, hit, flag, ee);		//攻撃処理
				break;
			}
			else {

			}
		}

		//確率から外れた場合もう一度やり直し
		else {

		}

		//攻撃出来ないとき何もせずにループから抜け出す
		if ((strcmp(moji2, "マスドライバー") != 0 && strcmp(moji3, "マスドライバー") != 0 && strcmp(moji2, "オートキャノン") != 0 && strcmp(moji2, "オートキャノン") != 0) && (strcmp(moji1, "タイタンランス") != 0 || ai_cooldown[0] > 0) && (strcmp(moji1, "事象崩壊砲") != 0 || ai_cooldown[1] > 0) && (strcmp(moji1, "大型実弾砲") != 0 || strcmp(moji2, "大型実弾砲") != 0 || strcmp(moji3, "大型実弾砲") != 0) && ai_cooldown[2] > 0) {
			flag = 6;
			damage = battle_attack_shori(youdef, 1, flag, ee);		//攻撃処理
			break;
		}

	}

	youhp -= damage;

	//ターン終了時にクールダウン時間を1減らす
	for (i = 0; i <= 2; i++) {
		ai_cooldown[i] -= 1;
	}
	playsound(sound, 0);
	battle_log(damage, flag, hit);
	rewind(stdin);
	getchar();

	closesound(sound);

	return youhp;
}

//攻撃画面
int battlepart(int kazu) {

	//変数宣言
	int i;
	int atari = 0;
	int x = 8, y = 1;
	int fps = 0;
	int number = 500;
	int sum = 0;
	int enter;
	bool hit = false;

	const char *nothing[7] = { "        ",
							   "           ",
							   "             ",
							   "              ",
							   "             ",
							   "           ",
							   "        ",
	};

	const char *cursor[7] = {"      ||",
							 "   ===||===",
							 " ===  ||  ===",
							 "------◎------",
							 " ===  ||  ===",
							 "   ===||===",
							 "      ||",
	};

	const char *target[7] = {"  ■■■■■■■",
							 "■              ■",
							 "■              ■",
							 "■      ◎      ■",
							 "■              ■",
							 "■              ■",
							 "  ■■■■■■■"
	};

	clrscr();

	//エンターキーが押されるまでループ
	while (1) {
		if (kbhit()) {		//どこかのキーが押されたとき
			enter = getch();		//そのキーの情報を"key"変数にいれる
			if (enter == 0x0d) {		//"key"に入ったのがエンターキーだった場合
				if (x > 80 && x < 100) {		//攻撃範囲内の場合
					atari++;
					hit = true;
				}
				else {		//攻撃範囲外の場合
					hit = false;
				}

				//弾の流れるスピード調整 500～1000
				number = 500 + rand() & 501;
				sum++;
				x = 8;
				y = 1;
				fps = 0;
				clrscr();
			}
		}
		else if (x > 130) {
			number = 500 + rand() & 501;
			x = 8;
			y = 1;
			fps = 0;
			sum++;
			hit = false;
			clrscr();
		}

		if (sum == kazu) {
			break;
		}

		//numberより上になったら画像処理をする
		if (fps > number) {

			//空白表示
			for (i = 0; i < 7; i++) {
				gotoxy(x - 8, y - 1 + i);
				printf("%s\n", nothing[i]);
			}

			//的表示
			for (i = 0; i < 7; i++) {
				gotoxy(86, 10 + i);
				printf("%s\n", target[i]);
			}

			//カーソル表示
			for (i = 0; i < 7; i++) {
				gotoxy(x, y + i);
				printf("%s\n", cursor[i]);
			}

			gotoxy(4, 39);
			printf("%d回中%d回", kazu, sum + 1);

			if (hit == true) {
				textcolor(4);
				gotoxy(89, 19);
				printf("HIT");
				textcolor(15);
				msleep(50);
			}

			fps = 0;
			x += 8;
			y++;
			hit = false;
			msleep(20);
		}
		
		fps++;
	}

	return atari;
}