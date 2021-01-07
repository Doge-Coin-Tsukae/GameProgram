//=====================================
//
//  �v���C���[
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Vector.h"
#include "sound.h"
#include "scene.h"
#include "input.h"
#include "camera.h"
#include "polygon.h"
#include "gauge.h"
#include "human.h"
#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "meshfield.h"
#include "bullet.h"
#include "bunker.h"
#include "fade.h"

#define		NORMALSPEED 0.25f
#define		SLOWSPEED	0.05f
#define		ANIMEBLENDSPEED	0.1f

typedef struct
{
	char *pFilename;	// �t�@�C����
} ANIMENAME;

ANIMENAME g_aParam[5] =
{
	{(char *)"idle"},				// �ҋ@
	{(char *)"ready"},				// �\����
	{(char *)"run"},				// ����
	{(char *)"fire"},				//����
	{(char *)"Death"},
};

void CPlayer::Init()
{
	//�N���X�̏�������
	m_Animodel = new CAnimationModel();
	m_Animodel->Load("asset\\model\\player\\chara.fbx");					//���f���̃��[�h(�{�[���t��)
	m_Animodel->LoadAnimation("asset\\model\\player\\idle.fbx", g_aParam[0].pFilename);		//�A�j���[�V����
	m_Animodel->LoadAnimation("asset\\model\\player\\ready.fbx", g_aParam[1].pFilename);		//�A�j���[�V����
	m_Animodel->LoadAnimation("asset\\model\\player\\run.fbx", g_aParam[2].pFilename);		//�A�j���[�V����
	m_Animodel->LoadAnimation("asset\\model\\player\\fire.fbx", g_aParam[3].pFilename);
	m_Animodel->LoadAnimation("asset\\model\\player\\Death.fbx", g_aParam[4].pFilename);

	m_Sight = new CSIGHT();
	m_Sight->Init();
	m_Sight->Setparent(this);	//�Ə��̐e��������

	m_Weapon = new CWEAPON();
	m_Weapon->Init();
	m_Weapon->Setparent(this);	//����̐e��������

	m_Colider.Init(m_Position + D3DXVECTOR3(-1.0f, 0.0f, -1.0f), m_Position + D3DXVECTOR3(1.0f, 2.0f, 1.0f), m_Position);

	//�����o�ϐ��̏�������
	m_Position = D3DXVECTOR3(350.0f, 1.0f, -200.0f);
	m_Velocity = m_Position;
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ModelRot = D3DXVECTOR3(1.6f, 0.0f, 0.0f);
	m_NowAnimationChara = g_aParam[0].pFilename;
	m_OldAnimationChara = g_aParam[1].pFilename;
	m_Scale = D3DXVECTOR3(1.3f, 1.3f, 1.3f);
	m_speed = 0.01f;
	m_TeamNumber = TEAM_FRIENDRY;	//�`�[���ҏW
	m_Death = false;
	m_Hp = 100;
	m_Frame = 0;
	rate = 0;

	const char* VSfilename[MAXSHADER] = //�o�[�e�b�N�X�V�F�[�_�t�@�C���l�[��
	{
		"vertexShader.cso",	//�V�F�[�_�[
		"pixelLightingVS.cso",	//�V�F�[�_�[
		"vertexLightingVS.cso",	//�V�F�[�_�[
		"vertexShader.cso",	//�V�F�[�_�[
	};
	const char* PSfilename[MAXSHADER] = //�s�N�Z���V�F�[�_�t�@�C���l�[��
	{
		"pixelShader.cso",	//�V�F�[�_�[
		"pixelLightingPS.cso",	//�V�F�[�_�[
		"vertexLightingPS.cso",	//�V�F�[�_�[
		"pixelShader.cso",	//�V�F�[�_�[
	};
	//�����ɃV�F�[�_�[�t�@�C���̃��[�h��ǉ�
	for (int i = 0; i < MAXSHADER; i++)
	{
		//�o�[�e�b�N�X�V�F�[�_�[�t�@�C���̃��[�h���I�u�W�F�N�g�쐬
		CRenderer::CreateVertexShader(&m_VertexShader[i], &m_VertexLayout, VSfilename[i]);

		//�s�N�Z���V�F�[�_�[�t�@�C���̃��[�h���I�u�W�F�N�g�쐬
		CRenderer::CreatePixelShader(&m_pixelShader[i], PSfilename[i]);
	}

	shaderNo = 0;
}

