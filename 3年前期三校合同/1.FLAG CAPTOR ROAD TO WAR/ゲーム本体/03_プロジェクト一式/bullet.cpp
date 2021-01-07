//=====================================
//
//  キャラクターが発射する弾
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "Vector.h"
#include "sound.h"
#include "model.h"
#include "explosion.h"
#include "human.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "enemy.h"
#include "player.h"
#include "bullet.h"
#include "bunker.h"
class CModel* CBullet::m_Model;

void CBullet::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\bullet.obj");
}

void CBullet::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CBullet::Init()
{
	DeleteTime = 8.0f;
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Zone = new CCOLIDER_CIRCLE();
	m_Zone->Init();
	m_Zone->SetScale(D3DXVECTOR3(3.0f, 3.0f,3.0f));
}

void CBullet::Uninit()
{
	m_Zone->Uninit();
	delete m_Zone;
}

void CBullet::Update()
{
	Update_Varios();

	//時間が0になったら削除
	if (DeleteTime <=0.0f)
	{
		SetDestroy();
		return;
	}
	//ヘルパー関数
	Update_Collision();
}

void CBullet::Update_Varios()
{
	m_Position += m_Dir * 5.0f;
	DeleteTime -= 0.1f;
}

void CBullet::Update_Collision()
{
	//当たり判定更新
	m_Zone->Update();
	m_Zone->SetPosition(m_Position);

	CScene* scene = CManager::GetScene();
	std::vector<CEnemy*> enemyList = scene->GetGameObjects<CEnemy>(1);
	std::vector<CBUNKER*> pBunker = scene->GetGameObjects<CBUNKER>(1);
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	AABB Bulletaabb;	//一時的に召喚
	Bulletaabb.Init(m_Position + D3DXVECTOR3(-1.0f, -1.0f, -1.0f), m_Position + D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_Position);

	//壁に激突
	for (CBUNKER* Bunker : pBunker)
	{
		if (intersectAABB(Bunker->GetColider(), Bulletaabb) == true)
		{
			SetDestroy();
			return;
		}
	}

	//弾が味方の物だった時
	if (m_TeamNumber == TEAM_FRIENDRY)
	{
		for (CEnemy* enemy : enemyList)
		{	//弾と敵の当たり判定
			if (m_Zone->GetColider(enemy->GetPosition()))
			{
				scene->AddGameObject<CExplosion>(2)->SetPosition(m_Position);	//画面に表示させる
				enemy->SetDestroy();
				PlaySound(SOUND_SE_DEATH);
				SetDestroy();
				return;
			}
		}
	}

	//弾が敵の物だった場合
	if (m_TeamNumber == TEAM_ENEMY)
	{
			if (m_Zone->GetColider(pPlayer->GetPosition()))
			{
				pPlayer->Damage();
				SetDestroy();
				return;
			}
	}
}

void CBullet::Draw()
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

	m_Model->Draw();
}

void  CBullet::Set(D3DXVECTOR3 SetPos, D3DXVECTOR3 SetSight,TEAM_NUMBER SetNUMBER)
{
	m_Position = SetPos;
	m_Dir = GetVector(SetPos,SetSight);
	m_TeamNumber = SetNUMBER;
}