#pragma once

#include "gameobject.h"

class CGAUGE :public CGameObject
{
private:
	D3DXVECTOR3 m_Pos;
	CMovePolygon *Lower;
	CMovePolygon *Gauge;
	int m_Gauge;		//ƒQ[ƒW‚Ì’†g
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetGauge(int SetGauge) { m_Gauge = SetGauge; }
	void SetPosition(D3DXVECTOR3 Pos)
	{ 
		m_Position = Pos; 
		Gauge->SetPosition(m_Position + D3DXVECTOR3(2.0f, 0.0f, 0.0f));
		Lower->SetPosition(m_Position);
	}
};