//****************************************
//�G�̃��X�|�[���|�C���g
//****************************************

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "scene.h"

#include "meshfield.h"

#include "model.h"
#include "colider.h"
#include "base.h"

#include "enemyrespornpoint.h"

class CModel* CEnemyRespornPoint::m_Model;

void CEnemyRespornPoint::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\flag.obj");
}

void CEnemyRespornPoint::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CEnemyRespornPoint::Init()
{

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//���b�V���t�B�[���h�����擾
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

	//id�̐ݒ�
	std::vector<CEnemyRespornPoint*> EnemyRespornPoints = CManager::GetScene()->GetGameObjects<CEnemyRespornPoint>(1);

	int setid = 0;

	for (CEnemyRespornPoint* bunker : EnemyRespornPoints)
	{
		setid++;	//1�����₷
	}

	m_Id = setid;	//�����


}

void CEnemyRespornPoint::Uninit()
{

}

void CEnemyRespornPoint::Update()
{
	//�w���p�[�֐�
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

}

void CEnemyRespornPoint::Draw()
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