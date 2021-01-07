//---------------------------------
//
//画面右にオブジェクト一覧を作る
//
//---------------------------------

#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"

#include "input.h"
#include "scene.h"
#include "polygon.h"

#include "selectpointer.h"

void CSelectpointer::Init()
{
	m_point = new CMovePolygon;
	m_point->Init();
	m_point->SetTexture((char*)"asset/texture/selectitem/cursor.png");
	m_point->SetSize(65.0f, 70.0f);

	Pointpos = D3DXVECTOR2(0.0f, 0.0f);
}

void CSelectpointer::Uninit()
{
	m_point->Uninit();
	delete m_point;
}

void CSelectpointer::Update()
{

	//画像の座標設定
	m_point->SetPosition(D3DXVECTOR3(m_Position.x + Pointpos.x * 74.0f, m_Position.y + Pointpos.y * 68.0f, m_Position.z));
	m_point->Update();

}

void CSelectpointer::Draw()
{
	m_point->Draw();
}