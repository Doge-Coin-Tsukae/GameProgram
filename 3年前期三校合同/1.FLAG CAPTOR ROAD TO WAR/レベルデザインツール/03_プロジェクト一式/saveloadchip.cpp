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
	//セーブロード
	for (int w = 0; w < 2; w++)
	{
		m_SaveLoadChip[w] = new CChip;
		m_SaveLoadChip[w]->Init();
		m_SaveLoadChip[w]->SetPosition(D3DXVECTOR3(m_Position.x - 65 + 32 * w, m_Position.y - 25, 0.0f));
		m_SaveLoadChip[w]->SetPolygon((char*)"asset/texture/selectitem/saveandload.png",
			D3DXVECTOR2(30.0f, 30.0f),
			D3DXVECTOR2(0.5f*w, 0.0f), D3DXVECTOR2(0.5f + (0.5f * w), 1.0f));

		m_SaveLoadChip[w]->Setid(w);		//0=セーブ,1=ロード
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
	GetCursorPos(&pos);		//現在のカーソルのポジション取得
	ScreenToClient(GetWindow(), &pos);

	//チップの当たり判定
		//縦方向
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