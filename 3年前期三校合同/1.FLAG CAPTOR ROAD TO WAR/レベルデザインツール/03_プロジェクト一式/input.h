#pragma once


class CInput
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];

	static D3DXVECTOR2 m_OldMousePos;
	static D3DXVECTOR2 m_MousePos;
public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );
	
	static void SetMousePos(D3DXVECTOR2 SetPos)
	{
		m_OldMousePos = m_MousePos;
		m_MousePos = SetPos;
	}
	static D3DXVECTOR2 GetMousedDfference()
	{
		return m_MousePos - m_OldMousePos;
	}
	static void ResetMousePos()
	{
		m_OldMousePos.x = SCREEN_WIDTH/2+m_OldMousePos.x;
		m_OldMousePos.y = SCREEN_HEIGHT/2 + m_OldMousePos.y;
		m_MousePos.x = SCREEN_WIDTH/2+ m_MousePos.x;
		m_MousePos.y = SCREEN_HEIGHT/2+ m_MousePos.y;
	}
};
