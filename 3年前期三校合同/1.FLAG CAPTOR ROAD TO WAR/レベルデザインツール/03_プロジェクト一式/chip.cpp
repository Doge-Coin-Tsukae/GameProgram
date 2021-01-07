//
//�`�b�v(�{�^��)�N���X
//
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "polygon.h"
#include "chip.h"

void CChip::Init()
{
	m_polygon = new CSplitPolygon;
	m_polygon->Init();
}
void CChip::Uninit()
{
	m_polygon->Uninit();
	delete m_polygon;
}
void CChip::Update()
{
	m_polygon->Update();
}
void CChip::Draw()
{
	m_polygon->Draw();
}

void CChip::SetPolygon(char* name, D3DXVECTOR2 Size, D3DXVECTOR2 Split,D3DXVECTOR2 Splitend)
{
	m_Size = Size;		//�T�C�Y���󂯎�����̂�

	m_polygon->SetSize(m_Size.y, m_Size.x);		//�|���S���̃T�C�Y��������
	m_polygon->SetTexture(name);				//�摜
	m_polygon->SetSplit(Split, Splitend);		//�摜���ǂ��ŋ�؂邩
	m_polygon->SetPosition(m_Position);			//���W�w��
}

bool CChip::Colision(POINT pos)
{
	if (m_Position.x > pos.x)return false;
	if (m_Position.x + m_Size.x < pos.x)return false;
	if (m_Position.y > pos.y)return false;
	if (m_Position.y + m_Size.y < pos.y)return false;

	return true;
}