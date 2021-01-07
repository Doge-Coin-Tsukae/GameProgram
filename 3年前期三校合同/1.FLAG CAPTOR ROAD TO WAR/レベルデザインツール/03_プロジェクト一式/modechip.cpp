#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "polygon.h"
#include "modechip.h"

void CMODECHIP::Init()
{
	m_polygon = new CMovePolygon;
	m_polygon->Init();
}
void CMODECHIP::Uninit()
{
	m_polygon->Uninit();
	delete m_polygon;
}
void CMODECHIP::Update()
{
	m_polygon->Update();
}
void CMODECHIP::Draw()
{
	if (m_SelectMode == true)
	m_polygon->Draw();
}

void CMODECHIP::SetPolygon(char* name, D3DXVECTOR2 Size)
{
	m_Size = Size;

	m_polygon->SetSize(m_Size.y, m_Size.x);
	m_polygon->SetTexture(name);
	m_polygon->SetPosition(m_Position);
}

void CMODECHIP::SetMode()
{
	if (m_SelectMode == false)
	{
		m_SelectMode = true;

	}
	else
	{
		m_SelectMode = false;
	}


}

bool CMODECHIP::Colision(POINT pos)
{
	if (m_Position.x > pos.x)return false;
	if (m_Position.x + m_Size.x < pos.x)return false;
	if (m_Position.y > pos.y)return false;
	if (m_Position.y + m_Size.y < pos.y)return false;

	return true;
}