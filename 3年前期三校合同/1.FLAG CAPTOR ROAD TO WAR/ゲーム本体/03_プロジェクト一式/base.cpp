//=====================================
//
//拠点オブジェクト(陣取り出来る)
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Vector.h"
#include "gamemaneger.h"
#include "polygon.h"
#include "gauge.h"
#include "game.h"
#include "human.h"
#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "base.h"
#include "captureui.h"


void CBASE::Init()
{
	//自身の変数の設定
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_territory = ENEMY_ZONE;
	m_Gauge = 100;

	//旗の設定
	m_Flag = new CModel();
	m_Flag->Load("asset\\model\\flag.obj");

	//当たり判定の設定
	m_Zone = new CCOLIDER_CIRCLE();
	m_Zone->Init();
	m_Zone->SetScale(D3DXVECTOR3(30.0f, 30.0f, 30.0f));		//判定の大きさ
}

void CBASE::Uninit()
{
	//当たり判定の削除
	m_Zone->Uninit();
	delete m_Zone;

	//旗の削除
	m_Flag->Unload();
	delete m_Flag;
}

void CBASE::Update_Colision()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	if (!pPlayer) return;

	//円の判定
	//プレイヤーが範囲に入ったらゲージを動かす
	if (m_Zone->GetColider(pPlayer->GetPosition()))
	{
		m_Territory_Invarter.x++;	//陣地の勢力数を増やす(友軍)

		if (m_inPlayer == false)
		{
			m_inPlayer = true;
			CScene* scene = CManager::GetScene();
			scene->AddGameObject<CCAPTUREGAUGE>(3)->Setparent(this);		//画面表示用作成+親を自分に
		}
	}
	else
	{
		m_inPlayer = false;
	}
}
void CBASE::Update_Gauge()
{
	//陣地に両軍の部隊が同じ数の時離脱
	if (m_Territory_Invarter.x == m_Territory_Invarter.y) { return; }
	//陣地が友軍の時
	if (m_territory == FRIENDRY_ZONE)
	{	//友軍の数が多い時離脱
		if (m_Territory_Invarter.x > m_Territory_Invarter.y) { return; }
	}
	//陣地が敵軍の時
	if (m_territory == ENEMY_ZONE)
	{	//敵軍の数が多い時離脱
		if (m_Territory_Invarter.x < m_Territory_Invarter.y) { return; }
	}
	m_Gauge--;		//勢力ゲージを減らす
}
void CBASE::Update_Territory()
{
	CScene* scene = CManager::GetScene();
	//勢力地が0ではないとき離脱
	if (m_Gauge > 0) { return; }
	//テリトリーの支配者
	switch (m_territory)
	{//所有者によって切り分ける
	case NONE_ZONE:
		if (m_Territory_Invarter.x > m_Territory_Invarter.y)
		{//友軍の方が多かったら
			m_territory = FRIENDRY_ZONE;
			m_Flag->Load("asset\\model\\flagblue.obj");
			scene->AddGameObject<CCAPTUREUI>(3);	//画面に表示させる
		}
		if (m_Territory_Invarter.x < m_Territory_Invarter.y)
		{//敵軍の方が多かったら
			m_territory = ENEMY_ZONE;
		}
		m_Gauge = 100;
		break;

	case FRIENDRY_ZONE:
		m_territory = NONE_ZONE;	//中立にする
		m_Gauge = 100;				//ゲージ回復
		break;

	case ENEMY_ZONE:
		m_territory = NONE_ZONE;	//中立にする
		m_Gauge = 100;				//ゲージ回復
		break;
	}
}
void CBASE::Update()
{
	m_Zone->SetPosition(m_Position);		//座標の設定
	m_Zone->Update();						//更新処理
	m_Territory_Invarter = D3DXVECTOR2(0, 0);	//侵入者の値リセット

	Update_Colision();		//当たり判定
	Update_Gauge();			//ゲージ処理
	Update_Territory();		//領地の支配者処理
}

void CBASE::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	//拡大縮小のマトリクス
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//ヨーピッチロールのマトリクス
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//位置マトリクス
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Flag->Draw();		//旗の描画
	m_Zone->Draw();		//当たり判定の描画
}

void CBASE::Load(FILE*fp, int line)
{
	for (int i = 0; i < line * 3; i++)
	{
		fscanf(fp, "");
	}

	fscanf(fp, "%f%f%f", &m_Position.x, &m_Position.y, &m_Position.z);
	fscanf(fp, "%f%f%f", &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
	fscanf(fp, "%f%f%f", &m_Scale.x, &m_Scale.y, &m_Scale.z);
}