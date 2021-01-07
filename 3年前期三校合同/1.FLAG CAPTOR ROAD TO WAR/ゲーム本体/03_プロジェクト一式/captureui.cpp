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
#include "polygon.h"
#include "gauge.h"
#include "model.h"
#include "colider.h"
#include "base.h"
#include "captureui.h"

#define DELETE_TIME 240		//削除されるまでの時間

void CCAPTUREUI::Init()
{
	DeleteTime = DELETE_TIME;

	Line = new CPolygon;
	Line->SetSize(50, 300);
	Line->Init(D3DXVECTOR3(SCREEN_WIDTH / 3, 50, 0.0f));
	Line->SetTexture((char*)"asset/texture/serif/capcha.png");
}

void CCAPTUREUI::Uninit()
{
	Line->Uninit();
	delete Line;
}

void CCAPTUREUI::Update()
{
	Line->Update();
	DeleteTime--;
	//時間が0になったとき
	if (DeleteTime <= 0)
	{
		SetDestroy();		//自身を削除する
	}
}

void CCAPTUREUI::Draw()
{
	Line->Draw();
}

void CCAPTUREGAUGE::Init()
{
	m_Gauge = new CGAUGE;
	m_Gauge->Init();
	m_Gauge->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT /2,0));
}

void CCAPTUREGAUGE::Uninit()
{
	m_Gauge->Uninit();
	delete m_Gauge;
}

void CCAPTUREGAUGE::Update()
{
	m_Gauge->SetGauge(m_parent->GetGauge()*2);		//ゲージの残量表示(最大200)
	m_Gauge->Update();

	if (m_parent->GetinPlayer() == false)
	{
		SetDestroy();
	}
}

void CCAPTUREGAUGE::Draw()
{
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);

	m_Gauge->Draw();
}