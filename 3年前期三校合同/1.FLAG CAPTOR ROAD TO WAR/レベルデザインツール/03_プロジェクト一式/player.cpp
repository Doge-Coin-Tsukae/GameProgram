//****************************************
//�v���C���[
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
	m_Sight->Setparent(this);	//�Ə��̐e��������

	m_Weapon = new CWEAPON();
	m_Weapon->Init();
	m_Weapon->Setparent(this);

	m_Colider.Init(m_Position + D3DXVECTOR3(-1.0f, 0.0f, -1.0f), m_Position + D3DXVECTOR3(1.0f, 2.0f, 1.0f), m_Position);

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Velocity = m_Position;
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_speed = 0.5f;
	m_TeamNumber = TEAM_FRIENDRY;	//�`�[���ҏW
	m_Death = false;
	m_Hp = 100;

	//���b�V���t�B�[���h�����擾
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
	//�w���p�[�֐��̍X�V
	//Update_Controll();

	//��������`�F�b�N
	//m_Rotation.z = min(m_Rotation.z, 0.0f);
	//m_Rotation.z = max(m_Rotation.z, -0.5f);

	//�v���C���[�ɓ����Ă���N���X�̍X�V����
	//m_Sight->Update();
	//m_Weapon->Update();
	//m_Colider.update(m_Velocity);

	//�����蔻�菈��
	//CScene* scene = CManager::GetScene();
	//std::vector<CBUNKER*> bunkerList = scene->GetGameObjects<CBUNKER>(1);
	//for (CBUNKER* bunker : bunkerList)
	//{
		//if (intersectAABB(m_Colider, bunker->GetColider()))
		//{
			//m_Velocity = m_Position;
		//}
	//}

	//���W���X�V
	//m_Position = m_Velocity;

	//�̗͂�0�ȉ��ɂȂ����Ƃ�
	//if (m_Hp <= 0)
	//{
		//Death();
	//}

	//�e�������Ă���Ƃ��͑��x������������
	//if (m_Weapon->GetNextShoot() ==true)
	//{
		//m_speed = SLOWSPEED;
	//}
	//else
	//{
		//m_speed = NORMALSPEED;
	//}

	//���b�V���t�B�[���h�����擾
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

}

void CPlayer::Update_Controll()
{
	//�L�[���͂ňړ�
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
	//�e����
	if (CInput::GetKeyPress(VK_LBUTTON))
	{	//�}�E�X���E�N���b�N���ꂽ��
		m_Weapon->Shoot(m_Position,m_Sight->GetPosition(),m_TeamNumber);	//���킩�甭�˂���
	}
}
void CPlayer::Draw()
{
	m_Weapon->Draw();
	m_Sight->Draw();

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

void CPlayer::Death()
{
	m_Death = true;
	m_Hp = 0;
}

void CPlayer::Damage()
{
	m_Hp -= 10;	//�_���[�W������
}

void CPlayer::Save(FILE* fp)
{
	//���W
	fprintf(fp, "%f ", m_Position.x);
	fprintf(fp, "%f ", m_Position.y);
	fprintf(fp, "%f\n", m_Position.z);
	//�p�x
	fprintf(fp, "%f ", m_Rotation.x);
	fprintf(fp, "%f ", m_Rotation.y);
	fprintf(fp, "%f\n", m_Rotation.z);
	//�傫��
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