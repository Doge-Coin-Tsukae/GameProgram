#pragma once

#include "gameobject.h"

class CGAUGE :public CGameObject
{
private:
	CPolygon *Lower;
	CMovePolygon *Gauge;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};