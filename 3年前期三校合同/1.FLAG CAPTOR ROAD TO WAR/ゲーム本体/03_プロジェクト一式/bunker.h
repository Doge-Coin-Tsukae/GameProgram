#pragma once

#include "gameobject.h"

class CBUNKER : public CGameObject
{
private:
	static CModel* m_Model;		//3Dƒ‚ƒfƒ‹ƒNƒ‰ƒX
	static CModel* m_ShadowModel;
	AABB m_Colider;
	OBB*  m_Obb;

public:
	CBUNKER(){}
	~CBUNKER(){}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Load(FILE*fp, int line);

	AABB GetColider() { return m_Colider; }
};