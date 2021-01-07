#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "gameobject.h"
#include "model.h"
#include "sight.h"

void CSIGHT::Init()
{
	m_Position = D3DXVECTOR3(0, 0, 0);
	m_Rotation = D3DXVECTOR3(0, 0, 0);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

}
void CSIGHT::Uninit()
{
	m_Position = D3DXVECTOR3(0, 0, 0);
}
void CSIGHT::Update()
{
	//座標の更新
	m_Position = m_parent->GetPosition();

	m_Position.x = m_Position.x - 8.0f * cos(m_parent->GetRotation().x)*cos(m_parent->GetRotation().z);	//座標
	m_Position.y = (m_Position.y+1.0f) - 8.0f * sin(m_parent->GetRotation().z);
	m_Position.z = m_Position.z - 8.0f *-sin(m_parent->GetRotation().x)*cos(m_parent->GetRotation().z);	//座標
}
void CSIGHT::Draw()
{

}