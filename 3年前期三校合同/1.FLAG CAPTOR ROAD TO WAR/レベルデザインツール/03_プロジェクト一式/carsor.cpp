//
//
//�J�[�\��
//writen by y.okubo
//
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "Vector.h"

#include "camera.h"
#include "meshfield.h"
#include "model.h"
#include "carsor.h"

void CCARSOR::Init()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\yokoari.obj");

	m_Scale = D3DXVECTOR3(2.0f, 2.0f, 2.0f);

	ShowCursor(FALSE);
}

void CCARSOR::Uninit()
{
	m_Model->Unload();
	delete m_Model;
}

void CCARSOR::Update()
{
	//�|�C���^�[�̃X�N���[�����W�K��
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(GetWindow(),&pos);	//�J�[�\���̍��W���A�v���P�[�V�����̍��W�ɂ���

	//�J�����ƃ��b�V���t�B�[���h�̃f�[�^����
	CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(0);
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);

	//�X�N���[�����W���烏�[���h���W�ɕϊ�
	CalcScreenToWorld(&ppos,pos.x, pos.y,1.0f,SCREEN_WIDTH,SCREEN_HEIGHT, &camera->GetViewMatrix(),&camera->GetProjectionMatrix());

	//�J�[�\���̍��W�ƃJ�����̍��W�Ńx�N�g�����Ƃ�
	D3DXVECTOR3 vpos = GetVector(camera->GetPosition(), ppos);	//�X�N���[���ƃJ�����̃x�N�g��
	m_Position = camera->GetPosition();	

	while (1)
	{
		m_Position += vpos;

		if (meshField->GetHeight(m_Position) >= m_Position.y)
		{
			m_Position.y = meshField->GetHeight(m_Position);
			break;
		}
	}
}

void CCARSOR::Draw()
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

// �X�N���[�����W�����[���h���W�ɕϊ�
D3DXVECTOR3* CCARSOR::CalcScreenToWorld(
	D3DXVECTOR3* pout,
	int Sx,  // �X�N���[��X���W
	int Sy,  // �X�N���[��Y���W
	float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
) 
{
	// �e�s��̋t�s����Z�o
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, View);
	D3DXMatrixInverse(&InvPrj, NULL, Prj);
	D3DXMatrixIdentity(&VP);
	VP._11 = Screen_w / 2.0f; VP._22 = -Screen_h / 2.0f;
	VP._41 = Screen_w / 2.0f; VP._42 = Screen_h / 2.0f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// �t�ϊ�
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(pout, &D3DXVECTOR3(Sx, Sy, fZ), &tmp);

	return pout;
}