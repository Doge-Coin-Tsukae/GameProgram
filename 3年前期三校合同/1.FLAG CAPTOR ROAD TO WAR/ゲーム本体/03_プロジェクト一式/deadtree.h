#pragma once

#include "gameobject.h"

class CDEADTREE : public CGameObject
{
private:
	static CModel* m_Model;		//3Dモデルクラス
	AABB m_Colider;

	D3DXVECTOR3 m_lightpos = D3DXVECTOR3(0,0,0);
	float length = 1000.0f;
	float angle = 1.0f;
	bool  isShadow;			//影情報を付けるか
public:
	CDEADTREE() {}
	~CDEADTREE() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Update_Controll();
	void Draw();

	void Load(FILE*fp, int line);

	AABB GetColider() { return m_Colider; }
};