#pragma once

#include "gameobject.h"

class CSaveLoadChip :public CGameObject
{
private:
	CChip *m_SaveLoadChip[2];	//�Z�[�u&���[�h�{�^��
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool ClickSaveLoad();
};