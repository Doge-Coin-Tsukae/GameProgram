#include "myDirect3D.h"
#include "texture.h"
#include "GameMag.h"
#include "player.h"

//�\����
typedef struct
{
	int gameset[MAX_PLAYER];		//�Z�b�g�J�E���g
	int time;					//��������
}GAMEMANEGER;

GAMEMANEGER game;

//�}�l�[�W���̏�������
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

//�����̒��̃v���C���[��1�Z�b�g��������̂Ǝ��ԃ��Z�b�g
/*void SetGameSet(int index)
{
	game.gameset[index] += 1;
	game.time = 0;
}*/