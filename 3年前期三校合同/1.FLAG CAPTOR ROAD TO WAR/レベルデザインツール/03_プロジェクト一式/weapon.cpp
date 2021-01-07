#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Vector.h"
#include "scene.h"
#include "model.h"
#include "human.h"
#include "colider.h"
#include "weapon.h"

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
	m_Position = D3DXVECTOR3(0, 0, 0);
	m_Rotation = D3DXVECTOR3(0, 0, 0);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

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

void CWEAPON::Shoot(D3DXVECTOR3 Pos, D3DXVECTOR3 SPos,TEAM_NUMBER SetTeamNumber)
{

}

void CWEAPON::NextShoot()
{
	NextShootTime = 50;		//���A�e���˂ł���܂ł̎��Ԃ��Z�b�g(����ɂ���ĕς���)
	isNextShoot = true;		//�t���O�����Ă�
}

void CWEAPON::Reload()
{
	Ammo = 0;
	ReloadTime = RELOADTIME;	//���U���I��鎞�Ԃ��Z�b�g(����ɂ���ĕς���)
	isReload = true;			//�t���O�����Ă�
}