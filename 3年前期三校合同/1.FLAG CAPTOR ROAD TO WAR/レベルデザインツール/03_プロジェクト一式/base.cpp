//
//���_�I�u�W�F�N�g(�w���o����)
//
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Vector.h"
#include "meshfield.h"
#include "gamemaneger.h"
#include "game.h"
#include "human.h"
#include "model.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "base.h"

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
	m_Zone->SetScale(D3DXVECTOR3(10.0f, 10.0f, 10.0f));
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

	//�~�̔���
	//�͈͂ɓ�������Q�[�W�𓮂���
	if (m_Zone->GetColider(pPlayer->GetPosition()))
	{
		m_Territory_Invarter.x++;	//�w�n�̐��͐��𑝂₷(�F�R)
		m_Rotation.x++;				//������Ղ�������]������
	}
}

void CBASE::Update()
{
	m_Zone->SetPosition(m_Position);		//���W�̐ݒ�
	m_Zone->Update();						//�X�V����

	m_Territory_Invarter = D3DXVECTOR2(0, 0);	//�N���҂̒l���Z�b�g

	//�w�n�ɕ����������Ă���Ƃ�
	if (m_Territory_Invarter.x != m_Territory_Invarter.y)
	{
		m_Gauge--;		//���̓Q�[�W�����炷
	}

	//���͒n��0�ɂȂ�����
	if (m_Gauge <= 0)
	{
		switch (m_territory)
		{//���L�҂ɂ���Đ؂蕪����
		case NONE_ZONE:
			if (m_Territory_Invarter.x > m_Territory_Invarter.y)
			{//�F�R�̕�������������
				m_territory = FRIENDRY_ZONE;
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

	//���b�V���t�B�[���h�����擾
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

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

void CBASE::Save(FILE* fp)
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