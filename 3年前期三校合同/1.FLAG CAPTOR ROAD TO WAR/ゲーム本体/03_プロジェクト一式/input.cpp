
#include "main.h"
#include "input.h"


BYTE CInput::m_OldKeyState[256];
BYTE CInput::m_KeyState[256];
D3DXVECTOR2 CInput::m_OldMousePos;
D3DXVECTOR2 CInput::m_MousePos;

void CInput::Init()
{

	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );

}

void CInput::Uninit()
{


}

void CInput::Update()
{

	memcpy( m_OldKeyState, m_KeyState, 256 );

	GetKeyboardState( m_KeyState );


	POINT pos;
	GetCursorPos(&pos);
	CInput::SetMousePos(D3DXVECTOR2(pos.x, pos.y));
}

bool CInput::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool CInput::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}