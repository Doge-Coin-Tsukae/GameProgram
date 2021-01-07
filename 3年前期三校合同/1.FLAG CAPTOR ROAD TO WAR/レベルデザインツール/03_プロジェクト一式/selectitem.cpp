//---------------------------------
//
//��ʉE�̃{�b�N�X�̊Ǘ�
//
//---------------------------------

#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "input.h"
#include "scene.h"
#include "polygon.h"
#include "chip.h"
#include "model.h"
#include "human.h"
#include "carsor.h"
#include "colider.h"
#include "bunker.h"
#include "sight.h"
#include "weapon.h"
#include "player.h"
#include "enemy.h"
#include "base.h"
#include "deadtree.h"
#include "tree.h"

#include "selectpointer.h"
#include "modechip.h"
#include "saveloadchip.h"
#include "selectitem.h"

enum BOTTONMODE
{
	SET,		//�ݒu
	EDIT,		//�ҏW
};

void CSelectItem::Init()
{
	const char* texturename[2] = //�t�@�C���l�[��
	{
		"asset/texture/selectitem/button-mode-set.png",
		"asset/texture/selectitem/button-mode-edit.png",
	};

	m_Position = D3DXVECTOR3(800.0f, 40.0f, 0.0f);

	m_under = new CPolygon;
	m_under->SetSize(300.0f,150.0f);
	m_under->SetTexture((char*)"asset/texture/selectitem/under2.png");
	m_under->Init(m_Position);

	m_pointer = new CSelectpointer;
	m_pointer->Init();
	m_pointer->SetPosition(m_Position = D3DXVECTOR3(m_Position.x+ 3.0f, m_Position.y+ 28.0f, 0.0f));

	//�c����
	for (int h = 0; h < 4;h++)
	{
		//������
		for (int w = 0; w < 2; w++)
		{
			m_chip[h][w] = new CChip;
			m_chip[h][w]->Init();
			m_chip[h][w]->SetPosition(D3DXVECTOR3(m_Position.x -2 + 75 * w, m_Position.y - 2 + 69 * h, 0.0f));
			m_chip[h][w]->SetPolygon((char*)"asset/texture/selectitem/chip2.png",
				D3DXVECTOR2(73.0f,68.0f),
				D3DXVECTOR2(0.5f*w, 0.25f*h), D3DXVECTOR2(0.5f + (0.5f * w), 0.25 + (0.25*h)));

			m_chip[h][w]->Setid((h*2)+ w);
		}
	}

	//���[�h�`�b�v�̐������[�v
	for (int h = 0; h < 2; h++)
	{
		m_modechip[h] = new CMODECHIP;
		m_modechip[h]->Init();
		m_modechip[h]->SetPosition(D3DXVECTOR3(m_Position.x-2 + 78 * h, m_Position.y -53, 0.0f));
		m_modechip[h]->SetPolygon((char*)texturename[h],
			D3DXVECTOR2(70.0f, 25.0f));
		m_modechip[h]->Setid(h);
	}
	m_modechip[1]->SetMode();		//�z�u���[�h�ɂ���
	NowMode = SET;

	m_carsor = new CCARSOR;
	m_carsor->Init();

	m_SaveLoadChip = new CSaveLoadChip;
	m_SaveLoadChip->SetPosition(m_Position);
	m_SaveLoadChip->Init();

	min = D3DXVECTOR2(0,0);
	max = D3DXVECTOR2(150.0f, 300.0f);
	click = false;
}

void CSelectItem::Uninit()
{
	m_SaveLoadChip->Uninit();
	delete m_SaveLoadChip;

	m_carsor->Uninit();
	delete m_carsor;

	for (int h = 0; h < 2; h++)
	{
		m_modechip[h]->Uninit();
		delete m_modechip[h];
	}

	//�c����
	for (int h = 0; h < 4; h++)
	{
		//������
		for (int w = 0; w < 2; w++)
		{
			m_chip[h][w]->Uninit();
			delete m_chip[h][w];
		}
	}

	m_pointer->Uninit();
	delete m_pointer;
	m_under->Uninit();
	delete m_under;
}

void CSelectItem::Update()
{
	//����𒲂ׂ�
	//m_Rotation.z = min(m_Rotation.z, 0.0f);
	//m_Rotation.z = max(m_Rotation.z, -0.5f);
	//m_Rotation.z = min(m_Rotation.z, 0.0f);
	//m_Rotation.z = max(m_Rotation.z, -0.5f);

	m_under->Update();
	m_pointer->Update();
	//�c����
	for (int h = 0; h < 4; h++)
	{
		//������
		for (int w = 0; w < 2; w++)
		{
			m_chip[h][w]->Update();
		}
	}

	for (int h = 0; h < 2; h++)
	{
		m_modechip[h]->Update();

	}

	m_carsor->Update();
	m_SaveLoadChip->Update();
	UpdateControll();
	
}

void CSelectItem::Draw()
{
	m_under->Draw();
	m_pointer->Draw();

	//�c����
	for (int h = 0; h < 3; h++)
	{
		//������
		for (int w = 0; w < 2; w++)
		{
			m_chip[h][w]->Draw();
		}
	}

	for (int i = 0; i < 2; i++)
	{
		m_modechip[i]->Draw();
	}

	m_carsor->Draw();

	m_SaveLoadChip->Draw();

	//�z�u���[�h�̎��ɔz�u����
	if (NowMode == SET)
	{
		//IMGUI

		ImGui::SetNextWindowSize(ImVec2(220, 100));
		ImGui::Begin("SET_MODE");
		ImGui::SliderFloat("rotation.X", &m_Rotation.x, 0.0f, 1.0f);
		ImGui::Text("fugafuga");
		ImGui::End();

	}

	//�ҏW���[�h�̎��ɔz�u����
	if (NowMode == EDIT)
	{
		//IMGUI

		ImGui::SetNextWindowSize(ImVec2(220, 100));
		ImGui::Begin("EDIT_MODE");
		if(m_EditGameObject !=nullptr)m_EditGameObject->SetImGui();		//���݃N���b�N���Ă���Q�[���I�u�W�F�N�g�̕ҏW��ʂ��o��
		ImGui::End();
	}


}

