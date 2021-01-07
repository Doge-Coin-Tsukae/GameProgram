#pragma once

#include "gameobject.h"

class CTITLE2D :public CGameObject
{
private:
	CPolygon *Gamename;
	CPolygon *Choose;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};