#pragma once

#include "gameobject.h"

class CBUNKER : public CGameObject
{
private:
	static CModel* m_Model;		//3Dモデルクラス
	AABB m_Colider;
public:
	CBUNKER(){}
	~CBUNKER(){}

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