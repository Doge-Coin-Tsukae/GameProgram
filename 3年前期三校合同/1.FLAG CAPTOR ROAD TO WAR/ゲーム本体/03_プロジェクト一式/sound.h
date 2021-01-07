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
	SOUND_BGM_BGM000,
	SOUND_BGM_BGM001,
	SOUND_BGM_BGM002,
	SOUND_BGM_BGM003,
	//SE
	SOUND_SE_SE001,
	SOUND_SE_SE002,
	SOUND_SE_RELOAD,
	SOUND_SE_RELOAD2,
	SOUND_SE_CLICK,
	SOUND_SE_DEATH,
	SOUND_SE_FALL,
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
