//=====================================
//
//  拠点を占領したときに画面に表示させる + 拠点を占領中に表示させる
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "camera.h"
#include "polygon.h"
#include "gauge.h"

#include "human.h"
#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"

#include "playerui.h"

void CPLAYERUI::Init()
{
	m_HpGauge = new CGAUGE;
	m_HpGauge->Init();
	m_HpGauge->SetPosition(D3DXVECTOR3(1, 1, 0));

	m_Sight = new CPolygon;
	m_Sight->SetTexture((char*)"asset/texture/sight.png");
	m_Sight->SetSize(32,32);
	m_Sight->Init(D3DXVECTOR3(SCREEN_WIDTH / 2.07f, SCREEN_HEIGHT / 1.45f, 0.0f));
}
void CPLAYERUI::Uninit()
{
	m_Sight->Uninit();
	delete m_Sight;

	m_HpGauge->Uninit();
	delete m_HpGauge;
}
void CPLAYERUI::Update()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	m_HpGauge->SetGauge(pPlayer->Getm_Hp()*2);		//ゲージの残量表示(最大200)
	m_HpGauge->Update();

	m_Sight->Update();
}
void CPLAYERUI::Draw()
{
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);

	m_HpGauge->Draw();

	CScene* scene = CManager::GetScene();
	CCamera* pcamera = scene->GetGameObject<CCamera>(0);
	//カメラをzoomしている時のみ表示
	if(pcamera->GetZoom())
	m_Sight->Draw();
}