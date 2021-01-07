#pragma once

#include "gameobject.h"

class Title_Effect_Manager : public CGameObject	//継承(インヘリタンス)
{
private:
	int m_SpownTime = 0;
	int m_randtime =0;
	D3DXVECTOR3 ExplosionPos[5];		//爆発位置(複数野候補から選ぶ)

	void  SetExplosion();
public:
	Title_Effect_Manager() {}
	~Title_Effect_Manager() {}

	void Init();
	void Uninit();
	void Update();
};