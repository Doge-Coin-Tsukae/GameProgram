#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "polygon.h"
#include "human.h"
#include "model.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "gauge.h"

void CGAUGE::Init()
{
	Lower = new CPolygon;
	Lower->SetSize(8, 200);
	Lower->Init(D3DXVECTOR3(0.0f,530.0f,0.0f));
	Lower->SetTexture((char*)"asset/texture/gauge/gaugebox.png");
	
	Gauge = new CMovePolygon;
	Gauge->Init();
	Gauge->SetTexture((char*)"asset/texture/gauge/gauge.png");
	Gauge->SetPosition(D3DXVECTOR3(2.0f, 530.0f, 0.0f));
}

void CGAUGE::Uninit()
{
	Gauge->Uninit();
	delete Gauge;
	Lower->Uninit();
	delete Lower;
}

void CGAUGE::Update()
{
	Lower->Update();

	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
	CWEAPON* pWeapon = pPlayer->GetWeapon();

	//画像サイズの変更
	Gauge->SetSize(8.0f, 196.0f - 1.0f* pWeapon->GetReloadTime());
	Gauge->Update();
}

void CGAUGE::Draw()
{
	Lower->Draw();
	Gauge->Draw();
}