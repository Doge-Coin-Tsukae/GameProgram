#pragma once

#include "scene.h"

class CTutorial : public CScene
{
private:
	CGAME_MANEGER* m_GameManeger;
	bool m_Clik;		//�G���^�[�����ꂽ��

public:
	void Init();
	void Uninit();
	void Update();
	//draw�͉��������Ȃ��ꍇ�AScene����Ăяo�����B
};