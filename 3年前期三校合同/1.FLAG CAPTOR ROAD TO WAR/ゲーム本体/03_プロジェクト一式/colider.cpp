//****************************************
//�����蔻��
//****************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "colider.h"

void CCOLIDER_CIRCLE::Init()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\colider.obj");
}
void CCOLIDER_CIRCLE::Uninit()
{

}
void CCOLIDER_CIRCLE::Update()
{

}
void CCOLIDER_CIRCLE::Draw()
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

bool CCOLIDER_CIRCLE::GetColider(D3DXVECTOR3 pPos)
{
	D3DXVECTOR3 direction = m_Position - pPos;
	float length = D3DXVec3Length(&direction);

	if (length < m_Scale.x)
	{
		return true;
	}


	return false;
}