void CSelectItem::UpdateControll()
{
	//�J�[�\��������
	if (CInput::GetKeyTrigger(VK_UP))	 m_pointer->move_up();
	if (CInput::GetKeyTrigger(VK_DOWN))  m_pointer->move_down();
	if (CInput::GetKeyTrigger(VK_LEFT))  m_pointer->move_left();
	if (CInput::GetKeyTrigger(VK_RIGHT)) m_pointer->move_right();

	//�E�N���b�N�������̓���
	if (CInput::GetKeyTrigger(VK_LBUTTON))
	{
		//�A�C�e���{�b�N�X���N���b�N���ĂȂ������烏�[���h�ɃI�u�W�F�N�g�z�u
		if (ClickItemBox() == false && ClikEditBox() == false && m_SaveLoadChip->ClickSaveLoad() ==false)
		{
			//�ݒu���[�h�̂Ƃ��̓��[���h�ɃI�u�W�F�N�g�z�u
			if (NowMode == SET)
				WorldObject();

			//�ҏW���[�h�̂Ƃ��̓I�u�W�F�N�g���N���b�N���ꂽ�炻�̃I�u�W�F�N�g�̕ҏW��ʕ\��
			if (NowMode == EDIT)
			{
				ClickColider();
			}
		}

		click = false;
	}
	if (CInput::GetKeyPress(VK_LBUTTON))
	{
		if (!m_EditGameObject) return;
		if(click == false)
		{
			if (m_carsor->Collision(m_EditGameObject) == false) return;
			click = true;
		}
		
		//�J�[�\���ɃQ�[���I�u�W�F�N�g���z���t����
		D3DXVECTOR3 cpos = m_carsor->GetPosition();
		m_EditGameObject->SetPosition(cpos);
	}
}

bool CSelectItem::ClikEditBox()
{
	POINT pos;
	GetCursorPos(&pos);		//���݂̃J�[�\���̃|�W�V�����擾
	ScreenToClient(GetWindow(), &pos);

	for (int i = 0; i < 2; i++)
	{
		//�{�^�����N���b�N����Ă���
		if (m_modechip[i]->Colision(pos) == true && NowMode != i)
		{
			m_modechip[i]->SetMode();
			m_modechip[1 - i]->SetMode();

			NowMode = i;	//���[�h�Z�b�g

			m_EditGameObject = nullptr;	//�ҏW���[�h�ŃI�u�W�F�N�g�폜���ă��[�h�ύX����ƃN���b�V������̂�

			return true;
		}
	}

	return false;
}

bool CSelectItem::ClickItemBox()
{
	POINT pos;
	GetCursorPos(&pos);		//���݂̃J�[�\���̃|�W�V�����擾
	ScreenToClient(GetWindow(), &pos);

	//�J�[�\�����{�b�N�X�͈̔͊O�������烋�[�v������
	if (pos.x < m_Position.x + min.x)return false;
	if (pos.x > m_Position.x + max.x)return false;
	if (pos.y < m_Position.y + min.y)return false;
	if (pos.y > m_Position.y + max.y)return false;

	m_EditGameObject = nullptr;	//�ҏW���[�h�ŃI�u�W�F�N�g�폜���ăA�C�e���{�b�N�X���N���b�N����ƃN���b�V������̂�

	//�`�b�v�̓����蔻��
		//�c����
	for (int h = 0; h < 4; h++)
	{
		//������
		for (int w = 0; w < 2; w++)
		{
			if (m_chip[h][w]->Colision(pos) == true)
			{
				m_pointer->SetPos(D3DXVECTOR2(w,h));	//�|�C���^�[�̈ʒu���J�[�\�����������Ƃ����
				return true;
			}
		}
	}

	return false;
}

void CSelectItem::ClickColider()
{
	CScene* scene = CManager::GetScene();

	std::vector<CGameObject*> gameobjectlist = scene->GetALLGameObjects<CGameObject>(1);
	CCARSOR *cursor = scene->GetGameObject<CCARSOR>(1);
	for (CGameObject* gameobject : gameobjectlist)
	{
		if (gameobject->GetPosition() != cursor->GetPosition())
		{
			if (cursor->Collision(gameobject) == true)
			{
				m_EditGameObject = gameobject;	//m_EditGameObject�ɃN���b�N���ꂽ�I�u�W�F�N�g�̃|�C���^�N���X������
				return;
			}
		}
	}
	//�Ȃɂ��N���b�N����Ȃ������Ƃ�
	m_EditGameObject == nullptr;
}

void CSelectItem::WorldObject()
{
	CScene* scene = CManager::GetScene();

	switch (m_chip[(int)m_pointer->GetPos().y][(int)m_pointer->GetPos().x]->GetId())
	{
	case 0:
		scene->AddGameObject<CPlayer>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 1:
		scene->AddGameObject<CEnemy>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 2:
		scene->AddGameObject<CBASE>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 3:
		scene->AddGameObject<CDEADTREE>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 4:
		scene->AddGameObject<CTREE>(1)->SetPosition(m_carsor->GetPosition());
		break;
	case 5:
		scene->AddGameObject<CBUNKER>(1)->SetPosition(m_carsor->GetPosition());
		break;
	default:
		scene->AddGameObject<CPlayer>(1)->SetPosition(m_carsor->GetPosition());
		break;
	}
}