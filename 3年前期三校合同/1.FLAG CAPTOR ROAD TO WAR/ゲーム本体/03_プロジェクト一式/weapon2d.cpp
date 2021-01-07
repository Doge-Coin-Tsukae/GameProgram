#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "human.h"

#include "polygon.h"
#include "gauge.h"
#include "number.h"
#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "weapon2d.h"

void CWEAPON2D::Init()
{
	m_Under = new CPolygon;
	m_Under->SetSize(100,200);
	m_Under->Init(D3DXVECTOR3(0.0f, 380.0f, 0.0f));
	m_Under->SetTexture((char*)"asset/texture/rifle.png");

	m_MaxAnmo = new CNUMBER;
	m_MaxAnmo->Init();

	m_Anmo = new CNUMBER;
	m_Anmo->Init();

	m_Gauge = new CGAUGE;
	m_Gauge->Init();
	m_Gauge->SetPosition(D3DXVECTOR3(0.0f,530.0f,0.0f));

	m_MaxAnmo->SetPosition(D3DXVECTOR3(100.0f, 480.0f, 0.0f));
	m_Anmo->SetPosition(D3DXVECTOR3(50.0f,480.0f,0.0f));

	m_MaxAnmo->SetLength(50.0f);
	m_Anmo->SetLength(50.0f);
}

void CWEAPON2D::Uninit()
{
	m_Gauge->Uninit();
	delete m_Gauge;
	m_Anmo->Uninit();
	delete m_Anmo;
	m_MaxAnmo->Uninit();
	delete m_MaxAnmo;
	m_Under->Uninit();
	delete m_Under;
}

void CWEAPON2D::Update()
{
	m_Under->Update();
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
	CWEAPON* pWeapon = pPlayer->GetWeapon();

	//値のセット
	m_MaxAnmo->SetNumber(pWeapon->GetMaxAmmo());
	m_Anmo->SetNumber(pWeapon->GetAmmo());

	int MaxGauge = 200 - pWeapon->GetReloadTime();
	m_Gauge->SetGauge(MaxGauge);
	m_Gauge->Update();
}

void CWEAPON2D::Draw()
{
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);

	m_Under->Draw();
	m_MaxAnmo->Draw();
	m_Anmo->Draw();
	m_Gauge->Draw();
}