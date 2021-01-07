//=====================================
//
//  �`���[�g���A���Ŏg��2D�|���S�����܂Ƃ߂�
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "polygon.h"
#include "tutorial2D.h"

void CTUTORIAL2D::Init()
{
	Gamename = new CPolygon;
	Gamename->SetSize(200,200);			//�T�C�Y�w��
	Gamename->SetTexture((char*) "asset/texture/tutorial/tutorial_move.png");	//�e�N�X�`���w��
	Gamename->Init(D3DXVECTOR3(0.0f,100.0f,0.0f));		//��������(���W�w��)
}
void CTUTORIAL2D::Uninit()
{
	Gamename->Uninit();
	delete Gamename;
}
void CTUTORIAL2D::Update()
{
	Gamename->Update();
}
void CTUTORIAL2D::Draw()
{
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);

	Gamename->Draw();
}
void CTUTORIAL2D::ChangeTexture(char* SetTextureName)
{
	Gamename->SetTexture(SetTextureName);
}