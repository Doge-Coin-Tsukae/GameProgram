#pragma once

#include "gameobject.h"

class CFriend : public CGameObject	//�p��(�C���w���^���X)
{
private:
	CModel* m_Model;			//3D���f���N���X

public:
	CFriend() {}
	~CFriend() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();
};