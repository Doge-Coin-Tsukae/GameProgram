#include "myDirect3D.h"
#include "texture.h"
#include "GameMag.h"
#include "player.h"

//構造体
typedef struct
{
	int gameset[MAX_PLAYER];		//セットカウント
	int time;					//制限時間
}GAMEMANEGER;

GAMEMANEGER game;

//マネージャの初期処理
HRESULT GameMane_Initialize(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		game.gameset[i] = 0;
	}
	game.time = 0;
}

void GameMane_Finalize(void)
{

}

void GameMane_Update(void)
{

}

void GameMane_Draw(void)
{

}

//引数の中のプレイヤーに1セットを加えるのと時間リセット
/*void SetGameSet(int index)
{
	game.gameset[index] += 1;
	game.time = 0;
}*/