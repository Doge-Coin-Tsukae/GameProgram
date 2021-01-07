//=====================================
//
//  ����
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
	//���W�̍X�V
	m_Position = m_parent->GetPosition();
	m_Position.x = m_Position.x - 1.0f * cos(m_parent->GetRotation().x)*cos(m_parent->GetRotation().z);	//���W
	m_Position.y += 2.8f;
	m_Position.z = m_Position.z - 1.0f *-sin(m_parent->GetRotation().x)*cos(m_parent->GetRotation().z);	//���W
	m_Rotation = m_parent->GetRotation();
	m_Rotation.x += 0.3f;

	//���U��
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

	//�����Ă�܂ł̎���
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
	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	//�g��k���̃}�g���N�X
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//���[�s�b�`���[���̃}�g���N�X
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//�ʒu�}�g���N�X
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();
}

void CWEAPON::Shoot(D3DXVECTOR3 SPos, TEAM_NUMBER SetTeamNumber)
{
	if (Ammo <= 0) 
	{ 
		Reload();		//����Ɍ���I�[�g�����[�h
		return; 
	}	//�e��0�ɂȂ����Ƃ�
	if (isNextShoot == false)
	{
		Ammo -= 1;		//�e�̏���
		NextShoot();	//���̒e����

		CScene* scene = CManager::GetScene();
		scene->AddGameObject<CBullet>(1)->Set(m_Position, SPos, SetTeamNumber);	//�e�̔���
		scene->AddGameObject<CSMOKE>(3)->SetPosition(m_Position);	//��
		PlaySound(SOUND_SE_SE001);
	}
}

void CWEAPON::NextShoot()
{
	NextShootTime = 80;		//���A�e���˂ł���܂ł̎��Ԃ��Z�b�g(����ɂ���ĕς���)
	isNextShoot = true;		//�t���O�����Ă�
}

void CWEAPON::Reload()
{
	if (isReload == true) return;
	Ammo = 0;
	ReloadTime = RELOADTIME;		//���U���I��鎞�Ԃ��Z�b�g(����ɂ���ĕς���)
	isReload = true;				//�t���O�����Ă�
	PlaySound(SOUND_SE_RELOAD2);	//�����[�h��
}