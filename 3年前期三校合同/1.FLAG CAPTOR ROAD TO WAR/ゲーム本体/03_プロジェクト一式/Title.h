#pragma once

#include "scene.h"

class CTitle : public CScene
{
private:
	bool m_Clik;		//�G���^�[�����ꂽ��
public:

	void Init();
	void Uninit();
	void Update();

};