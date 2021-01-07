#include <list>
#include <vector>
#include <typeinfo>
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "input.h"
#include "scene.h"
#include "gamemaneger.h"
#include "Game.h"

#include "gameobject.h"
#include "save.h"
#include "load.h"
#include "camera.h"
#include "field.h"
#include "meshfield.h"
#include "human.h"
#include "model.h"
#include "carsor.h"
#include "colider.h"
#include "sight.h"
#include "weapon.h"
#include "base.h"
#include "player.h"
#include "enemy.h"
#include "enemycommander.h"
#include "enemyrespornpoint.h"
#include "bunker.h"
#include "polygon.h"
#include "skydome.h"
#include "deadtree.h"

#include "tree.h"
#include "number.h"
#include "gauge.h"
#include "carsor.h"
#include "chip.h"
#include "modechip.h"
#include "selectpointer.h"
#include "saveloadchip.h"
#include "selectitem.h"

void CGame::Init()
{
	//�e�N�X�`�� + ���f�����[�h
	CBUNKER::Load();
	CEnemy::Load();
	CEnemyRespornPoint::Load();
	CWEAPON::Load();
	CDEADTREE::Load();

	m_GameManeger = new CGAME_MANEGER;
	m_GameManeger->Init();

	//�g���Q�[���I�u�W�F�N�g�Ăяo��
	//�J����0�� 3D���f��1�� 2D���f����
	AddGameObject<CCamera>(0);

	AddGameObject<CSAVE>(0);
	AddGameObject<CLOAD>(0);

	AddGameObject<CCARSOR>(1);

	//AddGameObject<CField>(1);
	AddGameObject<CMeshField>(1);

	AddGameObject<CENEMY_COMMANDER>(1);


	AddGameObject<CSelectItem>(2);
	//AddGameObject<CPolygon>(2);
}

void CGame::Uninit()
{
	//���X�g�ɓ����Ă���Q�[���I�u�W�F�N�g���폜
	CScene::Uninit();

	//�e�N�X�`���A�����[�h
	CDEADTREE::Unload();
	CWEAPON::UnLoad();
	CEnemyRespornPoint::Unload();
	CEnemy::Unload();
	CBUNKER::Unload();

	m_GameManeger->Uninit();
	delete m_GameManeger;
}

void CGame::Update()
{
	CScene::Update();	//���X�g�ɓ����Ă���Q�[���I�u�W�F�N�g���Ăяo��

	m_GameManeger->Update();
}

void CGame::Draw()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	CScene::Draw();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}