#pragma once

#include "gameobject.h"

class CENEMY_COMMANDER : public CGameObject	//�p��(�C���w���^���X)
{
private:
	int resporn_timer;		//�ďo������

public:
	CENEMY_COMMANDER() {}
	~CENEMY_COMMANDER() {}

	void Init();
	void Uninit();
	void Update();
	void Draw(){}
};