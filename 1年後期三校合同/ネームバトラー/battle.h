#ifndef _BATTLE_H_
#define _BATTLE_H_
#define MOJIRETU (15)

//プロトタイプ宣言
void haikei(int x,int y);
void character_graf(int grafnum, int x, int y);
void fune(void);
void fune_move(int j);
void enemy_fune(void);
void battle_log(int damage, int attacknum, int hit);
void weapon(int weapon);
void battle_display(char ship_name[32], char player_name[32], int you_hp, int x, int y, int text);
void animation(int attacknum,int hit);
void cooldowncnt(void);
void connldownreflesh(void);
void defense_hyoji(void);
int battle_input(void);
int battle_attack(int T, int XL, int L, int M, int S, char moji1[MOJIRETU], char moji2[MOJIRETU], char moji3[MOJIRETU], int eshiphp);
int battle_attack_shori(bool youdef, int atari,int flag, int pe);
int ai_battle(bool youdef,int youhp, int ee, char moji1[32], char moji2[32], char moji3[32], int L, int M, int S);
int battlepart(int kazu);

#endif _BATTLE_H_
