#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "input.h"
#include "save.h"
#include "load.h"
#include "model.h"

#include "polygon.h"
#include "chip.h"
#include "carsor.h"

#include "saveloadchip.h"

void CSaveLoadChip::Init()
{
	//�Z�[�u���[�h
	for (int w = 0; w < 2; w++)
	{
		m_SaveLoadChip[w] = new CChip;
		m_SaveLoadChip[w]->Init();
		m_SaveLoadChip[w]->SetPosition(D3DXVECTOR3(m_Position.x - 65 + 32 * w, m_Position.y - 25, 0.0f));
		m_SaveLoadChip[w]->SetPolygon((char*)"asset/texture/selectitem/saveandload.png",
			D3DXVECTOR2(30.0f, 30.0f),
			D3DXVECTOR2(0.5f*w, 0.0f), D3DXVECTOR2(0.5f + (0.5f * w), 1.0f));

		m_SaveLoadChip[w]->Setid(w);		//0=�Z�[�u,1=���[�h
	}
}
void CSaveLoadChip::Uninit()
{
	for (int h = 0; h < 2; h++)
	{
		m_SaveLoadChip[h]->Uninit();
		delete m_SaveLoadChip[h];

	}
}
void CSaveLoadChip::Update()
{
	for (int h = 0; h < 2; h++)
	{
		m_SaveLoadChip[h]->Update();
	}
}
void CSaveLoadChip::Draw()
{
	for (int h = 0; h < 2; h++)
	{
		m_SaveLoadChip[h]->Draw();
	}
}

bool CSaveLoadChip::ClickSaveLoad()
{
	POINT pos;
	GetCursorPos(&pos);		//���݂̃J�[�\���̃|�W�V�����擾
	ScreenToClient(GetWindow(), &pos);

	//�`�b�v�̓����蔻��
		//�c����
	for (int h = 0; h < 2; h++)
	{
		if (m_SaveLoadChip[h]->Colision(pos) == true)
		{

			if(m_SaveLoadChip[h]->GetId() == 0)
			{ 
				CSAVE* save = CManager::GetScene()->GetGameObject<CSAVE>(0);
				save->Data_Save();
			}
			else
			{
				CLOAD* load = CManager::GetScene()->GetGameObject<CLOAD>(0);
				load->Data_Load();

			}

			return true;
		}
	}

	return false;
}