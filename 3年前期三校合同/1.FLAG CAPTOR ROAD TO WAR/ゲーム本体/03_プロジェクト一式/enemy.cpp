//****************************************
//敵
//****************************************

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "scene.h"

#include "human.h"
#include "Vector.h"
#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "meshfield.h"
#include "enemy.h"

//class CAnimationModel* CEnemy::m_Animodel;

#define		ANIMEBLENDSPEED	0.1f

typedef struct
{
	char *pFilename;	// ファイル名
} ANIMENAME2;

ANIMENAME2 g_aParam2[5] =
{
	{(char *)"idle"},				// 待機
	{(char *)"ready"},				// 構える
	{(char *)"run"},				// 走る
	{(char *)"fire"},				//発射
	{(char *)"Death"},
};

void CEnemy::Load()
{
	
}

void CEnemy::Unload()
{


}

void CEnemy::Init()
{
	m_Animodel = new CAnimationModel();
	m_Animodel->Load("asset\\model\\player\\chara.fbx");					//モデルのロード(ボーン付き)
	m_Animodel->LoadAnimation("asset\\model\\player\\idle.fbx", g_aParam2[0].pFilename);		//アニメーション
	m_Animodel->LoadAnimation("asset\\model\\player\\ready.fbx", g_aParam2[1].pFilename);		//アニメーション
	m_Animodel->LoadAnimation("asset\\model\\player\\run.fbx", g_aParam2[2].pFilename);		//アニメーション
	m_Animodel->LoadAnimation("asset\\model\\player\\fire.fbx", g_aParam2[3].pFilename);
	m_Animodel->LoadAnimation("asset\\model\\player\\Death.fbx", g_aParam2[4].pFilename);

	m_Sight = new CSIGHT();
	m_Sight->Init();
	m_Sight->Setparent(this);		//照準の親を自分に

	m_Weapon = new CWEAPON();
	m_Weapon->Init();
	m_Weapon->Setparent(this);		//武器の親を自分に

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_ModelRot = D3DXVECTOR3(1.6f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.3f, 1.3f, 1.3f);
	m_TeamNumber = TEAM_ENEMY;		//チーム設定

	//アニメーション
	m_NowAnimationChara = g_aParam2[0].pFilename;
	m_OldAnimationChara = g_aParam2[1].pFilename;
	m_Frame = 0;
	rate = 0;
}

void CEnemy::Uninit()
{
	m_Weapon->Uninit();
	delete m_Weapon;

	m_Sight->Uninit();
	delete m_Sight;

	m_Animodel->Unload();
	delete m_Animodel;
}

void CEnemy::Update()
{
	rate = std::min(rate, 1.0f);
	rate = std::max(rate, 0.0f);

	//ヘルパー関数
	Update_AI();
	//プレイヤーに入っているクラスの更新処理
	m_Sight->Update();
	m_Weapon->Update();
	m_Animodel->Update(m_OldAnimationChara, m_NowAnimationChara, m_Frame, rate);

	rate += ANIMEBLENDSPEED;
	m_Frame++;

	//メッシュフィールド高さ取得
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);
}

void CEnemy::Update_AI()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	//当たり判定
	D3DXVECTOR3 direction = m_Position - pPlayer->GetPosition();
	float length = D3DXVec3Length(&direction);

	LookPlayer();

	//範囲内になったら接近する
	if (length < 100.0f)
	{
		if (length > 50.0f)
		{
			D3DXVECTOR3 Velocity = GetVector(m_Position, pPlayer->GetPosition());
			m_Position += Velocity / 10;
			ChangeAnimation((char*)"run");
		}
		else
		{
			m_Weapon->Shoot(m_Sight->GetPosition(), m_TeamNumber);
			ChangeAnimation((char*)"fire");
		}
	}
	else
	{
		ChangeAnimation((char*)"idle");
	}

	if (m_Weapon->GetAmmo() <= 0)
	{
		m_Weapon->Reload();
	}
}

void CEnemy::Draw()
{
	m_Weapon->Draw();
	m_Sight->Draw();

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	//拡大縮小のマトリクス
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//ヨーピッチロールのマトリクス
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x + m_ModelRot.x, -m_Rotation.z - m_ModelRot.z, m_Rotation.y + m_ModelRot.y);
	//位置マトリクス6
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Animodel->Draw();
}

void CEnemy::LookPlayer()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	D3DXVECTOR3 Velocity = GetVector(m_Position, pPlayer->GetPosition());
	D3DXVECTOR3 Velocity2 = GetVector(m_Position,m_Sight->GetPosition());
	m_Rotation.x += (Velocity.x * Velocity2.x+ Velocity.z*Velocity2.z) / (sqrt((Velocity.x*Velocity.x) + (Velocity.z*Velocity.z))*sqrt((Velocity2.x*Velocity2.x) + (Velocity2.z*Velocity2.z)));
	m_Rotation.x -= 1.0f;
}

void CEnemy::ChangeAnimation(char* Name)
{
	if (m_NowAnimationChara == Name)return;	//今のアニメーションと次のアニメーションが一緒なら
	m_OldAnimationChara = m_NowAnimationChara;		//新しいアニメーションデータを古いアニメーションデータにする
	m_NowAnimationChara = Name;						//新しいアニメーションデータを入れる
	rate = 0.0f;									//ブレンド値をリセット
}

void CEnemy::Load(FILE* fp, int line)
{
	for (int i = 0; i < line * 3; i++)
	{
		fscanf(fp, "");
	}

	fscanf(fp, "%f%f%f", &m_Position.x, &m_Position.y, &m_Position.z);
	fscanf(fp, "%f%f%f", &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
	fscanf(fp, "%f%f%f", &m_Scale.x, &m_Scale.y, &m_Scale.z);
}