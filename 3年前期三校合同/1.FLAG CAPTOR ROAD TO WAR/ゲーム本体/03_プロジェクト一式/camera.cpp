//****************************************
//�J��������
//****************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "input.h"

#include "scene.h"

#include "human.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include"camera.h"

void CCamera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 3.0f, -150.0f);
	m_Target = D3DXVECTOR3(1.0f, 3.0f, -150.0f);
	m_zoom = false;
}

void CCamera::Uninit()
{

}

void CCamera::Update()
{
	//�v���C���[�擾
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	if (!pPlayer) return;		//�v���C���[��񂪂Ȃ��Ƃ��͏������s��Ȃ�

	Target_Player();		//�v���C���[��ǂ�������
	BackFront_Player();		//�v���C���[�̌��ɉ�荞�ނ悤�ɂ���
	Zoom_Player();			//�Y�[��
}
void CCamera::Target_Player()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	m_Target = pPlayer->GetPosition();		//�����_���v���C���[��
	m_Target.y += 8.0f;						//�J�������������
}
void CCamera::BackFront_Player()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	m_Position.x = m_Target.x + 12.0f *cos(pPlayer->GetRotation().x)*cos(pPlayer->GetRotation().z);	//���W
	m_Position.y = m_Target.y + 12.0f *sin(pPlayer->GetRotation().z);
	m_Position.z = m_Target.z + 12.0f *-sin(pPlayer->GetRotation().x)*cos(pPlayer->GetRotation().z);	//���W
}
void CCamera::Zoom_Player()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	if (m_zoom == true)
	{
		m_Target.y -= 3.0f;
		m_Target.x = m_Target.x + 1.4f *sin(pPlayer->GetRotation().x)*cos(pPlayer->GetRotation().z);	//���W
		m_Target.y = m_Target.y + 1.4f *sin(pPlayer->GetRotation().z);
		m_Target.z = m_Target.z + 1.4f *cos(pPlayer->GetRotation().x)*cos(pPlayer->GetRotation().z);	//���W

		m_Position.x = m_Target.x + 4.0f *cos(pPlayer->GetRotation().x)*cos(pPlayer->GetRotation().z);	//���W
		m_Position.y = m_Target.y + 4.0f *sin(pPlayer->GetRotation().z);
		m_Position.z = m_Target.z + 4.0f *-sin(pPlayer->GetRotation().x)*cos(pPlayer->GetRotation().z);	//���W
	}
}
void CCamera::Draw()
{
	//�r���[�}�g���N�X�ݒ�
	D3DXMatrixLookAtLH(&viewMatrix,&m_Position,&m_Target,&D3DXVECTOR3(0.0f,1.0f,0.0f));

	CRenderer::SetViewMatrix(&viewMatrix);		//Direct9��SetTransform�ɋ߂�

	//�v���W�F�N�V�����}�g���N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&projectionMatrix,1.0f,(float)SCREEN_WIDTH/SCREEN_HEIGHT,1.0f,1000.0f);

	CRenderer::SetProjectionMatrix(&projectionMatrix);
	CRenderer::SetCameraPosition(m_Position);
}