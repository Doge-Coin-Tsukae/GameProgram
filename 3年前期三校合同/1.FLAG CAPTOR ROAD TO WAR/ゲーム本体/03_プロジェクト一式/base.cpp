//=====================================
//
//���_�I�u�W�F�N�g(�w���o����)
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
	//���g�̕ϐ��̐ݒ�
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_territory = ENEMY_ZONE;
	m_Gauge = 100;

	//���̐ݒ�
	m_Flag = new CModel();
	m_Flag->Load("asset\\model\\flag.obj");

	//�����蔻��̐ݒ�
	m_Zone = new CCOLIDER_CIRCLE();
	m_Zone->Init();
	m_Zone->SetScale(D3DXVECTOR3(30.0f, 30.0f, 30.0f));		//����̑傫��
}

void CBASE::Uninit()
{
	//�����蔻��̍폜
	m_Zone->Uninit();
	delete m_Zone;

	//���̍폜
	m_Flag->Unload();
	delete m_Flag;
}

void CBASE::Update_Colision()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	if (!pPlayer) return;

	//�~�̔���
	//�v���C���[���͈͂ɓ�������Q�[�W�𓮂���
	if (m_Zone->GetColider(pPlayer->GetPosition()))
	{
		m_Territory_Invarter.x++;	//�w�n�̐��͐��𑝂₷(�F�R)

		if (m_inPlayer == false)
		{
			m_inPlayer = true;
			CScene* scene = CManager::GetScene();
			scene->AddGameObject<CCAPTUREGAUGE>(3)->Setparent(this);		//��ʕ\���p�쐬+�e��������
		}
	}
	else
	{
		m_inPlayer = false;
	}
}
void CBASE::Update_Gauge()
{
	//�w�n�ɗ��R�̕������������̎����E
	if (m_Territory_Invarter.x == m_Territory_Invarter.y) { return; }
	//�w�n���F�R�̎�
	if (m_territory == FRIENDRY_ZONE)
	{	//�F�R�̐������������E
		if (m_Territory_Invarter.x > m_Territory_Invarter.y) { return; }
	}
	//�w�n���G�R�̎�
	if (m_territory == ENEMY_ZONE)
	{	//�G�R�̐������������E
		if (m_Territory_Invarter.x < m_Territory_Invarter.y) { return; }
	}
	m_Gauge--;		//���̓Q�[�W�����炷
}
void CBASE::Update_Territory()
{
	CScene* scene = CManager::GetScene();
	//���͒n��0�ł͂Ȃ��Ƃ����E
	if (m_Gauge > 0) { return; }
	//�e���g���[�̎x�z��
	switch (m_territory)
	{//���L�҂ɂ���Đ؂蕪����
	case NONE_ZONE:
		if (m_Territory_Invarter.x > m_Territory_Invarter.y)
		{//�F�R�̕�������������
			m_territory = FRIENDRY_ZONE;
			m_Flag->Load("asset\\model\\flagblue.obj");
			scene->AddGameObject<CCAPTUREUI>(3);	//��ʂɕ\��������
		}
		if (m_Territory_Invarter.x < m_Territory_Invarter.y)
		{//�G�R�̕�������������
			m_territory = ENEMY_ZONE;
		}
		m_Gauge = 100;
		break;

	case FRIENDRY_ZONE:
		m_territory = NONE_ZONE;	//�����ɂ���
		m_Gauge = 100;				//�Q�[�W��
		break;

	case ENEMY_ZONE:
		m_territory = NONE_ZONE;	//�����ɂ���
		m_Gauge = 100;				//�Q�[�W��
		break;
	}
}
void CBASE::Update()
{
	m_Zone->SetPosition(m_Position);		//���W�̐ݒ�
	m_Zone->Update();						//�X�V����
	m_Territory_Invarter = D3DXVECTOR2(0, 0);	//�N���҂̒l���Z�b�g

	Update_Colision();		//�����蔻��
	Update_Gauge();			//�Q�[�W����
	Update_Territory();		//�̒n�̎x�z�ҏ���
}

void CBASE::Draw()
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

	m_Flag->Draw();		//���̕`��
	m_Zone->Draw();		//�����蔻��̕`��
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