void CPlayer::Uninit()
{
	m_Weapon->Uninit();
	delete m_Weapon;

	m_Sight->Uninit();
	delete m_Sight;

	m_Animodel->Unload();
	delete m_Animodel;

	for (int i = 0; i < MAXSHADER; i++)
	{
		m_VertexShader[i]->Release();
		m_pixelShader[i]->Release();
	}
}

void CPlayer::Update()
{
	//�w���p�[�֐��̍X�V
	Update_Controll();

	//��������`�F�b�N
	m_Rotation.z = std::min(m_Rotation.z, 0.0f);
	m_Rotation.z = std::max(m_Rotation.z, -0.5f);
	rate = std::min(rate, 1.0f);
	rate = std::max(rate, 0.0f);

	//�v���C���[�ɓ����Ă���N���X�̍X�V����
	m_Sight->Update();
	m_Weapon->Update();
	m_Colider.update(m_Velocity);
	m_Animodel->Update(m_OldAnimationChara,m_NowAnimationChara, m_Frame, rate);

	//�����蔻�菈��
	CScene* scene = CManager::GetScene();
	std::vector<CBUNKER*> bunkerList = scene->GetGameObjects<CBUNKER>(1);
	for (CBUNKER* bunker : bunkerList)
	{
		//AABB
		/*if (intersectAABB(m_Colider, bunker->GetColider()))
		{
			m_Velocity = m_Position;
			m_speed = 0.01f;
		}*/

		//OBB(����)
		D3DXVECTOR3 bukerPos = bunker->GetPosition();
		D3DXVECTOR3 direction = m_Position - bukerPos;

		D3DXVECTOR3 obbx, obby, obbz;
		float obbLenx, obbLeny,obbLenz;

		obbx = bunker->GetObbX();
		obbLenx = D3DXVec3Length(&obbx);
		obbx /= obbLenx;

		obby = bunker->GetObbY();
		obbLeny = D3DXVec3Length(&obby);
		obby /= obbLeny;

		obbz = bunker->GetObbZ();
		obbLenz = D3DXVec3Length(&obbz);
		obbz /= obbLenz;

		float lenX,lenY, lenZ;
		lenX = D3DXVec3Dot(&obbx, &direction);
		lenY = D3DXVec3Dot(&obby, &direction);
		lenZ = D3DXVec3Dot(&obbz, &direction);

		if (fabs(lenX) < obbLenx && fabs(lenY) < obbLeny && fabs(lenZ) < obbLenz)
		{
			m_Velocity = m_Position;
			m_speed = 0.01f;
		}
	}

	//���W���X�V
	m_Position = m_Velocity;

	//�̗͂�0�ȉ��ɂȂ����Ƃ�
	if (m_Hp <= 0)
	{
		Death();
	}

	//�e�������Ă���Ƃ��͑��x������������
	if (m_Weapon->GetNextShoot() ==true)
	{
		if (m_speed >= SLOWSPEED)
			m_speed = SLOWSPEED;
	}
	else
	{
		if (m_speed >= NORMALSPEED)
			m_speed = NORMALSPEED;
	}

	//���񂾎��̏���
	if (m_Death == true)
	{
		m_OldAnimationChara = (char*)"Death";
		m_NowAnimationChara = (char*)"Death";
	}

	//�ϐ�
	rate+= ANIMEBLENDSPEED;
	m_Frame++;
	//if(m_Frame >= 240)
	//	m_Frame = 0;
	//���b�V���t�B�[���h�����擾
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);
}

