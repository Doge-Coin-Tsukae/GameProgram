#pragma once

#include "gameobject.h"

class CPLAYERUI : public  CGameObject
{
private:
	CGAUGE*				m_HpGauge;		//ëÃóÕÇÃÉQÅ[ÉW
	CPolygon*			m_Sight;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};