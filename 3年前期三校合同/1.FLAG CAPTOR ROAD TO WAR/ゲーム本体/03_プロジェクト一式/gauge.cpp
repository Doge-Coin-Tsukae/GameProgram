//=====================================
//
//  画面にゲージを表示する
//  written by Y.Okubo
//
//=====================================

#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "polygon.h"
#include "human.h"
#include "animationmodel.h"
#include "model.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "gauge.h"

void CGAUGE::Init()
{
	Lower = new CMovePolygon;
	Lower->Init();
	Lower->SetTexture((char*)"asset/texture/gauge/gaugebox.png");
	
	Gauge = new CMovePolygon;
	Gauge->Init();
	Gauge->SetTexture((char*)"asset/texture/gauge/gauge.png");
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
	//位置変更
	Lower->SetSize(8, 204);
	Lower->Update();
;
	//画像サイズの変更
	Gauge->SetSize(8, m_Gauge);
	Gauge->Update();
}

void CGAUGE::Draw()
{
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);

	Lower->Draw();
	Gauge->Draw();
}