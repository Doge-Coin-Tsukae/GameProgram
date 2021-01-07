//==============================================================================
// File name / type  :  x_gamepad.h
//  Private number   :  [AT-12C-342] No.19 
// Writer copyright  :  (C) Aoi Shibuichi All rights reserved.
//==============================================================================
#ifndef _X_GAMEPAD_H_	// ２重インクルード防止のマクロ定義
#define _X_GAMEPAD_H_

#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")

//==============================================================================
// ポート番号
//==============================================================================
enum port
{
	PP_LX, // 左スティックX軸 32768 ～ 32767
	PP_LY, // 左スティックY軸 32768 ～ 32767
	PP_RX, // 右スティックX軸 32768 ～ 32767
	PP_RY, // 右スティックY軸 32768 ～ 32767
	PP_LT, // LTボタン 0 ～ 255
	PP_RT, // RTボタン 0 ～ 255
	PP_Tr,
	PP_UP,
	PP_DOWN,
	PP_LEFT,
	PP_RIGHT,
	PP_START,
	PP_BACK,
	PP_L1,
	PP_L3,
	PP_R1,
	PP_R3,
	PP_A,
	PP_B, 
	PP_X,
	PP_Y
};

//==============================================================================
//インプット関数
//==============================================================================
int gamepad_inport(DWORD index, enum port port);

#endif