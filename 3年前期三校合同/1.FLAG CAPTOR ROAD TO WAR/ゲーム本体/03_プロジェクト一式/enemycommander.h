#pragma once

#include "gameobject.h"

class CENEMY_COMMANDER : public CGameObject	//継承(インヘリタンス)
{
private:
	int resporn_timer;		//再出撃時間

public:
	CENEMY_COMMANDER() {}
	~CENEMY_COMMANDER() {}

	void Init();
	void Uninit();
	void Update();
	void Draw(){}
};