void CPlayer::Update_Controll()
{
	if (m_Death == true) return;
	//�L�[���͂ňړ�
	if (CInput::GetKeyPress('A'))
	{
		m_Velocity.x -= sin(m_Rotation.x)*m_speed;
		m_Velocity.z -= cos(m_Rotation.x)*m_speed;
		m_speed += 0.01f;
		ChangeAnimation((char*)"run");
	}
	if (CInput::GetKeyPress('D'))
	{
		m_Velocity.x += sin(m_Rotation.x)*m_speed;
		m_Velocity.z += cos(m_Rotation.x)*m_speed;
		m_speed += 0.01f;
		ChangeAnimation((char*)"run");
	}
	if (CInput::GetKeyPress('W'))
	{
		m_Velocity.z += sin(m_Rotation.x)*m_speed;
		m_Velocity.x -= cos(m_Rotation.x)*m_speed;
		m_speed += 0.01f;
		ChangeAnimation((char*)"run");
	}
	if (CInput::GetKeyPress('S'))
	{
		m_Velocity.z -= sin(m_Rotation.x)*m_speed;
		m_Velocity.x += cos(m_Rotation.x)*m_speed;
		m_speed += 0.01f;
		ChangeAnimation((char*)"run");
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

	if (m_Velocity.x == m_Position.x)
	{
		m_speed = 0.01f;
		if(m_Weapon->GetNextShoot() == false)
		ChangeAnimation((char*)g_aParam[0 + m_ready].pFilename);	//�\�����A�C�h����Ԃ�
	}

	//�e����
	if (CInput::GetKeyPress(VK_LBUTTON))
	{	//�}�E�X���E�N���b�N���ꂽ��
		m_Weapon->Shoot(m_Sight->GetPosition(),m_TeamNumber);	//���킩�甭�˂���
		ChangeAnimation((char*)"fire");
	}

	//�\��
	if (CInput::GetKeyTrigger(VK_RBUTTON))
	{
		CScene* scene = CManager::GetScene();
		CCamera* pcamera = scene->GetGameObject<CCamera>(0);

		pcamera->ZoomCamera();	//�Y�[�����������������
		m_ready = 1 - m_ready;	//�\���������������
	}

	//�V�F�[�_�[�؂�ւ�
	if (CInput::GetKeyTrigger('Z'))
	{
		shaderNo++;
		if (shaderNo >= MAXSHADER) shaderNo = 0;
	}

}
void CPlayer::Draw()
{
	//�C���v�b�g���C�A�E�g�̃Z�b�g(DirectX�֒��_�̍\����������)
	CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	//�o�[�e�b�N�X�V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
	CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader[shaderNo], NULL, 0);
	//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
	CRenderer::GetDeviceContext()->PSSetShader(m_pixelShader[shaderNo], NULL, 0);

	m_Weapon->Draw();
	m_Sight->Draw();

	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;	
	//�g��k���̃}�g���N�X
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//���[�s�b�`���[���̃}�g���N�X
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x + m_ModelRot.x, -m_Rotation.z - m_ModelRot.z, m_Rotation.y + m_ModelRot.y);
	//�ʒu�}�g���N�X6
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Animodel->Draw();

	//�C���v�b�g���C�A�E�g�̃Z�b�g(DirectX�֒��_�̍\����������)
	//CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	//�o�[�e�b�N�X�V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
	//CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader[MAXSHADER-1], NULL, 0);
	//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
	//CRenderer::GetDeviceContext()->PSSetShader(m_pixelShader[MAXSHADER-1], NULL, 0);
}

void CPlayer::Death()
{
	if (m_Death == true) return;
	PlaySound(SOUND_SE_DEATH);
	m_Death = true;
	m_Hp = 0;
}

void CPlayer::Damage()
{
	if (m_Death == true) return;
	m_Hp -= 10;	//�_���[�W������
	CFADE::SetTexture((char*)"asset/texture/fade_red.png");
	CFADE::Fade_Start(false, 10.0f, D3DXCOLOR());
}

void CPlayer::ChangeAnimation(char* Name)
{
	if (m_NowAnimationChara == Name)return;	//���̃A�j���[�V�����Ǝ��̃A�j���[�V�������ꏏ�Ȃ�
	m_OldAnimationChara = m_NowAnimationChara;		//�V�����A�j���[�V�����f�[�^���Â��A�j���[�V�����f�[�^�ɂ���
	m_NowAnimationChara = Name;						//�V�����A�j���[�V�����f�[�^������
	rate = 0.0f;									//�u�����h�l�����Z�b�g
}

void CPlayer::Load(FILE* fp)
{
	fscanf(fp, "%f%f%f", &m_Position.x, &m_Position.y, &m_Position.z);
	m_Velocity = m_Position;
	fscanf(fp, "%f%f%f", &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
	fscanf(fp, "%f%f%f", &m_Scale.x, &m_Scale.y, &m_Scale.z);
}
