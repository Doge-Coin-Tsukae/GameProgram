//=====================================
//
//  ゲームシーン
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
#include "Result.h"

#include "gameobject.h"
#include "load.h"
#include "camera.h"
#include "field.h"
#include "meshfield.h"
#include "animationmodel.h"
#include "human.h"
#include "model.h"
#include "colider.h"
#include "sight.h"
#include "weapon.h"

#include "player.h"
#include "enemy.h"
#include "friend.h"
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

void CGame::Init()
{
	//テクスチャ + モデルロード
	CBullet::Load();	//弾のモデルを呼び出す
	CBUNKER::Load();	//バンカーのモデルを呼び出す
	CEnemy::Load();		//敵のモデルを呼び出す
	CFriend::Load();
	CWEAPON::Load();	//銃のモデルを呼び出す
	CDEADTREE::Load();	//枯れ木のモデルを呼び出す
	CSMOKE::Load();		//煙の画像を呼び出す

	CLOAD *m_Load = new CLOAD;

	m_GameManeger = new CGAME_MANEGER;
	m_GameManeger->Init(GAME_RULE_CONQUEST);

	//使うゲームオブジェクト呼び出し
	//カメラ0番 3Dモデル1番 3Dモデル(当たり判定のやつ)2番 ビルボード(煙)の3番 2Dモデル4番
	AddGameObject<CCamera>(0);		//カメラ

	AddGameObject<CSKYDOME>(1);		//スカイドーム
	AddGameObject<CMeshField>(1);	//地面

	AddGameObject<CWEAPON2D>(4);
	AddGameObject<CPLAYERUI>(4);
	AddGameObject<CENEMY_COMMANDER>(4);

	m_Load->Data_Load();	//データのロード

	//PlaySound(SOUND_BGM_BGM002);

	CFADE::SetTexture((char*)"asset/texture/fade.png");
	CFADE::Fade_Start(false,60,D3DCOLOR());
}

void CGame::Uninit()
{
	//リストに入っているゲームオブジェクトを削除
	CScene::Uninit();

	//テクスチャアンロード
	CDEADTREE::Unload();
	CSMOKE::Unload();
	CWEAPON::UnLoad();
	CEnemy::Unload();
	CBUNKER::Unload();
	CBullet::Unload();

	m_GameManeger->Uninit();
	delete m_GameManeger;

	StopSound();
}

void CGame::Update()
{
	CScene::Update();	//リストに入っているゲームオブジェクトを呼び出す

	m_GameManeger->Update();
}