//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#pragma once
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#include <dsound.h>
#include <windows.h>
#include "xaudio2.h"						// サウンド処理で必要


//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	//BGM
	SOUND_LABEL_TITLE_BGM,				// 1.タイトルBGM
	SOUND_LABEL_TUTORIAL_BGM,			// 2.リザルトBGM
	SOUND_LABEL_BATTLE_BGM,				// 3.戦闘中BGM（必要ならば）

	//フィールドSE
	SOUND_LABEL_SE_POINT_SELECT,		// 7.セレクト音
	SOUND_LABEL_SE_SELECT_DECISION,		// 8.セレクト決定音

	SOUND_LABEL_SE_POINT_COUNT,			// 9.カウントダウン
	SOUND_LABEL_SE_POINT_COUNT_GO,		// 10.カウントダウン終了ゲームスタート音

	//プレイヤーSE
	SOUND_LABEL_SE_PUNCH_MISS,		// 15.プレイヤーの足音
	SOUND_LABEL_SE_PUNCH_HIT,		// 16.矢を引くチャージ音 
	SOUND_LABEL_SE_PUNCH_FLY,		// 17.矢を飛ばすときの音
	SOUND_LABEL_SE_KICK_MISS,		// 18.矢が空中にある時の音
	SOUND_LABEL_SE_KICK_HIT,		// 19.矢と的が接触したときの音
	SOUND_LABEL_SE_KICK_FLY,		// 20.矢がプレイヤーと接触したときの音
	SOUND_LABEL_SE_DEATH,			//死亡時のSE


	//リザルトSE
	SOUND_LABEL_SE_TIMEUP,				// 21.タイムアップ音
	SOUND_LABEL_SE_DRAMROLL,			// 22.リザルト発表時のドラムロール
	SOUND_LABEL_SE_CHEERS,				// 23.リザルト発表時の歓声
	SOUND_LABEL_SE_MATASONDENE,			// 24.またあそんでね
	
	SOUND_LABEL_TEST_BGM,		// 25.テスト

	SOUND_LABEL_MAX,

} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
