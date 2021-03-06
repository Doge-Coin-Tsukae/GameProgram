#pragma once

#include "gameobject.h"

class CWEAPON2D : public  CGameObject
{
private:
	CNUMBER*			m_MaxAnmo;		//最大弾数
	CNUMBER*			m_Anmo;			//現在の弾数
	CPolygon*			m_Under;		//下地
	CGAUGE*				m_Gauge;		//弾のゲージ

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};