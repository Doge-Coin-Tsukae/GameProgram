//
//家オブジェクト
//
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "scene.h"

#include "colider.h"
#include "house.h"

class CModel* CHOUSE::m_Model;

void CHOUSE::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\bunker.obj");
}

void CHOUSE::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CHOUSE::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Colider.Init(m_Position + D3DXVECTOR3(-8.0f, 0.0f, -8.0f), m_Position + D3DXVECTOR3(8.0f, 2.0f, 8.0f), m_Position);
}

void CHOUSE::Uninit()
{
}
void CHOUSE::Update()
{
	m_Colider.update(m_Position);
}
void CHOUSE::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	//拡大縮小のマトリクス
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//ヨーピッチロールのマトリクス
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//位置マトリクス
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();
}