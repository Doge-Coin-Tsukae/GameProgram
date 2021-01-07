//=====================================
//
//  勝敗の表示させる
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"

#include "polygon.h"
#include "vicordef.h"

void VICORDEF::Init()
{
	//必ずセットを使うこと
}

void VICORDEF::Uninit()
{
	Serif->Uninit();
	delete Serif;
}
void VICORDEF::Update()
{
	Serif->Update();
	DeleteTime--;

	//時間が過ぎたら
	if (DeleteTime <= 0)
	{
		Delete = true;
	}
}
void VICORDEF::Draw()
{
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);

	Serif->Draw();
}
void VICORDEF::Set(bool Sets)
{
	Serif = new CPolygon;
	if (Sets == true)
	{
		Serif->SetTexture((char*)"asset/texture/serif/missioncomp.png");
	}
	else
	{
		Serif->SetTexture((char*)"asset/texture/serif/missiondefeat.png");
	}

	Serif->SetSize(100, 500);
	Serif->Init(D3DXVECTOR3(200, 100, 0));
	DeleteTime = 270;
	Delete = false;
}