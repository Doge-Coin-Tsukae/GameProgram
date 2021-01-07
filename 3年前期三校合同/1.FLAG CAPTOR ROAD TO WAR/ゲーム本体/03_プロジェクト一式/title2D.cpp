//=====================================
//
//  タイトルで使う2Dポリゴンをまとめる
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "polygon.h"
#include "title2D.h"

void CTITLE2D::Init()
{
	//ゲームタイトル表示
	Gamename = new CPolygon;
	Gamename->SetTexture((char*)"asset/texture/title.png");
	Gamename->SetSize(200, 600);
	Gamename->Init(D3DXVECTOR3(200, 0, 0));

	//スペースボタンクリックを表示
	Choose = new CPolygon;
	Choose->SetTexture((char*)"asset/texture/choose.png");
	Choose->SetSize(300, 800);
	Choose->Init(D3DXVECTOR3(100, 200, 0));
}
void CTITLE2D::Uninit()
{
	Choose->Uninit();
	delete Choose;

	Gamename->Uninit();
	delete Gamename;
}
void CTITLE2D::Update()
{
	Gamename->Update();
	Choose->Update();
}
void CTITLE2D::Draw()
{
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);

	Gamename->Draw();
	Choose->Draw();
}