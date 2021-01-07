#pragma once

#include "gameobject.h"

class CDEADTREE : public CGameObject
{
private:
	static CModel* m_Model;		//3Dƒ‚ƒfƒ‹ƒNƒ‰ƒX
	AABB m_Colider;
public:
	CDEADTREE() {}
	~CDEADTREE() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Save(FILE* fp);
	void Load(FILE*fp, int line);

	AABB GetColider() { return m_Colider; }
};