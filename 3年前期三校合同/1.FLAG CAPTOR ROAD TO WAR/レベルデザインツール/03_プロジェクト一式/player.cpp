//****************************************
//プレイヤー
//****************************************

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Vector.h"
#include "scene.h"
#include "meshfield.h"
#include "input.h"
#include "human.h"
#include "model.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "bunker.h"

#define		NORMALSPEED 0.5f
#define		SLOWSPEED	0.1f

void CPlayer::Init()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\ningen.obj");

	m_Sight = new CSIGHT();
	m_Sight->Init();
	m_Sight->Setparent(this);	//照準の親を自分に

	m_Weapon = new CWEAPON();
	m_Weapon->Init();
	m_Weapon->Setparent(this);

	m_Colider.Init(m_Position + D3DXVECTOR3(-1.0f, 0.0f, -1.0f), m_Position + D3DXVECTOR3(1.0f, 2.0f, 1.0f), m_Position);

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Velocity = m_Position;
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_speed = 0.5f;
	m_TeamNumber = TEAM_FRIENDRY;	//チーム編集
	m_Death = false;
	m_Hp = 100;

	//メッシュフィールド高さ取得
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

}

void CPlayer::Uninit()
{

	m_Weapon->Uninit();
	delete m_Weapon;

	m_Sight->Uninit();
	delete m_Sight;

	m_Model->Unload();
	delete m_Model;
}

void CPlayer::Update()
{
	//ヘルパー関数の更新
	//Update_Controll();

	//上限加減チェック
	//m_Rotation.z = min(m_Rotation.z, 0.0f);
	//m_Rotation.z = max(m_Rotation.z, -0.5f);

	//プレイヤーに入っているクラスの更新処理
	//m_Sight->Update();
	//m_Weapon->Update();
	//m_Colider.update(m_Velocity);

	//当たり判定処理
	//CScene* scene = CManager::GetScene();
	//std::vector<CBUNKER*> bunkerList = scene->GetGameObjects<CBUNKER>(1);
	//for (CBUNKER* bunker : bunkerList)
	//{
		//if (intersectAABB(m_Colider, bunker->GetColider()))
		//{
			//m_Velocity = m_Position;
		//}
	//}

	//座標を更新
	//m_Position = m_Velocity;

	//体力が0以下になったとき
	//if (m_Hp <= 0)
	//{
		//Death();
	//}

	//銃を撃っているときは速度を減速させる
	//if (m_Weapon->GetNextShoot() ==true)
	//{
		//m_speed = SLOWSPEED;
	//}
	//else
	//{
		//m_speed = NORMALSPEED;
	//}

	//メッシュフィールド高さ取得
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

}

void CPlayer::Update_Controll()
{
	//キー入力で移動
	if (CInput::GetKeyPress('A'))
	{
		m_Velocity.x -= sin(m_Rotation.x)*m_speed;
		m_Velocity.z -= cos(m_Rotation.x)*m_speed;
	}
	if (CInput::GetKeyPress('D'))
	{
		m_Velocity.x += sin(m_Rotation.x)*m_speed;
		m_Velocity.z += cos(m_Rotation.x)*m_speed;
	}
	if (CInput::GetKeyPress('W'))
	{
		m_Velocity.z += sin(m_Rotation.x)*m_speed;
		m_Velocity.x -= cos(m_Rotation.x)*m_speed;
	}
	if (CInput::GetKeyPress('S'))
	{
		m_Velocity.z -= sin(m_Rotation.x)*m_speed;
		m_Velocity.x += cos(m_Rotation.x)*m_speed;
	}
	if (CInput::GetKeyPress('Q'))
		m_Rotation.x -= 0.1f;
	if (CInput::GetKeyPress('E'))
		m_Rotation.x += 0.1f;

	if (CInput::GetKeyPress('Z'))
		m_Rotation.z -= 0.1f;
	if (CInput::GetKeyPress('C'))
		m_Rotation.z += 0.1f;

	if (CInput::GetKeyTrigger('R'))
		m_Weapon->Reload();

	m_Rotation.x += CInput::GetMousedDfference().x / 100;
	m_Rotation.z -= CInput::GetMousedDfference().y / 100;
	//弾発射
	if (CInput::GetKeyPress(VK_LBUTTON))
	{	//マウスが右クリックされた時
		m_Weapon->Shoot(m_Position,m_Sight->GetPosition(),m_TeamNumber);	//武器から発射する
	}
}
void CPlayer::Draw()
{
	m_Weapon->Draw();
	m_Sight->Draw();

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

void CPlayer::Death()
{
	m_Death = true;
	m_Hp = 0;
}

void CPlayer::Damage()
{
	m_Hp -= 10;	//ダメージを入れる
}

void CPlayer::Save(FILE* fp)
{
	//座標
	fprintf(fp, "%f ", m_Position.x);
	fprintf(fp, "%f ", m_Position.y);
	fprintf(fp, "%f\n", m_Position.z);
	//角度
	fprintf(fp, "%f ", m_Rotation.x);
	fprintf(fp, "%f ", m_Rotation.y);
	fprintf(fp, "%f\n", m_Rotation.z);
	//大きさ
	fprintf(fp, "%f ", m_Scale.x);
	fprintf(fp, "%f ", m_Scale.y);
	fprintf(fp, "%f\n", m_Scale.z);

	fputs("end\n", fp);
}

void CPlayer::Load(FILE* fp)
{
	fscanf(fp,"%f%f%f", &m_Position.x, &m_Position.y, &m_Position.z);
	fscanf(fp, "%f%f%f", &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
	fscanf(fp, "%f%f%f", &m_Scale.x, &m_Scale.y, &m_Scale.z);
}