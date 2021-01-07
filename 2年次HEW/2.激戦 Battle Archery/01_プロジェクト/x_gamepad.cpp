//==============================================================================
// File name / type  :  x_gamepad.cpp
//  Private number   :  [AT-12C-342] No.19 
// Writer copyright  :  (C) Aoi Shibuichi All rights reserved.
//==============================================================================
#include "x_gamepad.h"

//==============================================================================
// コントローラのステータス
//==============================================================================
XINPUT_STATE state[4];

//==============================================================================
// gamepad_inport
// index : コントローラのインデックス
// port  : 情報を取得したいキーのポート番号
//==============================================================================
int gamepad_inport(DWORD index, enum port port)
{
	int back;	//戻り値

	//--------------------------------------------------------------------------
	// コントローラの状態取得
	//--------------------------------------------------------------------------
	XInputGetState(index, &state[index]);

	if(port == PP_LX)
	{
		back = state[index].Gamepad.sThumbLX;
	}
	else if(port == PP_LY)
	{
		back = state[index].Gamepad.sThumbLY;
	}
	else if(port == PP_RX)
	{
		back = state[index].Gamepad.sThumbRX;
	}
	else if(port == PP_RY)
	{
		back = state[index].Gamepad.sThumbRY;
	}
	else if(port == PP_LT)
	{
		back = state[index].Gamepad.bLeftTrigger;
	}
	else if(port == PP_RT)
	{
		back = state[index].Gamepad.bRightTrigger;
	}
	else if(port == PP_Tr)
	{
		back = (state[index].Gamepad.bRightTrigger) - (state[index].Gamepad.bLeftTrigger);
	}
	else if(port == PP_UP)
	{
		if((state[index].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0)
		{
			back = 1;
		}
		else
		{
			back = 0;
		}
	}
	else if(port == PP_DOWN)
	{
		if((state[index].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0)
		{
			back = 1;
		}
		else
		{
			back = 0;
		}
	}
	else if(port == PP_LEFT)
	{
		if((state[index].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0)
		{
			back = 1;
		}
		else
		{
			back = 0;
		}
	}
	else if(port == PP_RIGHT)
	{
		if((state[index].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0)
		{
			back = 1;
		}
		else
		{
			back = 0;
		}
	}
	else if(port == PP_START)
	{
		if((state[index].Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0)
		{
			back = 1;
		}
		else
		{
			back = 0;
		}
	}
	else if(port == PP_BACK)
	{
		if((state[index].Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0)
		{
			back = 1;
		}
		else
		{
			back = 0;
		}
	}
	else if(port == PP_L1)
	{
		if((state[index].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0)
		{
			back = 1;
		}
		else
		{
			back = 0;
		}
	}
	else if(port == PP_L3)
	{
		if((state[index].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0)
		{
			back = 1;
		}
		else
		{
			back = 0;
		}
	}
	else if(port == PP_R1)
	{
		if((state[index].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0)
		{
			back = 1;
		}
		else
		{
			back = 0;
		}
	}
	else if(port == PP_R3)
	{
		if((state[index].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0)
		{
			back = 1;
		}
		else
		{
			back = 0;
		}
	}
	else if(port == PP_A)
	{
		if((state[index].Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0)
		{
			back = 1;
		}
		else
		{
			back = 0;
		}
	}
	else if(port == PP_B)
	{
		if((state[index].Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0)
		{
			back = 1;
		}
		else
		{
			back = 0;
		}
	}
	else if(port == PP_X)
	{
		if((state[index].Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0)
		{
			back = 1;
		}
		else
		{
			back = 0;
		}
	}
	else if(port == PP_Y)
	{
		if((state[index].Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0)
		{
			back = 1;
		}
		else
		{
			back = 0;
		}
	}
	return back;
}