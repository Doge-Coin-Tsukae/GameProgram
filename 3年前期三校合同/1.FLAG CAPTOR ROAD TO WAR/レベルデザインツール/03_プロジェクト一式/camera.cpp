//****************************************
//カメラ操作
//****************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "scene.h"

#include "model.h"
#include "carsor.h"
#include"camera.h"

void CCamera::Init()
{
	m_Position = D3DXVECTOR3(10.0f,120.0f, -30.0f);
	m_Target = D3DXVECTOR3(10.0f, 115.0f, -32.0f);
	m_speed = 0.5f;
}

void CCamera::Uninit()
{
}

void CCamera::Update()
{
	Controll_Update();	//操作
}
void CCamera::Controll_Update()
{
	m_Velocity = D3DXVECTOR3(0,0,0);

	//キー入力で移動
	if (CInput::GetKeyPress('D'))
	{
		m_Velocity.z += sin(m_Rotation.x)*m_speed;
		m_Velocity.x -= cos(m_Rotation.x)*m_speed;
	}
	if (CInput::GetKeyPress('A'))
	{
		m_Velocity.z -= sin(m_Rotation.x)*m_speed;
		m_Velocity.x += cos(m_Rotation.x)*m_speed;
	}
	if (CInput::GetKeyPress('S'))
	{
		m_Velocity.x += sin(m_Rotation.x)*m_speed;
		m_Velocity.z += cos(m_Rotation.x)*m_speed;
	}
	if (CInput::GetKeyPress('W'))
	{
		m_Velocity.x -= sin(m_Rotation.x)*m_speed;
		m_Velocity.z -= cos(m_Rotation.x)*m_speed;
	}

	if (CInput::GetKeyPress('Z'))
		m_Velocity.y -= 0.1f;
	if (CInput::GetKeyPress('C'))
		m_Velocity.y += 0.1f;

	//カーソルから玉飛ばしたい
	if (CInput::GetKeyPress('U'))
	{
		CCARSOR* carsor = CManager::GetScene()->GetGameObject<CCARSOR>(1);
	}

	m_Position += m_Velocity;
	m_Target += m_Velocity;

	//m_Rotation.x += CInput::GetMousedDfference().x / 100;
	//m_Rotation.z -= CInput::GetMousedDfference().y / 100;
}
void CCamera::Draw()
{
	//ビューマトリクス設定
	D3DXMatrixLookAtLH(&viewMatrix,&m_Position,&m_Target,&D3DXVECTOR3(0.0f,1.0f,0.0f));

	CRenderer::SetViewMatrix(&viewMatrix);		//Direct9のSetTransformに近い

	//プロジェクションマトリクス設定
	D3DXMatrixPerspectiveFovLH(&projectionMatrix,1.0f,(float)SCREEN_WIDTH/SCREEN_HEIGHT,1.0f,1000.0f);

	CRenderer::SetProjectionMatrix(&projectionMatrix);
}