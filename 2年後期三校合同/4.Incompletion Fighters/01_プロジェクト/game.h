#pragma once

typedef enum PHASE_INDEX
{
	PHASE_INDEX_FADE,
	PHASE_INDEX_PLAYER_IN,

	PHASE_INDEX_STAGE_CLEAR,
	PHASE_INDEX_END,

	PHASE_INDEX_MAX
};

void Game_Initialize(void);
void Game_Finalize(void);
void Game_Update(void);
void Game_Draw(void);
void SetGameSet(int index);
void SetDeathflag(void);
int GetSetCount(int index);