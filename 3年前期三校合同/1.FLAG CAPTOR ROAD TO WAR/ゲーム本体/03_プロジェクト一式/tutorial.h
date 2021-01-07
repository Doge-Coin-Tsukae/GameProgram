#pragma once

#include "scene.h"

class CTutorial : public CScene
{
private:
	CGAME_MANEGER* m_GameManeger;
	bool m_Clik;		//エンター押されたか

public:
	void Init();
	void Uninit();
	void Update();
	//drawは何も書かない場合、Sceneから呼び出される。
};