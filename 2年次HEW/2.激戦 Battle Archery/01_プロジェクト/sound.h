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
	SOUND_LABEL_RESULT_BGM,				// 2.リザルトBGM
	//SOUND_LABEL_BATTLE_BGM,			// 3.戦闘中BGM（必要ならば）
	SOUND_LABEL_STAFFROLL_BGM,			// 4.スタッフロール（必要ならば）
	SOUND_LABEL_WEATHER_RAIN_BGM,		// 5.天候音、雨
	SOUND_LABEL_WEATHER_THUNDER_BGM,	// 6.天候音、雷
	SOUND_LABEL_WEATHER_1_BGM,	// 6.天候音、雷
	SOUND_LABEL_WEATHER_2_BGM,	// 6.天候音、雷

	//フィールドSE
	SOUND_LABEL_SE_POINT_SELECT,		// 7.セレクト音
	SOUND_LABEL_SE_SELECT_DECISION,		// 8.セレクト決定音

	SOUND_LABEL_SE_POINT_COUNT,			// 9.カウントダウン
	SOUND_LABEL_SE_POINT_COUNT_GO,		// 10.カウントダウン終了ゲームスタート音

	SOUND_LABEL_SE_GIRL_COUNT_1,		// 11.女の子カウントダウン１
	SOUND_LABEL_SE_GIRL_COUNT_2,		// 12.女の子カウントダウン２
	SOUND_LABEL_SE_GIRL_COUNT_3,		// 13.女の子カウントダウン３
	SOUND_LABEL_SE_GIRL_COUNT_GO,		// 14.女の子カウントダウンGO
	SOUND_LABEL_SE_GIRL_TIME_UP,		// 14.女の子TIMEUP


	//プレイヤーSE
	SOUND_LABEL_SE_FOOTSTEPS,			// 15.プレイヤーの足音
	SOUND_LABEL_SE_CHARGE,				// 16.矢を引くチャージ音 
	SOUND_LABEL_SE_SHOT,				// 17.矢を飛ばすときの音
	SOUND_LABEL_SE_ARROW_FLYING,		// 18.矢が空中にある時の音
	SOUND_LABEL_SE_TARGET_HIT,			// 19.矢と的が接触したときの音
	SOUND_LABEL_SE_TARGET_HIT_CHEERS,	// 20.歓声
	SOUND_LABEL_SE_PLAYER_HIT,			// 21.矢がプレイヤーと接触したときの音


	//リザルトSE
	SOUND_LABEL_SE_TIMEUP,				// 22.タイムアップ音
	SOUND_LABEL_SE_DRAMROLL,			// 23.リザルト発表時のドラムロール
	SOUND_LABEL_SE_CHEERS,				// 24.リザルト発表時の歓声
	SOUND_LABEL_SE_MATASONDENE,			// 25.またあそんでね
	
	SOUND_LABEL_TEST_BGM,		// 26.テスト

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
