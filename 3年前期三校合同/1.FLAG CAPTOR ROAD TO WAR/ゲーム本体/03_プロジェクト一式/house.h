#pragma once

#include "gameobject.h"

class CHOUSE : public CGameObject
{
private:
	static CModel* m_Model;		//3Dƒ‚ƒfƒ‹ƒNƒ‰ƒX
	AABB m_Colider;
public:
	CHOUSE() {}
	~CHOUSE() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	AABB GetColider() { return m_Colider; }
};