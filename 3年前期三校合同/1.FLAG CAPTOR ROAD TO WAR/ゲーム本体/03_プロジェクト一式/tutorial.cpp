//=====================================
//
//  チュートリアルシーン
//  written by Y.Okubo
//
//=====================================
#include <list>
#include <vector>
#include <typeinfo>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"
#include "scene.h"
#include "fade.h"
#include "gamemaneger.h"
#include "Game.h"
#include "tutorial.h"

#include "gameobject.h"
#include "camera.h"
#include "field.h"
#include "meshfield.h"
#include "human.h"
#include "model.h"
#include "animationmodel.h"
#include "colider.h"
#include "sight.h"
#include "weapon.h"

#include "player.h"
#include "enemy.h"
#include "enemycommander.h"
#include "bullet.h"
#include "bunker.h"
#include "polygon.h"
#include "skydome.h"
#include "base.h"
#include "deadtree.h"

#include "explosion.h"
#include "smoke.h"
#include "tree.h"
#include "number.h"
#include "gauge.h"
#include "weapon2d.h"
#include "captureui.h"
#include "playerui.h"
#include "tutorial2D.h"

void CTutorial::Init()
{
	m_Clik = false;

	//テクスチャ + モデルロード
	CBullet::Load();	//弾のモデルを呼び出す
	CWEAPON::Load();	//銃のモデルを呼び出す
	CSMOKE::Load();		//煙の画像を呼び出す

	m_GameManeger = new CGAME_MANEGER;		//ゲームマネージャ召喚
	m_GameManeger->Init(GAME_RULE_TUTORIAL);

	//使うゲームオブジェクト呼び出し
	//カメラ0番 3Dモデル1番 3Dモデル(当たり判定のやつ)2番 2Dモデル3番
	AddGameObject<CCamera>(0);

	AddGameObject<CSKYDOME>(1);

	//地面
	AddGameObject<CMeshField>(1)->flatworld();

	AddGameObject<CPlayer>(1)->SetPosition(D3DXVECTOR3(350.0f, 1.0f,  -200.0f));

	AddGameObject<CBASE>(2)->SetPosition(D3DXVECTOR3(300.0f, 0.0f,-200.0f));

	AddGameObject<CWEAPON2D>(4);
	AddGameObject<CPLAYERUI>(4);

	//PlaySound(SOUND_BGM_BGM000);

	CFADE::Fade_Start(false, 60, D3DCOLOR());
}

void CTutorial::Uninit()
{
	//リストに入っているゲームオブジェクトを削除
	CScene::Uninit();

	//テクスチャアンロード
	CSMOKE::Unload();
	CWEAPON::UnLoad();
	CBullet::Unload();

	m_GameManeger->Uninit();
	delete m_GameManeger;

	StopSound();		//音楽止める
}

void CTutorial::Update()
{
	CScene::Update();	//リストに入っているゲームオブジェクトを呼び出す

	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		m_Clik = true;
		CFADE::SetTexture((char*)"asset/texture/fade.png");
		CFADE::Fade_Start(true, 60, D3DCOLOR());
	}

	m_GameManeger->Update();

	if (m_Clik == false) { return; }
	if (CFADE::Fade_IsFade() == false)
	{
		CManager::SetScene<CGame>();
	}
}