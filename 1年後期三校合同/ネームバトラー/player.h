#ifndef _PLAYER_H_
#define _PLAYER_H_
#define CHARACTER

#define MOJIRETU (15)

//プロトタイプ宣言
void player_soto(void);
void player_name(bool hantei);
void ship_name(bool hantei);
void frame(void);
int input(char name[32]);
int player_atai(char name[32]);
int player_efficiency(int ascii);
int player_graphic(int ascii);
void plyaer_display(char name[32],int efficiency,int gra);
int ship_atai(char name[32]);
int ship_hp(int ascii);
int ship_parts(int ascii);
int ship_weapon_t(int head, int t);
int ship_weapon_xl(int head, int xl);
int ship_weapon_l(int head, int botom, int leg, int l);
int ship_weapon_m(int botom, int leg, int m);
int ship_weapon_s(int botom, int leg, int s);
int moji1(char moji[MOJIRETU],int head);
int moji2(char moji[MOJIRETU], int head, int botom);
int moji3(char moji[MOJIRETU], int head, int botom, int leg);
void ship_display(char name[32], int HP, int HEAD, int BOTOM, int LEG, int WEAPON_T, int WEAPON_XL, int WEAPON_L, int WEAPON_M, int WEAPON_S);

#endif _PLAYER_H_