//=====================================
//
//  武器
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "Vector.h"
#include "scene.h"
#include "smoke.h"
#include "model.h"
#include "human.h"
#include "colider.h"
#include "weapon.h"
#include "bullet.h"

#define RELOADTIME 240

class CModel* CWEAPON::m_Model;

void CWEAPON::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\rifl.obj");
}
void CWEAPON::UnLoad()
{
	m_Model->Unload();
	delete m_Model;
}
void CWEAPON::Init()
{
	m_Position = D3DXVECTOR3(0, 1, 0);
	m_Rotation = D3DXVECTOR3(0, 0, 0);
	m_Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	MaxAmmo = 5;
	Ammo = MaxAmmo;
	isReload = false;
	isNextShoot = false;
	ReloadTime = 0;
	NextShootTime = 0;
}
void CWEAPON::Uninit()
{

}
void CWEAPON::Update()
{
	//座標の更新
	m_Position = m_parent->GetPosition();
	m_Position.x = m_Position.x - 1.0f * cos(m_parent->GetRotation().x)*cos(m_parent->GetRotation().z);	//座標
	m_Position.y += 2.8f;
	m_Position.z = m_Position.z - 1.0f *-sin(m_parent->GetRotation().x)*cos(m_parent->GetRotation().z);	//座標
	m_Rotation = m_parent->GetRotation();
	m_Rotation.x += 0.3f;

	//装填中
	if (isReload == true)
	{
		if (ReloadTime <= 0)
		{
			Ammo = MaxAmmo;
			isReload = false;
			ReloadTime = 0;
		}
		ReloadTime--;
	}

	//次撃てるまでの時間
	if (isNextShoot == true)
	{
		if (NextShootTime <= 0)
		{
			PlaySound(SOUND_SE_RELOAD);
			isNextShoot = false;
			NextShootTime = 0;
			return;
		}
		NextShootTime--;
	}
}
void CWEAPON::Draw()
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

void CWEAPON::Shoot(D3DXVECTOR3 SPos, TEAM_NUMBER SetTeamNumber)
{
	if (Ammo <= 0) 
	{ 
		Reload();		//今回に限りオートリロード
		return; 
	}	//弾が0になったとき
	if (isNextShoot == false)
	{
		Ammo -= 1;		//弾の消費
		NextShoot();	//次の弾発射

		CScene* scene = CManager::GetScene();
		scene->AddGameObject<CBullet>(1)->Set(m_Position, SPos, SetTeamNumber);	//弾の発射
		scene->AddGameObject<CSMOKE>(3)->SetPosition(m_Position);	//煙
		PlaySound(SOUND_SE_SE001);
	}
}

void CWEAPON::NextShoot()
{
	NextShootTime = 80;		//次、弾発射できるまでの時間をセット(武器によって変える)
	isNextShoot = true;		//フラグを建てる
}

void CWEAPON::Reload()
{
	if (isReload == true) return;
	Ammo = 0;
	ReloadTime = RELOADTIME;		//装填が終わる時間をセット(武器によって変える)
	isReload = true;				//フラグを建てる
	PlaySound(SOUND_SE_RELOAD2);	//リロード音
}