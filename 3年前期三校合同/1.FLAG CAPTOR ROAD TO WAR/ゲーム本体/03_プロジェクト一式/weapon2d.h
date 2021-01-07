#pragma once

#include "gameobject.h"

class CWEAPON2D : public  CGameObject
{
private:
	CNUMBER*			m_MaxAnmo;		//Å‘å’e”
	CNUMBER*			m_Anmo;			//Œ»İ‚Ì’e”
	CPolygon*			m_Under;		//‰º’n
	CGAUGE*				m_Gauge;		//’e‚ÌƒQ[ƒW

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};