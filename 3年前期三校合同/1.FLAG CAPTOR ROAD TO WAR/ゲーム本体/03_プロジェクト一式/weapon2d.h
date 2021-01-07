#pragma once

#include "gameobject.h"

class CWEAPON2D : public  CGameObject
{
private:
	CNUMBER*			m_MaxAnmo;		//�ő�e��
	CNUMBER*			m_Anmo;			//���݂̒e��
	CPolygon*			m_Under;		//���n
	CGAUGE*				m_Gauge;		//�e�̃Q�[�W

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};