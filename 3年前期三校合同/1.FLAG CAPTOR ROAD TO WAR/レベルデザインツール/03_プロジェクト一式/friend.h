#pragma once

#include "gameobject.h"

class CFriend : public CGameObject	//継承(インヘリタンス)
{
private:
	CModel* m_Model;			//3Dモデルクラス

public:
	CFriend() {}
	~CFriend() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();
};