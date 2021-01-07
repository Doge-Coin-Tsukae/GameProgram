#pragma once

#include "gameobject.h"

class CCAPTUREUI :public CGameObject
{
private:
	CPolygon *Line;		//�\�������錾�t��png

	int DeleteTime;			//�I�u�W�F�N�g���폜�����܂ł̎���
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

class CCAPTUREGAUGE :public CGameObject
{
private:
	CGAUGE *m_Gauge;		//�\�������錾�t��png]
	CBASE *m_parent;	//�e

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Setparent(CBASE* object) { m_parent = object; }
};