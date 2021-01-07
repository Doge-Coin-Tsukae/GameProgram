#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#define MOJIRETU (15)

//構造体配列の定義
//キャラクターの定義
typedef struct
{
	char NAME[32];
	char GRAPHIC[10][10];
	int EFFICIENCY;
	int GRA;
}PLAYER;

//船の定義
typedef struct
{
	char NAME[32];
	char WEA_MOJI1[MOJIRETU];
	char WEA_MOJI2[MOJIRETU];
	char WEA_MOJI3[MOJIRETU];
	int HP;
	int HEAD;
	int BOTOM;
	int LEG;
	int WEAPON_T = 0;
	int WEAPON_XL = 0;
	int WEAPON_L = 0;
	int WEAPON_M = 0;
	int WEAPON_S = 0;
}SHIP;

PLAYER player[2];
SHIP ship[2];

#endif _CHARACTER_H_