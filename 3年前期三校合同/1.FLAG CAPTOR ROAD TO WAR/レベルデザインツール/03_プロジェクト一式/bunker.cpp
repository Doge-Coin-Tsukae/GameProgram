#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "scene.h"
#include "meshfield.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "colider.h"
#include "bunker.h"

class CModel* CBUNKER::m_Model;

void CBUNKER::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\bunker.obj");
}

void CBUNKER::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CBUNKER::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Colider.Init(m_Position + D3DXVECTOR3(-8.0f, 0.0f, -8.0f), m_Position+ D3DXVECTOR3(8.0f, 2.0f, 8.0f), m_Position);

	//���b�V���t�B�[���h�����擾
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

}

void CBUNKER::Uninit()
{
}
void CBUNKER::Update()
{
	m_Colider.update(m_Position);
}
void CBUNKER::Draw()
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

void CBUNKER::Save(FILE* fp)
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

void CBUNKER::Load(FILE*fp, int line)
{
	for (int i = 0; i < line * 3; i++)
	{
		fscanf(fp, "");
	}

	fscanf(fp, "%f%f%f", &m_Position.x, &m_Position.y, &m_Position.z);
	fscanf(fp, "%f%f%f", &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
	fscanf(fp, "%f%f%f", &m_Scale.x, &m_Scale.y, &m_Scale.z);
}