#pragma once

#include "gameobject.h"

class Title_Effect_Manager : public CGameObject	//�p��(�C���w���^���X)
{
private:
	int m_SpownTime = 0;
	int m_randtime =0;
	D3DXVECTOR3 ExplosionPos[5];		//�����ʒu(�������₩��I��)

	void  SetExplosion();
public:
	Title_Effect_Manager() {}
	~Title_Effect_Manager() {}

	void Init();
	void Uninit();
	void Update();
};