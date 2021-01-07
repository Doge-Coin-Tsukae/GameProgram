#pragma once

#include "gameobject.h"

class CCAPTUREUI :public CGameObject
{
private:
	CPolygon *Line;		//表示させる言葉のpng

	int DeleteTime;			//オブジェクトが削除されるまでの時間
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

class CCAPTUREGAUGE :public CGameObject
{
private:
	CGAUGE *m_Gauge;		//表示させる言葉のpng]
	CBASE *m_parent;	//親

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Setparent(CBASE* object) { m_parent = object; }
};